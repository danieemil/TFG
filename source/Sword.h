#ifndef _SWORD_
#define _SWORD_

#include "Weapon.h"


class Sword : public Weapon
{

public:
    // Constructores
    Sword(int dam, float knock, float t_attack, const Vector2d<float>& rel_attack,
        float t_pre_attack = 0.0f, float t_end_attack = 0.0f,
        Sprite* spr = nullptr, World* w = nullptr, Shape* sh = nullptr,
        CollisionFlag type_flag = CollisionFlag::none,
        CollisionFlag interests_flag = CollisionFlag::none,
        const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        Combat_Character* cc = nullptr, Animation* at_anim = nullptr);
    Sword(const Sword& s);

    Sword& operator= (const Sword& s);

    // Métodos
        //Entity
    void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    void update() override;
    void updateFromCollider() override;
    void interpolate(float rp = 0.0f) override;
    void manageAnimations() override;
    void collision(void * ent) override;
        //Weapon
    void attack() override;
    void cancelAttack() override;
        //Sword

    // Setters
        //Entity
    void setSprite(Sprite* spr) override;
    void setPosition(const Vector2d<float>& pos) override;
    void setWorld(World* w) override;
    void setBody(Collider* c) override;
    void setVelocity(const Vector2d<float>& vel) override;
    void setAngle(float angl) override;
    void setOrientation(const Vector2d<float>& ori) override;
        //Weapon
    void setCharacter(Combat_Character* cc) override;
    void setRelativePosition(const Vector2d<float>& rl_pos) override;
    void setAttackingTime(float at_time) override;
    void setDamage(int dam) override;
    void setKnockback(float knock) override;
        //Sword

    // Getters
        //Entity
    Sprite* getSprite() const override;
    const Vector2d<float>& getPosition() const override;
    World* getWorld() const override;
    Collider* getBody() const override;
    const Vector2d<float>& getVelocity() const override;
    const Vector2d<float>& getPrePosition() const override;
    const Vector2d<float>& getRenderPosition() const override;
    const EntityType& getEntityType() const override;
    float getAngle() const override;
    Vector2d<float> getCenter() const override;
    const Vector2d<float>& getOrientation() const override;
        //Weapon
    Combat_Character* getCharacter() const override;
    const Vector2d<float>& getRelativePosition() const override;
    bool getAttacking() const override;
    int getDamage() const override;
    float getKnockback() const override;
    const WeaponType& getWeaponType() const override;
        //Sword

    // Destructor
    ~Sword();

protected:

    void calculateCenter() override;

private:

};

#endif