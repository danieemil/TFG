#ifndef _ENTITY_
#define _ENTITY_

#include "Sprite.h"
#include "Physics_Engine.h"


class World;

class Entity
{

public:
    // Constructores
    Entity(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr, Collider* c = nullptr);
    Entity(const Entity& e);

    Entity& operator= (const Entity& e);

    // Métodos
    virtual void render();
    virtual void update();
    virtual void updateFromCollider();

    // Setters
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);

    // Getters
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;

    // Destructor
    virtual ~Entity();

protected:

    World* world;
    Sprite* sprite;
    Vector2d<float> position;
    Collider* body;

private:


};

#endif