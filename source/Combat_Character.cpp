#include "Combat_Character.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Combat_Character::Combat_Character(const Combat_Character& c) : Character(c)
{

}

Combat_Character::Combat_Character(const Vector2d<float>& pos, Sprite* spr) : Character(pos, spr)
{

}

Combat_Character::Combat_Character(World* w, const Vector2d<float>& pos, Sprite* spr, Weapon* wp) : Character(w, pos, spr)
{
    if(wp!=nullptr)
    {
        weapons.emplace_back(wp);
    }
}

Combat_Character& Combat_Character::operator= (const Combat_Character& c)
{
    this->Character::operator=(c);

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Combat_Character::render()
{
    Character::render();
    for(auto it = weapons.begin();it!=weapons.end();it++)
    {
        (*it)->render();
    }
}

void Combat_Character::update()
{
    Character::update();
    for(auto it = weapons.begin();it!=weapons.end();it++)
    {
        (*it)->update();
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Combat_Character::setSprite(Sprite* spr)
{
    Character::setSprite(spr);
}

void Combat_Character::setPosition(const Vector2d<float>& pos)
{
    Character::setPosition(pos);
}

void Combat_Character::setWorld(World* w)
{
    Character::setWorld(w);
}

void Combat_Character::addWeapon(Weapon* wp)
{
    if(wp!=nullptr)
    {
        weapons.emplace_back(wp);
    }
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Combat_Character::getSprite() const
{
    return Character::getSprite();
}

const Vector2d<float>& Combat_Character::getPosition() const
{
    return Character::getPosition();
}

World* Combat_Character::getWorld() const
{
    return Character::getWorld();
}

const std::vector<Weapon*>& Combat_Character::getWeapons() const
{
    return weapons;
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Combat_Character::~Combat_Character()
{

    auto weapon = weapons.begin();

    while (weapon!=weapons.end())
    {
        Weapon* w = (*weapon);
        if(w!=nullptr)
        {
            delete w;
        }
        weapons.erase(weapon);
    }
    
}