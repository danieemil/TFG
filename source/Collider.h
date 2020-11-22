#ifndef _COLLIDER_
#define _COLLIDER_

#include "AABB.h"
#include "Circle.h"
#include "Convex.h"
#include <functional>


enum class CollisionType
{
    col_none,
    col_static,
    col_cinematic,
    col_dynamic,
};


enum class CollisionFlag
{
    none                = 0,
    player_hit          = 1 << 0,
    player_hurt         = 1 << 1,
    enemy_hit           = 1 << 2,
    enemy_hurt          = 1 << 3,
    interactable_hit    = 1 << 4,
};

// 0+8+0+1 |16+8+0+0 =16+8+0+1 -> simula el comportamiento de una puerta OR
// 0 1 0 1 | 1 1 0 0 = 1 1 0 1 (1 | 0 = 1, 1 | 1 = 1, 0 | 0 = 0) 
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


using Callback = std::function<void(void*)>;

class Collider
{

public:
    // Constructores
    Collider(const Vector2d<float>& pos, Shape* s = nullptr,
    const CollisionFlag& ft = CollisionFlag::none, const CollisionFlag& fi = CollisionFlag::none,
    const CollisionType& t = CollisionType::col_none, void* c = nullptr, Callback cb = nullptr,
    int i = -1, float a = 0.0f, const Vector2d<float>& rot_cent = Vector2d<float>(0,0),
    const Vector2d<float>& vel = Vector2d<float>(), bool act = true,
    const Vector2d<float>& m_vel = Vector2d<float>(INFINITY, INFINITY),
    const Vector2d<float>& accel = Vector2d<float>(),
    const Vector2d<float>& m_accel = Vector2d<float>(INFINITY, INFINITY),
    const Vector2d<float>& frict = Vector2d<float>(),
    const Vector2d<float>& imp = Vector2d<float>());
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
    bool isColliding() const;

    void update(float dt);
    void render(const Vector2d<float>& view_pos = Vector2d<float>());

    void callBack(void* e);

    // Setters
    void setPosition(const Vector2d<float>& pos);
    void setTypeFlags(const CollisionFlag& f);
    void setIntersetedFlags(const CollisionFlag& f);
    void setType(const CollisionType& t);
    void setCreator(void* c);
    void setCallback(Callback c);
    void setIndex(int i);
    void setGlobalRotation(float a);
    void setLocalsRotation(float a);
    void setRotationCenter(const Vector2d<float>& rot_cent);
    void setVelocity(const Vector2d<float>& vel);
    void setActive(bool a);
    void setMaxVelocity(const Vector2d<float>& m_vel);
    void setAcceleration(const Vector2d<float>& accel);
    void setMaxAcceleration(const Vector2d<float>& m_accel);
    void setFriction(const Vector2d<float>& frict);
    void setImpulse(const Vector2d<float>& imp);
    void setIntersected();

    // Getters
    const Vector2d<float>& getPosition() const;
    const Vector2d<float>& getPreviousPosition() const;
    const Bounding_Box& getBounds() const;
    const CollisionFlag& getTypeFlags() const;
    const CollisionFlag& getInterestedFlags() const;
    const CollisionType& getType() const;
    void* getCreator() const;
    Callback getCallback() const;
    int getIndex() const;
    float getRotation() const;
    const Vector2d<float>& getRotationCenter() const;
    const Vector2d<float>& getVelocity() const;
    bool getActive() const;
    const Vector2d<float>& getMaxVelocity() const;
    const Vector2d<float>& getAcceleration() const;
    const Vector2d<float>& getMaxAcceleration() const;
    const Vector2d<float>& getFriction() const;

    // Destructor
    ~Collider();

private:

    std::vector<Shape*> shapes;
    Vector2d<float> position;
    Vector2d<float> previous_position;
    Bounding_Box bounds;
    CollisionFlag type_flags;
    CollisionFlag interested_flags;
    CollisionType type;
    void* creator;
    Callback callback;
    int index;
    float angle;
    Vector2d<float> rotation_center;
    Vector2d<float> velocity; // Describe lo que te mueves en X e Y en un segundo
    bool active; // Indica si tiene habilitadas o inhabilitadas las colisiones por flags

    // Variables para el movimiento de los cuerpos
    Vector2d<float> max_velocity;
    Vector2d<float> acceleration;
    Vector2d<float> max_acceleration;
    Vector2d<float> friction;
    Vector2d<float> impulse;

    void calculateValues();

};

#endif