#include "Convex.h"
#include "AABB.h"
#include "Circle.h"
#include "Collider.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Convex::Convex(const std::vector<Vector2d<float>>& v, Collider* c)
: Shape(c)
{
    vertices = v;
    type = Shape_Type::Convex;

    calculateCenter();

}

Convex::Convex(const Convex& c)
: Shape(c)
{
    vertices = c.vertices;
    type = Shape_Type::Convex;
    calculateCenter();
}

Convex& Convex::operator= (const Convex& c)
{
    Shape::operator=(c);
    vertices = c.vertices;
    type = Shape_Type::Convex;
    calculateCenter();

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Intersection* Convex::intersect(Shape* s)
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
Intersection* Convex::intersect(AABB* ab)
{
    if(collider!=nullptr)
    {
        if(ab!=nullptr)
        {
            Collider* ab_collider = ab->collider;
            if(ab_collider!=nullptr)
            {
                // Detectar Convex vs AABB
                Vector2d<float> pos = collider->getPosition();

                std::vector<Vector2d<float>> ab_vertices = ab->getVertices();
                Vector2d<float> c_pos = ab_collider->getPosition();

                // Calcular posición absoluta de cada uno de los vértices
                std::vector<Vector2d<float>> vertices_pos;
                for (auto &&vertex : vertices)
                {
                    vertices_pos.push_back(vertex + pos);
                }

                std::vector<Vector2d<float>> ab_vertices_pos;
                for (auto &&c_vertex : ab_vertices)
                {
                    ab_vertices_pos.push_back(c_vertex + c_pos);
                }

                float overlap = INFINITY;

                if(overlapping(vertices_pos,ab_vertices_pos, overlap) && overlapping(ab_vertices_pos, vertices_pos, overlap))
                {
                    // Corregir Convex

                    Vector2d<float> center_pos = center + pos;
                    Vector2d<float> c_center_pos = ((ab->max + ab->min)/2.0f) + c_pos;

                    Vector2d<float> d = c_center_pos - center_pos;
                    d.Normalize();

                    Vector2d<float> fix_pos = (center_pos - (d * overlap)) - center;


                    intersection.fixed_position = fix_pos;
                    intersection.intersects = true;
                    intersection.position = pos;
                    intersection.A = collider;
                    intersection.B = ab_collider;

                    return &intersection;
                }

                return nullptr;
            }
        }
    }
    return nullptr;
}

/*
*   (this)  -> collisionable dinámico
*   (c)     -> collisionable estático
*/
Intersection* Convex::intersect(Circle* c)
{
    if(collider!=nullptr)
    {
        if(c!=nullptr)
        {
            Collider* c_collider = c->getCollider();
            if(c_collider!=nullptr)
            {
                // Detectar Convex vs Circle
                Vector2d<float> pos = collider->getPosition();



                Vector2d<float> c_pos = c_collider->getPosition();


                // Corregir Convex

                

                return nullptr;
            }
        }
    }
    return nullptr;
}

/*
*   (this)  -> collisionable dinámico
*   (c)     -> collisionable estático
*/
Intersection* Convex::intersect(Convex* c)
{
    if(collider!=nullptr)
    {
        if(c!=nullptr)
        {
            Collider* c_collider = c->getCollider();
            if(c_collider!=nullptr)
            {
                // Detectar Convex vs Convex
                Vector2d<float> pos = collider->getPosition();

                std::vector<Vector2d<float>> c_vertices = c->vertices;
                Vector2d<float> c_pos = c_collider->getPosition();

                // Calcular posición absoluta de cada uno de los vértices
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

                if(overlapping(vertices_pos,c_vertices_pos, overlap) && overlapping(c_vertices_pos, vertices_pos, overlap))
                {
                    // Corregir Convex

                    Vector2d<float> center_pos = center + pos;
                    Vector2d<float> c_center_pos = c->center + c_pos;

                    Vector2d<float> d = c_center_pos - center_pos;

                    Vector2d<float> fix_pos = (center_pos - ((d * overlap)/d.Length())) - center;


                    intersection.fixed_position = fix_pos;
                    intersection.intersects = true;
                    intersection.position = pos;
                    intersection.A = collider;
                    intersection.B = c_collider;

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

void Convex::setCollider(Collider* c)
{
    Shape::setCollider(c);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Collider* Convex::getCollider() const
{
    return Shape::getCollider();
}

Vector2d<float> Convex::getMin() const
{
    Vector2d<float> min = Vector2d<float>(INFINITY,INFINITY);

    for(auto&& vertex : vertices)
    {
        min.x = std::min(min.x, vertex.x);
        min.y = std::min(min.y, vertex.y);
    }
    
    return min;
}

Vector2d<float> Convex::getMax() const
{
    Vector2d<float> max = Vector2d<float>(-INFINITY,-INFINITY);

    for(auto&& vertex : vertices)
    {
        max.x = std::max(max.x, vertex.x);
        max.y = std::max(max.y, vertex.y);
    }
    
    return max;
}

const Shape_Type& Convex::getType() const
{
    return Shape::getType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Convex::~Convex()
{
    
}


//=========================================
//=                PRIVATE   	    	  =
//=========================================

bool Convex::overlapping(std::vector<Vector2d<float>> v_a, std::vector<Vector2d<float>> v_b, float& overlap)
{
    int v_a_size = (int)v_a.size();
    int v_b_size = (int)v_b.size();

    for(int a = 0; a < v_a_size; a++)
    {
        int b = (a+1) % v_a_size;

        Vector2d<float> n_proj = (v_a[b] - v_a[a]).Normal();

        float min_r1 = INFINITY;
        float max_r1 = -INFINITY;

        for(int p = 0; p < v_a_size; p++)
        {
            float q = v_a[p].DotProduct(n_proj);
            min_r1 = std::min(min_r1, q);
            max_r1 = std::max(max_r1, q);
        }


        float min_r2 = INFINITY;
        float max_r2 = -INFINITY;

        for(int p = 0; p < v_b_size; p++)
        {
            float q = v_b[p].DotProduct(n_proj);
            min_r2 = std::min(min_r2, q);
            max_r2 = std::max(max_r2, q);
        }

        overlap = std::min((std::min(max_r1, max_r2) - std::max(min_r1, min_r2)),overlap);

        if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
        {
            return false;
        }
    }
    return true;
}

void Convex::calculateCenter()
{
    for (auto &&vertex : vertices)
    {
        center+=vertex;
    }
    
    center/=vertices.size();
}