#ifndef _TILE_
#define _TILE_

#include "Entity.h"


class Tile : public Entity
{

public:
    // Constructores
    Tile(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr, Collider* c = nullptr);
    Tile(const Tile& c);

    Tile& operator= (const Tile& c);

    // Métodos
        //Entity
    virtual void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    virtual void update() override;
    virtual void updateFromCollider();
        //Tile

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
    virtual void setBody(Collider* c);
    virtual void setVelocity(const Vector2d<float>& vel);
        //Tile

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
    virtual Collider* getBody() const;
    virtual const Vector2d<float>& getVelocity() const;
    virtual const Vector2d<float>& getPrePosition() const;
        //Tile

    // Destructor
    virtual ~Tile();

protected:


private:

};

#endif