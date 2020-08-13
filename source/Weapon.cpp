#include "Weapon.h"
#include "Combat_Character.h"
#include "World.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Weapon::Weapon(float t_attack, const Vector2d<float>& rel_attack, const Vector2d<float>& rel_pos, Sprite* spr, World* w, Collider* c, Combat_Character* cc)
: Entity(rel_pos, spr, w, c), character(cc), rel_position(rel_pos), orig_rel_position(rel_position), attack_rel_position(rel_attack), attacking(false), attack_time(t_attack)
{
    id = Class_Id::e_weapon;

    position = rel_position;

    if(character!=nullptr)
    {
        position += character->getPosition();
        character->addWeapon(this);
    }

}

Weapon::Weapon(const Weapon& w)
: Entity(w), character(w.character), rel_position(w.rel_position), orig_rel_position(w.orig_rel_position), attack_rel_position(w.attack_rel_position), attacking(false), attack_time(w.attack_time)
{
    position = rel_position;

    if(character!=nullptr)
    {
        position += character->getPosition();
        character->addWeapon(this);
    }
}

Weapon& Weapon::operator= (const Weapon& w)
{
    this->Entity::operator=(w);
    character = w.character;

    if(character!=nullptr)
    {
        character->addWeapon(this);
    }

    attacking = false;
    attack_time = w.attack_time;
    rel_position = w.rel_position;
    orig_rel_position = w.orig_rel_position;
    attack_rel_position = w.attack_rel_position;

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Weapon::render(const Vector2d<float>& view_pos)
{
    Entity::render(view_pos);
}

void Weapon::update()
{
    rel_position = orig_rel_position;

    if(attacking)
    {
        rel_position += attack_rel_position;

        if (time_attacking.getElapsed() > attack_time)
        {
            attacking = false;
        }
    }

    if (character!=nullptr)
    {
        position = character->getPosition() + rel_position;
    }

    Entity::update();
}

void Weapon::updateFromCollider()
{
    Entity::updateFromCollider();
}

void Weapon::interpolate(float rp)
{
    render_position = rel_position;

    if(character!=nullptr)
    {
        render_position += character->getRenderPosition();
    }
}

void Weapon::collision(void * ent)
{
    Entity::collision(ent);
}

void Weapon::attack()
{
    if(!attacking)
    {
        attacking = true;
        time_attacking.reset();
    }
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

    position = rel_position;

    if(character!=nullptr)
    {
        character->removeWeapon(this);
    }

    character = cc;

    if(character!=nullptr)
    {
        position += character->getPosition();
        character->addWeapon(this);
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

const Vector2d<float>& Weapon::getRelativePosition() const
{
    return rel_position;
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