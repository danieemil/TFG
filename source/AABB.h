#ifndef _AABB_
#define _AABB_

#include "Shape.h"
#include "vector"

class Circle;
class Convex;

class AABB : public Shape
{

public:
    // Constructores
    AABB(const Vector2d<float>& min_rel, const Vector2d<float>& max_rel, Collider* c = nullptr);
    AABB(const AABB& ab);

    AABB& operator= (const AABB& ab);

    // Métodos
    Intersection* intersect(Shape* s) override;
    Intersection* intersect(const Vector2d<float>& a, const Vector2d<float>& b) override;
    Intersection* intersect(AABB* ab);
    Intersection* intersect(Circle* c);
    Intersection* intersect(Convex* c);

    // Setters
    void setCollider(Collider* c) override;
    void setGlobalRotation() override;
    void setLocalRotation(float a) override;

    // Getters
    Collider* getCollider() const override;
    Vector2d<float> getMin() const override;
    Vector2d<float> getMax() const override;
    const Shape_Type& getType() const override;
    float getLocalRotation() const override;
    const Vector2d<float>& getCenter() const override;

    std::vector<Vector2d<float>> getVertices();
    

    // Destructor
    ~AABB();

private:

    Vector2d<float> model_center;
    Vector2d<float> min, max;

    friend class Circle;
    friend class Convex;

};

#endif