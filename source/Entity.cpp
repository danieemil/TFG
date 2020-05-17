#include "Entity.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Entity::Entity(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c)
: world(w), sprite(spr), position(pos), pre_position(pos), body(c), velocity()
{
    if(c!=nullptr)
    {
        c->setCreator(this);
    }
}

Entity::Entity(const Entity& e) :
world(nullptr), sprite(nullptr), position(e.position), pre_position(e.pre_position), body(nullptr), velocity(e.velocity)
{
    
}

Entity& Entity::operator= (const Entity& e)
{
    sprite = nullptr;
    world = nullptr;
    body = nullptr;

    position = e.position;
    pre_position = e.pre_position;
    velocity = e.velocity;
    
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Entity::render(const Vector2d<float>& view_pos)
{
    if(sprite!=nullptr)
    {
        sprite->setPosition(position);
        sprite->drawSprite(view_pos);
    }
}

void Entity::update()
{
    pre_position = position;
    position = position + velocity;

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
        delete body;
    }
    body = c;

    if(body!=nullptr)
    {
        body->setCreator(this);
    }
}

void Entity::setVelocity(const Vector2d<float>& vel)
{
    velocity = vel;
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

const Vector2d<float>& Entity::getVelocity() const
{
    return velocity;
}

const Vector2d<float>& Entity::getPrePosition() const
{
    return pre_position;
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
        delete body;
        body = nullptr;
    }
}