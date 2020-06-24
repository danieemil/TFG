#ifndef _CHARACTER_
#define _CHARACTER_

#include "Entity.h"


class Character : public Entity
{

public:
    // Constructores
    Character(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr,
        Collider* c = nullptr, const Vector2d<float>& max_vel = Vector2d<float>(0.0f,0.0f),
        const Vector2d<float>& accel = Vector2d<float>(0.0f,0.0f),
        const Vector2d<float>& decel = Vector2d<float>(0.0f,0.0f));
    Character(const Character& c);

    Character& operator= (const Character& c);

    // Métodos
        //Entity
    virtual void render(float rp = 0.0f, const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider();
        //Character

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
        //Character

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
        //Character

    // Destructor
    virtual ~Character();

protected:

    Vector2d<float> max_velocity;
    Vector2d<float> max_acceleration;
    Vector2d<float> acceleration;
    Vector2d<float> deceleration;

private:

};

#endif