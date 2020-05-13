#ifndef _SHAPE_
#define _SHAPE_

#include "Utilities.h"

using namespace utilities;

enum class Shape_Type
{
    AABB,
    Circle,
};


class Shape
{

public:
    // Constructores
    Shape(Vector2d<float>* pos = nullptr, Vector2d<float>* prev = nullptr);
    Shape(const Shape& s);

    Shape& operator= (const Shape& s);

    // Métodos
    virtual bool intersect(Shape* s) = 0;

    virtual void changePosition(const Vector2d<float>& pos);

    // Setters
    virtual void setPosition(Vector2d<float>* pos);
    virtual void setPreviousPosition(Vector2d<float>* prev);

    // Getters
    virtual Vector2d<float>* getPosition() const;
    virtual Vector2d<float> getMin() const = 0;
    virtual Vector2d<float> getMax() const = 0;
    virtual const Shape_Type& getType() const;

    // Destructor
    virtual ~Shape() = 0;

protected:

    Vector2d<float>* position;
    Vector2d<float>* previous_position;
    Shape_Type type;

private:

};

#endif