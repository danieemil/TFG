#ifndef _PLAYER_
#define _PLAYER_

#include "Combat_Character.h"
#include "Unvisual_Engine.h"


class Player : public Combat_Character
{

public:
    // Constructores
    Player(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr,
        Collider* c = nullptr, const Vector2d<float>& max_vel = Vector2d<float>(0.0f,0.0f),
        const Vector2d<float>& accel = Vector2d<float>(0.0f,0.0f),
        const Vector2d<float>& decel = Vector2d<float>(0.0f,0.0f), Weapon* wp = nullptr);
    Player(const Player& p);

    Player& operator= (const Player& p);

    // Métodos
        //Entity
    void render(float rp = 0.0f, const Vector2d<float>& view_pos = Vector2d<float>()) override;
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
    void equipWeapon(size_t index);
        //Player

    // Getters
        //Entity
    Sprite* getSprite() const;
    const Vector2d<float>& getPosition() const;
    World* getWorld() const;
    Collider* getBody() const;
    const Vector2d<float>& getVelocity() const;
    const Vector2d<float>& getPrePosition() const;
    const Vector2d<float>& getRenderPosition() const;
    const Class_Id& getClassId() const;
        //Character
        //Combat_Character
    const std::vector<Weapon*>& getWeapons() const;
    Weapon* getWeaponEquipped() const;
        //Player

    // Destructor
    ~Player();

protected:

private:

    // En qué dirección se está apuntando según las teclas pulsadas
    // X: +1=derecha,   0=No,   -1=izquierda
    // Y: +1=abajo,     0=No,   -1=arriba
    Vector2d<float> heading; 

};

#endif