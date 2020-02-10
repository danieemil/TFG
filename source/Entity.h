#ifndef _ENTITY_
#define _ENTITY_

#include "Sprite.h"


class World;

class Entity
{

public:
    // Constructores
    Entity();
    Entity(const Entity&);
    Entity(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr);
    Entity(World* w = nullptr, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr);

    Entity& operator= (const Entity&);

    // Métodos
    void render();
    void update();

    // Setters
    void setSprite(Sprite* spr);
    void setPosition(const Vector2d<float>& pos);
    void setWorld(World* w);

    // Getters
    Sprite* getSprite() const;
    const Vector2d<float>& getPosition() const;
    World* getWorld() const;

    // Destructor
    ~Entity();

private:

    World* world;

    Sprite* sprite;
    Vector2d<float> position;



};

#endif