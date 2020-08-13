#ifndef _CIRCLE_
#define _CIRCLE_

#include "Shape.h"



class AABB;
class Convex;



class Circle : public Shape
{

public:
    // Constructores
    Circle(const Vector2d<float>& center_rel, const float& radius_rel, Collider* c = nullptr);
    Circle(const Circle& ab);

    Circle& operator= (const Circle& ab);

    // Métodos
    Intersection* intersect(Shape* s) override;
    Intersection* intersect(const Vector2d<float>& a, const Vector2d<float>& b) override;
    Intersection* intersect(AABB* ab);
    Intersection* intersect(Circle* c);
    Intersection* intersect(Convex* c);

    void update(float dt);
    void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    bool hasIntersected() const;

    // Setters
    void setCollider(Collider* pos) override;
    void setGlobalRotation() override;
    void setLocalRotation(float a) override;
    void setIntersected(bool i) override;

    // Getters
    Collider* getCollider() const override;
    Vector2d<float> getMin() const override;
    Vector2d<float> getMax() const override;
    const Shape_Type& getType() const override;
    float getLocalRotation() const override;
    const Vector2d<float>& getCenter() const override;
    

    // Destructor
    ~Circle();

private:

    Vector2d<float> model_center;
    float radius;

    friend class AABB;
    friend class Convex;

};

#endif