#include "Tile.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Tile::Tile(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c,
    const Vector2d<float>& ori)
: Entity(pos, spr, w, c, ori)
{
    if(spr!=nullptr)
    {
        spr->setDepth(-1);
    }

    id = EntityType::e_tile;
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

void Tile::interpolate(float rp)
{
    Entity::interpolate(rp);
}

void Tile::manageAnimations()
{
    Entity::manageAnimations();
}

void Tile::collision(void* ent)
{
    Entity::collision(ent);
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

void Tile::setAngle(float angl)
{
    Entity::setAngle(angl);
}

void Tile::setOrientation(const Vector2d<float>& ori)
{
    Entity::setOrientation(ori);
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

const Vector2d<float>& Tile::getRenderPosition() const
{
    return Entity::getRenderPosition();
}

const EntityType& Tile::getEntityType() const
{
    return Entity::getEntityType();
}

float Tile::getAngle() const
{
    return Entity::getAngle();
}

Vector2d<float> Tile::getCenter() const
{
    return Entity::getCenter();
}

const Vector2d<float>& Tile::getOrientation() const
{
    return Entity::getOrientation();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Tile::~Tile()
{
    
}