#ifndef _SPRITE_
#define _SPRITE_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <citro2d.h>
#include <3ds.h>
#include "Utilities.h"


using namespace utilities;

class SpriteManager;

class Sprite
{

public:
    // Constructores
    Sprite();
    Sprite(const Sprite&);
    Sprite(SpriteManager* man, size_t collection_index);

    Sprite& operator= (const Sprite&);

    // Métodos
    void drawSprite();

    // Setters
    void setSprite(SpriteManager* man, size_t collection_index);
    void setRawManager(SpriteManager* man);
    void setPosition(const Vector2d<float>& position);
    void setRotation(float angle);
    void setScale(const Vector2d<float>& scale);
    void setCenter(const Vector2d<float>& center);

    // Getters
    size_t getIndex() const;
    SpriteManager* getManager() const;
    Vector2d<float> getPosition() const;
    Vector2d<float> getCenter() const;

    // Destructor
    ~Sprite();

private:

    C2D_Sprite sprite;
    size_t index;

    SpriteManager* manager;

};

#endif