#ifndef _ENEMY_
#define _ENEMY_

#include "Combat_Character.h"
#include "Weapon.h"
#include "BinaryTree.h"


class Enemy : public Combat_Character
{

public:
    // Constructores
    Enemy(int l, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr,
        CollisionFlag interests_flag = CollisionFlag::player_hurt, const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        const Vector2d<float>& max_vel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& max_accel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& frict = Vector2d<float>(0.0f,0.0f), Weapon* wp = nullptr,
        float st_time = 0.0f, BinaryTree* bt = nullptr);
    Enemy(const Enemy& cc);

    Enemy& operator= (const Enemy& cc);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider() override;
    virtual void interpolate(float rp = 0.0f) override;
    virtual void collision(void * ent) override;
        //Character
        //Combat_Character
    virtual void attack() override;
    virtual void die() override;
        //Enemy
    virtual bool checkNearPlayer(float distance);
    virtual bool checkFarPlayer(float distance);
    virtual void actionTowardsPlayer();
    virtual void actionStop();

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
    virtual void setAngle(float angl);
    virtual void setOrientation(const Vector2d<float>& ori);
        //Character
    virtual void setAcceleration(const Vector2d<float>& accel);
    virtual void setFriction(const Vector2d<float>& frict);
        //Combat_Character
    virtual bool addWeapon(Weapon* wp);
    virtual void removeWeapon(Weapon* wp);
    virtual void equipWeapon(size_t index);
    virtual void setAttacked(bool at);
    virtual void setStunned(bool st);
    virtual void setLife(int l);
    virtual void setMaxLife(int l);
    virtual bool increaseLife(int l);
        //Enemy

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;
    virtual const Vector2d<float>& getVelocity() const;
    virtual const Vector2d<float>& getPrePosition() const;
    virtual const Vector2d<float>& getRenderPosition() const;
    virtual const EntityType& getEntityType() const;
    virtual float getAngle() const;
    virtual Vector2d<float> getCenter() const;
    virtual const Vector2d<float>& getOrientation() const;
        //Character
    virtual const Vector2d<float>& getAcceleration() const;
        //Combat_Character
    virtual const std::vector<Weapon*>& getWeapons() const;
    virtual Weapon* getWeaponEquipped() const;
    virtual bool getAttacking() const;
    virtual bool getAttacked() const;
    virtual bool getStunned() const;
    virtual int getLife() const;
    virtual int getMaxLife() const;
        //Enemy

    // Destructor
    ~Enemy();

protected:

    BinaryTree* b_tree;

private:


};

#endif