#include "Convex.h"
#include "AABB.h"
#include "Circle.h"
#include "Collider.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Convex::Convex(const std::vector<Vector2d<float>>& v, Collider* c)
: Shape(c)
{
    model_vertices = v;
    rotated_vertices = model_vertices;
    type = Shape_Type::Convex;
    angle = 0;

    calculateRotation();

}

Convex::Convex(const Convex& c)
: Shape(c)
{
    model_vertices = c.model_vertices;
    rotated_vertices = c.rotated_vertices;
    type = Shape_Type::Convex;
    angle = c.angle;

    calculateRotation();
}

Convex& Convex::operator= (const Convex& c)
{
    Shape::operator=(c);
    model_vertices = c.model_vertices;
    rotated_vertices = c.rotated_vertices;
    type = Shape_Type::Convex;
    angle = c.angle;

    calculateRotation();

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Intersection* Convex::intersect(Shape* s)
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

Intersection* Convex::intersect(const Vector2d<float>& a, const Vector2d<float>& b)
{
    if(collider!=nullptr)
    {
        intersection.A = collider;

        bool inters, intersects = false;
        int intersections = 0;

        Vector2d<float> pos = b;
        float dist = (b - a).Length();

        Vector2d<float> p;

        Vector2d<float> position = collider->getPosition();

        size_t s_vertices = rotated_vertices.size();

        for (size_t c = 0; c < s_vertices; c++)
        {
            size_t d = (c + 1) % s_vertices;

            p = segmentsIntersection(a, b, rotated_vertices[c] + position, rotated_vertices[d] + position, inters);
            if(inters)
            {
                intersections++;
                intersects = true;
                float dif = (p - a).Length();
                if(dif < dist)
                {
                    dist = dif;
                    pos = p;
                }
                intersection.position = pos;
                if(intersections==2)
                {
                    return &intersection;
                }
            }
        }

        if(intersects)
        {
            return &intersection;
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
                Vector2d<float> ab_pos = ab_collider->getPosition();

                // Calcular posición absoluta de cada uno de los vértices
                std::vector<Vector2d<float>> vertices_pos;
                for (auto &&vertex : rotated_vertices)
                {
                    vertices_pos.push_back(vertex + pos);
                }

                std::vector<Vector2d<float>> ab_vertices_pos;
                for (auto &&ab_vertex : ab_vertices)
                {
                    ab_vertices_pos.push_back(ab_vertex + ab_pos);
                }

                float overlap = INFINITY;
                Vector2d<float> overlap_dir;

                if(overlapping(vertices_pos,ab_vertices_pos, overlap, overlap_dir) &&
                    overlapping(ab_vertices_pos, vertices_pos, overlap, overlap_dir))
                {
                    // Corregir Convex

                    Vector2d<float> center_pos = center + pos;
                    Vector2d<float> ab_center_pos = ((ab->max + ab->min)/2.0f) +ab_pos;

                    Vector2d<float> d = center_pos - ab_center_pos;
                    
                    float sX = sign(d.x);
                    float sY = sign(d.y);
                    if(!sX) sign(overlap_dir.x);
                    if(!sY) sign(overlap_dir.y);

                    overlap_dir.x = abs(overlap_dir.x) * sX;
                    overlap_dir.y = abs(overlap_dir.y) * sY;

                    intersection.overlap = overlap_dir * overlap;

                    Vector2d<float> fix_pos = center_pos + (intersection.overlap) - center;

                    intersection.fixed_position = fix_pos;
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
                Vector2d<float> center_pos = center + pos;

                Vector2d<float> c_pos = c_collider->getPosition();
                Vector2d<float> c_center_pos = c->center + c_pos;
                float c_radius = c->radius;

                // Calcular posición absoluta de cada uno de los vértices
                std::vector<Vector2d<float>> vertices_pos;
                for (auto &&vertex : rotated_vertices)
                {
                    vertices_pos.push_back(vertex + pos);
                }

                float overlap = -INFINITY;
                Vector2d<float> dir_overlap;

                // Comprobamos si algún punto está dentro del círculo
                for(auto &&vertex : vertices_pos)
                {
                    Vector2d<float> dist = c_center_pos - vertex;
                    float d = dist.Length();

                    if(d < c_radius)
                    {
                        float o = c_radius - d;
                        if(overlap < o)
                        {
                            overlap = o;
                            dir_overlap = vertex - c_center_pos;
                            dir_overlap.Normalize();
                        }
                    }
                }

                // Comprobamos si alguna recta colisiona con el círculo
                for (size_t a = 0; a < vertices_pos.size(); a++)
                {
                    size_t b = (a + 1) % vertices_pos.size();

                    Vector2d<float> a_b = vertices_pos[b] - vertices_pos[a];
                    Vector2d<float> a_c = c_center_pos - vertices_pos[a];
                    float dist_ab = a_b.Length();
                    Vector2d<float> dir_ab = a_b;
                    dir_ab.Normalize();

                    float dist_ap = a_b.DotProduct(a_c)/pow(dist_ab,2);

                    if(dist_ap >= 0 && dist_ap <= dist_ab)
                    {
                        Vector2d<float> p = vertices_pos[a] + (dir_ab*dist_ap);

                        Vector2d<float> dist = p - c_center_pos;
                        float d = dist.Length();

                        if(d < c_radius)
                        {
                            float dif = c_radius - d;
                            if(dif > overlap)
                            {
                                overlap = dif;
                                dir_overlap = dist;
                                dir_overlap.Normalize();
                            }
                        }
                    }
                }

                if(overlap != -INFINITY)
                {
                    // Corregir Convex

                    Vector2d<float> dir = center_pos - c_center_pos;
                    dir.Normalize();

                    if(!(dir_overlap==Vector2d<float>()))
                    {
                        dir = dir_overlap;
                    }

                    intersection.overlap = dir * overlap;

                    Vector2d<float> fix_pos = center_pos + (intersection.overlap) - center;


                    intersection.fixed_position = fix_pos;
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

                std::vector<Vector2d<float>> c_vertices = c->rotated_vertices;
                Vector2d<float> c_pos = c_collider->getPosition();

                // Calcular posición absoluta de cada uno de los vértices
                std::vector<Vector2d<float>> vertices_pos;
                for (auto &&vertex : rotated_vertices)
                {
                    vertices_pos.push_back(vertex + pos);
                }

                std::vector<Vector2d<float>> c_vertices_pos;
                for (auto &&c_vertex : c_vertices)
                {
                    c_vertices_pos.push_back(c_vertex + c_pos);
                }

                float overlap = INFINITY;
                float overlap1 = overlap;
                float overlap2 = overlap;
                Vector2d<float> overlap_dir;
                Vector2d<float> overlap_dir1;
                Vector2d<float> overlap_dir2;

                if(overlapping(vertices_pos,c_vertices_pos, overlap1, overlap_dir1)&&
                    overlapping(c_vertices_pos, vertices_pos, overlap2, overlap_dir2))
                {
                    // Corregir Convex

                    overlap = overlap2;
                    overlap_dir = overlap_dir2;

                    if(overlap1<=overlap2)
                    {
                        overlap = overlap1;
                        overlap_dir = overlap_dir1 * (-1);
                    }

                    Vector2d<float> center_pos = center + pos;
                    Vector2d<float> center_prev = center + collider->getPreviousPosition();
                    Vector2d<float> c_center_pos = c->center + c_pos;

                    Vector2d<float> d = center_prev - center_pos;

                    intersection.overlap = overlap_dir * overlap;

                    Vector2d<float> fix_pos = center_pos - (intersection.overlap) - center;


                    intersection.fixed_position = fix_pos;
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

void Convex::update(float dt)
{
    Shape::update(dt);
}

void Convex::render(const Vector2d<float>& view_pos)
{
    Shape::render(view_pos);
}

bool Convex::hasIntersected() const
{
    return Shape::hasIntersected();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Convex::setCollider(Collider* c)
{
    Shape::setCollider(c);
}

void Convex::setGlobalRotation()
{
    calculateRotation();
}

void Convex::setLocalRotation(float a)
{
    angle = a;
    calculateRotation();

}

void Convex::setIntersected(bool i)
{
    Shape::setIntersected(i);
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

    for(auto&& vertex : rotated_vertices)
    {
        min.x = std::min(min.x, vertex.x);
        min.y = std::min(min.y, vertex.y);
    }
    
    return min;
}

Vector2d<float> Convex::getMax() const
{
    Vector2d<float> max = Vector2d<float>(-INFINITY,-INFINITY);

    for(auto&& vertex : rotated_vertices)
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

float Convex::getLocalRotation() const
{
    return Shape::getLocalRotation();
}

const Vector2d<float>& Convex::getCenter() const
{
    return Shape::getCenter();
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

bool Convex::overlapping(std::vector<Vector2d<float>> v_a, std::vector<Vector2d<float>> v_b, float& overlap, Vector2d<float>& overlap_dir)
{
    int v_a_size = (int)v_a.size();
    int v_b_size = (int)v_b.size();

    float prev_overlap, cur_overlap;
    float near = INFINITY;

    for(int a = 0; a < v_a_size; a++)
    {
        int b = (a+1) % v_a_size;

        Vector2d<float> n_proj = (v_a[b] - v_a[a]).Normal();
        n_proj.Normalize();

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

        cur_overlap = std::min(max_r1, max_r2) - std::max(min_r1, min_r2);

        prev_overlap = std::min(cur_overlap,overlap);

        if(prev_overlap <= overlap)
        {
            if(cur_overlap == overlap)
            {
                // Cuál de las dos proyecciones está más cerca
                float near2 = (v_a[b] - v_b[0]).Length() + (v_a[a] - v_b[0]).Length();

                if(near>near2)
                {
                    near = near2;
                    overlap_dir = n_proj;
                }
            }else if(cur_overlap < overlap)
            {
                near = (v_a[b] - v_b[0]).Length() + (v_a[a] - v_b[0]).Length();
                overlap_dir = n_proj;
                overlap = prev_overlap;
            }
            
        }

        if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
        {
            return false;
        }
    }
    return true;
}

// No se usa
bool Convex::circleOverlapping(std::vector<Vector2d<float>> v_a, std::vector<Vector2d<float>> v_b, float& overlap)
{
    int v_a_size = (int)v_a.size();
    int v_b_size = (int)v_b.size();

    for(int a = 0; a < v_a_size; a++)
    {
        int b = (a+1) % v_a_size;

        Vector2d<float> n_proj = (v_a[b] - v_a[a]).Normal();
        n_proj.Normalize();

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

        overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2),overlap);

        if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
        {
            return false;
        }
        a++;
    }
    return true;
}

void Convex::calculateCenter()
{
    for (auto &&vertex : rotated_vertices)
    {
        center += vertex;
    }
    
    center /= rotated_vertices.size();
}

void Convex::calculateRotation()
{

    if(collider!=nullptr)
    {
        float d = collider->getRotation();

        Vector2d<float> cent = collider->getRotationCenter();

        float s = sin(d);
        float c = cos(d);

        for (size_t v = 0; v!=model_vertices.size(); v++)
        {

            Vector2d<float> vertex = model_vertices[v];

            Vector2d<float> c_dist = vertex - cent;

            Vector2d<float> n_vertex;
            n_vertex.x = c_dist.x * c - c_dist.y * s;
            n_vertex.y = c_dist.x * s + c_dist.y * c;

            rotated_vertices[v] = n_vertex + cent;
        }
    }
    
    calculateCenter();

    return;

    float s = sin(angle);
    float c = cos(angle);

    for (size_t v = 0; v!=rotated_vertices.size(); v++)
    {

        Vector2d<float> vertex = rotated_vertices[v];

        Vector2d<float> c_dist = vertex - center;

        Vector2d<float> n_vertex;
        n_vertex.x = c_dist.x * c - c_dist.y * s;
        n_vertex.y = c_dist.x * s + c_dist.y * c;

        rotated_vertices[v] = n_vertex + center;
    }
}