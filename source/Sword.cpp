#include "Sword.h"
#include "Combat_Character.h"
#include "World.h"
#include "Unvisual_Engine.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Sword::Sword(int dam, float knock, float t_attack, const Vector2d<float>& rel_attack,
    float t_pre_attack, float t_end_attack, Sprite* spr, World* w, Shape* sh,
    CollisionFlag type_flag, CollisionFlag interests_flag, const Vector2d<float>& ori,
    Combat_Character* cc, Animation* at_anim)
: Weapon(dam, knock, t_attack, rel_attack, t_pre_attack, t_end_attack, spr, w, sh, type_flag,
    interests_flag, ori, cc, at_anim)
{
    sub_id = WeaponType::sword;
}

Sword::Sword(const Sword& s)
: Weapon(s)
{

}

Sword& Sword::operator= (const Sword& s)
{
    this->Weapon::operator=(s);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Sword::render(const Vector2d<float>& view_pos)
{
    Weapon::render(view_pos);
}

void Sword::update()
{
    Weapon::update();
}

void Sword::updateFromCollider()
{
    Weapon::updateFromCollider();
}

void Sword::interpolate(float rp)
{
    Weapon::interpolate(rp);
}

void Sword::manageAnimations()
{
    Weapon::manageAnimations();
}

void Sword::collision(void * ent)
{
    Weapon::collision(ent);
}

void Sword::attack()
{
    Weapon::attack();
}

void Sword::cancelAttack()
{
    Weapon::cancelAttack();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Sword::setSprite(Sprite* spr)
{
    Weapon::setSprite(spr);
}

void Sword::setPosition(const Vector2d<float>& pos)
{
    Weapon::setPosition(pos);
}

void Sword::setWorld(World* w)
{
    Weapon::setWorld(w);
}

void Sword::setBody(Collider* c)
{
    Weapon::setBody(c);
}

void Sword::setVelocity(const Vector2d<float>& vel)
{
    Weapon::setVelocity(vel);
}

void Sword::setAngle(float angl)
{
    Weapon::setAngle(angl);
}

void Sword::setOrientation(const Vector2d<float>& ori)
{
    Weapon::setOrientation(ori);
}

void Sword::setCharacter(Combat_Character* cc)
{
    Weapon::setCharacter(cc);
}

void Sword::setRelativePosition(const Vector2d<float>& rl_pos)
{
    Weapon::setRelativePosition(rl_pos);
}

void Sword::setAttackingTime(float at_time)
{
    Weapon::setAttackingTime(at_time);
}

void Sword::setDamage(int dam)
{
    Weapon::setDamage(dam);
}

void Sword::setKnockback(float knock)
{
    Weapon::setKnockback(knock);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Sword::getSprite() const
{
    return Weapon::getSprite();
}

const Vector2d<float>& Sword::getPosition() const
{
    return Weapon::getPosition();
}

World* Sword::getWorld() const
{
    return Weapon::getWorld();
}

Collider* Sword::getBody() const
{
    return Weapon::getBody();
}

const Vector2d<float>& Sword::getVelocity() const
{
    return Weapon::getVelocity();
}

const Vector2d<float>& Sword::getPrePosition() const
{
    return Weapon::getPrePosition();
}

const Vector2d<float>& Sword::getRenderPosition() const
{
    return Weapon::getRenderPosition();
}

const EntityType& Sword::getEntityType() const
{
    return Weapon::getEntityType();
}

float Sword::getAngle() const
{
    return Weapon::getAngle();
}

Vector2d<float> Sword::getCenter() const
{
    return Weapon::getCenter();
}

const Vector2d<float>& Sword::getOrientation() const
{
    return Weapon::getOrientation();
}

Combat_Character* Sword::getCharacter() const
{
    return Weapon::getCharacter();
}

const Vector2d<float>& Sword::getRelativePosition() const
{
    return Weapon::getRelativePosition();
}

bool Sword::getAttacking() const
{
    return Weapon::getAttacking();
}

int Sword::getDamage() const
{
    return Weapon::getDamage();
}

float Sword::getKnockback() const
{
    return Weapon::getKnockback();
}

const WeaponType& Sword::getWeaponType() const
{
    return Weapon::getWeaponType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Sword::~Sword()
{

}


//=========================================
//=               PROTECTED   	    	  =
//=========================================

void Sword::calculateCenter()
{
    Weapon::calculateCenter();
}