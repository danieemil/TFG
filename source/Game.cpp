#include "Game.h"
#include "LevelFactory.h"

using namespace std;
using namespace unvisual::input;

// Gráficos de los sprites de fondo de pantalla
const char* screen_graphics = "romfs:/gfx/background.t3x";

// Singleton
Game* Game::p_instance = 0;
Game* Game::Instance()
{
    if(p_instance)
    {
        return p_instance;
    }else
    {
        p_instance = new Game();
        return p_instance;
    }
}



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game::Game()
: running(true), dt(0.0f), delta_time(), prev_state(state_type::none),
    state(new Game_MainMenu()), post_state(state_type::none), saved(false),
    background_manager(screen_graphics)
{

}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Game::init()
{

    running = true;
    
    unvisual::setCurrentScreen(N3DS_screenV::N3DS_TOP);

    // Delta time
	dt = 0.0f;
	delta_time.reset();

    // Ya que solo se están usando gráficos en 2D
    unvisual::prepare2D();
    
    saved = LevelFactory::checkSave();
    
    unvisual::setCurrentScreen(N3DS_screenV::N3DS_TOP);
    unvisual::getCurrentScreen()->setBackgroundColor(0,0,0,0);

    unvisual::setCurrentScreen(N3DS_screenV::N3DS_BOTTOM);
    unvisual::getCurrentScreen()->setBackgroundColor(255,255,255,255);

    state->init();
	
}

void Game::processInput()
{

    if(aptIsHomePressed() || true)
    {
        unvisual::resumeClock();
    }

    // Si se pulsa 'start' se sale del programa
    if (isPressed(N3DS_buttons::Key_Start))
    {
        running = false;
        return;
    }

    if(isPressed(N3DS_buttons::Key_X))
    {
        if(unvisual::clockStopped())
        {
            //unvisual::debugger->setRow(20);
            //unvisual::debugger->print(unvisual::getTimeStopped());
            unvisual::resumeClock();
        }
        else
        {
            //unvisual::debugger->setRow(20);
            //unvisual::debugger->print(unvisual::getTimeStopped());
            unvisual::stopClock();
        }
        
    }

    if(isHeld(N3DS_buttons::Key_A) || isPressed(N3DS_buttons::Key_A))
    {
        //unvisual::debugger->clear();
    }
    
    if(isPressed(N3DS_buttons::Key_B))
    {
        //unvisual::debugger->setColumn(1);
        //unvisual::debugger->print("He pulsado la B " + std::to_string(//unvisual::debugger->getRow()) + " veces");
        //unvisual::debugger->nextLine();
    }

    if(state!=nullptr)
    {
        state->processInput();
    }
}

void Game::processEvents()
{
    if(state!=nullptr)
    {
        state->processEvents();
    }
}

void Game::renderTop()
{
    unvisual::setCurrentScreen(N3DS_screenV::N3DS_TOP);
    unvisual::prepare2D();
    unvisual::drawOnCurrentScreen();

    if(state!=nullptr)
    {
        state->renderTop();
    }

    unvisual::waitRenderScreen();
}

void Game::renderBottom()
{
    if(unvisual::debugger==nullptr)
    {
        unvisual::setCurrentScreen(N3DS_screenV::N3DS_BOTTOM);
        unvisual::prepare2D();
        unvisual::drawOnCurrentScreen();

        if(state!=nullptr)
        {
            state->renderBottom();
        }
        
        unvisual::waitRenderScreen();
    }
}

void Game::update()
{
    if(state!=nullptr)
    {
        state->update();
    }
}

void Game::manageAnimations()
{
    if(state!=nullptr)
    {
        state->manageAnimations();
    }
}

void Game::loop()
{
    // Main loop
	while (aptMainLoop() && running)
	{
		
		dt = delta_time.getElapsed();
		delta_time.reset();
        
        // Escaneamos las teclas pulsadas(Inputs de la N3DS)
	    IM_scan();

        processInput();

        update();

        manageAnimations();

        unvisual::drawBegin();

        // Renderizamos la pantalla inferior con su respectivo contenido
        renderBottom();

        // Renderizamos la pantalla superior con su respectivo contenido
        renderTop();

        unvisual::drawEnd();


        processEvents();
	}
}

bool Game::isRunning()
{
    return running;
}

void Game::stopRunning()
{
    running = false;
}

void Game::erasePlayer()
{
    if(state->getStateType()==state_type::playing)
    {
        Game_Playing* gp = static_cast<Game_Playing*>(state);
        gp->erasePlayer();
    }
}

Sprite* Game::createBackgroundSprite(size_t index)
{
    return background_manager.createSprite(index);
}

void Game::nextLevelEvent()
{
    if(state->getStateType()==state_type::playing)
    {
        Game_Playing* gp = static_cast<Game_Playing*>(state);
        Event e = [gp](){gp->nextLevel();};
        gp->addEvent(e);
    }
}

void Game::resetLevelEvent()
{
    if(state->getStateType()==state_type::playing)
    {
        Game_Playing* gp = static_cast<Game_Playing*>(state);
        Event e = [gp](){gp->resetLevel();};
        gp->addEvent(e);
    }
}

void Game::deleteEntityEvent(Entity* ent)
{
    if(state->getStateType()==state_type::playing)
    {
        Game_Playing* gp = static_cast<Game_Playing*>(state);
        Event e = [gp, ent](){gp->getWorld()->deleteEntity(ent);};
        gp->addEvent(e);
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

// Cambiar de estado de juego sin transiciones(deInit() y init())
void Game::setState(Game_State* s)
{
    if(state!=nullptr)
    {
        prev_state = state->getStateType();
        delete state;
    }
    state = s;
    if(state!=nullptr)
    {
        post_state = state->getStateType();
    }
}

void Game::setSaved(bool s)
{
    saved = s;
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

float Game::getDeltaTime() const
{
    return dt;
}

Player* Game::getPlayer() const
{
    if(state!=nullptr && (state->getStateType()==state_type::playing))
    {
        return (static_cast<Game_Playing*>(state))->getPlayer();
    }

    return nullptr;
}

state_type Game::getPrevState() const
{
    return prev_state;
}

Game_State* Game::getActualState() const
{
    return state;
}

state_type Game::getPostState() const
{
    return post_state;
}

bool Game::getSaved() const
{
    return saved;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

void Game::over()
{
    delete this;
}

Game::~Game()
{
    if(state!=nullptr)
    {
        delete state;
        state = nullptr;
    }
}