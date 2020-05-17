#ifndef _CIRCLE_
#define _CIRCLE_

#include "Shape.h"



class AABB;



class Circle : public Shape
{

public:
    // Constructores
    Circle(const Vector2d<float>& center_rel, const float& radius_rel, Collider* c = nullptr);
    Circle(const Circle& ab);

    Circle& operator= (const Circle& ab);

    // Métodos
    Intersection* intersect(Shape* s) override;
    Intersection* intersect(AABB* ab);
    Intersection* intersect(Circle* c);

    // Setters
    void setCollider(Collider* pos) override;

    // Getters
    Collider* getCollider() const override;
    Vector2d<float> getMin() const override;
    Vector2d<float> getMax() const override;
    const Shape_Type& getType() const override;
    

    // Destructor
    ~Circle();

private:

    Vector2d<float> center;
    float radius;

    friend class AABB;

};

#endif