#ifndef _COMBAT_CHARACTER_
#define _COMBAT_CHARACTER_

#include "Character.h"
#include "Weapon.h"
#include "vector"


class Combat_Character : public Character
{

public:
    // Constructores
    Combat_Character(int l, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
        World* w = nullptr, CollisionFlag type_flag = CollisionFlag::none, CollisionFlag interests_flag = CollisionFlag::none,
        const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        const Vector2d<float>& max_vel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& max_accel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& frict = Vector2d<float>(0.0f,0.0f), Weapon* wp = nullptr,
        float st_time = 0.0f);
    Combat_Character(const Combat_Character& cc);

    Combat_Character& operator= (const Combat_Character& cc);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider() override;
    virtual void interpolate(float rp = 0.0f) override;
    virtual void collision(void * ent) override;
        //Character
        //Combat_Character
    virtual void attack();
    virtual void die();

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
    virtual void addWeapon(Weapon* wp);
    virtual void removeWeapon(Weapon* wp);
    virtual void equipWeapon(size_t index);
    virtual void setAttacked(bool at);
    virtual void setStunned(bool st);
    virtual void setLife(int l);
    virtual void setMaxLife(int l);

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;
    virtual const Vector2d<float>& getVelocity() const;
    virtual const Vector2d<float>& getPrePosition() const;
    virtual const Vector2d<float>& getRenderPosition() const;
    virtual const Class_Id& getClassId() const;
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

    // Destructor
    ~Combat_Character();

protected:

    std::vector<Weapon*> weapons;
    Weapon* equipped;

    bool attacked;

    // Mecánica de aturdimiento
    bool stunned;
    float stun_time;
    Timepoint stun_timing;

    // Atributos de personaje
    int life;
    int max_life;


private:


};

#endif