#ifndef _AABB_
#define _AABB_

#include "Shape.h"

class AABB : public Shape
{

public:
    // Constructores
    AABB(const Vector2d<float>& min_rel, const Vector2d<float>& max_rel, Vector2d<float>* pos = nullptr);
    AABB(const AABB& ab);

    AABB& operator= (const AABB& ab);

    // Métodos
    bool intersect(Shape* s) override;
    bool intersect(AABB* ab);

    void changePosition(const Vector2d<float>& pos) override;

    // Setters
    void setPosition(Vector2d<float>* pos) override;

    // Getters
    Vector2d<float>* getPosition() const override;
    const Vector2d<float>& getMin() const override;
    const Vector2d<float>& getMax() const override;
    const Shape_Type& getType() const override;
    

    // Destructor
    ~AABB();

private:

    Vector2d<float> min, max;

};

#endif