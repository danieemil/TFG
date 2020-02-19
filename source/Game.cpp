#include "Game.h"


using namespace input;


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================
Game::Game(const char* spr_path)
{
    manager = new SpriteManager(spr_path);
    world = new World();
    running = true;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================
void Game::init(const char* spr_path)
{
    manager->setSprites(spr_path);
    running = true;
}

void Game::deInit()
{

}

void Game::render()
{
    world->render();
}

void Game::update()
{
    world->update();
}

void Game::loop()
{

}

void Game::processInput()
{
    // Si se pulsa 'start' se sale del programa
    if (isPressed(N3DS_buttons::Key_Start))
    {
        running = false;
        return;
    }

    if(isPressed(N3DS_buttons::Key_X))
    {
        
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

    world->processInput();
    
}

bool Game::isRunning()
{
    return running;
}


//=========================================
//=               SETTERS   	    	  =
//=========================================
void Game::setWorldEntity(Entity* e)
{
    world->addEntity(e);
}

void Game::setWorldPlayer(Player* p)
{
    world->addPlayer(p);
}

void Game::setSpriteManager(const char* spr_path)
{
    manager->setSprites(spr_path);
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
    deInit();

    if(world!=nullptr)
    {
        delete world;
    }

    if(manager!=nullptr)
    {
        delete manager;
    }
}