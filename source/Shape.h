#ifndef _SHAPE_
#define _SHAPE_

#include "Utilities.h"
#include "Bounding_Box.h"

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
    Convex,
};


class Shape
{

public:
    // Constructores
    Shape(Collider* c = nullptr, float a = 0.0f);
    Shape(const Shape& s);
    Shape(const Shape* s);

    Shape& operator= (const Shape& s);

    // Métodos
    virtual Intersection* intersect(Shape* s) = 0;
    virtual Intersection* intersect(const Vector2d<float>& a, const Vector2d<float>& b) = 0;

    // Setters
    virtual void setCollider(Collider* c);
    virtual void setGlobalRotation() = 0;
    virtual void setLocalRotation(float a);

    // Getters
    virtual Collider* getCollider() const;
    virtual Vector2d<float> getMin() const = 0;
    virtual Vector2d<float> getMax() const = 0;
    virtual const Shape_Type& getType() const;
    virtual float getLocalRotation() const;
    virtual const Vector2d<float>& getCenter() const;

    // Destructor
    virtual ~Shape() = 0;

protected:

    Collider* collider;
    Shape_Type type;
    Intersection intersection;

    float angle;                     // Ángulo relativo a la rotación de la colisión en general
    Vector2d<float> center;

private:

};


#endif