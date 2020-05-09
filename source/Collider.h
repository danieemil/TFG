#ifndef _COLLIDER_
#define _COLLIDER_

#include "Bounding_Box.h"
#include "AABB.h"
#include "vector"


class Collider
{

public:
    // Constructores
    Collider(const Vector2d<float>& pos, Shape* s = nullptr);
    Collider(const Collider& c);

    Collider& operator= (const Collider& c);

    // Métodos
    void addShape(Shape* s);
    void delShape(Shape* s);

    bool intersectBounds(Collider* c);
    bool intersectShapes(Collider* c);

    // Setters
    void setPosition(const Vector2d<float>& pos);

    // Getters
    const Vector2d<float>& getPosition() const;
    const Bounding_Box& getBounds() const;

    // Destructor
    ~Collider();

private:

    std::vector<Shape*> shapes;
    Vector2d<float> position;
    Bounding_Box bounds;

    void calculateValues();

};

#endif