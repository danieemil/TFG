#include "Character.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Character::Character(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c)
: Entity(pos, spr, w, c)
{

}

Character::Character(const Character& c)
: Entity(c)
{

}

Character& Character::operator= (const Character& c)
{
    this->Entity::operator=(c);

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
}

void Character::updateFromCollider()
{
    Entity::updateFromCollider();
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

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Character::~Character()
{
    
}