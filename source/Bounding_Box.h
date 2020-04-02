#ifndef _BOUNDING_BOX_
#define _BOUNDING_BOX_

#include "Utilities.h"

using namespace utilities;


class Bounding_Box
{

public:
    // Constructores
    Bounding_Box(const Vector2d<float>& min_pos, float width, float height);
    Bounding_Box(const Vector2d<float>& min_pos, const Vector2d<float>& max_pos);
    Bounding_Box(const Bounding_Box&);

    Bounding_Box& operator= (const Bounding_Box& bb);

    // Métodos
    bool intersects(const Bounding_Box& bb);

    // Setters
    void setPosition(const Vector2d<float>& min_pos);
    void setSize(const Vector2d<float>& bb_size);
    void setCenter(const Vector2d<float>& center);

    // Getters
    const Vector2d<float>& getPosition() const;
    const Vector2d<float>& getSize() const;
    Vector2d<float> getCenter() const;

    // Destructor
    ~Bounding_Box();

private:

    Vector2d<float> min;
    Vector2d<float> size;

};

#endif