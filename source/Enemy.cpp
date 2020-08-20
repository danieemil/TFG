#include "Enemy.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Enemy::Enemy(const Vector2d<float>& pos, float angl, Sprite* spr, World* w, Collider* c,
    const Vector2d<float>& max_vel, const Vector2d<float>& accel, const Vector2d<float>& decel, Weapon* wp)
: Combat_Character(pos, angl, spr, w, c, max_vel, accel, decel, wp)
{
    id = Class_Id::e_enemy;
}

Enemy::Enemy(const Enemy& cc)
: Combat_Character(cc)
{
    id = Class_Id::e_enemy;
}

Enemy& Enemy::operator= (const Enemy& cc)
{
    Combat_Character::operator=(cc);
    
    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Enemy::render(const Vector2d<float>& view_pos)
{
    Combat_Character::render(view_pos);
}

void Enemy::update()
{
    Combat_Character::update();
}

void Enemy::updateFromCollider()
{
    Combat_Character::updateFromCollider();
}

void Enemy::interpolate(float rp)
{
    Combat_Character::interpolate(rp);
}

void Enemy::collision(void* ent)
{
    Combat_Character::collision(ent);
}

void Enemy::attack()
{
    Combat_Character::attack();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Enemy::setSprite(Sprite* spr)
{
    Combat_Character::setSprite(spr);
}

void Enemy::setPosition(const Vector2d<float>& pos)
{
    Combat_Character::setPosition(pos);
}

void Enemy::setWorld(World* w)
{
    Combat_Character::setWorld(w);
}

void Enemy::setBody(Collider* c)
{
    Combat_Character::setBody(c);
}

void Enemy::setVelocity(const Vector2d<float>& vel)
{
    Combat_Character::setVelocity(vel);
}

void Enemy::setAngle(float angl)
{
    Combat_Character::setAngle(angl);
}

void Enemy::addWeapon(Weapon* wp)
{
    Combat_Character::addWeapon(wp);
}

void Enemy::removeWeapon(Weapon* wp)
{
    Combat_Character::removeWeapon(wp);
}

void Enemy::equipWeapon(size_t index)
{
    Combat_Character::equipWeapon(index);
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Enemy::getSprite() const
{
    return Combat_Character::getSprite();
}

const Vector2d<float>& Enemy::getPosition() const
{
    return Combat_Character::getPosition();
}

World* Enemy::getWorld() const
{
    return Combat_Character::getWorld();
}

Collider* Enemy::getBody() const
{
    return Combat_Character::getBody();
}

const Vector2d<float>& Enemy::getVelocity() const
{
    return Combat_Character::getVelocity();
}

const Vector2d<float>& Enemy::getPrePosition() const
{
    return Combat_Character::getPrePosition();
}

const Vector2d<float>& Enemy::getRenderPosition() const
{
    return Combat_Character::getRenderPosition();
}

const Class_Id& Enemy::getClassId() const
{
    return Combat_Character::getClassId();
}

float Enemy::getAngle() const
{
    return Combat_Character::getAngle();
}

const std::vector<Weapon*>& Enemy::getWeapons() const
{
    return Combat_Character::getWeapons();
}

Weapon* Enemy::getWeaponEquipped() const
{
    return Combat_Character::getWeaponEquipped();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Enemy::~Enemy()
{

}