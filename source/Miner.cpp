#include "Miner.h"

#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Miner::Miner(int l, const Vector2d<float>& pos, Sprite* spr, World* w, Shape* sh,
    CollisionFlag interests_flag, const Vector2d<float>& ori, const Vector2d<float>& max_vel,
    const Vector2d<float>& max_accel, const Vector2d<float>& frict, Weapon* wp, float st_time,
    BinaryTree* bt)
: Enemy(l, pos, spr, w, sh, interests_flag, ori, max_vel, max_accel, frict, wp, st_time, bt)
{
    sub_id = EnemyType::miner;
}

Miner::Miner(const Miner& m)
: Enemy(m)
{

}

Miner& Miner::operator= (const Miner& m)
{
    Enemy::operator=(m);
    
    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Miner::render(const Vector2d<float>& view_pos)
{
    Enemy::render(view_pos);
}

void Miner::update()
{
    Enemy::update();
}

void Miner::updateFromCollider()
{
    Enemy::updateFromCollider();
}

void Miner::interpolate(float rp)
{
    Enemy::interpolate(rp);
}

void Miner::manageAnimations()
{
    Enemy::manageAnimations();
}

void Miner::collision(void* ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getEntityType()==EntityType::e_weapon)
        {
            //Weapon* w = static_cast<Weapon*>(e);
        }
    }

    Enemy::collision(ent);
}

void Miner::attack()
{
    Enemy::attack();
}

void Miner::die()
{
    Enemy::die();
}

bool Miner::checkNearPlayer(float distance)
{
    return Enemy::checkNearPlayer(distance);
}

bool Miner::checkFarPlayer(float distance)
{
    return Enemy::checkFarPlayer(distance);
}

void Miner::actionTowardsPlayer()
{
    Enemy::actionTowardsPlayer();
}

void Miner::actionStop()
{
    Enemy::actionStop();
}



//=========================================
//=               SETTERS   	    	  =
//=========================================

void Miner::setSprite(Sprite* spr)
{
    Enemy::setSprite(spr);
}

void Miner::setPosition(const Vector2d<float>& pos)
{
    Enemy::setPosition(pos);
}

void Miner::setWorld(World* w)
{
    Enemy::setWorld(w);
}

void Miner::setBody(Collider* c)
{
    Enemy::setBody(c);
}

void Miner::setVelocity(const Vector2d<float>& vel)
{
    Enemy::setVelocity(vel);
}

void Miner::setAngle(float angl)
{
    if(angle == angl) return;

    Enemy::setAngle(angl);
}

void Miner::setOrientation(const Vector2d<float>& ori)
{
    Enemy::setOrientation(ori);
}

void Miner::setAcceleration(const Vector2d<float>& accel)
{
    Enemy::setAcceleration(accel);
}

void Miner::setFriction(const Vector2d<float>& frict)
{
    Enemy::setFriction(frict);
}

bool Miner::addWeapon(Weapon* wp)
{
    return Enemy::addWeapon(wp);
}

void Miner::removeWeapon(Weapon* wp)
{
    Enemy::removeWeapon(wp);
}

void Miner::equipWeapon(size_t index)
{
    Enemy::equipWeapon(index);
}

void Miner::equipNextWeapon()
{
    Enemy::equipNextWeapon();
}

void Miner::setAttacked(bool at)
{
    Enemy::setAttacked(at);
}

void Miner::setStunned(bool st)
{
    Enemy::setStunned(st);
}

void Miner::setLife(int l)
{
    Enemy::setLife(l);
}

void Miner::setMaxLife(int l)
{
    Enemy::setMaxLife(l);
}

bool Miner::increaseLife(int l)
{
    return Enemy::increaseLife(l);
}

void Miner::setBehaviour(BinaryTree* bt)
{
    Enemy::setBehaviour(bt);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Miner::getSprite() const
{
    return Enemy::getSprite();
}

const Vector2d<float>& Miner::getPosition() const
{
    return Enemy::getPosition();
}

World* Miner::getWorld() const
{
    return Enemy::getWorld();
}

Collider* Miner::getBody() const
{
    return Enemy::getBody();
}

const Vector2d<float>& Miner::getVelocity() const
{
    return Enemy::getVelocity();
}

const Vector2d<float>& Miner::getPrePosition() const
{
    return Enemy::getPrePosition();
}

const Vector2d<float>& Miner::getRenderPosition() const
{
    return Enemy::getRenderPosition();
}

const EntityType& Miner::getEntityType() const
{
    return Enemy::getEntityType();
}

float Miner::getAngle() const
{
    return Enemy::getAngle();
}

Vector2d<float> Miner::getCenter() const
{
    return Enemy::getCenter();
}

const Vector2d<float>& Miner::getOrientation() const
{
    return Enemy::getOrientation();
}

const Vector2d<float>& Miner::getAcceleration() const
{
    return Enemy::getAcceleration();
}

const std::vector<Weapon*>& Miner::getWeapons() const
{
    return Enemy::getWeapons();
}

Weapon* Miner::getWeaponEquipped() const
{
    return Enemy::getWeaponEquipped();
}

bool Miner::getAttacking() const
{
    return Enemy::getAttacking();
}

bool Miner::getAttacked() const
{
    return Enemy::getAttacked();
}

bool Miner::getStunned() const
{
    return Enemy::getStunned();
}

int Miner::getLife() const
{
    return Enemy::getLife();
}

int Miner::getMaxLife() const
{
    return Enemy::getMaxLife();
}

bool Miner::hasWeapon(const WeaponType& wt) const
{
    return Enemy::hasWeapon(wt);
}

const EnemyType& Miner::getEnemyType() const
{
    return Enemy::getEnemyType();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Miner::~Miner()
{
    
}