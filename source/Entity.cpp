#include "Entity.h"
#include "World.h"

#include "Game.h"

using std::placeholders::_1;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Entity::Entity(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c, const Vector2d<float>& ori)
: world(w), sprite(spr), position(pos), render_position(pos), pre_position(pos), body(c), velocity(), id(Class_Id::e_none), angle(0.0f), orientation(ori)
{
    if(body!=nullptr)
    {
        body->setCreator(this);
        body->setCallback(std::bind(&Entity::collision, this, _1));
        body->setPosition(position);
        body->setVelocity(velocity);
    }

    if(orientation.x!=0.0f)
    {
        setAngle((90.0f*orientation.x) + (45.0f*orientation.x*orientation.y));
    }
    else
    {
        setAngle(90.0f + 90.0f*orientation.y);
    }

}

Entity::Entity(const Entity& e) :
world(nullptr), sprite(nullptr), position(e.position), render_position(e.render_position), pre_position(e.pre_position), body(nullptr), velocity(e.velocity), id(e.id), angle(e.angle), orientation(e.orientation)
{
    if(orientation.x!=0.0f)
    {
        setAngle((90.0f*orientation.x) + (45.0f*orientation.x*orientation.y));
    }
    else
    {
        setAngle(90.0f + 90.0f*orientation.y);
    }
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
    angle = e.angle;
    orientation = e.orientation;

    if(orientation.x!=0.0f)
    {
        setAngle((90.0f*orientation.x) + (45.0f*orientation.x*orientation.y));
    }
    else
    {
        setAngle(90.0f + 90.0f*orientation.y);
    }
    
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Entity::render(const Vector2d<float>& view_pos)
{
    if(sprite!=nullptr)
    {
        sprite->setPosition(render_position);
        sprite->drawSprite(view_pos);
    }
}

void Entity::update()
{
    pre_position = position;
    if(body!=nullptr)
    {
        velocity = body->getVelocity();
        position = body->getPosition();
    }
    else
    {
        position = position + velocity;
    }
    
    // Obtener el ángulo a partir de la orientación
    if(orientation.x!=0.0f)
    {
        setAngle((90.0f*orientation.x) + (45.0f*orientation.x*orientation.y));
    }
    else
    {
        setAngle(90.0f + 90.0f*orientation.y);
    }
    
}

void Entity::updateFromCollider()
{
    if(body!=nullptr)
    {
        position = body->getPosition();
    }
}

void Entity::interpolate(float rp)
{
    
    if(body!=nullptr)
    {
        render_position = body->getPosition();
    }else
    {
        // Interpolación
        render_position = pre_position + (position - pre_position) * rp;
    }
    
}

void Entity::collision(void * ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getClassId()==Class_Id::e_none)
        {
            return;
        }
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
    sprite->setRotation(angle);

}

void Entity::setPosition(const Vector2d<float>& pos)
{
    position = pos;
    if(body!=nullptr)
    {
        body->setPosition(position);
    }
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
    if(body!=nullptr && c != body)
    {
        delete body;
    }
    body = c;

    if(body!=nullptr)
    {
        body->setCreator(this);
        body->setCallback(std::bind(&Entity::collision, this, _1));
        body->setPosition(position);
        body->setVelocity(velocity);
        body->setGlobalRotation(angle);
    }
}

void Entity::setVelocity(const Vector2d<float>& vel)
{
    velocity = vel;
    if(body!=nullptr)
    {
        body->setVelocity(velocity);
    }
}

void Entity::setAngle(float angl)
{
    if(angle == angl) return;

    angle = angl;
    if(sprite!=nullptr)
    {
        sprite->setRotation(angle);
    }
    if(body!=nullptr)
    {
        body->setGlobalRotation(angle);
    }
}

void Entity::setOrientation(const Vector2d<float>& ori)
{
    orientation = ori;
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

float Entity::getAngle() const
{
    return angle;
}

Vector2d<float> Entity::getCenter() const
{
    Vector2d<float> cent = position;
    if(sprite!=nullptr)
    {
        cent += sprite->getCenter();
    }
    return cent;
}

const Vector2d<float>& Entity::getOrientation() const
{
    return orientation;
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