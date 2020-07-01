#include "Collider.h"
#include "Physics_Engine.h"


using namespace physics;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Collider::Collider(const Vector2d<float>& pos, Shape* s, const CollisionFlag& f, const CollisionType& t, void* c, int i, float a, const Vector2d<float>& rot_cent, const Vector2d<float>& vel)
: position(pos), previous_position(pos), flags(f), type(t), creator(c), index(i), angle(a), rotation_center(rot_cent), velocity(vel)
{
    if(s!=nullptr)
    {
        addShape(s);
    }

    if(flags != CollisionFlag::none)
    {
        addCollider(this);
    }
    
    if (type == CollisionType::col_static)
    {
        addStatic(this);
        velocity = Vector2d<float>();
    }
    else if (type == CollisionType::col_dynamic)
    {
        addDynamic(this);
    }
    

}

Collider::Collider(const Collider& c)
: position(c.position), previous_position(c.previous_position), bounds(c.bounds), flags(c.flags), creator(nullptr), index(-1), angle(c.angle), rotation_center(c.rotation_center), velocity(c.velocity)
{
    for (auto it = c.shapes.begin(); it!=c.shapes.end(); it++)
    {
        Shape* s = (*it);

        if(s!=nullptr)
        {
            addShape(s);
        }
    }

    if(flags != CollisionFlag::none)
    {
        addCollider(this);
    }
    
    if (type == CollisionType::col_static)
    {
        addStatic(this);
        velocity = Vector2d<float>();
    }
    else if (type == CollisionType::col_dynamic)
    {
        addDynamic(this);
    }

}

