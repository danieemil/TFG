#ifndef _INTERACTABLE_
#define _INTERACTABLE_

#include "Entity.h"


class Interactable : public Entity
{

public:
    // Constructores
    Interactable(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr,
        Collider* c = nullptr, const Vector2d<float>& ori = Vector2d<float>(0.0f, -1.0f));
    Interactable(const Interactable& i);

    Interactable& operator= (const Interactable& i);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider();
    virtual void interpolate(float rp = 0.0f);
        //Interactable

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
    virtual void setAngle(float angl);
    virtual void setOrientation(const Vector2d<float>& ori);
        //Interactable

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
    virtual Vector2d<float> getCenter() const;
    virtual const Vector2d<float>& getOrientation() const;
        //Interactable

    // Destructor
    virtual ~Interactable();

protected:


private:

};

#endif