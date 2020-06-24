#include "Entity.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Entity::Entity(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c)
: world(w), sprite(spr), position(pos), render_position(pos), pre_position(pos), body(c), velocity(), id(Class_Id::e_none)
{
    if(c!=nullptr)
    {
        c->setCreator(this);
    }
}

Entity::Entity(const Entity& e) :
world(nullptr), sprite(nullptr), position(e.position), render_position(e.render_position), pre_position(e.pre_position), body(nullptr), velocity(e.velocity), id(e.id)
{
    
}

Entity& Entity::operator= (const Entity& e)
{
    sprite = nullptr;
    world = nullptr;
    body = nullptr;

    position = e.position;
    render_position = e.render_position;
    pre_position = e.pre_position;
    velocity = e.velocity;
    id = e.id;
    
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Entity::render(float rp, const Vector2d<float>& view_pos)
{
    // Interpolación
    render_position = pre_position + (position - pre_position) * rp;

    if(sprite!=nullptr)
    {
        sprite->setPosition(render_position);
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

const Vector2d<float>& Entity::getRenderPosition() const
{
    return render_position;
}

const Class_Id& Entity::getClassId() const
{
    return id;
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