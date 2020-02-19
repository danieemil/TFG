#include "Character.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Character::Character(const Character& c) : Entity(c)
{

}

Character::Character(const Vector2d<float>& pos, Sprite* spr, World* w) : Entity(pos, spr, w)
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

void Character::render()
{
    Entity::render();
}

void Character::update()
{
    Entity::update();   
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

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Character::~Character()
{
    
}