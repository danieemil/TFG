#ifndef _WEAPON_
#define _WEAPON_

#include "Entity.h"

class Combat_Character;

class Weapon : public Entity
{

public:
    // Constructores
    Weapon(const Weapon&);
    Weapon(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr);
    Weapon(World* w = nullptr, const Vector2d<float>& pos = Vector2d<float>(),
            Sprite* spr = nullptr, Combat_Character* cc = nullptr);

    Weapon& operator= (const Weapon&);

    // Métodos
        //Entity
    virtual void render();
    virtual void update() override;
        //Weapon

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
        //Weapon
    virtual void setCharacter(Combat_Character* cc);

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
        //Weapon
    virtual Combat_Character* getCharacter() const;
    // Destructor
    ~Weapon();

protected:

    Combat_Character* character;

private:

};

#endif