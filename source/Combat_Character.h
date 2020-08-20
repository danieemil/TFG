#ifndef _COMBAT_CHARACTER_
#define _COMBAT_CHARACTER_

#include "Character.h"
#include "Weapon.h"
#include "vector"


class Combat_Character : public Character
{

public:
    // Constructores
    Combat_Character(const Vector2d<float>& pos = Vector2d<float>(), float angl = 0.0f, Sprite* spr = nullptr, World* w = nullptr,
        Collider* c = nullptr, const Vector2d<float>& max_vel = Vector2d<float>(0.0f,0.0f),
        const Vector2d<float>& accel = Vector2d<float>(0.0f,0.0f),
        const Vector2d<float>& decel = Vector2d<float>(0.0f,0.0f), Weapon* wp = nullptr);
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

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
    virtual void setAngle(float angl);
        //Character
        //Combat_Character
    virtual void addWeapon(Weapon* wp);
    virtual void removeWeapon(Weapon* wp);
    virtual void equipWeapon(size_t index);

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
        //Character
        //Combat_Character
    virtual const std::vector<Weapon*>& getWeapons() const;
    virtual Weapon* getWeaponEquipped() const;

    // Destructor
    ~Combat_Character();

protected:

    std::vector<Weapon*> weapons;
    Weapon* equipped;

private:


};

#endif