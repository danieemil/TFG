#ifndef _COLLIDER_
#define _COLLIDER_

#include "Bounding_Box.h"
#include "AABB.h"
#include "Circle.h"
#include "Convex.h"


enum class CollisionType
{
    col_none,
    col_static,
    col_cinematic,
    col_dynamic,
};


enum class CollisionFlag
{
    none = 0,
    player = 1 << 0,
    enemy = 1 << 1,
    weapon = 1 << 2,
};

inline CollisionFlag operator |(const CollisionFlag& a, const CollisionFlag& b)
{
    return static_cast<CollisionFlag>(static_cast<int>(a) | static_cast<int>(b));
}

inline CollisionFlag operator &(const CollisionFlag& a, const CollisionFlag& b)
{
    return static_cast<CollisionFlag>(static_cast<int>(a) & static_cast<int>(b));
}

inline CollisionFlag operator ~(const CollisionFlag& a)
{
    return static_cast<CollisionFlag>(~static_cast<int>(a));
}

class Collider
{

public:
    // Constructores
    Collider(const Vector2d<float>& pos, Shape* s = nullptr, const CollisionFlag& f = CollisionFlag::none, const CollisionType& t = CollisionType::col_none, void* c = nullptr);
    Collider(const Collider& c);

    Collider& operator= (const Collider& c);

    // Métodos
    void addShape(Shape* s);
    void delShape(Shape* s);

    bool intersectBounds(Collider* c);
    Intersection* intersectShapes(Collider* c);
    void intersectFix(Intersection* inter);

    // Setters
    void setPosition(const Vector2d<float>& pos);
    void setFlags(const CollisionFlag& f);
    void setType(const CollisionType& t);
    void setCreator(void* c);

    // Getters
    const Vector2d<float>& getPosition() const;
    const Vector2d<float>& getPreviousPosition() const;
    const Bounding_Box& getBounds() const;
    const CollisionFlag& getFlags() const;
    const CollisionType& getType() const;
    void* getCreator() const;

    // Destructor
    ~Collider();

private:

    std::vector<Shape*> shapes;
    Vector2d<float> position;
    Vector2d<float> previous_position;
    Bounding_Box bounds;
    CollisionFlag flags;
    CollisionType type;
    void* creator;

    void calculateValues();

};

#endif