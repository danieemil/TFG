#include "Enemy.h"

#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Enemy::Enemy(int l, const Vector2d<float>& pos, Sprite* spr, World* w, CollisionFlag interests_flag,
    const Vector2d<float>& ori, const Vector2d<float>& max_vel, const Vector2d<float>& max_accel,
    const Vector2d<float>& frict, Weapon* wp, float st_time, BinaryTree* bt)
: Combat_Character(l, pos, spr, w, CollisionFlag::enemy_hit, interests_flag, ori, max_vel, max_accel, frict, wp, st_time), b_tree(bt)
{
    id = EntityType::e_enemy;
}

Enemy::Enemy(const Enemy& cc)
: Combat_Character(cc), b_tree(cc.b_tree)
{
    id = EntityType::e_enemy;
}

Enemy& Enemy::operator= (const Enemy& cc)
{
    Combat_Character::operator=(cc);
    b_tree = cc.b_tree;
    
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

    if(b_tree!=nullptr)
    {
        b_tree->update(this);
    }   

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
        if(e->getEntityType()==EntityType::e_weapon)
        {
            //Weapon* w = static_cast<Weapon*>(e);
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

bool Enemy::checkNearPlayer(float distance)
{

    Player* p = Game::Instance()->getPlayer();

    if(p!=nullptr)
    {
        Vector2d<float> dist = p->getPosition() - position;
        if(dist.Length() < distance)
        {
            return true;
        }   
    }

    return false;
}

bool Enemy::checkFarPlayer(float distance)
{
    Player* p = Game::Instance()->getPlayer();

    if(p!=nullptr)
    {
        Vector2d<float> dist = p->getPosition() - position;
        if(dist.Length() > distance)
            return true;
    }

    return false;
}

void Enemy::actionTowardsPlayer()
{

    Player* p = Game::Instance()->getPlayer();

    if(p!=nullptr)
    {
        Vector2d<float> dist = p->getPosition() - position;

        Vector2d<float> dir = dist;
        dir.Normalize();

        Vector2d<int> ori = Vector2d<int>(sign(dir.x), sign(dir.y));

        if((dir.x * ori.x) > 0.5f) dir.x = 1.0f * ori.x;
        else dir.x = 0.0f;

        if((dir.y * ori.y) > 0.5f) dir.y = 1.0f * ori.y;
        else dir.y = 0.0f;

        orientation = dir;

        float accel = 20.0f;

        dir.Normalize();
        acceleration = dir * accel;

    }
}

void Enemy::actionStop()
{
    acceleration = Vector2d<float>(0.0f, 0.0f);
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
    //Combat_Character::setAngle(angl);
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

bool Enemy::addWeapon(Weapon* wp)
{
    if(Combat_Character::addWeapon(wp))
    {
        // Colisiones del arma
        CollisionFlag WeaponType = CollisionFlag::enemy_hurt;
        CollisionFlag weapon_interests = CollisionFlag::player_hit;

        Collider* weapon_collider = wp->getBody();
        if(weapon_collider!=nullptr)
        {
            CollisionFlag type = weapon_collider->getTypeFlags();
            CollisionFlag interests = weapon_collider->getInterestedFlags();

            weapon_collider->setTypeFlags(WeaponType | type);
            weapon_collider->setIntersetedFlags(weapon_interests | interests);
        }

        return true;
    }
    return false;
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

void Enemy::setMaxLife(int l)
{
    Combat_Character::setMaxLife(l);
}

bool Enemy::increaseLife(int l)
{
    return Combat_Character::increaseLife(l);
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

const EntityType& Enemy::getEntityType() const
{
    return Combat_Character::getEntityType();
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

int Enemy::getMaxLife() const
{
    return Combat_Character::getMaxLife();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Enemy::~Enemy()
{
    
}