#include "Weapon.h"
#include "Combat_Character.h"
#include "World.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Weapon::Weapon(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c, Combat_Character* cc) : Entity(pos, spr, w, c)
{
    if(cc!=nullptr)
    {
        character = cc;
    }
}

Weapon::Weapon(const Weapon& w) : Entity(w)
{

}

Weapon& Weapon::operator= (const Weapon& w)
{
    this->Entity::operator=(w);

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

void Weapon::updateFromCollider()
{
    Entity::updateFromCollider();
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

void Weapon::setBody(Collider* c)
{
    Entity::setBody(c);
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

Collider* Weapon::getBody() const
{
    return Entity::getBody();
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