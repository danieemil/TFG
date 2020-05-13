#ifndef _CIRCLE_
#define _CIRCLE_

#include "Shape.h"



class AABB;



class Circle : public Shape
{

public:
    // Constructores
    Circle(const Vector2d<float>& center_rel, const float& radius_rel, Vector2d<float>* pos = nullptr, Vector2d<float>* prev = nullptr);
    Circle(const Circle& ab);

    Circle& operator= (const Circle& ab);

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
    ~Circle();

private:

    Vector2d<float> center;
    float radius;

    friend class AABB;

};

#endif