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


Shape::Shape(Collider* c)
: collider(c)
{
    
}

Shape::Shape(const Shape& s)
: collider(nullptr), type(s.type)
{
    
}

Shape& Shape::operator= (const Shape& s)
{
    collider = nullptr;
    type = s.type;

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


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Intersection::~Intersection()
{
    
}

Shape::~Shape()
{
    
}