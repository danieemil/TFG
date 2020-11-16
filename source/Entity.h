#ifndef _ENTITY_
#define _ENTITY_

#include "Sprite.h"
#include "Physics_Engine.h"


// Clases que pueden ser instanciadas.
// Se usan en las físicas
enum class EntityType
{
    e_none = -1,
    e_tile,
    e_player,
    e_enemy,
    e_weapon,
    e_exit,
};


class World;

class Entity
{

public:
    // Constructores
    Entity(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
    World* w = nullptr, Collider* c = nullptr, const Vector2d<float>& ori = Vector2d<float>(0,-1));
    Entity(const Entity& e);

    Entity& operator= (const Entity& e);

    // Métodos
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>());
    virtual void update();
    virtual void updateFromCollider();
    virtual void interpolate(float rp = 0.0f);

    virtual void collision(void * ent);

    // Setters
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
    virtual void setAngle(float angl);
    virtual void setOrientation(const Vector2d<float>& ori);

    // Getters
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
    EntityType id;

    float angle;
    Vector2d<float> orientation;


private:


};

#endif