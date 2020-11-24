#ifndef _PICKAXE_
#define _PICKAXE_

#include "Weapon.h"


class Pickaxe : public Weapon
{

public:
    // Constructores
    Pickaxe(int dam, float knock, float t_attack, const Vector2d<float>& rel_attack,
        Sprite* spr = nullptr, World* w = nullptr, Shape* sh = nullptr,
        CollisionFlag type_flag = CollisionFlag::none,
        CollisionFlag interests_flag = CollisionFlag::none,
        const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        Combat_Character* cc = nullptr, Animation* at_anim = nullptr);
    Pickaxe(const Pickaxe& p);

    Pickaxe& operator= (const Pickaxe& p);

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
        //Pickaxe

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
        //Pickaxe

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
        //Pickaxe

    // Destructor
    ~Pickaxe();

protected:

    void calculateCenter() override;

private:

};

#endif