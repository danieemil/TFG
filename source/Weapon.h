#ifndef _WEAPON_
#define _WEAPON_

#include "Entity.h"

class Combat_Character;

class Weapon : public Entity
{

public:
    // Constructores
    Weapon(int dam, float knock, float t_attack, const Vector2d<float>& rel_attack,
        Sprite* spr = nullptr, World* w = nullptr, Shape* sh = nullptr,
        CollisionFlag type_flag = CollisionFlag::none,
        CollisionFlag interests_flag = CollisionFlag::none,
        const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        Combat_Character* cc = nullptr, Animation* at_anim = nullptr);
    Weapon(const Weapon& w);

    Weapon& operator= (const Weapon& w);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider() override;
    virtual void interpolate(float rp = 0.0f) override;
    virtual void manageAnimations() override;
    virtual void collision(void * ent) override;
        //Weapon
    virtual void attack();

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
    virtual void setAngle(float angl);
    virtual void setOrientation(const Vector2d<float>& ori);
        //Weapon
    virtual void setCharacter(Combat_Character* cc);
    virtual void setRelativePosition(const Vector2d<float>& rl_pos);
    virtual void setAttackingTime(float at_time);
    virtual void setDamage(int dam);
    virtual void setKnockback(float knock);

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;
    virtual const Vector2d<float>& getVelocity() const;
    virtual const Vector2d<float>& getPrePosition() const;
    virtual const Vector2d<float>& getRenderPosition() const;
    virtual const EntityType& getEntityType() const;
    virtual float getAngle() const;
    virtual Vector2d<float> getCenter() const;
    virtual const Vector2d<float>& getOrientation() const;
        //Weapon
    virtual Combat_Character* getCharacter() const;
    virtual const Vector2d<float>& getRelativePosition() const;
    virtual bool getAttacking() const;
    virtual int getDamage() const;
    virtual float getKnockback() const;

    // Destructor
    ~Weapon();

protected:

    Combat_Character* character;
    Vector2d<float> attack_rel_position;

    Vector2d<float> center_rel;

    // Mecánica de atacar
    bool attacking;
    float attack_time;
    Timepoint time_attacking;

    // Atributos del arma
    int damage;
    float knockback;

    // Animación
    Animation* attack_animation;

    void calculateCenter();

private:

};

#endif