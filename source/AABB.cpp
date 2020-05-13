#include "AABB.h"
#include "Circle.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

AABB::AABB(const Vector2d<float>& min_rel, const Vector2d<float>& max_rel, Vector2d<float>* pos, Vector2d<float>* prev)
: Shape(pos, prev), min(min_rel), max(max_rel)
{
    type = Shape_Type::AABB;
}

AABB::AABB(const AABB& ab)
: Shape(ab), min(ab.min), max(ab.max)
{
    type = Shape_Type::AABB;
}

AABB& AABB::operator= (const AABB& ab)
{
    Shape::operator=(ab);
    min = ab.min;
    max = ab.max;
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
        if(s->getType()==Shape_Type::Circle)
        {
            return intersect(static_cast<Circle*>(s));
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
    if(position!=nullptr)
    {
        if(ab!=nullptr)
        {
            Vector2d<float>* ab_position = ab->position;
            if(ab_position!=nullptr)
            {
                // Detectar AABB vs AABB
                Vector2d<float> pos = *position;
                Vector2d<float> max_pos = pos + max;
                Vector2d<float> min_pos = pos + min;

                Vector2d<float> ab_pos = *ab_position;
                Vector2d<float> ab_max_pos = ab_pos + ab->max;
                Vector2d<float> ab_min_pos = ab_pos + ab->min;

                Vector2d<float> sizeA = max_pos - min_pos;
                Vector2d<float> sizeB = ab_max_pos - ab_min_pos;
                Vector2d<float> m = ab_min_pos;

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
                Vector2d<float> centerB = (ab_max_pos + ab_min_pos) / 2.0f;

                Vector2d<float> distance = centerA - centerB;

                float px = ((halfB.x + halfA.x) - abs(distance.x))/halfB.x;
                float py = ((halfB.y + halfA.y) - abs(distance.y))/halfB.y;

                float posX = centerA.x;
                float posY = centerA.y;

                // Corregimos en el eje en el que haya menos penetración
                if(px < py)
                {
                    posX = centerB.x + (halfB.x + halfA.x) * float(sign(distance.x));

                }else if (py < px)
                {
                    posY = centerB.y + (halfB.y + halfA.y) * float(sign(distance.y));
                }

                posX = (posX - halfA.x) - min.x;
                posY = (posY - halfA.y) - min.y;

                changePosition(Vector2d<float>(posX, posY));

                return true;
            }
        }
    }
    return false;
}

/*
*   (this)  -> collisionable dinámico
*   (c)     -> collisionable estático
*/
bool AABB::intersect(Circle* c)
{
    if(position!=nullptr)
    {
        if(c!=nullptr)
        {
            Vector2d<float>* c_position = c->position;
            if(c_position!=nullptr)
            {
                // Detectar AABB vs Circle
                Vector2d<float> pos = *position;
                Vector2d<float> min_pos = min + pos;
                Vector2d<float> max_pos = max + pos;

                Vector2d<float> size = max_pos - min_pos;
                Vector2d<float> half = size/2.0f;
                Vector2d<float> center = min_pos + half;

                Vector2d<float> c_pos = *c_position;
                Vector2d<float> c_center = c->center + c_pos;

                float c_radius = c->radius;

                Vector2d<float> distance = center - c_center;

                float nearDX = clamp(-half.x, half.x, distance.x);
                float nearDY = clamp(-half.y, half.y, distance.y);

                Vector2d<float> nearD = Vector2d<float>(nearDX, nearDY);
                Vector2d<float> near = center - nearD;

                Vector2d<float> distance_near = near - c_center;

                float d = distance_near.Length();

                if(d < c_radius)
                {
                    // Corregir AABB
                    Vector2d<float> dir = Vector2d<float>(sign(distance.x), sign(distance.y));
                    Vector2d<float> norm = distance;
                    if(d!=0)
                    {
                        norm = distance_near;
                    }
                    
                    norm.Normalize();
                    
                    Vector2d<float>* prev = previous_position;
                    if(previous_position!=nullptr)
                    {
                        Vector2d<float> vel = pos - *prev;
                    }
                    

                    Vector2d<float> center_fixed = c_center + (norm * c_radius) + (dir * half);
                    
                    changePosition(center_fixed - half - min);
                }

            }
        }
    }
    return false;
}

void AABB::changePosition(const Vector2d<float>& pos)
{
    Shape::changePosition(pos);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void AABB::setPosition(Vector2d<float>* pos)
{
    Shape::setPosition(pos);
}

void AABB::setPreviousPosition(Vector2d<float>* prev)
{
    Shape::setPreviousPosition(prev);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Vector2d<float>* AABB::getPosition() const
{
    return Shape::getPosition();
}

Vector2d<float> AABB::getMin() const
{
    return min;
}

Vector2d<float> AABB::getMax() const
{
    return max;
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