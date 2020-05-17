#include "Tile.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Tile::Tile(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c)
: Entity(pos, spr, w, c)
{
    if(spr!=nullptr)
    {
        spr->setDepth(-1);
    }
}

Tile::Tile(const Tile& c)
: Entity(c)
{

}

Tile& Tile::operator= (const Tile& c)
{
    this->Entity::operator=(c);

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Tile::render(const Vector2d<float>& view_pos)
{
    Entity::render(view_pos);
}

void Tile::update()
{
    Entity::update();   
}

void Tile::updateFromCollider()
{
    Entity::updateFromCollider();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Tile::setSprite(Sprite* spr)
{
    Entity::setSprite(spr);
}

void Tile::setPosition(const Vector2d<float>& pos)
{
    Entity::setPosition(pos);
}

void Tile::setWorld(World* w)
{
    Entity::setWorld(w);
}

void Tile::setBody(Collider* c)
{
    Entity::setBody(c);
}

void Tile::setVelocity(const Vector2d<float>& vel)
{
    Entity::setVelocity(vel);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Tile::getSprite() const
{
    return Entity::getSprite();
}

const Vector2d<float>& Tile::getPosition() const
{
    return Entity::getPosition();
}

World* Tile::getWorld() const
{
    return Entity::getWorld();
}

Collider* Tile::getBody() const
{
    return Entity::getBody();
}

const Vector2d<float>& Tile::getVelocity() const
{
    return Entity::getVelocity();
}

const Vector2d<float>& Tile::getPrePosition() const
{
    return Entity::getPrePosition();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Tile::~Tile()
{
    
}