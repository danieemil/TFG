#ifndef _WEAPON_
#define _WEAPON_

#include "Entity.h"

class Combat_Character;

class Weapon : public Entity
{

public:
    // Constructores
    Weapon(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
            World* w = nullptr, Collider* c = nullptr, Combat_Character* cc = nullptr);
    Weapon(const Weapon& w);

    Weapon& operator= (const Weapon& w);

    // Métodos
        //Entity
    virtual void render() override;
    virtual void update() override;
    virtual void updateFromCollider();
        //Weapon

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
        //Weapon
    virtual void setCharacter(Combat_Character* cc);

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;
        //Weapon
    virtual Combat_Character* getCharacter() const;
    // Destructor
    ~Weapon();

protected:

    Combat_Character* character;

private:

};

#endif