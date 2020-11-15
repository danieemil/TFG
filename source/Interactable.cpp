#include "Interactable.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Interactable::Interactable(const Vector2d<float>& pos, Sprite* spr, World* w,
    CollisionFlag type_flag, CollisionFlag interests_flag, const Vector2d<float>& ori)
: Entity(pos, spr, w, new Collider(pos, physics::getSpriteShape(spr), type_flag, interests_flag, CollisionType::col_none), ori)
{
    
}

Interactable::Interactable(const Interactable& i)
: Entity(i)
{

}

Interactable& Interactable::operator= (const Interactable& i)
{
    this->Entity::operator=(i);

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Interactable::render(const Vector2d<float>& view_pos)
{
    Entity::render(view_pos);
}

void Interactable::update()
{
    Entity::update();
}

void Interactable::updateFromCollider()
{
    Entity::updateFromCollider();
}

void Interactable::interpolate(float rp)
{
    Entity::interpolate(rp);
}

void Interactable::collision(void * ent)
{
    Entity::collision(ent);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Interactable::setSprite(Sprite* spr)
{
    Entity::setSprite(spr);
}

void Interactable::setPosition(const Vector2d<float>& pos)
{
    Entity::setPosition(pos);
}

void Interactable::setWorld(World* w)
{
    Entity::setWorld(w);
}

void Interactable::setBody(Collider* c)
{
    Entity::setBody(c);
}

void Interactable::setVelocity(const Vector2d<float>& vel)
{
    Entity::setVelocity(vel);
}

void Interactable::setAngle(float angl)
{
    Entity::setAngle(angl);
}

void Interactable::setOrientation(const Vector2d<float>& ori)
{
    Entity::setOrientation(ori);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Interactable::getSprite() const
{
    return Entity::getSprite();
}

const Vector2d<float>& Interactable::getPosition() const
{
    return Entity::getPosition();
}

World* Interactable::getWorld() const
{
    return Entity::getWorld();
}

Collider* Interactable::getBody() const
{
    return Entity::getBody();
}

const Vector2d<float>& Interactable::getVelocity() const
{
    return Entity::getVelocity();
}

const Vector2d<float>& Interactable::getPrePosition() const
{
    return Entity::getPrePosition();
}

const Vector2d<float>& Interactable::getRenderPosition() const
{
    return Entity::getRenderPosition();
}

const EntityType& Interactable::getEntityType() const
{
    return Entity::getEntityType();
}

float Interactable::getAngle() const
{
    return Entity::getAngle();
}

Vector2d<float> Interactable::getCenter() const
{
    return Entity::getCenter();
}

const Vector2d<float>& Interactable::getOrientation() const
{
    return Entity::getOrientation();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Interactable::~Interactable()
{
    
}