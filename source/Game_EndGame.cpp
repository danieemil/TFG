#include "Game_EndGame.h"
#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_EndGame::Game_EndGame()
: Game_State()
{
    type = state_type::menu;

}

Game_EndGame::Game_EndGame(const Game_EndGame& gmm)
: Game_State(gmm)
{

}

Game_EndGame& Game_EndGame::operator= (const Game_EndGame& gmm)
{
    Game_State::operator=(gmm);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================
void Game_EndGame::init()
{

    top_background = Game::Instance()->createBackgroundSprite(BACKGROUND_END_GAME_TOP);

    bottom_background = Game::Instance()->createBackgroundSprite(BACKGROUND_END_GAME_BOTTOM);

    timer.reset();

}

void Game_EndGame::processInput()
{
    
    if((timer.getElapsed() > END_SCREEN_DURATION) && unvisual::input::isAnyKeyPressed())
    {
        Game::Instance()->stateTransition<Game_MainMenu>();
    }
}

void Game_EndGame::update()
{

}

void Game_EndGame::renderTop()
{
    Game_State::renderTop();
}

void Game_EndGame::renderBottom()
{
    Game_State::renderBottom();
}

void Game_EndGame::manageAnimations()
{
    
}

void Game_EndGame::deInit()
{
    delete this;
}

void Game_EndGame::processEvents()
{
    Game_State::processEvents();
}

void Game_EndGame::addEvent(Event e)
{
    Game_State::addEvent(e);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Game_EndGame::setTopBackground(Sprite* spr)
{
    Game_State::setTopBackground(spr);
}

void Game_EndGame::setBottomBackground(Sprite* spr)
{
    Game_State::setBottomBackground(spr);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================
state_type Game_EndGame::getStateType() const
{
    return Game_State::getStateType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Game_EndGame::~Game_EndGame()
{
    //unvisual::debugger->print("He destruido el estado Menú Principal");
    //unvisual::debugger->nextLine();
}