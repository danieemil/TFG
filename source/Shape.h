#ifndef _SHAPE_
#define _SHAPE_

#include "Utilities.h"

using namespace utilities;

class Collider;

class Intersection
{

public:
    // Constructores
    Intersection();
    Intersection(const Intersection& i);

    Intersection& operator= (const Intersection& i);

    //Métodos

    // Setters

    // Getters

    // Destructor
    ~Intersection();

    Collider* A;
    Collider* B;

    Vector2d<float> position;
    Vector2d<float> fixed_position;

    bool intersects;

};



enum class Shape_Type
{
    AABB,
    Circle,
};


class Shape
{

public:
    // Constructores
    Shape(Collider* c = nullptr);
    Shape(const Shape& s);

    Shape& operator= (const Shape& s);

    // Métodos
    virtual Intersection* intersect(Shape* s) = 0;

    // Setters
    virtual void setCollider(Collider* c);

    // Getters
    virtual Collider* getCollider() const;
    virtual Vector2d<float> getMin() const = 0;
    virtual Vector2d<float> getMax() const = 0;
    virtual const Shape_Type& getType() const;

    // Destructor
    virtual ~Shape() = 0;

protected:

    Collider* collider;
    Shape_Type type;
    Intersection intersection;

private:

};

#endif