#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

World::World()
{
    player = nullptr;
}

World::World(const World& d)
{
    player = nullptr;
}

World::World(const std::vector<Entity*>& v, Player* p)
{
    entities = v;
    player = p;
}

World& World::operator= (const World& d)
{

    return *this;

}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void World::addEntity(Entity* e)
{
    if(e!=nullptr)
    {
        for(auto entity = entities.begin();entity!=entities.end();entity++)
        {
            if(e==(*entity))
            {
                return;
            }
        }

        entities.emplace_back(e);
        e->setWorld(this);
    }
}

void World::addPlayer(Player* p)
{
    player = p;
}

void World::deleteEntity(Entity* e)
{
    if(e!=nullptr)
    {
        for(auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if((*entity)==e)
            {
                entities.erase(entity);
                delete e;
                break;
            }
        }
    }
}

void World::eraseEntity(Entity* e)
{
    if(e!=nullptr)
    {
        for(auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if((*entity)==e)
            {
                entities.erase(entity);
                break;
            }
            if(entity==entities.end())
            {
                break;
            }
        }
    }
}

void World::processInput()
{
    if(player!=nullptr)
    {
        player->processInput();
    }
}

void World::render()
{
    renderEntities();
    renderPlayer();
}

void World::renderEntities()
{
    for(auto ent = entities.begin();ent!=entities.end();ent++)
    {
        (*ent)->render();
    }
}

void World::renderPlayer()
{
    if(player!=nullptr)
    {
        player->render();
    }
}

void World::update()
{
    updatePlayer();
    updateEntities();
}

void World::updateEntities()
{
    auto ent = entities.begin();

    while(ent!=entities.end())
    {
        Entity* updating = (*ent);
        
        if(updating!=nullptr)
        {
            updating->update();
        }

        Entity* updated = (*ent);

        if((ent!=entities.end())&&(updating==updated))
        {
            ent++;
        }
    }
}

void World::updatePlayer()
{
    if(player!=nullptr)
    {
        player->update();
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void World::setEntities(const std::vector<Entity*>& v)
{
    entities = v;
}

void World::setPlayer(Player* p)
{
    if(player!=nullptr)
    {
        delete player;
    }
    player = p;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const std::vector<Entity*>& World::getEntities() const
{
    return entities;
}

Player* World::getPlayer() const
{
    return player;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

World::~World()
{
    auto entity = entities.begin();

    while (entity!=entities.end())
    {
        Entity* e = (*entity);

        if(e!=nullptr)
        {
            unvisual::debugger->print("Borrando Entidad: ");
            unvisual::debugger->print(e);
            unvisual::debugger->nextLine();
            delete e;
        }
    }

    if(player!=nullptr)
    {
        unvisual::debugger->print("Borrando Player: ");
        unvisual::debugger->print(player);
        unvisual::debugger->nextLine();
        delete player;
    }
}