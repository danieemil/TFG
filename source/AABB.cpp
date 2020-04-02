#include "AABB.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

AABB::AABB(const Bounding_Box& bb) :
Collider(bb)
{
    type = Collider_Type::AABB;
}

AABB::AABB(const AABB& ab) :
Collider(ab)
{
    type = Collider_Type::AABB;
}

AABB& AABB::operator= (const AABB& ab)
{
    Collider::operator=(ab);
    type = Collider_Type::AABB;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

bool AABB::detect(Collider* c)
{
    if(c!=nullptr)
    {
        if(c->getType()==Collider_Type::AABB)
        {
            return detect(static_cast<AABB*>(c));
        }
    }
    return false;
}

void AABB::intersect(Collider* c)
{
    if(c!=nullptr)
    {
        if(c->getType()==Collider_Type::AABB)
        {
            intersect(static_cast<AABB*>(c));
        }
    }
}

bool AABB::detect(AABB* ab)
{
    if(ab!=nullptr)
    {
        return bounds.intersects(ab->bounds);
    }
    
    return false;
}

/*
*   (this)  -> collisionable dinámico
*   (ab)    -> collisionable estático
*/
void AABB::intersect(AABB* ab)
{
    if(detect(ab))
    {
        Vector2d<float> halfA = bounds.getSize();
        halfA = halfA/2.0f;
        Vector2d<float> halfB = ab->bounds.getSize();
        halfB = halfB/2.0f;
        
        Vector2d<float> centerA = bounds.getCenter();
        Vector2d<float> centerB = ab->bounds.getCenter();

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
        
        setCenter(Vector2d<float>(posX, posY));
    }
}



//=========================================
//=               SETTERS   	    	  =
//=========================================

void AABB::setPosition(const Vector2d<float>& min_pos)
{
    Collider::setPosition(min_pos);
}

void AABB::setSize(const Vector2d<float>& size)
{
    Collider::setSize(size);
}

void AABB::setCenter(const Vector2d<float>& center)
{
    Collider::setCenter(center);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& AABB::getPosition() const
{
    return Collider::getPosition();
}

const Vector2d<float>& AABB::getSize() const
{
    return Collider::getSize();
}

Vector2d<float> AABB::getCenter() const
{
    return Collider::getCenter();
}

const Collider_Type& AABB::getType() const
{
    return Collider::getType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

AABB::~AABB()
{
    
}