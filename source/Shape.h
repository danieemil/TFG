#ifndef _SHAPE_
#define _SHAPE_

#include "Utilities.h"

using namespace utilities;

enum class Shape_Type
{
    AABB,
};


class Shape
{

public:
    // Constructores
    Shape(const Vector2d<float>& pos);
    Shape(const Shape& s);

    Shape& operator= (const Shape& s);

    // Métodos
    virtual bool intersect(Shape* s) = 0;

    // Setters
    virtual void setPosition(const Vector2d<float>& pos);

    // Getters
    virtual const Vector2d<float>& getPosition() const;
    virtual const Vector2d<float>& getMin() const = 0;
    virtual const Vector2d<float>& getMax() const = 0;
    virtual const Shape_Type& getType() const;

    // Destructor
    virtual ~Shape() = 0;

protected:

    Vector2d<float> position;
    Shape_Type type;

private:

};

#endif