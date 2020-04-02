#ifndef _COLLIDER_
#define _COLLIDER_

#include "Bounding_Box.h"


enum class Collider_Type
{
    AABB,
};


class Collider
{

public:
    // Constructores
    Collider(const Bounding_Box& bb);
    Collider(const Collider& c);

    Collider& operator= (const Collider& c);

    // Métodos
    virtual bool detect(Collider* c) = 0;
    virtual void intersect(Collider* c) = 0;

    // Setters
    virtual void setPosition(const Vector2d<float>& min_pos);
    virtual void setSize(const Vector2d<float>& size);
    virtual void setCenter(const Vector2d<float>& center);

    // Getters
    virtual const Vector2d<float>& getPosition() const;
    virtual const Vector2d<float>& getSize() const;
    virtual Vector2d<float> getCenter() const;
    virtual const Collider_Type& getType() const;

    // Destructor
    virtual ~Collider() = 0;

protected:

    Bounding_Box bounds;
    Collider_Type type;

private:

};

#endif