#include "Entity.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Entity::Entity(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c)
: world(w), sprite(spr), position(pos), body(c)
{

}

Entity::Entity(const Entity& e) :
world(nullptr), sprite(nullptr), position(e.position), body(nullptr)
{
    
}

Entity& Entity::operator= (const Entity& e)
{
    sprite = nullptr;
    world = nullptr;
    body = nullptr;

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
        sprite->setPosition(position);
        sprite->drawSprite();
    }
}

void Entity::update()
{
    if(body!=nullptr)
    {
        body->setPosition(position);
    }
}

void Entity::updateFromCollider()
{
    if(body!=nullptr)
    {
        position = body->getPosition();
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
    if(world!=nullptr && w!=world)
    {
        world->eraseEntity(this);
    }
    world = w;
}

void Entity::setBody(Collider* c)
{
    if(body!=nullptr)
    {
        physics::removeCollider(body);
        delete body;
    }
    body = c;
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

Collider* Entity::getBody() const
{
    return body;
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

    if(body!=nullptr)
    {
        physics::removeCollider(body);
        delete body;
        body = nullptr;
    }
}