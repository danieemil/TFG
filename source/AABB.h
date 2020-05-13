#ifndef _AABB_
#define _AABB_

#include "Shape.h"

class Circle;

class AABB : public Shape
{

public:
    // Constructores
    AABB(const Vector2d<float>& min_rel, const Vector2d<float>& max_rel, Vector2d<float>* pos = nullptr, Vector2d<float>* prev = nullptr);
    AABB(const AABB& ab);

    AABB& operator= (const AABB& ab);

    // Métodos
    bool intersect(Shape* s) override;
    bool intersect(AABB* ab);
    bool intersect(Circle* c);

    void changePosition(const Vector2d<float>& pos) override;

    // Setters
    void setPosition(Vector2d<float>* pos) override;
    void setPreviousPosition(Vector2d<float>* prev) override;

    // Getters
    Vector2d<float>* getPosition() const override;
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