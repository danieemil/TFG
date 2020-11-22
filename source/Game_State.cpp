#include "Game_State.h"
#include "Unvisual_Engine.h"

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_State::Game_State()
: type(state_type::none), events(), top_background(nullptr), bottom_background(nullptr)
{
    
}

Game_State::Game_State(const Game_State& gs)
: type(gs.type), events(), top_background(nullptr), bottom_background(nullptr)
{

}

Game_State& Game_State::operator= (const Game_State& gs)
{
    type = gs.type;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Game_State::renderTop()
{
    if(top_background!=nullptr)
    {
        top_background->drawSprite();
    }
}

void Game_State::renderBottom()
{
    if(bottom_background!=nullptr)
    {
        bottom_background->drawSprite();
    }
}

void Game_State::processEvents()
{
    if(!events.empty())
    {
        Event e = events.top();
        if(e!=nullptr)
        {
            e();
        }
        events.pop();
    }
}

void Game_State::addEvent(Event e)
{
    events.push(e);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Game_State::setTopBackground(Sprite* spr)
{
    if(top_background!=nullptr)
    {
        delete top_background;
    }
    top_background = spr;
}

void Game_State::setBottomBackground(Sprite* spr)
{
    if(bottom_background!=nullptr)
    {
        delete bottom_background;
    }
    bottom_background = spr;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================
state_type Game_State::getStateType() const
{
    return type;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Game_State::~Game_State()
{
    if(top_background!=nullptr)
    {
        delete top_background;
        top_background = nullptr;
    }

    if(bottom_background!=nullptr)
    {
        delete bottom_background;
        bottom_background = nullptr;
    }
}