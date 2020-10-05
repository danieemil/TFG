#include "Game_Paused.h"
#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_Paused::Game_Paused()
: Game_State()
{
    type = state_type::paused;

    unvisual::debugger->print("He creado el estado Pausa");
    unvisual::debugger->nextLine();
}

Game_Paused::Game_Paused(const Game_Paused& gp)
: Game_State(gp), playingState(gp.playingState)
{

}

Game_Paused& Game_Paused::operator= (const Game_Paused& gp)
{
    Game_State::operator=(gp);

    playingState = gp.playingState;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================
void Game_Paused::init()
{
    playingState = static_cast<Game_Playing*>(Game::Instance()->getActualState());
}

void Game_Paused::processInput()
{
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_L))
    {
        Game::Instance()->stateTransition<Game_MainMenu>();
        return;
    }
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_R))
    {
        playingState->resetLevel();
        Game::Instance()->setState(playingState);
    }
}

void Game_Paused::update()
{

}

void Game_Paused::render()
{
    if(playingState!=nullptr)
    {
        playingState->render();
    }
}

void Game_Paused::deInit()
{
    if(playingState!=nullptr)
    {
        delete playingState;
    }

    delete this;
}




//=========================================
//=               SETTERS   	    	  =
//=========================================




//=========================================
//=               GETTERS   	    	  =
//=========================================
state_type Game_Paused::getStateType() const
{
    return Game_State::getStateType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Game_Paused::~Game_Paused()
{
    unvisual::debugger->print("He destruido el estado Pausa");
    unvisual::debugger->nextLine();
}