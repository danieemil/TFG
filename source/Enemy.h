#ifndef _ENEMY_
#define _ENEMY_

#include "Combat_Character.h"
#include "Weapon.h"
#include "vector"


class Enemy : public Combat_Character
{

public:
    // Constructores
    Enemy(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr,
        Collider* c = nullptr, const Vector2d<float>& max_vel = Vector2d<float>(0.0f,0.0f),
        const Vector2d<float>& accel = Vector2d<float>(0.0f,0.0f),
        const Vector2d<float>& decel = Vector2d<float>(0.0f,0.0f), Weapon* wp = nullptr);
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
    virtual void attack();
        //Enemy

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
        //Character
        //Combat_Character
    virtual void addWeapon(Weapon* wp);
    virtual void removeWeapon(Weapon* wp);
    virtual void equipWeapon(size_t index);
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
    virtual const Class_Id& getClassId() const;
        //Character
        //Combat_Character
    virtual const std::vector<Weapon*>& getWeapons() const;
    virtual Weapon* getWeaponEquipped() const;
        //Enemy

    // Destructor
    ~Enemy();

protected:


private:


};

#endif