#ifndef _INTERACTABLE_
#define _INTERACTABLE_

#include "Entity.h"


// Tipos de interactuables instanciables
enum class InteractableType
{
    exit,
    health,
    weapon,
};

class Interactable : public Entity
{

public:
    // Constructores
    Interactable(int val = 0, const Vector2d<float>& pos = Vector2d<float>(),
        Sprite* spr = nullptr, World* w = nullptr, Shape* sh = nullptr,
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
    virtual void manageAnimations() override;
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
    virtual void setValue(int v);

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
    virtual int getValue() const;
    virtual const InteractableType& getInteractableType() const;

    // Destructor
    virtual ~Interactable();

protected:
    int value;
    InteractableType sub_id;

private:

};

#endif