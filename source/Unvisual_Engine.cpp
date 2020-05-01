#include "Unvisual_Engine.h"


using namespace utilities;

namespace unvisual
{


    ////////////////////////////
    //  Gestión de librerías  //
    ////////////////////////////
    void init()
    {

        // Inicializador por defecto de los gráficos básicos
        gfxInitDefault();

        // Permitimos acceder a la ROMFS (Read Only Memory File System)
        // Eso significa que podemos acceder a la carpeta romfs poniendo "romfs:"
        romfsInit();

        // Inicializador de Citro3D(Gráficos especializados del 3D y renderizado)
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

        // Inicializador de Citro2D(Gráficos especializados del 2D)
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

        // Inicializador de los inputs
        hidInit();
    }

    void deInit()
    {
        // Apagamos el depurador
        if(debugger!=nullptr)
        {
            delete debugger;
            debugger = nullptr;
        }

        // Quitamos los puntos en el tiempo
        clearAllTimepoints();

        // Liberamos la memoria de los inputs
        hidExit();

        // Liberamos la memoria de la librería Citro3D
        C3D_Fini();
        
        // Liberamos la memoria de la librería Citro2D
        C2D_Fini();

        // Salimos de la Romfs
        romfsExit();

        // Liberamos la memoria que se usa para los gráficos básicos
        gfxExit();
    }



    ///////////////////////////
    //       Depurando       //
    ///////////////////////////
    void initDebugger()
    {
        debugger = new Debugger(N3DS_screenV::N3DS_TOP);
    }

    Debugger* debugger = nullptr;



    ///////////////////////////
    //      Renderizado      //
    ///////////////////////////

    namespace
    {
        Screen* current_screen = nullptr;
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
		    C3D_RenderTargetClear(current_screen->getRenderer(),C3D_CLEAR_ALL, current_screen->getBackground(), 0);
        }
    }

    void prepare2D()
    {
        if(current_screen!=nullptr)
        {
            C2D_SceneBegin(current_screen->getRenderer());
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

    void setCurrentScreen(Screen* sc)
    {
        current_screen = sc;
    }

    Screen* getCurrentScreen()
    {
        return current_screen;
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
                unvisual::debugger->print("Eliminando timepoint: ");
                unvisual::debugger->print(timepoint);
                unvisual::debugger->nextLine();
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

        void IM_scan()
        {
            hidScanInput();
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
            hidTouchRead(&t_position);
            return Vector2d<u16>(t_position.px,t_position.py);
        }
    }
}