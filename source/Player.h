#ifndef _PLAYER_
#define _PLAYER_

#include "Combat_Character.h"
#include "Unvisual_Engine.h"


class Player : public Combat_Character
{

public:
    // Constructores
    Player(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr,
    Collider* c = nullptr, Weapon* wp = nullptr, const Vector2d<float>& maxvel = Vector2d<float>(2,2));
    Player(const Player& p);

    Player& operator= (const Player& p);

    // Métodos
        //Entity
    void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
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
    void setVelocity(const Vector2d<float>& vel);
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
    const Vector2d<float>& getVelocity() const;
    const Vector2d<float>& getPrePosition() const;
        //Character
        //Combat_Character
    const std::vector<Weapon*>& getWeapons() const;
        //Player

    // Destructor
    ~Player();

protected:

private:

    Vector2d<float> max_velocity;

};

#endif