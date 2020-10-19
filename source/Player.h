#ifndef _PLAYER_
#define _PLAYER_

#include "Combat_Character.h"
#include "Unvisual_Engine.h"


class Player : public Combat_Character
{

public:
    // Constructores
    Player(int l, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
        World* w = nullptr, Collider* c = nullptr,
        const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        const Vector2d<float>& max_vel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& max_accel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& frict = Vector2d<float>(0.0f,0.0f), Weapon* wp = nullptr,
        float st_time = 0.0f);
    Player(const Player& p);

    Player& operator= (const Player& p);

    // Métodos
        //Entity
    void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    void update() override;
    void updateFromCollider() override;
    void interpolate(float rp = 0.0f) override;
    void collision(void * ent) override;
        //Character
        //Combat_Character
    void attack() override;
    void die() override;
        //Player
    void processInput();

    // Setters
        //Entity
    void setSprite(Sprite* spr) override;
    void setPosition(const Vector2d<float>& pos) override;
    void setWorld(World* w) override;
    void setBody(Collider* c) override;
    void setVelocity(const Vector2d<float>& vel) override;
    void setAngle(float angl) override;
    void setOrientation(const Vector2d<float>& ori) override;
        //Character
    void setAcceleration(const Vector2d<float>& accel) override;
    void setFriction(const Vector2d<float>& frict) override;
        //Combat_Character
    void addWeapon(Weapon* wp) override;
    void removeWeapon(Weapon* wp) override;
    void equipWeapon(size_t index) override;
    void setAttacked(bool at) override;
    void setStunned(bool st) override;
    void setLife(int l) override;
    void setMaxLife(int l) override;
        //Player

    // Getters
        //Entity
    Sprite* getSprite() const override;
    const Vector2d<float>& getPosition() const override;
    World* getWorld() const override;
    Collider* getBody() const override;
    const Vector2d<float>& getVelocity() const override;
    const Vector2d<float>& getPrePosition() const override;
    const Vector2d<float>& getRenderPosition() const override;
    const Class_Id& getClassId() const override;
    float getAngle() const override;
    Vector2d<float> getCenter() const override;
    const Vector2d<float>& getOrientation() const override;
        //Character
    const Vector2d<float>& getAcceleration() const override;
        //Combat_Character
    const std::vector<Weapon*>& getWeapons() const override;
    Weapon* getWeaponEquipped() const override;
    bool getAttacking() const override;
    bool getAttacked() const override;
    bool getStunned() const override;
    int getLife() const override;
    int getMaxLife() const override;
        //Player
    const Vector2d<float>& getHeading() const;

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