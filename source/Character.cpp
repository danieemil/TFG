#include "Character.h"
#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Character::Character(const Vector2d<float>& pos, float angl, Sprite* spr, World* w, Collider* c,
    const Vector2d<float>& max_vel, const Vector2d<float>& accel, const Vector2d<float>& decel)
: Entity(pos, angl, spr, w, c), max_velocity(max_vel), max_acceleration(accel),
    acceleration(Vector2d<float>()), deceleration(decel)
{

}

Character::Character(const Character& c)
: Entity(c), max_velocity(c.max_velocity), max_acceleration(c.max_acceleration),
    acceleration(c.acceleration), deceleration(c.deceleration)
{

}

Character& Character::operator= (const Character& c)
{
    this->Entity::operator=(c);
    max_velocity = c.max_velocity;
    max_acceleration = c.max_acceleration;
    acceleration = c.acceleration;
    deceleration = c.deceleration;

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Character::render(const Vector2d<float>& view_pos)
{
    Entity::render(view_pos);
}

void Character::update()
{

    Entity::update();

    velocity += acceleration;

    if(abs(velocity.x)>max_velocity.x)
    {
        velocity.x = max_velocity.x*sign(velocity.x);
    }
    if(abs(velocity.y)>max_velocity.y)
    {
        velocity.y = max_velocity.y*sign(velocity.y);
    }

    if(abs(velocity.x)<acceleration.x/3.0f)
    {
        velocity.x = 0.0f;
    }
    if(abs(velocity.y)<acceleration.y/3.0f)
    {
        velocity.y = 0.0f;
    }
    
}

void Character::updateFromCollider()
{
    Entity::updateFromCollider();
}

void Character::interpolate(float rp)
{
    Entity::interpolate(rp);
}

void Character::collision(void * ent)
{
    Entity::collision(ent);
}

//=========================================
//=               SETTERS   	    	  =
//=========================================

void Character::setSprite(Sprite* spr)
{
    Entity::setSprite(spr);
}

void Character::setPosition(const Vector2d<float>& pos)
{
    Entity::setPosition(pos);
}

void Character::setWorld(World* w)
{
    Entity::setWorld(w);
}

void Character::setBody(Collider* c)
{
    Entity::setBody(c);
}

void Character::setVelocity(const Vector2d<float>& vel)
{
    Entity::setVelocity(vel);
}

void Character::setAngle(float angl)
{
    Entity::setAngle(angl);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Character::getSprite() const
{
    return Entity::getSprite();
}

const Vector2d<float>& Character::getPosition() const
{
    return Entity::getPosition();
}

World* Character::getWorld() const
{
    return Entity::getWorld();
}

Collider* Character::getBody() const
{
    return Entity::getBody();
}

const Vector2d<float>& Character::getVelocity() const
{
    return Entity::getVelocity();
}

const Vector2d<float>& Character::getPrePosition() const
{
    return Entity::getPrePosition();
}

const Vector2d<float>& Character::getRenderPosition() const
{
    return Entity::getRenderPosition();
}

const Class_Id& Character::getClassId() const
{
    return Entity::getClassId();
}

float Character::getAngle() const
{
    return Entity::getAngle();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Character::~Character()
{
    
}