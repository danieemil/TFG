#ifndef _AABB_
#define _AABB_

#include "Shape.h"

class AABB : public Shape
{

public:
    // Constructores
    AABB(const Vector2d<float>& pos, const Vector2d<float>& min_rel, const Vector2d<float>& max_rel);
    AABB(const AABB& ab);

    AABB& operator= (const AABB& ab);

    // Métodos
    bool intersect(Shape* s);
    bool intersect(AABB* ab);

    // Setters
    void setPosition(const Vector2d<float>& pos) override;

    // Getters
    const Vector2d<float>& getPosition() const override;
    const Vector2d<float>& getMin() const override;
    const Vector2d<float>& getMax() const override;
    const Shape_Type& getType() const override;
    

    // Destructor
    ~AABB();

private:

    Vector2d<float> min, max;
    Vector2d<float> min_pos, max_pos;

};

#endif