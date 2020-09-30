#include "Game.h"


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
{

    state = new Game_Playing();

    init();
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Game::init()
{

    running = true;

    // Creamos una "Ventana" para dibujos en 3D y la ubicamos en la pantalla de abajo
	screen.setScreen(MAX_WIDTH_DOWN, MAX_HEIGHT_DOWN, N3DS_screenV::N3DS_BOTTOM);
	screen.setBackground(u8(255),u8(255),u8(255),u8(255));
	unvisual::setCurrentScreen(&screen);

    // Delta time
	dt = 0.0f;
	delta_time.reset();

    // Ya que solo se están usando gráficos en 2D
    unvisual::prepare2D();


    state->init();
	
}

void Game::render()
{

}

void Game::update()
{

}

void Game::updateCollisions()
{
    
}

void Game::interpolate()
{
    
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

        if(state!=nullptr)
        {
            state->loop();
        }
	}
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
            unvisual::debugger->setRow(20);
            unvisual::debugger->print(unvisual::getTimeStopped());
            unvisual::resumeClock();
        }
        else
        {
            unvisual::debugger->setRow(20);
            unvisual::debugger->print(unvisual::getTimeStopped());
            unvisual::stopClock();
        }
        
    }

    if(isHeld(N3DS_buttons::Key_A) || isPressed(N3DS_buttons::Key_A))
    {
        unvisual::debugger->clear();
    }
    
    if(isPressed(N3DS_buttons::Key_B))
    {
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("He pulsado la B " + std::to_string(unvisual::debugger->getRow()) + " veces");
        unvisual::debugger->nextLine();
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


//=========================================
//=               SETTERS   	    	  =
//=========================================




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


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

void Game::over()
{
    delete this;
}

Game::~Game()
{
    
}