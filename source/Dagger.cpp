





#include "Dagger.h"
#include "Combat_Character.h"
#include "World.h"
#include "Unvisual_Engine.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Dagger::Dagger(int dam, float knock, float t_attack, const Vector2d<float>& rel_attack,
    Sprite* spr, World* w, Shape* sh, CollisionFlag type_flag, CollisionFlag interests_flag,
    const Vector2d<float>& ori, Combat_Character* cc, Animation* at_anim)
: Weapon(dam, knock, t_attack, rel_attack, spr, w, sh, type_flag, interests_flag, ori, cc, at_anim)
{
    sub_id = WeaponType::dagger;
}

Dagger::Dagger(const Dagger& d)
: Weapon(d)
{

}

Dagger& Dagger::operator= (const Dagger& d)
{
    this->Weapon::operator=(d);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Dagger::render(const Vector2d<float>& view_pos)
{
    Weapon::render(view_pos);
}

void Dagger::update()
{
    Weapon::update();
}

void Dagger::updateFromCollider()
{
    Weapon::updateFromCollider();
}

void Dagger::interpolate(float rp)
{
    Weapon::interpolate(rp);
}

void Dagger::manageAnimations()
{
    Weapon::manageAnimations();
}

void Dagger::collision(void * ent)
{
    Weapon::collision(ent);
}

void Dagger::attack()
{
    Weapon::attack();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Dagger::setSprite(Sprite* spr)
{
    Weapon::setSprite(spr);
}

void Dagger::setPosition(const Vector2d<float>& pos)
{
    Weapon::setPosition(pos);
}

void Dagger::setWorld(World* w)
{
    Weapon::setWorld(w);
}

void Dagger::setBody(Collider* c)
{
    Weapon::setBody(c);
}

void Dagger::setVelocity(const Vector2d<float>& vel)
{
    Weapon::setVelocity(vel);
}

void Dagger::setAngle(float angl)
{
    Weapon::setAngle(angl);
}

void Dagger::setOrientation(const Vector2d<float>& ori)
{
    Weapon::setOrientation(ori);
}

void Dagger::setCharacter(Combat_Character* cc)
{
    Weapon::setCharacter(cc);
}

void Dagger::setRelativePosition(const Vector2d<float>& rl_pos)
{
    Weapon::setRelativePosition(rl_pos);
}

void Dagger::setAttackingTime(float at_time)
{
    Weapon::setAttackingTime(at_time);
}

void Dagger::setDamage(int dam)
{
    Weapon::setDamage(dam);
}

void Dagger::setKnockback(float knock)
{
    Weapon::setKnockback(knock);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Dagger::getSprite() const
{
    return Weapon::getSprite();
}

const Vector2d<float>& Dagger::getPosition() const
{
    return Weapon::getPosition();
}

World* Dagger::getWorld() const
{
    return Weapon::getWorld();
}

Collider* Dagger::getBody() const
{
    return Weapon::getBody();
}

const Vector2d<float>& Dagger::getVelocity() const
{
    return Weapon::getVelocity();
}

const Vector2d<float>& Dagger::getPrePosition() const
{
    return Weapon::getPrePosition();
}

const Vector2d<float>& Dagger::getRenderPosition() const
{
    return Weapon::getRenderPosition();
}

const EntityType& Dagger::getEntityType() const
{
    return Weapon::getEntityType();
}

float Dagger::getAngle() const
{
    return Weapon::getAngle();
}

Vector2d<float> Dagger::getCenter() const
{
    return Weapon::getCenter();
}

const Vector2d<float>& Dagger::getOrientation() const
{
    return Weapon::getOrientation();
}

Combat_Character* Dagger::getCharacter() const
{
    return Weapon::getCharacter();
}

const Vector2d<float>& Dagger::getRelativePosition() const
{
    return Weapon::getRelativePosition();
}

bool Dagger::getAttacking() const
{
    return Weapon::getAttacking();
}

int Dagger::getDamage() const
{
    return Weapon::getDamage();
}

float Dagger::getKnockback() const
{
    return Weapon::getKnockback();
}

const WeaponType& Dagger::getWeaponType() const
{
    return Weapon::getWeaponType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Dagger::~Dagger()
{

}


//=========================================
//=               PROTECTED   	    	  =
//=========================================

void Dagger::calculateCenter()
{
    Weapon::calculateCenter();
}