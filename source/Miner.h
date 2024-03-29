#ifndef _MINER_
#define _MINER_

#include "Enemy.h"


class Miner : public Enemy
{

public:
    // Constructores
    Miner(int l, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
        World* w = nullptr, Shape* sh = nullptr,
        CollisionFlag interests_flag = CollisionFlag::player_hurt,
        const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        const Vector2d<float>& max_vel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& max_accel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& frict = Vector2d<float>(0.0f,0.0f), Weapon* wp = nullptr,
        float st_time = 0.0f, float inv_time = 0.0f, BinaryTree* bt = nullptr, float vr = 10.0f);
    Miner(const Miner& cc);

    Miner& operator= (const Miner& cc);

    // Métodos
        //Entity
    void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    void update() override;
    void updateFromCollider() override;
    void interpolate(float rp = 0.0f) override;
    void manageAnimations() override;
    void collision(void * ent) override;
        //Character
        //Combat_Character
    void attack() override;
    void cancelAttack() override;
    void die() override;
        //Enemy
    bool checkNearPlayer(float distance) override;
    bool checkFarPlayer(float distance) override;
    void actionMoveTowardsPlayer() override;
    void actionStop() override;
    bool checkSeePlayer() override;
    bool checkPlayerInWeaponRange() override;
    void actionOrientateToPlayer() override;
        //Miner

    // Setters
        //Entity
    void setSprite(Sprite* spr) override;
    void setPosition(const Vector2d<float>& pos) override;
    void setWorld(World* w) override;
    void setBody(Collider* c) override;
    void setVelocity(const Vector2d<float>& vel) override;
    void setAngle(float angl) override;
    void setOrientation(const Vector2d<float>& ori) override;
        //Character
    void setAcceleration(const Vector2d<float>& accel) override;
    void setFriction(const Vector2d<float>& frict) override;
        //Combat_Character
    bool addWeapon(Weapon* wp) override;
    void removeWeapon(Weapon* wp) override;
    void equipWeapon(size_t index) override;
    void equipNextWeapon() override;
    void setAttacked(bool at) override;
    void setStunned(bool st) override;
    void setLife(int l) override;
    void setMaxLife(int l) override;
    bool increaseLife(int l) override;
        //Enemy
    void setBehaviour(BinaryTree* bt) override;
    void setVisionRange(float vr) override;
        //Miner

    // Getters
        //Entity
    Sprite* getSprite() const override;
    const Vector2d<float>& getPosition() const override;
    World* getWorld() const override;
    Collider* getBody() const override;
    const Vector2d<float>& getVelocity() const override;
    const Vector2d<float>& getPrePosition() const override;
    const Vector2d<float>& getRenderPosition() const override;
    const EntityType& getEntityType() const override;
    float getAngle() const override;
    Vector2d<float> getCenter() const override;
    const Vector2d<float>& getOrientation() const override;
        //Character
    const Vector2d<float>& getAcceleration() const override;
        //Combat_Character
    const std::vector<Weapon*>& getWeapons() const override;
    Weapon* getWeaponEquipped() const override;
    bool getAttacking() const override;
    bool getAttacked() const override;
    bool getStunned() const override;
    bool getInvincible() const override;
    int getLife() const override;
    int getMaxLife() const override;
    bool hasWeapon(const WeaponType& wt) const override;
        //Enemy
    const EnemyType& getEnemyType() const override;
    float getVisionRange() const override;
        //Miner

    // Destructor
    ~Miner();

protected:

private:


};

#endif