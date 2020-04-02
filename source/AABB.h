#ifndef _AABB_
#define _AABB_

#include "Collider.h"

class AABB : public Collider
{

public:
    // Constructores
    AABB(const Bounding_Box& bb);
    AABB(const AABB& ab);

    AABB& operator= (const AABB& ab);

    // Métodos
    bool detect(Collider* c) override;
    void intersect(Collider* c) override;

    bool detect(AABB* ab);
    void intersect(AABB* ab);

    // Setters
    void setPosition(const Vector2d<float>& min_pos);
    void setSize(const Vector2d<float>& size);
    void setCenter(const Vector2d<float>& center);

    // Getters
    const Vector2d<float>& getPosition() const;
    const Vector2d<float>& getSize() const;
    Vector2d<float> getCenter() const;
    const Collider_Type& getType() const;

    // Destructor
    ~AABB();

private:

};

#endif