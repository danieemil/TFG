#include "Entity.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Entity::Entity(const Entity& e)
{
    world = nullptr;
    sprite = nullptr;
}

Entity::Entity(const Vector2d<float>& pos, Sprite* spr)
: position(pos)
{
    world = nullptr;
    sprite = spr;
}

Entity::Entity(World* w, const Vector2d<float>& pos, Sprite* spr)
: position(pos)
{
    world = w;
    sprite = spr;
}

Entity& Entity::operator= (const Entity& e)
{
    sprite = nullptr;
    world = nullptr;

    position = e.position;
    
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Entity::render()
{
    if(sprite!=nullptr)
    {
        sprite->drawSprite();
    }
}

void Entity::update()
{
    
    position.x += 1;

    if(sprite!=nullptr)
    {
        sprite->setPosition(position);
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Entity::setSprite(Sprite* spr)
{

    if(sprite!=nullptr)
    {
        delete sprite;
    }

    sprite = spr;

}

void Entity::setPosition(const Vector2d<float>& pos)
{
    position = pos;
}

void Entity::setWorld(World* w)
{
    if(world!=nullptr)
    {
        world->eraseEntity(this);
    }
    world = w;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Entity::getSprite() const
{
    return sprite;
}

const Vector2d<float>& Entity::getPosition() const
{
    return position;
}

World* Entity::getWorld() const
{
    return world;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Entity::~Entity()
{
    if(sprite!=nullptr)
    {
        delete sprite;
    }

    if(world!=nullptr)
    {
        world->eraseEntity(this);
    }
}