#include "Collider.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Collider::Collider(const Vector2d<float>& pos, Shape* s)
: position(pos), previous_position(pos)
{
    if(s!=nullptr)
    {
        addShape(s);
    }
}

Collider::Collider(const Collider& c)
: position(c.position), previous_position(c.previous_position), bounds(c.bounds)
{
    for (auto it = c.shapes.begin(); it!=c.shapes.end(); it++)
    {
        Shape* s = (*it);

        if(s!=nullptr)
        {
            addShape(s);
        }
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
        s->setPosition(&position);
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
bool Collider::intersectShapes(Collider* c)
{
    bool intersects = false;
    if (c!=nullptr)
    {
        for (auto it = shapes.begin(); it!=shapes.end(); it++)
        {
            Shape* sA = (*it);

            for (auto it2 = c->shapes.begin(); it2!=c->shapes.end(); it2++)
            {
                Shape* sB = (*it2);
                if(sA->intersect(sB))
                {
                    intersects = true;
                }
            }
        }
        if(intersects)
        {
            calculateValues();
        }
    }
    return intersects;
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


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& Collider::getPosition() const
{
    return position;
}

const Bounding_Box& Collider::getBounds() const
{
    return bounds;
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