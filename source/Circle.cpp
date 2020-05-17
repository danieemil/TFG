#include "Circle.h"
#include "AABB.h"
#include "Collider.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Circle::Circle(const Vector2d<float>& center_rel, const float& radius_rel, Collider* c)
: Shape(c), center(center_rel), radius(radius_rel)
{
    type = Shape_Type::Circle;
}

Circle::Circle(const Circle& ab)
: Shape(ab), center(ab.center), radius(ab.radius)
{
    type = Shape_Type::Circle;
}

Circle& Circle::operator= (const Circle& ab)
{
    Shape::operator=(ab);
    center = ab.center;
    radius = ab.radius;
    type = Shape_Type::Circle;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Intersection* Circle::intersect(Shape* s)
{
    intersection.intersects = false;
    intersection.A = collider;
    intersection.B = s->getCollider();

    if(s!=nullptr)
    {
        if(s->getType()==Shape_Type::AABB)
        {
            return intersect(static_cast<AABB*>(s));
        }
        else if(s->getType()==Shape_Type::Circle)
        {
            return intersect(static_cast<Circle*>(s));
        }
        
    }
    return nullptr;
}

/*
*   (this)  -> collisionable dinámico
*   (ab)     -> collisionable estático
*/
Intersection* Circle::intersect(AABB* ab)
{
    if(collider!=nullptr)
    {
        if(ab!=nullptr)
        {
            Collider* ab_collider = ab->collider;
            if(ab_collider!=nullptr)
            {
                // Detectar Circle vs AABB
                Vector2d<float> ab_pos = ab_collider->getPosition();
                Vector2d<float> ab_min = ab->min + ab_pos;
                Vector2d<float> ab_max = ab->max + ab_pos;

                Vector2d<float> ab_size = ab_max - ab_min;
                Vector2d<float> ab_half = ab_size/2.0f;

                Vector2d<float> ab_center = ab_min + ab_half;
                
                Vector2d<float> position = collider->getPosition();
                Vector2d<float> center_pos = center + position;

                Vector2d<float> distance = center_pos - ab_center;

                float nearDX = clamp(-ab_half.x, ab_half.x, distance.x);
                float nearDY = clamp(-ab_half.y, ab_half.y, distance.y);

                Vector2d<float> nearD = Vector2d<float>(nearDX,nearDY);
                Vector2d<float> near = ab_center + nearD;

                if((near - center_pos).Length() < radius)
                {

                    //Corregir Circle

                    Vector2d<float> dir = Vector2d<float>(sign(distance.x), sign(distance.y));
                    Vector2d<float> pen = distance/(ab_half);

                    pen.x = abs(pen.x);
                    pen.y = abs(pen.y);

                    Vector2d<float> center_fixed = (ab_center + (dir * ab_half));
                    center_fixed.x = center_fixed.x + (radius*dir.x);
                    center_fixed.y = center_fixed.y + (radius*dir.y);

                    if(pen.x > pen.y)
                    {
                        center_fixed.y = center_pos.y;
                    }
                    else if (pen.y > pen.x)
                    {
                        center_fixed.x = center_pos.x;
                    }
                    
                    intersection.fixed_position = center_fixed - center;
                    intersection.intersects = true;
                    intersection.A = collider;
                    intersection.B = ab_collider;
                    intersection.position = position;


                    return &intersection;

                }
            }
        }
    }
    return nullptr;
}

/*
*   (this)  -> collisionable dinámico
*   (c)     -> collisionable estático
*/
Intersection* Circle::intersect(Circle* c)
{
    if(collider!=nullptr)
    {
        if(c!=nullptr)
        {
            Collider* c_collider = c->getCollider();
            if(c_collider!=nullptr)
            {
                // Detectar Circle vs Circle
                Vector2d<float> position = collider->getPosition();
                Vector2d<float> c_position = c_collider->getPosition();
                Vector2d<float> center_pos = center + position;
                Vector2d<float> c_center = c->center + c_position;

                float radius_sum = radius + c->radius;

                Vector2d<float> distance = center_pos - c_center;

                if((distance).Length() < radius_sum)
                {

                    // Corregir Circle
                    Vector2d<float> norm = distance;
                    norm.Normalize();

                    Vector2d<float> fixPos = (c_center + (norm*radius_sum)) - center;

                    intersection.fixed_position = fixPos;
                    intersection.intersects = true;
                    intersection.A = collider;
                    intersection.B = c_collider;
                    intersection.position = position;

                    return &intersection;
                }
            }
        }
    }
    return nullptr;
}

//=========================================
//=               SETTERS   	    	  =
//=========================================

void Circle::setCollider(Collider* c)
{
    Shape::setCollider(c);
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

Collider* Circle::getCollider() const
{
    return Shape::getCollider();
}

Vector2d<float> Circle::getMin() const
{
    return (center - radius);
}

Vector2d<float> Circle::getMax() const
{
    return (center + radius);
}

const Shape_Type& Circle::getType() const
{
    return Shape::getType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Circle::~Circle()
{
    
}