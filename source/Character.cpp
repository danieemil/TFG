#include "Character.h"
#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Character::Character(const Vector2d<float>& pos, Sprite* spr, World* w, CollisionFlag type_flag, CollisionFlag interests_flag,
const Vector2d<float>& ori, const Vector2d<float>& max_vel, const Vector2d<float>& max_accel,
const Vector2d<float>& frict)
: Entity(pos, spr, w, new Collider(pos, physics::getSpriteShape(spr), type_flag, interests_flag, CollisionType::col_dynamic), ori)
{
    if(body!= nullptr)
    {
        body->setMaxVelocity(max_vel);
        body->setMaxAcceleration(max_accel);
        body->setFriction(frict);
    }
}

Character::Character(const Character& c)
: Entity(c)
{
    if(body!=nullptr && c.body!=nullptr)
    {
        body->setMaxVelocity(c.body->getMaxVelocity());
        body->setMaxAcceleration(c.body->getMaxAcceleration());
        body->setFriction(c.body->getFriction());
    }
}

Character& Character::operator= (const Character& c)
{
    this->Entity::operator=(c);

    if(body!=nullptr && c.body!=nullptr)
    {
        body->setMaxVelocity(c.body->getMaxVelocity());
        body->setMaxAcceleration(c.body->getMaxAcceleration());
        body->setFriction(c.body->getFriction());
    }

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
    if(body!=nullptr)
    {
        body->setAcceleration(acceleration);
    }
    Entity::update();
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

void Character::setOrientation(const Vector2d<float>& ori)
{
    Entity::setOrientation(ori);
}

void Character::setAcceleration(const Vector2d<float>& accel)
{
    acceleration = accel;
    if(body!=nullptr)
    {
        body->setAcceleration(acceleration);
    }
}

void Character::setFriction(const Vector2d<float>& frict)
{
    if(body!=nullptr)
    {
        body->setFriction(frict);
    }
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

const EntityType& Character::getEntityType() const
{
    return Entity::getEntityType();
}

float Character::getAngle() const
{
    return Entity::getAngle();
}


Vector2d<float> Character::getCenter() const
{
    return Entity::getCenter();
}

const Vector2d<float>& Character::getOrientation() const
{
    return Entity::getOrientation();
}

const Vector2d<float>& Character::getAcceleration() const
{
    return acceleration;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Character::~Character()
{
    
}