Collider& Collider::operator= (const Collider& c)
{
    for (auto it = c.shapes.begin(); it!=c.shapes.end(); it++)
    {
        Shape* s = (*it);

        if(s!=nullptr)
        {
            addShape(s);
        }
    }

    position = c.position;
    previous_position = c.previous_position;
    bounds = c.bounds;
    creator = nullptr;
    index = -1;
    angle = c.angle;
    rotation_center = c.rotation_center;
    velocity = c.velocity;

    setFlags(c.flags);
    setType(c.type);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Collider::addShape(Shape* s)
{
    if(s!=nullptr)
    {
        for(auto it = shapes.begin(); it!=shapes.end(); it++)
        {
            if((*it)==s)
            {
                return;
            }
        }
        shapes.push_back(s);
        s->setCollider(this);
        calculateValues();
    }
}

void Collider::delShape(Shape* s)
{
    if(s!=nullptr)
    {
        for (auto it = shapes.begin(); it!=shapes.end(); it++)
        {
            if((*it)==s)
            {
                delete s;
                shapes.erase(it);
                calculateValues();
                return;
            }
        }
    }
}

// Detecta si los bounds intersectan con los de "c"
bool Collider::intersectBounds(Collider* c)
{
    if(c!=nullptr)
    {
        return bounds.intersects(c->bounds);
    }
    return false;
}

// Detecta y corrige si las figuras(shapes) intersectan con las de "c".
Intersection* Collider::intersectShapes(Collider* c)
{
    if (c!=nullptr)
    {
        for (auto it = shapes.begin(); it!=shapes.end(); it++)
        {
            Shape* sA = (*it);

            for (auto it2 = c->shapes.begin(); it2!=c->shapes.end(); it2++)
            {
                Shape* sB = (*it2);

                Intersection* inter = sA->intersect(sB);

                if(inter!=nullptr)
                {
                    return inter;
                }
            }
        }
    }
    return nullptr;
}

void Collider::intersectFix(Intersection* inter)
{
    if(inter!=nullptr && inter->intersects)
    {
        position = inter->fixed_position;
    }
}

Intersection* Collider::intersectSegment(const Vector2d<float>& a, const Vector2d<float>& b)
{
    if(bounds.intersects(Bounding_Box(Vector2d<float>(std::min(a.x,b.x),std::min(a.y,b.y)),Vector2d<float>(std::max(a.x,b.x),std::max(a.y,b.y)))))
    {
        if(bounds.intersects(a, b))
        {
            Intersection* i = nullptr;

            for (auto &&shape : shapes)
            {
                i = shape->intersect(a, b);

                if(i!=nullptr)
                {
                    return i;
                }
            }
        }
    }
    return nullptr;
}

bool Collider::isStatic() const
{
    return (type == CollisionType::col_static);
}

void Collider::update(float dt)
{
    previous_position = position;
    position = position + velocity * dt;

    calculateValues();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Collider::setPosition(const Vector2d<float>& pos)
{
    previous_position = position;
    position = pos;

    calculateValues();
}

void Collider::setFlags(const CollisionFlag& f)
{

    if(flags != CollisionFlag::none)
    {
        removeCollider(this);
    }

    flags = f;

    if(flags != CollisionFlag::none)
    {
        addCollider(this);
    }

}

void Collider::setType(const CollisionType& t)
{

    if (type == CollisionType::col_static)
    {
        removeStatic(this);
    }
    else if (type == CollisionType::col_dynamic)
    {
        removeDynamic(this);
    }

    type = t;

    if (type == CollisionType::col_static)
    {
        addStatic(this);
        velocity = Vector2d<float>();
    }
    else if (type == CollisionType::col_dynamic)
    {
        addDynamic(this);
    }
}

void Collider::setCreator(void* c)
{
    creator = c;
}

void Collider::setIndex(int i)
{
    index = i;
}

void Collider::setGlobalRotation(float a)
{
    angle = a;
    for (auto &&shape : shapes)
    {
        if (shape!=nullptr)
        {
            shape->setGlobalRotation();
        }
    }
    calculateValues();
}

void Collider::setLocalsRotation(float a)
{
    for (auto &&shape : shapes)
    {
        if (shape!=nullptr)
        {
            shape->setLocalRotation(a);
        }
    }
    calculateValues();
}

void Collider::setRotationCenter(const Vector2d<float>& rot_cent)
{
    rotation_center = rot_cent;
}

void Collider::setVelocity(const Vector2d<float>& vel)
{
    velocity = vel;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& Collider::getPosition() const
{
    return position;
}

const Vector2d<float>& Collider::getPreviousPosition() const
{
    return previous_position;
}

const Bounding_Box& Collider::getBounds() const
{
    return bounds;
}

const CollisionFlag& Collider::getFlags() const
{
    return flags;
}

const CollisionType& Collider::getType() const
{
    return type;
}

void* Collider::getCreator() const
{
    return creator;
}

int Collider::getIndex() const
{
    return index;
}

float Collider::getRotation() const
{
    return angle;
}

const Vector2d<float>& Collider::getRotationCenter() const
{
    return rotation_center;
}

const Vector2d<float>& Collider::getVelocity() const
{
    return velocity;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Collider::~Collider()
{

    auto it = shapes.begin();

    while (it!=shapes.end())
    {
        Shape* s = (*it);
        if(s!=nullptr)
        {
            delete s;
        }
        shapes.erase(it);
    }

    if(flags != CollisionFlag::none)
    {
        removeCollider(this);
    }
    
    if (type == CollisionType::col_static)
    {
        removeStatic(this);
    }
    else if (type == CollisionType::col_dynamic)
    {
        removeDynamic(this);
    }
}


//=========================================
//=               PRIVATE   	    	  =
//=========================================

// Recalcula los datos de la bounding box que contiene a todas las figuras
void Collider::calculateValues()
{
    Vector2d<float> min;    // La menor X y la menor Y de todas las figuras
    Vector2d<float> max;    // La mayor X y la mayor Y de todas las figuras
    bool first = true;

    for(auto it = shapes.begin(); it!=shapes.end(); it++)
    {
        Shape* s = (*it);
        Vector2d<float> smin = s->getMin() + position;
        Vector2d<float> smax = s->getMax() + position;

        if(s!=nullptr)
        {
            if(first)
            {
                min = smin;
                max = smax;
                first = false;
            }else
            {
                if(min.x > smin.x) min.x = smin.x;
                if(min.y > smin.y) min.y = smin.y;
                if(max.x < smax.x) max.x = smax.x;
                if(max.y < smax.y) max.y = smax.y;
            }
        }
    }
    if(!first)
    {
        bounds = Bounding_Box(min, max);
    }

}