#include "Collider.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Collider::Collider(const Bounding_Box& bb) : bounds(bb)
{
    
}

Collider::Collider(const Collider& c) : bounds(c.bounds)
{

}

Collider& Collider::operator= (const Collider& c)
{
    bounds = c.bounds;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================




//=========================================
//=               SETTERS   	    	  =
//=========================================

void Collider::setPosition(const Vector2d<float>& min_pos)
{
    bounds.setPosition(min_pos);
}

void Collider::setSize(const Vector2d<float>& size)
{
    bounds.setSize(size);
}

void Collider::setCenter(const Vector2d<float>& center)
{
    bounds.setCenter(center);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& Collider::getPosition() const
{
    return bounds.getPosition();
}

const Vector2d<float>& Collider::getSize() const
{
    return bounds.getSize();
}

Vector2d<float> Collider::getCenter() const
{
    return bounds.getCenter();
}

const Collider_Type& Collider::getType() const
{
    return type;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Collider::~Collider()
{
    
}