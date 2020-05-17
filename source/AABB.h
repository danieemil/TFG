#ifndef _AABB_
#define _AABB_

#include "Shape.h"

class Circle;

class AABB : public Shape
{

public:
    // Constructores
    AABB(const Vector2d<float>& min_rel, const Vector2d<float>& max_rel, Collider* c = nullptr);
    AABB(const AABB& ab);

    AABB& operator= (const AABB& ab);

    // Métodos
    Intersection* intersect(Shape* s) override;
    Intersection* intersect(AABB* ab);
    Intersection* intersect(Circle* c);

    // Setters
    void setCollider(Collider* c) override;

    // Getters
    Collider* getCollider() const override;
    Vector2d<float> getMin() const override;
    Vector2d<float> getMax() const override;
    const Shape_Type& getType() const override;
    

    // Destructor
    ~AABB();

private:

    Vector2d<float> min, max;

    friend class Circle;

};

#endif