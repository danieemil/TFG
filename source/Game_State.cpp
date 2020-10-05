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