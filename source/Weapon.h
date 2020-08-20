#ifndef _WEAPON_
#define _WEAPON_

#include "Entity.h"

class Combat_Character;

class Weapon : public Entity
{

public:
    // Constructores
    Weapon(float t_attack, const Vector2d<float>& rel_attack, float angl = 0.0f, Sprite* spr = nullptr,
            World* w = nullptr, Collider* c = nullptr, Combat_Character* cc = nullptr);
    Weapon(const Weapon& w);

    Weapon& operator= (const Weapon& w);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider() override;
    virtual void interpolate(float rp = 0.0f) override;
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
        //Weapon
    virtual void setCharacter(Combat_Character* cc);

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;
    virtual const Vector2d<float>& getVelocity() const;
    virtual const Vector2d<float>& getPrePosition() const;
    virtual const Vector2d<float>& getRenderPosition() const;
    virtual const Class_Id& getClassId() const;
    virtual float getAngle() const;
        //Weapon
    virtual Combat_Character* getCharacter() const;
    virtual const Vector2d<float>& getRelativePosition() const;
    // Destructor
    ~Weapon();

protected:

    Combat_Character* character;
    Vector2d<float> attack_rel_position;

    bool attacking;
    float attack_time;
    Timepoint time_attacking;

private:

};

#endif