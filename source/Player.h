#ifndef _PLAYER_
#define _PLAYER_

#include "Combat_Character.h"
#include "Unvisual_Engine.h"


class Player : public Combat_Character
{

public:
    // Constructores
    Player(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr, Collider* c = nullptr, Weapon* wp = nullptr);
    Player(const Player& p);

    Player& operator= (const Player& p);

    // Métodos
        //Entity
    void render() override;
    void update() override;
    void updateFromCollider();
        //Character
        //Combat_Character
        //Player
    void processInput();

    // Setters
        //Entity
    void setSprite(Sprite* spr);
    void setPosition(const Vector2d<float>& pos);
    void setWorld(World* w);
    void setBody(Collider* c) override;
        //Character
        //Combat_Character
    void addWeapon(Weapon* wp);
        //Player

    // Getters
        //Entity
    Sprite* getSprite() const;
    const Vector2d<float>& getPosition() const;
    World* getWorld() const;
    Collider* getBody() const;
        //Character
        //Combat_Character
    const std::vector<Weapon*>& getWeapons() const;
        //Player

    // Destructor
    ~Player();

protected:

private:


};

#endif