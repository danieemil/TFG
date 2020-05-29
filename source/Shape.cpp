#include "Shape.h"
#include "Collider.h"

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Intersection::Intersection()
{
    intersects = false;
    A = nullptr;
    B = nullptr;
}

Intersection::Intersection(const Intersection& i)
{
    intersects = i.intersects;
    A = i.A;
    B = i.B;
    position = i.position;
    fixed_position = i.fixed_position;
}

Intersection& Intersection::operator=(const Intersection& i)
{
    intersects = i.intersects;
    A = i.A;
    B = i.B;
    position = i.position;
    fixed_position = i.fixed_position;

    return *this;
}


Shape::Shape(Collider* c, float a)
: collider(c), angle(a)
{
    
}

Shape::Shape(const Shape& s)
: collider(nullptr), type(s.type), intersection(s.intersection), angle(s.angle)
{
    
}

Shape& Shape::operator= (const Shape& s)
{
    collider = nullptr;
    type = s.type;
    intersection = s.intersection;
    angle = s.angle;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================



//=========================================
//=               SETTERS   	    	  =
//=========================================

void Shape::setCollider(Collider* c)
{
    collider = c;
}

void Shape::setLocalRotation(float a)
{
    angle = a;
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

Collider* Shape::getCollider() const
{
    return collider;
}

const Shape_Type& Shape::getType() const
{
    return type;
}

float Shape::getLocalRotation() const
{
    return angle;
}

const Vector2d<float>& Shape::getCenter() const
{
    return center;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Intersection::~Intersection()
{
    
}

Shape::~Shape()
{
    
}