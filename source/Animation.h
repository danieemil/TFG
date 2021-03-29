#ifndef _ANIMATION_
#define _ANIMATION_

#include "Sprite.h"
#include "vector"
#include "Timepoint.h"


class Animation
{

public:
    // Constructores
    Animation();

    // Métodos
    void update();

    void addBackSprite(Sprite* spr, float dur);
    void resetAnimation();
    void endAnimation();
    void nextSprite();
    bool hasEnded() const;
    bool hasSprites() const;

    // Setters
    void setIndex(size_t i);

    // Getters
    Sprite* getActualSprite() const;
    Sprite* getSpriteAt(size_t i) const;
    size_t getIndex() const;

    // Destructor
    ~Animation();

private:

    std::vector<std::pair<Sprite*, float>> sprites;

    Timepoint timer;

    bool ended;
    size_t index;


};

#endif