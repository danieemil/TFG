#ifndef _CHARACTER_
#define _CHARACTER_

#include "Entity.h"


class Character : public Entity
{

public:
    // Constructores
    Character(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
        World* w = nullptr, Shape* sh = nullptr, CollisionFlag type_flag = CollisionFlag::none,
        CollisionFlag interests_flag = CollisionFlag::none,
        const Vector2d<float>& ori = Vector2d<float>(0.0f,-1.0f),
        const Vector2d<float>& max_vel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& max_accel = Vector2d<float>(INFINITY,INFINITY),
        const Vector2d<float>& frict = Vector2d<float>(0.0f,0.0f));
    Character(const Character& c);

    Character& operator= (const Character& c);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider() override;
    virtual void interpolate(float rp = 0.0f) override;
    virtual void manageAnimations() override;
    virtual void collision(void * ent) override;
        //Character

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
    virtual void setAngle(float angl);
    virtual void setOrientation(const Vector2d<float>& ori);
        //Character
    virtual void setAcceleration(const Vector2d<float>& accel);
    virtual void setFriction(const Vector2d<float>& frict);

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
        //Character
    virtual const Vector2d<float>& getAcceleration() const;

    // Destructor
    virtual ~Character();

protected:

    Vector2d<float> acceleration;

private:

};

#endif