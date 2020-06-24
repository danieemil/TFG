#include "Combat_Character.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Combat_Character::Combat_Character(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c,
    const Vector2d<float>& max_vel, const Vector2d<float>& accel, const Vector2d<float>& decel, Weapon* wp)
: Character(pos, spr, w, c, max_vel, accel, decel)
{
    if(wp!=nullptr)
    {
        weapons.emplace_back(wp);
    }
    equipped = wp;
}

Combat_Character::Combat_Character(const Combat_Character& cc)
: Character(cc)
{
    equipped = nullptr;
}

Combat_Character& Combat_Character::operator= (const Combat_Character& cc)
{
    Character::operator=(cc);
    equipped = nullptr;
    
    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Combat_Character::render(float rp, const Vector2d<float>& view_pos)
{
    Character::render(rp, view_pos);
    if(equipped!=nullptr)
    {
        equipped->render(rp, view_pos);
    }
}

void Combat_Character::update()
{
    Character::update();
    if(equipped!=nullptr)
    {
        equipped->update();
    }
}

void Combat_Character::updateFromCollider()
{
    Character::updateFromCollider();
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

void Combat_Character::setBody(Collider* c)
{
    Character::setBody(c);
}

void Combat_Character::setVelocity(const Vector2d<float>& vel)
{
    Character::setVelocity(vel);
}

void Combat_Character::addWeapon(Weapon* wp)
{
    if(wp!=nullptr)
    {
        weapons.emplace_back(wp);
    }
}

void Combat_Character::equipWeapon(size_t index)
{
    if(weapons.empty())
    {
        equipped = nullptr;
        return;
    }

    size_t ind = index;

    if(ind >= weapons.size())
    {
        ind = weapons.size() - 1;
    }

    equipped = weapons[ind];
    
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

Collider* Combat_Character::getBody() const
{
    return Character::getBody();
}

const Vector2d<float>& Combat_Character::getVelocity() const
{
    return Character::getVelocity();
}

const Vector2d<float>& Combat_Character::getPrePosition() const
{
    return Character::getPrePosition();
}

const Vector2d<float>& Combat_Character::getRenderPosition() const
{
    return Character::getRenderPosition();
}

const Class_Id& Combat_Character::getClassId() const
{
    return Character::getClassId();
}

const std::vector<Weapon*>& Combat_Character::getWeapons() const
{
    return weapons;
}

Weapon* Combat_Character::getWeaponEquipped() const
{
    return equipped;
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