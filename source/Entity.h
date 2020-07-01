#ifndef _ENTITY_
#define _ENTITY_

#include "Sprite.h"
#include "Physics_Engine.h"


// Clases que pueden ser instanciadas.
// Se usan en las físicas
enum class Class_Id
{
    e_none = -1,
    e_tile,
    e_player,
    e_weapon,
    e_enemy,

};


class World;

class Entity
{

public:
    // Constructores
    Entity(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr, Collider* c = nullptr);
    Entity(const Entity& e);

    Entity& operator= (const Entity& e);

    // Métodos
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>());
    virtual void update();
    virtual void updateFromCollider();
    virtual void interpolate(float rp = 0.0f);

    // Setters
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);

    // Getters
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;
    virtual const Vector2d<float>& getVelocity() const;
    virtual const Vector2d<float>& getPrePosition() const;
    virtual const Vector2d<float>& getRenderPosition() const;
    virtual const Class_Id& getClassId() const;

    // Destructor
    virtual ~Entity();

protected:

    World* world;
    Sprite* sprite;
    Vector2d<float> position;
    Vector2d<float> render_position;
    Vector2d<float> pre_position;
    Collider* body;
    Vector2d<float> velocity;
    Class_Id id;


private:


};

#endif