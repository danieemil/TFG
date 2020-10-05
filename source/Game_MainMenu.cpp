#include "Game_MainMenu.h"
#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_MainMenu::Game_MainMenu()
: Game_State()
{
    type = state_type::menu;

    unvisual::debugger->print("He creado el estado Menú Principal");
    unvisual::debugger->nextLine();
}

Game_MainMenu::Game_MainMenu(const Game_MainMenu& gmm)
: Game_State(gmm)
{

}

Game_MainMenu& Game_MainMenu::operator= (const Game_MainMenu& gmm)
{
    Game_State::operator=(gmm);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================
void Game_MainMenu::init()
{

}

void Game_MainMenu::processInput()
{
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_L))
    {
        Game::Instance()->stateTransition<Game_Playing>();
    }
}

void Game_MainMenu::update()
{

}

void Game_MainMenu::render()
{

}

void Game_MainMenu::deInit()
{
    delete this;
}




//=========================================
//=               SETTERS   	    	  =
//=========================================




//=========================================
//=               GETTERS   	    	  =
//=========================================
state_type Game_MainMenu::getStateType() const
{
    return Game_State::getStateType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Game_MainMenu::~Game_MainMenu()
{
    unvisual::debugger->print("He destruido el estado Menú Principal");
    unvisual::debugger->nextLine();
}