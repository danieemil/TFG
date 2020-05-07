#include "Shape.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Shape::Shape(const Vector2d<float>& pos)
: position(pos)
{
    
}

Shape::Shape(const Shape& s)
: position(s.position), type(s.type)
{
    
}

Shape& Shape::operator= (const Shape& s)
{
    position = s.position;
    type = s.type;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================




//=========================================
//=               SETTERS   	    	  =
//=========================================

void Shape::setPosition(const Vector2d<float>& pos)
{
    position = pos;
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& Shape::getPosition() const
{
    return position;
}

const Shape_Type& Shape::getType() const
{
    return type;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Shape::~Shape()
{
    
}