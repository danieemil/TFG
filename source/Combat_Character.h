#ifndef _COMBAT_CHARACTER_
#define _COMBAT_CHARACTER_

#include "Character.h"
#include "Weapon.h"
#include "vector"


class Combat_Character : public Character
{

public:
    // Constructores
    Combat_Character(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr, Collider* c = nullptr, Weapon* wp = nullptr);
    Combat_Character(const Combat_Character& cc);

    Combat_Character& operator= (const Combat_Character& cc);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider();
        //Character
        //Combat_Character

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

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;
    virtual const Vector2d<float>& getVelocity() const;
    virtual const Vector2d<float>& getPrePosition() const;
        //Character
        //Combat_Character
    virtual const std::vector<Weapon*>& getWeapons() const;

    // Destructor
    ~Combat_Character();

protected:

    std::vector<Weapon*> weapons;

private:


};

#endif