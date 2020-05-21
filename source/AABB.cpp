#include "AABB.h"
#include "Circle.h"
#include "Convex.h"
#include "Collider.h"
#include "Unvisual_Engine.h"

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

AABB::AABB(const Vector2d<float>& min_rel, const Vector2d<float>& max_rel, Collider* c)
: Shape(c), min(min_rel), max(max_rel)
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

Intersection* AABB::intersect(Shape* s)
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
        if(s->getType()==Shape_Type::Circle)
        {
            return intersect(static_cast<Circle*>(s));
        }
        if (s->getType()==Shape_Type::Convex)
        {
            return intersect(static_cast<Convex*>(s));
        }
    }
    return nullptr;
}

/*
*   (this)  -> collisionable dinámico
*   (ab)    -> collisionable estático
*/
Intersection* AABB::intersect(AABB* ab)
{
    if(collider!=nullptr)
    {
        if(ab!=nullptr)
        {
            Collider* ab_collider = ab->collider;
            if(ab_collider!=nullptr)
            {
                // Detectar AABB vs AABB
                Vector2d<float> pos = collider->getPosition();
                Vector2d<float> max_pos = pos + max;
                Vector2d<float> min_pos = pos + min;

                Vector2d<float> ab_pos = ab_collider->getPosition();
                Vector2d<float> ab_max_pos = ab_pos + ab->max;
                Vector2d<float> ab_min_pos = ab_pos + ab->min;

                Vector2d<float> sizeA = max_pos - min_pos;
                Vector2d<float> sizeB = ab_max_pos - ab_min_pos;
                Vector2d<float> m = ab_min_pos;

                if (m.x > min_pos.x + sizeA.x || min_pos.x > m.x + sizeB.x)
                {
                    return nullptr;
                }

                if (m.y > min_pos.y + sizeA.y || min_pos.y > m.y + sizeB.y)
                {
                    return nullptr;
                }

                

                // Corregir AABB(this) para que no colisione con AABB(ab)
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

                intersection.fixed_position = Vector2d<float>(posX, posY);
                intersection.intersects = true;
                intersection.position = pos;
                intersection.A = collider;
                intersection.B = ab_collider;

                return &intersection;
            }
        }
    }
    return nullptr;
}

/*
*   (this)  -> collisionable dinámico
*   (c)     -> collisionable estático
*/
Intersection* AABB::intersect(Circle* c)
{
    if(collider!=nullptr)
    {
        if(c!=nullptr)
        {
            Collider* c_collider = c->getCollider();
            if(c_collider!=nullptr)
            {
                // Detectar AABB vs Circle
                Vector2d<float> pos = collider->getPosition();
                Vector2d<float> min_pos = min + pos;
                Vector2d<float> max_pos = max + pos;

                Vector2d<float> size = max_pos - min_pos;
                Vector2d<float> half = size/2.0f;
                Vector2d<float> center = min_pos + half;

                Vector2d<float> c_pos = c_collider->getPosition();
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
                    
                    Vector2d<float> prev = collider->getPreviousPosition();
                    Vector2d<float> vel = pos - prev;
                    

                    Vector2d<float> center_fixed = c_center + (norm * c_radius) + (dir * half);
                    
                    intersection.fixed_position = center_fixed - half - min;
                    intersection.intersects = true;
                    intersection.A = collider;
                    intersection.B = c_collider;
                    intersection.position = pos;

                    return &intersection;
                }

            }
        }
    }

    return nullptr;
}

Intersection* AABB::intersect(Convex* c)
{
    if(collider!=nullptr)
    {
        if(c!=nullptr)
        {
            Collider* c_collider = c->collider;
            if(c_collider!=nullptr)
            {
                // Detectar AABB vs Convex
                Vector2d<float> pos = collider->getPosition();

                std::vector<Vector2d<float>> c_vertices = c->vertices;
                std::vector<Vector2d<float>> vertices = getVertices();
                Vector2d<float> c_pos = c_collider->getPosition();

                auto deb = unvisual::debugger;

                // Calcular posición csoluta de cada uno de los vértices
                std::vector<Vector2d<float>> vertices_pos;
                for (auto &&vertex : vertices)
                {
                    vertices_pos.push_back(vertex + pos);
                }

                std::vector<Vector2d<float>> c_vertices_pos;
                for (auto &&c_vertex : c_vertices)
                {
                    c_vertices_pos.push_back(c_vertex + c_pos);
                }

                float overlap = INFINITY;

                if(c->overlapping(vertices_pos,c_vertices_pos, overlap) && c->overlapping(c_vertices_pos, vertices_pos, overlap))
                {
                    // Corregir Convex

                    Vector2d<float> center = (min + max)/2.0f;
                    Vector2d<float> center_pos = center + pos;
                    Vector2d<float> c_center_pos = c->center + c_pos;

                    Vector2d<float> d = c_center_pos - center_pos;
                    d.Normalize();

                    Vector2d<float> fix_pos = center_pos - (d * overlap) - center;
                    

                    intersection.fixed_position = collider->getPreviousPosition();
                    intersection.intersects = true;
                    intersection.position = pos;
                    intersection.A = collider;
                    intersection.B = c_collider;

                    return &intersection;
                }

                return nullptr;
            }
        }
    }
    return nullptr;
}

//=========================================
//=               SETTERS   	    	  =
//=========================================

void AABB::setCollider(Collider* c)
{
    Shape::setCollider(c);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Collider* AABB::getCollider() const
{
    return Shape::getCollider();
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

std::vector<Vector2d<float>> AABB::getVertices()
{
    std::vector<Vector2d<float>> v;

    v.push_back(min);
    v.push_back(Vector2d<float>(max.x, min.y));
    v.push_back(max);
    v.push_back(Vector2d<float>(min.x, max.y));

    return v;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

AABB::~AABB()
{
    
}