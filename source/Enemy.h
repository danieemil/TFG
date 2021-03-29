#ifndef _ENEMY_
#define _ENEMY_

#include "Combat_Character.h"
#include "Weapon.h"
#include "BinaryTree.h"


// Tipos de enemigos instanciables
enum class EnemyType
{
    miner,
};


class Enemy : public Combat_Character
{

public:
    // Constructores
    Enemy(int l, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
        World* w = nullptr, Shape* sh = nullptr,
        CollisionFlag interests_flag = CollisionFlag::player_hurt,
        const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        const Vector2d<float>& max_vel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& max_accel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& frict = Vector2d<float>(0.0f,0.0f), Weapon* wp = nullptr,
        float st_time = 0.0f, float inv_time = 0.0f, BinaryTree* bt = nullptr, float vr = 10.0f);
    Enemy(const Enemy& e);

    Enemy& operator= (const Enemy& e);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider() override;
    virtual void interpolate(float rp = 0.0f) override;
    virtual void manageAnimations() override;
    virtual void collision(void * ent) override;
        //Character
        //Combat_Character
    virtual void attack() override;
    virtual void cancelAttack() override;
    virtual void die() override;
        //Enemy
    virtual bool checkNearPlayer(float distance);
    virtual bool checkFarPlayer(float distance);
    virtual void actionMoveTowardsPlayer();
    virtual void actionStop();
    virtual bool checkSeePlayer();
    virtual bool checkPlayerInWeaponRange();
    virtual void actionOrientateToPlayer();

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr) override;
    virtual void setPosition(const Vector2d<float>& pos) override;
    virtual void setWorld(World* w) override;
    virtual void setBody(Collider* c) override;
    virtual void setVelocity(const Vector2d<float>& vel) override;
    virtual void setAngle(float angl) override;
    virtual void setOrientation(const Vector2d<float>& ori) override;
        //Character
    virtual void setAcceleration(const Vector2d<float>& accel) override;
    virtual void setFriction(const Vector2d<float>& frict) override;
        //Combat_Character
    virtual bool addWeapon(Weapon* wp) override;
    virtual void removeWeapon(Weapon* wp) override;
    virtual void equipWeapon(size_t index) override;
    virtual void equipNextWeapon() override;
    virtual void setAttacked(bool at) override;
    virtual void setStunned(bool st) override;
    virtual void setLife(int l) override;
    virtual void setMaxLife(int l) override;
    virtual bool increaseLife(int l) override;
        //Enemy
    virtual void setBehaviour(BinaryTree* bt);
    virtual void setVisionRange(float vr);

    // Getters
        //Entity
    virtual Sprite* getSprite() const override;
    virtual const Vector2d<float>& getPosition() const override;
    virtual World* getWorld() const override;
    virtual Collider* getBody() const override;
    virtual const Vector2d<float>& getVelocity() const override;
    virtual const Vector2d<float>& getPrePosition() const override;
    virtual const Vector2d<float>& getRenderPosition() const override;
    virtual const EntityType& getEntityType() const override;
    virtual float getAngle() const override;
    virtual Vector2d<float> getCenter() const override;
    virtual const Vector2d<float>& getOrientation() const override;
        //Character
    virtual const Vector2d<float>& getAcceleration() const override;
        //Combat_Character
    virtual const std::vector<Weapon*>& getWeapons() const override;
    virtual Weapon* getWeaponEquipped() const override;
    virtual bool getAttacking() const override;
    virtual bool getAttacked() const override;
    virtual bool getStunned() const override;
    virtual bool getInvincible() const override;
    virtual int getLife() const override;
    virtual int getMaxLife() const override;
    virtual bool hasWeapon(const WeaponType& wt) const override;
        //Enemy
    virtual const EnemyType& getEnemyType() const;
    virtual float getVisionRange() const;

    // Destructor
    virtual ~Enemy();

protected:

    BinaryTree* b_tree;
    EnemyType sub_id;

    float vision_range;

private:


};

#endif