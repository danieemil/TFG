#ifndef _ENTITY_
#define _ENTITY_

#include "Sprite.h"


class World;

class Entity
{

public:
    // Constructores
    Entity(const Entity&);
    Entity(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr);
    Entity(World* w = nullptr, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr);

    Entity& operator= (const Entity&);

    // Métodos
    virtual void render();
    virtual void update();

    // Setters
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);

    // Getters
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;

    // Destructor
    virtual ~Entity();

protected:

    World* world;

    Sprite* sprite;
    Vector2d<float> position;

private:


};

#endif