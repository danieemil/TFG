#include "Unvisual_Engine.h"


using namespace utilities;

namespace unvisual
{
    namespace
    {
        aptHookCookie* hc = nullptr;
    }

    ////////////////////////////
    //  Gestión de librerías  //
    ////////////////////////////
    void init()
    {

        // Inicializador por defecto de los gráficos básicos
        gfxInitDefault();

        gfxSetDoubleBuffering(gfxScreen_t::GFX_BOTTOM, true);

        // Permitimos acceder a la ROMFS (Read Only Memory File System)
        // Eso significa que podemos acceder a la carpeta romfs poniendo "romfs:"
        romfsInit();

        // Inicializador de Citro3D(Gráficos especializados del 3D y renderizado)
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

        // Inicializador de Citro2D(Gráficos especializados del 2D)
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

        input::IM_init();

        // Inicializar el monitor de estados del APT
        initAPT();

        initScreens();
    }

    void initAPT()
    {
        aptSetHomeAllowed(true);
        aptSetSleepAllowed(true);

        if(hc==nullptr)
        {
            hc = new aptHookCookie();
            hc->next = nullptr;
            hc->callback = aptState;
            hc->param = nullptr;
        }
        
        aptHook(hc,hc->callback, nullptr);
    }

    void deInit()
    {
        // Apagamos el depurador
        //deInitDebugger();

        // Quitamos los puntos en el tiempo
        //clearAllTimepoints();

        deInitScreens();

        input::IM_deInit();

        // Liberamos la memoria de la librería Citro3D
        C3D_Fini();
        
        // Liberamos la memoria de la librería Citro2D
        C2D_Fini();

        // Salimos de la Romfs
        romfsExit();

        // Liberamos la memoria que se usa para los gráficos básicos
        gfxExit();

        // Liberar el monitor de estados del APT
        deInitAPT();
        
    }

    void deInitAPT()
    {
        if(hc!=nullptr)
        {
            aptUnhook(hc);
            delete hc;
            hc = nullptr;
        }
    }


    void aptState(APT_HookType hook, void* param)
    {
        if(hook == APTHOOK_ONSUSPEND || hook == APTHOOK_ONSLEEP)
        {
            stopClock();
        }
        else if (hook == APTHOOK_ONRESTORE || hook == APTHOOK_ONWAKEUP)
        {
            resumeClock();
        }
    }


    ///////////////////////////
    //       Depurando       //
    ///////////////////////////
    void initDebugger(N3DS_screenV sc_place)
    {
        if(debugger==nullptr)
        {
            debugger = new Debugger(sc_place);
        }
    }

    void deInitDebugger()
    {
        if(debugger!=nullptr)
        {
            delete debugger;
            debugger = nullptr;
        }
    }

    Debugger* debugger = nullptr;

    ///////////////////////////
    //      Renderizado      //
    ///////////////////////////

    namespace
    {
        Screen* current_screen = nullptr;

        Screen* top_screen = nullptr;
        Screen* bottom_screen = nullptr;
    }

    void initScreens()
    {
        // Creamos una "Ventana" para dibujar en 2D/3D y la ubicamos en la pantalla superior
	    top_screen = new Screen(MAX_WIDTH_UP, MAX_HEIGHT_UP, N3DS_screenV::N3DS_TOP);

	    // Creamos una "Ventana" para dibujar en 2D/3D y la ubicamos en la pantalla inferior
	    bottom_screen = new Screen(MAX_WIDTH_DOWN, MAX_HEIGHT_DOWN, N3DS_screenV::N3DS_BOTTOM);

        // Por defecto se empieza renderizando la escena en la pantalla superior
        current_screen = top_screen;
    }

    void deInitScreens()
    {
        if(top_screen!=nullptr)
        {
            delete top_screen;
            top_screen = nullptr;
        }

        if(bottom_screen!=nullptr)
        {
            delete bottom_screen;
            bottom_screen = nullptr;
        }

        current_screen = nullptr;
    }

    void drawBegin()
    {
        // Cuando se llama a esta función establecemos que en el frame actual se pintará lo siguiente 
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    }

    void drawOnCurrentScreen()
    {
        if(current_screen!=nullptr)
        {
            C3D_FrameDrawOn(current_screen->getRenderer());
		    C3D_RenderTargetClear(current_screen->getRenderer(),C3D_CLEAR_ALL, current_screen->getBackgroundColor(), 0);
        }
    }

    void prepare2D()
    {
        if(current_screen!=nullptr)
        {
            C2D_SceneTarget(current_screen->getRenderer());
            C2D_Prepare();
        }
    }

    void drawEnd()
    {
        // Nos aseguramos que todo se ha dibujado 
		C2D_Flush();

		// A partir de esta línea acaba lo que se dibujaría en el frame actual y pasa al siguiente
		C3D_FrameEnd(0);
    }

    void drawRectangle(const Vector2d<float>& pos, float depth, const Vector2d<float>& dimensions, u8 r, u8 g, u8 b, u8 a)
    {
        C2D_DrawRectSolid(pos.x, pos.y, depth, dimensions.x, dimensions.y, C2D_Color32(r,g,b,a));
    }

    void drawCircle(const Vector2d<float>& pos, float depth, float radius, u8 r, u8 g, u8 b, u8 a)
    {
        C2D_DrawCircleSolid(pos.x, pos.y, depth, radius, C2D_Color32(r,g,b,a));
    }

    void drawData(void* data, size_t data_size)
    {
        u8* fb = gfxGetFramebuffer(current_screen->getRenderer()->screen, current_screen->getRenderer()->side, NULL, NULL);
        memcpy(fb,data, data_size);
    }

