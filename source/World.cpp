#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

World::World()
{

}

World::World(const World& d)
{

}

World::World(const std::vector<Entity*>& v)
{
    entities = v;
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
        entities.emplace_back(e);
        e->setWorld(this);
    }
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
        }
    }
}

void World::render()
{
    for(auto ent = entities.begin();ent!=entities.end();ent++)
    {
        (*ent)->render();
    }
}

void World::update()
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



//=========================================
//=               SETTERS   	    	  =
//=========================================

void World::setEntities(const std::vector<Entity*>& v)
{
    entities = v;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const std::vector<Entity*>& World::getEntities() const
{
    return entities;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

World::~World()
{
    auto entity = entities.begin();

    while (entity!=entities.end())
    {
        if((*entity)!=nullptr)
        {
            delete (*entity);
        }

        entities.erase(entity);
    }
}