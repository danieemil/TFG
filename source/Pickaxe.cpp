#include "Pickaxe.h"
#include "Combat_Character.h"
#include "World.h"
#include "Unvisual_Engine.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Pickaxe::Pickaxe(int dam, float knock, float t_attack, const Vector2d<float>& rel_attack,
    Sprite* spr, World* w, Shape* sh, CollisionFlag type_flag, CollisionFlag interests_flag,
    const Vector2d<float>& ori, Combat_Character* cc, Animation* at_anim)
: Weapon(dam, knock, t_attack, rel_attack, spr, w, sh, type_flag, interests_flag, ori, cc, at_anim)
{
    sub_id = WeaponType::pickaxe;
}

Pickaxe::Pickaxe(const Pickaxe& p)
: Weapon(p)
{

}

Pickaxe& Pickaxe::operator= (const Pickaxe& p)
{
    this->Weapon::operator=(p);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Pickaxe::render(const Vector2d<float>& view_pos)
{
    Weapon::render(view_pos);
}

void Pickaxe::update()
{
    Weapon::update();
}

void Pickaxe::updateFromCollider()
{
    Weapon::updateFromCollider();
}

void Pickaxe::interpolate(float rp)
{
    Weapon::interpolate(rp);
}

void Pickaxe::manageAnimations()
{
    Weapon::manageAnimations();
}

void Pickaxe::collision(void * ent)
{
    Weapon::collision(ent);
}

void Pickaxe::attack()
{
    Weapon::attack();
}

void Pickaxe::cancelAttack()
{
    Weapon::cancelAttack();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Pickaxe::setSprite(Sprite* spr)
{
    Weapon::setSprite(spr);
}

void Pickaxe::setPosition(const Vector2d<float>& pos)
{
    Weapon::setPosition(pos);
}

void Pickaxe::setWorld(World* w)
{
    Weapon::setWorld(w);
}

void Pickaxe::setBody(Collider* c)
{
    Weapon::setBody(c);
}

void Pickaxe::setVelocity(const Vector2d<float>& vel)
{
    Weapon::setVelocity(vel);
}

void Pickaxe::setAngle(float angl)
{
    Weapon::setAngle(angl);
}

void Pickaxe::setOrientation(const Vector2d<float>& ori)
{
    Weapon::setOrientation(ori);
}

void Pickaxe::setCharacter(Combat_Character* cc)
{
    Weapon::setCharacter(cc);
}

void Pickaxe::setRelativePosition(const Vector2d<float>& rl_pos)
{
    Weapon::setRelativePosition(rl_pos);
}

void Pickaxe::setAttackingTime(float at_time)
{
    Weapon::setAttackingTime(at_time);
}

void Pickaxe::setDamage(int dam)
{
    Weapon::setDamage(dam);
}

void Pickaxe::setKnockback(float knock)
{
    Weapon::setKnockback(knock);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Pickaxe::getSprite() const
{
    return Weapon::getSprite();
}

const Vector2d<float>& Pickaxe::getPosition() const
{
    return Weapon::getPosition();
}

World* Pickaxe::getWorld() const
{
    return Weapon::getWorld();
}

Collider* Pickaxe::getBody() const
{
    return Weapon::getBody();
}

const Vector2d<float>& Pickaxe::getVelocity() const
{
    return Weapon::getVelocity();
}

const Vector2d<float>& Pickaxe::getPrePosition() const
{
    return Weapon::getPrePosition();
}

const Vector2d<float>& Pickaxe::getRenderPosition() const
{
    return Weapon::getRenderPosition();
}

const EntityType& Pickaxe::getEntityType() const
{
    return Weapon::getEntityType();
}

float Pickaxe::getAngle() const
{
    return Weapon::getAngle();
}

Vector2d<float> Pickaxe::getCenter() const
{
    return Weapon::getCenter();
}

const Vector2d<float>& Pickaxe::getOrientation() const
{
    return Weapon::getOrientation();
}

Combat_Character* Pickaxe::getCharacter() const
{
    return Weapon::getCharacter();
}

const Vector2d<float>& Pickaxe::getRelativePosition() const
{
    return Weapon::getRelativePosition();
}

bool Pickaxe::getAttacking() const
{
    return Weapon::getAttacking();
}

int Pickaxe::getDamage() const
{
    return Weapon::getDamage();
}

float Pickaxe::getKnockback() const
{
    return Weapon::getKnockback();
}

const WeaponType& Pickaxe::getWeaponType() const
{
    return Weapon::getWeaponType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Pickaxe::~Pickaxe()
{

}


//=========================================
//=               PROTECTED   	    	  =
//=========================================

void Pickaxe::calculateCenter()
{
    Weapon::calculateCenter();
}