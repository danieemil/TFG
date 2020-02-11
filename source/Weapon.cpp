#include "Weapon.h"
#include "Combat_Character.h"
#include "World.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Weapon::Weapon(const Weapon& c) : Entity(c)
{

}

Weapon::Weapon(const Vector2d<float>& pos, Sprite* spr) : Entity(pos, spr)
{

}

Weapon::Weapon(World* w, const Vector2d<float>& pos, Sprite* spr, Combat_Character* cc) : Entity(w, pos, spr)
{
    if(cc!=nullptr)
    {
        character = cc;
    }
}

Weapon& Weapon::operator= (const Weapon& c)
{
    this->Entity::operator=(c);

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Weapon::render()
{
    Entity::render();
}

void Weapon::update()
{
    Entity::update();   
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Weapon::setSprite(Sprite* spr)
{
    Entity::setSprite(spr);
}

void Weapon::setPosition(const Vector2d<float>& pos)
{
    Entity::setPosition(pos);
}

void Weapon::setWorld(World* w)
{
    Entity::setWorld(w);
}

void Weapon::setCharacter(Combat_Character* cc)
{
    if(cc!=nullptr)
    {
        character = cc;
    }
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Weapon::getSprite() const
{
    return Entity::getSprite();
}

const Vector2d<float>& Weapon::getPosition() const
{
    return Entity::getPosition();
}

World* Weapon::getWorld() const
{
    return Entity::getWorld();
}

Combat_Character* Weapon::getCharacter() const
{
    return character;
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Weapon::~Weapon()
{
    
}