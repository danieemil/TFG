#ifndef _COLLIDER_
#define _COLLIDER_

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

// 0101 & 1100 = 1101 (1 | 0 = 1, 1 | 1 = 1, 0 | 0 = 0) 
inline CollisionFlag operator |(const CollisionFlag& a, const CollisionFlag& b)
{
    return static_cast<CollisionFlag>(static_cast<int>(a) | static_cast<int>(b));
}

// 0101 & 1100 = 0100 (1 & 0 = 0, 1 & 1 = 1, 0 & 0 = 0) 
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
    Collider(const Vector2d<float>& pos, Shape* s = nullptr, const CollisionFlag& f = CollisionFlag::none, const CollisionType& t = CollisionType::col_none, void* c = nullptr, int i = -1, float a = 0.0f, const Vector2d<float>& rot_cent = Vector2d<float>(0,0));
    Collider(const Collider& c);

    Collider& operator= (const Collider& c);

    // Métodos
    void addShape(Shape* s);
    void delShape(Shape* s);

    bool intersectBounds(Collider* c);
    Intersection* intersectShapes(Collider* c);
    void intersectFix(Intersection* inter);

    Intersection* intersectSegment(const Vector2d<float>& a, const Vector2d<float>& b);

    bool isStatic() const;

    // Setters
    void setPosition(const Vector2d<float>& pos);
    void setFlags(const CollisionFlag& f);
    void setType(const CollisionType& t);
    void setCreator(void* c);
    void setIndex(int i);
    void setGlobalRotation(float a);
    void setLocalsRotation(float a);
    void setRotationCenter(const Vector2d<float>& rot_cent);

    // Getters
    const Vector2d<float>& getPosition() const;
    const Vector2d<float>& getPreviousPosition() const;
    const Bounding_Box& getBounds() const;
    const CollisionFlag& getFlags() const;
    const CollisionType& getType() const;
    void* getCreator() const;
    int getIndex() const;
    float getRotation() const;
    const Vector2d<float>& getRotationCenter() const;

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
    int index;
    float angle;
    Vector2d<float> rotation_center;

    void calculateValues();

};

#endif