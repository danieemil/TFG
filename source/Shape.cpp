#include "Shape.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Shape::Shape(Vector2d<float>* pos, Vector2d<float>* prev)
: position(pos), previous_position(prev)
{
    
}

Shape::Shape(const Shape& s)
: position(nullptr), previous_position(nullptr), type(s.type)
{
    
}

Shape& Shape::operator= (const Shape& s)
{
    position = nullptr;
    previous_position = nullptr;
    type = s.type;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Shape::changePosition(const Vector2d<float>& pos)
{
    if(position!=nullptr)
    {
        *position = pos;
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Shape::setPosition(Vector2d<float>* pos)
{
    position = pos;
}

void Shape::setPreviousPosition(Vector2d<float>* prev)
{
    previous_position = prev;
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

Vector2d<float>* Shape::getPosition() const
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