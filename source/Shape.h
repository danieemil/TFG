#ifndef _SHAPE_
#define _SHAPE_

#include "Collider.h"


enum class Shape_Type
{
    AABB,
};


class Shape
{

public:
    // Constructores
    Shape();
    Shape(const Shape& s);

    Shape& operator= (const Shape& s);

    // Métodos
    virtual void intersect(const Shape& s) = 0;

    // Setters

    // Getters
    virtual const Shape_Type& getType() const;

    // Destructor
    virtual ~Shape() = 0;

protected:

    Shape_Type type;

private:

};

#endif