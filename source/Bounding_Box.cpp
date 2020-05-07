#include "Bounding_Box.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Bounding_Box::Bounding_Box()
{
    
}

Bounding_Box::Bounding_Box(const Vector2d<float>& min_pos, float width, float height) :
min(min_pos),
size(width, height)
{

}

Bounding_Box::Bounding_Box(const Vector2d<float>& min_pos, const Vector2d<float>& max_pos) :
min(min_pos),
size(max_pos.x - min_pos.x, max_pos.y - min_pos.y)
{

}

Bounding_Box::Bounding_Box(const Bounding_Box& bb) :
min(bb.min),
size(bb.size)
{

}

Bounding_Box& Bounding_Box::operator= (const Bounding_Box& bb)
{
    min = bb.min;
    size = bb.size;
    
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

bool Bounding_Box::intersects(const Bounding_Box& bb)
{

    Vector2d<float> m = bb.min;
    Vector2d<float> s = bb.size;

    if (m.x > min.x + size.x || min.x > m.x + s.x)
    {
        return false;
    }

    if (m.y > min.y + size.y || min.y > m.y + s.y)
    {
        return false;
    }
    
    return true;

}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Bounding_Box::setPosition(const Vector2d<float>& min_pos)
{
    min = min_pos;
}

void Bounding_Box::setSize(const Vector2d<float>& bb_size)
{
    size = bb_size;
}

void Bounding_Box::setCenter(const Vector2d<float>& center)
{
    min = Vector2d<float>(center.x - size.x/2.0f, center.y - size.y/2.0f);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& Bounding_Box::getPosition() const
{
    return min;
}

const Vector2d<float>& Bounding_Box::getSize() const
{
    return size;
}

Vector2d<float> Bounding_Box::getCenter() const
{
    return Vector2d<float>(min.x + size.x/2.0f, min.y + size.y/2.0f);
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Bounding_Box::~Bounding_Box()
{
    
}