#ifndef _COMBAT_CHARACTER_
#define _COMBAT_CHARACTER_

#include "Character.h"
#include "Weapon.h"
#include "vector"


class Combat_Character : public Character
{

public:
    // Constructores
    Combat_Character(const Combat_Character&);
    Combat_Character(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr);
    Combat_Character(World* w = nullptr, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, Weapon* wp = nullptr);

    Combat_Character& operator= (const Combat_Character&);

    // Métodos
        //Entity
    virtual void render();
    virtual void update() override;
        //Character
        //Combat_Character

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
        //Character
        //Combat_Character
    virtual void addWeapon(Weapon* wp);

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
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