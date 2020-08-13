#include "Circle.h"
#include "AABB.h"
#include "Convex.h"
#include "Collider.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Circle::Circle(const Vector2d<float>& center_rel, const float& radius_rel, Collider* c)
: Shape(c), model_center(center_rel), radius(radius_rel)
{
    center = model_center;
    type = Shape_Type::Circle;
}

Circle::Circle(const Circle& c)
: Shape(c), model_center(c.model_center), radius(c.radius)
{
    center = c.center;
    type = Shape_Type::Circle;
}

Circle& Circle::operator= (const Circle& c)
{
    Shape::operator=(c);
    model_center = c.model_center;
    center = c.center;
    radius = c.radius;
    type = Shape_Type::Circle;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Intersection* Circle::intersect(Shape* s)
{
    intersection.A = collider;
    intersection.B = s->getCollider();

    Intersection* i = nullptr;

    if(s!=nullptr)
    {
        if(s->getType()==Shape_Type::AABB)
        {
            i = intersect(static_cast<AABB*>(s));
        }
        if(s->getType()==Shape_Type::Circle)
        {
            i = intersect(static_cast<Circle*>(s));
        }
        if (s->getType()==Shape_Type::Convex)
        {
            i = intersect(static_cast<Convex*>(s));
        }
    }

    if(i!=nullptr)
    {
        intersection.intersects = true;
        s->setIntersected(true);
    }

    return i;
}

Intersection* Circle::intersect(const Vector2d<float>& a, const Vector2d<float>& b)
{
    if(collider!=nullptr)
    {
        intersection.A = collider;

        Vector2d<float> position = collider->getPosition();

        Vector2d<float> center_pos = center + position;

        // Comprobamos si algún punto está dentro del círculo
        Vector2d<float> distA = center_pos - a;
        float dA = distA.Length();

        Vector2d<float> distB = center_pos - b;
        float dB = distB.Length();

        if(dA < radius)
        {
            intersection.position = a;
            return &intersection;
        }
        else if (dB < radius)
        {
            intersection.position = b;
            return &intersection;
        }
        


        // Comprobamos si la recta colisiona con el círculo
        Vector2d<float> a_b = b - a;
        Vector2d<float> a_c = center_pos - a;
        float dist_ab = a_b.Length();
        Vector2d<float> dir_ab = a_b;
        dir_ab.Normalize();

        float dist_ap = a_b.DotProduct(a_c)/(dist_ab * dist_ab);

        if(dist_ap >= 0 && dist_ap <= dist_ab)
        {
            Vector2d<float> p = a + (dir_ab*dist_ap);

            Vector2d<float> dist = p - center_pos;
            float d = dist.Length();

            if(d < radius)
            {
                intersection.position = p;
                return &intersection;
            }
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

/*
*   (this)  -> collisionable dinámico
*   (c)     -> collisionable estático
*/
Intersection* Circle::intersect(Convex* c)
{
    if(collider!=nullptr)
    {
        if(c!=nullptr)
        {
            Collider* c_collider = c->getCollider();
            if(c_collider!=nullptr)
            {
                // Detectar Circle vs Convex
                Vector2d<float> pos = collider->getPosition();



                Vector2d<float> c_pos = c_collider->getPosition();


                // Corregir Circle

                

                return nullptr;
            }
        }
    }
    return nullptr;
}

void Circle::update(float dt)
{
    Shape::update(dt);
}

void Circle::render(const Vector2d<float>& view_pos)
{

}

bool Circle::hasIntersected() const
{
    return Shape::hasIntersected();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Circle::setCollider(Collider* c)
{
    Shape::setCollider(c);
}

void Circle::setGlobalRotation()
{
    if(collider!=nullptr)
    {
        float angl = collider->getRotation();
        Vector2d<float> cent = collider->getRotationCenter();
        Vector2d<float> dist = model_center - cent;

        float s = sin(angl);
        float c = cos(angl);

        center.x = dist.x * c - dist.x * s;
        center.y = dist.y * s + dist.y * c;

        center += cent;
    }
}

void Circle::setLocalRotation(float a)
{
    Shape::setLocalRotation(a);
}

void Circle::setIntersected(bool i)
{
    Shape::setIntersected(i);
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

float Circle::getLocalRotation() const
{
    return Shape::getLocalRotation();
}

const Vector2d<float>& Circle::getCenter() const
{
    return Shape::getCenter();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Circle::~Circle()
{
    
}