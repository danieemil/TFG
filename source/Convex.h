#ifndef _CONVEX_
#define _CONVEX_

#include "Shape.h"
#include "vector"

class Circle;
class AABB;

class Convex : public Shape
{

public:
    // Constructores
    Convex(const std::vector<Vector2d<float>>& v, Collider* c = nullptr);
    Convex(const Convex& ab);

    Convex& operator= (const Convex& ab);

    // Métodos
    Intersection* intersect(Shape* s) override;
    Intersection* intersect(AABB* ab);
    Intersection* intersect(Circle* c);
    Intersection* intersect(Convex* c);

    // Setters
    void setCollider(Collider* c) override;

    // Getters
    Collider* getCollider() const override;
    Vector2d<float> getMin() const override;
    Vector2d<float> getMax() const override;
    const Shape_Type& getType() const override;
    

    // Destructor
    ~Convex();

private:

    std::vector<Vector2d<float>> vertices;
    Vector2d<float> center;


    bool overlapping(std::vector<Vector2d<float>> a, std::vector<Vector2d<float>> b, float& overlap);
    void calculateCenter();

    friend class Circle;
    friend class AABB;

};

#endif