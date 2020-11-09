#include "Game.h"
#include "LevelFactory.h"

using namespace std;
using namespace unvisual::input;


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
state(new Game_MainMenu()), post_state(state_type::none), saved(false)
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

void Game::render()
{
    if(state!=nullptr)
    {
        state->render();
    }
}

void Game::update()
{
    if(state!=nullptr)
    {
        state->update();
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

        unvisual::drawBegin();
        unvisual::drawOnCurrentScreen();

        // Renderizamos el juego entero en la patnalla seleccionada
        render();

        unvisual::drawEnd();
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