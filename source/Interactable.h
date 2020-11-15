#ifndef _INTERACTABLE_
#define _INTERACTABLE_

#include "Entity.h"


class Interactable : public Entity
{

public:
    // Constructores
    Interactable(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
        World* w = nullptr, CollisionFlag type_flag = CollisionFlag::none,
        CollisionFlag interests_flag = CollisionFlag::none,
        const Vector2d<float>& ori = Vector2d<float>(0.0f, -1.0f));
    Interactable(const Interactable& i);

    Interactable& operator= (const Interactable& i);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider() override;
    virtual void interpolate(float rp = 0.0f) override;

    virtual void collision(void * ent) override;
        //Interactable

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr) override;
    virtual void setPosition(const Vector2d<float>& pos) override;
    virtual void setWorld(World* w) override;
    virtual void setBody(Collider* c) override;
    virtual void setVelocity(const Vector2d<float>& vel) override;
    virtual void setAngle(float angl) override;
    virtual void setOrientation(const Vector2d<float>& ori) override;
        //Interactable

    // Getters
        //Entity
    virtual Sprite* getSprite() const override;
    virtual const Vector2d<float>& getPosition() const override;
    virtual World* getWorld() const override;
    virtual Collider* getBody() const override;
    virtual const Vector2d<float>& getVelocity() const override;
    virtual const Vector2d<float>& getPrePosition() const override;
    virtual const Vector2d<float>& getRenderPosition() const override;
    virtual const EntityType& getEntityType() const override;
    virtual float getAngle() const override;
    virtual Vector2d<float> getCenter() const override;
    virtual const Vector2d<float>& getOrientation() const override;
        //Interactable

    // Destructor
    virtual ~Interactable();

protected:


private:

};

#endif