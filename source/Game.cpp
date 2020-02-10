#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================
Game::Game(SpriteManager* man, World* w)
{
    manager = man;
    world = w;
}

Game::Game(const Game& d)
{
    manager = nullptr;
    world = nullptr;
}

Game& Game::operator= (const Game& d)
{
    manager = nullptr;
    world = nullptr;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================
void Game::render()
{
    world->render();
}

void Game::update()
{
    world->update();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================
void Game::setWorld(World* w)
{
    if(world!=nullptr)
    {
        delete world;
    }
    world = w;
}

void Game::setSpriteManager(SpriteManager* man)
{
    if(manager!=nullptr)
    {
        delete manager;
    }
    manager = man;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================
World* Game::getWorld() const
{
    return world;
}

SpriteManager* Game::getSpriteManager() const
{
    return manager;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Game::~Game()
{
    if(world!=nullptr)
    {
        delete world;
    }

    if(manager!=nullptr)
    {
        delete manager;
    }
}