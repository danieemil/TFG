#include "Bounding_Box.h"
#include "Unvisual_Engine.h"


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

bool Bounding_Box::intersects(const Vector2d<float>& a, const Vector2d<float>& b)
{

    // True=El segmento AB itersecta con alguna parte del contorno(Arriba, derecha, abajo, izquierda)

    bool intersection = false;

    Vector2d<float> ard = Vector2d<float>(min.x + size.x, min.y);
    Vector2d<float> abd = min + size;
    Vector2d<float> abi = Vector2d<float>(min.x, min.y + size.y);


    // Comprobar arriba
    segmentsIntersection(a,b,min, ard, intersection);
    if(intersection) return true;

    // Comprobar derecha
    segmentsIntersection(a,b,ard,abd, intersection);
    if(intersection) return true;

    // Comprobar abajo
    segmentsIntersection(a,b,abd,abi, intersection);
    if(intersection) return true;

    // Comprobar izquierda
    segmentsIntersection(a,b,abi,min, intersection);
    if(intersection) return true;

    return false;
}

void Bounding_Box::render(const Vector2d<float>& view_pos)
{
    unvisual::drawRectangle(min - view_pos, 0.0f, size, 0, 255, 0, 100);
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
    return min + (size/2.0f);
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Bounding_Box::~Bounding_Box()
{
    
}




// Comprueba en qué punto intersectan AB y CD. Además detecta si ese punto está en ambos segmentos
Vector2d<float> segmentsIntersection(const Vector2d<float>& a, const Vector2d<float>& b, const Vector2d<float> c, const Vector2d<float> d, bool& between)
{
    between = false;
    Vector2d<float> point;

    Vector2d<float> ab = b - a;
    Vector2d<float> cd = d - c;
    Vector2d<float> ca = a - c;

    float ab_cd = ab.CrossProduct(cd);

    float pAB = ca.CrossProduct(cd) / ab_cd;
    float pCD = ca.CrossProduct(ab) / ab_cd;

    point = a + (ab * pAB);

    if (pAB >= 0.0f && pAB <= 1.0f && pCD >= 0.0f && pCD <= 1.0f)
    {
        between = true;
    }

    return point;

}