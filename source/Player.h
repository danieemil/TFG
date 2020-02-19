#ifndef _PLAYER_
#define _PLAYER_

#include "Combat_Character.h"
#include "InputManager.h"
#include "Unvisual_Engine.h"


class Player : public Combat_Character
{

public:
    // Constructores
    Player(const Player&);
    Player(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr, Weapon* wp = nullptr);

    Player& operator= (const Player&);

    // Métodos
        //Entity
    virtual void render() override;
    virtual void update() override;
        //Character
        //Combat_Character
        //Player
    void processInput();

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
        //Character
        //Combat_Character
    virtual void addWeapon(Weapon* wp);
        //Player

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
        //Character
        //Combat_Character
    virtual const std::vector<Weapon*>& getWeapons() const;
        //Player

    // Destructor
    ~Player();

protected:

private:


};

#endif