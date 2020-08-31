#include "Enemy.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Enemy::Enemy(int l, const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c,
    const Vector2d<float>& ori, const Vector2d<float>& max_vel, const Vector2d<float>& max_accel,
    const Vector2d<float>& frict, Weapon* wp, float st_time)
: Combat_Character(l, pos, spr, w, c, ori, max_vel, max_accel, frict, wp, st_time)
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
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getClassId()==Class_Id::e_weapon)
        {
            Weapon* w = static_cast<Weapon*>(e);
        }
    }

    Combat_Character::collision(ent);
}

void Enemy::attack()
{
    Combat_Character::attack();
}

void Enemy::die()
{
    Combat_Character::die();
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

void Enemy::setOrientation(const Vector2d<float>& ori)
{
    Combat_Character::setOrientation(ori);
}

void Enemy::setAcceleration(const Vector2d<float>& accel)
{
    Combat_Character::setAcceleration(accel);
}

void Enemy::setFriction(const Vector2d<float>& frict)
{
    Combat_Character::setFriction(frict);
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

void Enemy::setAttacked(bool at)
{
    Combat_Character::setAttacked(at);
}

void Enemy::setStunned(bool st)
{
    Combat_Character::setStunned(st);
}

void Enemy::setLife(int l)
{
    Combat_Character::setLife(l);
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

Vector2d<float> Enemy::getCenter() const
{
    return Combat_Character::getCenter();
}

const Vector2d<float>& Enemy::getOrientation() const
{
    return Combat_Character::getOrientation();
}

const Vector2d<float>& Enemy::getAcceleration() const
{
    return Combat_Character::getAcceleration();
}

const std::vector<Weapon*>& Enemy::getWeapons() const
{
    return Combat_Character::getWeapons();
}

Weapon* Enemy::getWeaponEquipped() const
{
    return Combat_Character::getWeaponEquipped();
}

bool Enemy::getAttacking() const
{
    return Combat_Character::getAttacking();
}

bool Enemy::getAttacked() const
{
    return Combat_Character::getAttacked();
}

bool Enemy::getStunned() const
{
    return Combat_Character::getStunned();
}

int Enemy::getLife() const
{
    return Combat_Character::getLife();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Enemy::~Enemy()
{

}