    u32 getColor2D(u8 r, u8 g, u8 b, u8 a)
    {
        return C2D_Color32(r, g, b, a);
    }

    void setCurrentScreen(N3DS_screenV sc_place)
    {
        if(sc_place == N3DS_screenV::N3DS_TOP)
        {
            current_screen = top_screen;
        }
        else if(sc_place == N3DS_screenV::N3DS_BOTTOM)
        {
            current_screen = bottom_screen;
        }
    }

    void setCurrentScreenTarget(const utilities::Vector2d<float>* t_pos)
    {
        if(current_screen!=nullptr)
        {
            current_screen->setTargetPosition(t_pos);
        }
    }

    Screen* getCurrentScreen()
    {
        return current_screen;
    }

    utilities::Vector2d<float> getCurrentScreenSize()
    {
        return utilities::Vector2d<float>(current_screen->getWidth(), current_screen->getHeight());
    }



    //////////////////////////
    //     Temporizador     //
    //////////////////////////
    namespace
    {
        std::vector<Timepoint*> timepoints;
        u64 pauseAt = 0;
        u64 resumeAt = 1;

        void fixTimepoints()
        {
            u64 dur = resumeAt - pauseAt;

            auto timepoint_it = timepoints.begin();

            while(timepoint_it!=timepoints.end())
            {
                Timepoint* t = (*timepoint_it);
                if(t!=nullptr)
                {
                    t->operator+(dur);
                }
                timepoint_it++;
            }
        }
    }

    void addTimepoint(Timepoint* t)
    {
        timepoints.emplace_back(t);
    }

    void eraseTimepoint(Timepoint* t)
    {
        auto timepoint_it = timepoints.begin();

        while (timepoint_it!=timepoints.end())
        {
            Timepoint* timepoint = (*timepoint_it);
            if(timepoint==t)
            {
                timepoints.erase(timepoint_it);
                break;
            }
            timepoint_it++;
        }
    }

    void clearAllTimepoints()
    {
        auto timepoint_it = timepoints.begin();

        while (timepoint_it!=timepoints.end())
        {
            Timepoint* timepoint = (*timepoint_it);
            if(timepoint!=nullptr)
            {   
                delete timepoint;
            }
            if((*timepoint_it)==timepoint && timepoint_it!=timepoints.end())
            {
                timepoint_it++;
            }
        }
    }

    void stopClock()
    {
        if(resumeAt>pauseAt)
        {
            pauseAt = svcGetSystemTick();
        }
    }

    void resumeClock()
    {
        if(resumeAt<pauseAt)
        {
            resumeAt = svcGetSystemTick();

            fixTimepoints();
        }
    }

    float getTimeStopped()
    {
        if(resumeAt>pauseAt)
        {
            return float((resumeAt - pauseAt)/FREQUENCY);
        }

        return float((svcGetSystemTick() - pauseAt)/FREQUENCY);
    }

    bool clockStopped()
    {
        return resumeAt<pauseAt;
    }

    u64 getPausedPoint()
    {
        if(clockStopped())
        {
            return pauseAt;
        }

        return svcGetSystemTick();
    }
    

    ////////////////////////////
    //   Detector de teclas   //
    ////////////////////////////
    namespace input
    {
        namespace
        {
            touchPosition t_position;
            touchPosition t_prev_position;

            std::map<N3DS_buttons,u32> key_mapping = 
            {
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_A,KEY_A),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_B,KEY_B),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_Select,KEY_SELECT),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_Start,KEY_START),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_DRight,KEY_DRIGHT),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_DLeft,KEY_DLEFT),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_DUp,KEY_DUP),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_DDown,KEY_DDOWN),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_R,KEY_R),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_L,KEY_L),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_X,KEY_X),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_Y,KEY_Y),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_Touch,KEY_TOUCH),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_CPAD_Right,KEY_CPAD_RIGHT),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_CPAD_Left,KEY_CPAD_LEFT),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_CPAD_Up,KEY_CPAD_UP),
                std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_CPAD_Down,KEY_CPAD_DOWN),
            };
        }

        void IM_init()
        {
            // Inicializador de los inputs
            hidInit();
        }

        void IM_scan()
        {
            
            hidScanInput();

            hidTouchRead(&t_position);
            if (!isReleased(N3DS_buttons::Key_Touch))
            {
                t_prev_position = t_position;
            }
            
        }

        bool isPressed(N3DS_buttons key)
        {
            auto it = key_mapping.find(key);
            u32 key_mapped = it->second;

            return (hidKeysDown() & key_mapped);
        }

        bool isHeld(N3DS_buttons key)
        {

            auto it = key_mapping.find(key);
            u32 key_mapped = it->second;

            return (hidKeysHeld() & key_mapped);
        }

        bool isReleased(N3DS_buttons key)
        {
            auto it = key_mapping.find(key);
            u32 key_mapped = it->second;

            return (hidKeysUp() & key_mapped);
        }

        Vector2d<u16> getPositionTouched()
        {
            return Vector2d<u16>(t_position.px,t_position.py);
        }

        Vector2d<u16> getLastPositionTouched()
        {
            return Vector2d<u16>(t_prev_position.px,t_prev_position.py);
        }

        void IM_deInit()
        {
            // Liberamos la memoria de los inputs
            hidExit();
        }
    }

    void breakpoint()
    {
        unvisual::stopClock();
        bool pressed = false;
        while (!pressed)
        {
            unvisual::input::IM_scan();
            pressed = unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_Select);
        }
        unvisual::resumeClock();
    }
}