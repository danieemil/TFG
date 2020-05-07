#include "AABB.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

AABB::AABB(const Vector2d<float>& pos, const Vector2d<float>& min_rel, const Vector2d<float>& max_rel)
: Shape(pos), min(min_rel), max(max_rel), min_pos(pos+min_rel), max_pos(pos+max_rel)
{
    type = Shape_Type::AABB;
}

AABB::AABB(const AABB& ab)
: Shape(ab), min(ab.min), max(ab.max), min_pos(ab.min_pos), max_pos(ab.max_pos)
{
    type = Shape_Type::AABB;
}

AABB& AABB::operator= (const AABB& ab)
{
    Shape::operator=(ab);
    min = ab.min;
    max = ab.max;
    min_pos = ab.min_pos;
    max_pos = ab.max_pos;
    type = Shape_Type::AABB;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

bool AABB::intersect(Shape* s)
{
    if(s!=nullptr)
    {
        if(s->getType()==Shape_Type::AABB)
        {
            return intersect(static_cast<AABB*>(s));
        }
    }
    return false;
}

/*
*   (this)  -> collisionable dinámico
*   (ab)    -> collisionable estático
*/
bool AABB::intersect(AABB* ab)
{
    if(ab!=nullptr)
    {
        // Detectar AABB vs AABB
        Vector2d<float> sizeA = max_pos - min_pos;
        Vector2d<float> sizeB = ab->max_pos - ab->min_pos;
        Vector2d<float> m = ab->min_pos;

        if (m.x > min_pos.x + sizeA.x || min_pos.x > m.x + sizeB.x)
        {
            return false;
        }

        if (m.y > min_pos.y + sizeA.y || min_pos.y > m.y + sizeB.y)
        {
            return false;
        }

        // Corregir AABB(this) para que no colisiones con AABB(ab)
        Vector2d<float> halfA = sizeA/2.0f;
        Vector2d<float> halfB = sizeB/2.0f;

        Vector2d<float> centerA = (max_pos + min_pos) / 2.0f;
        Vector2d<float> centerB = (ab->max_pos + ab->min_pos) / 2.0f;

        Vector2d<float> distance = centerB - centerA;

        float px = (halfB.x + halfA.x) - abs(distance.x);
        float py = (halfB.y + halfA.y) - abs(distance.y);

        float posX = centerA.x;
        float posY = centerA.y;

        // Corregimos en el eje en el que haya menos penetración
        if(px < py)
        {
            posX = centerB.x + (halfB.x + halfA.x) * float(sign(distance.x))*(-1);

        }else
        {
            posY = centerB.y + (halfB.y + halfA.y) * float(sign(distance.y))*(-1);
        }

        posX = (posX - halfA.x) - min.x;
        posY = (posY - halfA.y) - min.y;

        setPosition(Vector2d<float>(posX, posY));

        return true;
    }
    return false;
}



//=========================================
//=               SETTERS   	    	  =
//=========================================

void AABB::setPosition(const Vector2d<float>& pos)
{
    Shape::setPosition(pos);

    min_pos = position + min;
    max_pos = position + max;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& AABB::getPosition() const
{
    return Shape::getPosition();
}

const Vector2d<float>& AABB::getMin() const
{
    return min_pos;
}

const Vector2d<float>& AABB::getMax() const
{
    return max_pos;
}

const Shape_Type& AABB::getType() const
{
    return Shape::getType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

AABB::~AABB()
{
    
}