#include "Game_State.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_State::Game_State()
{
    
}

Game_State::Game_State(const Game_State& gs)
: type(gs.type)
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
    
}