#include "Weapon.h"
#include "Combat_Character.h"
#include "World.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Weapon::Weapon(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c, Combat_Character* cc)
: Entity(pos, spr, w, c), character(cc)
{
    id = Class_Id::e_weapon;
}

Weapon::Weapon(const Weapon& w)
: Entity(w), character(w.character)
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

void Weapon::render(float rp, const Vector2d<float>& view_pos)
{
    Entity::render(rp, view_pos);
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

void Weapon::setVelocity(const Vector2d<float>& vel)
{
    Entity::setVelocity(vel);
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

const Vector2d<float>& Weapon::getVelocity() const
{
    return Entity::getVelocity();
}

const Vector2d<float>& Weapon::getPrePosition() const
{
    return Entity::getPrePosition();
}

const Vector2d<float>& Weapon::getRenderPosition() const
{
    return Entity::getRenderPosition();
}

Combat_Character* Weapon::getCharacter() const
{
    return character;
}

const Class_Id& Weapon::getClassId() const
{
    return Entity::getClassId();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Weapon::~Weapon()
{
    
}