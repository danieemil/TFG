#ifndef _ANIMATION_
#define _ANIMATION_

#include "Sprite.h"
#include "vector"


class Animation
{

public:
    // Constructores
    Animation(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr);
    Animation(const Animation& a);

    Animation& operator= (const Animation& a);

    // Métodos
    void render(const Vector2d<float>& view_pos = Vector2d<float>());

    void addBackSprite(Sprite* spr);
    void moveIndex(int offset);

    bool atEnd() const;
    bool hasSprites() const;

    // Setters
    void setPosition(const Vector2d<float>& pos);
    void setIndex(size_t i);

    // Getters
    const Vector2d<float>& getPosition() const;
    Sprite* getActualSprite() const;
    Sprite* getSpriteAt(size_t i) const;
    size_t getIndex() const;

    // Destructor
    ~Animation();

private:

    Vector2d<float> position;

    std::vector<Sprite*> sprites;

    size_t index;

};

#endif