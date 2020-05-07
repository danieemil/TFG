#include "Collider.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Collider::Collider(Shape* s)
{
    if(s!=nullptr)
    {
        addShape(s);
    }
}

Collider::Collider(const std::vector<Shape*>& s)
{
    shapes = s;
}

Collider::Collider(const Collider& c)
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

bool Collider::intersectBounds(Collider* c)
{
    if(c!=nullptr)
    {
        return bounds.intersects(c->bounds);
    }
    return false;
}

bool Collider::intersectShapes(Collider* c)
{
    bool intersects = false;
    if (c!=nullptr)
    {
        for (auto it = shapes.begin(); it!=shapes.end(); it++)
        {
            Shape* sA = (*it);
            // Si se mueve una figura, se mueven lo mismo las otras
            Vector2d<float> prev_pos = sA->getPosition();

            for (auto it2 = c->shapes.begin(); it2!=c->shapes.end(); it2++)
            {
                Shape* sB = (*it2);
                if(sA->intersect(sB))
                {
                    intersects = true;
                }
            }
            Vector2d<float> motion = sA->getPosition() - prev_pos;
            for(auto it1 = shapes.begin(); it1!=shapes.end();it1++)
            {
                Shape* sA2 = (*it1);

                if(sA!=sA2)
                {
                    sA2->setPosition(sA2->getPosition() + motion);
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
    Vector2d<float> motion = pos - position;

    for (auto it = shapes.begin(); it!=shapes.end(); it++)
    {
        Shape* s = (*it);

        if(s!=nullptr)
        {
            s->setPosition(s->getPosition() + motion);
        }
    }

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

void Collider::calculateValues()
{
    Vector2d<float> min;    // La menor X y la menor Y de todas las figuras
    Vector2d<float> max;    // La mayor X y la mayor Y de todas las figuras
    Vector2d<float> pos;    // Posición intermedia de todas las figuras
    size_t number = 0;

    for(auto it = shapes.begin(); it!=shapes.end(); it++)
    {
        Shape* s = (*it);
        auto smin = s->getMin();
        auto smax = s->getMax();
        auto spos = s->getPosition();

        if(s!=nullptr)
        {
            if(number==0)
            {
                min = smin;
                max = smax;
            }else
            {
                if(min.x > smin.x) min.x = smin.x;
                if(min.y > smin.y) min.y = smin.y;
                if(max.x < smax.x) max.x = smax.x;
                if(max.y < smax.y) max.y = smax.y;
            }
            pos += spos;
            number++;
        }
    }
    if(number>0)
    {
        bounds = Bounding_Box(min, max);
        position = pos / float(number);
    }

}