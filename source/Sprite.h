#ifndef _SPRITE_
#define _SPRITE_

#include "Unvisual_Engine.h"


using namespace utilities;

class SpriteManager;

class Sprite
{

public:
    // Constructores
    Sprite(SpriteManager* man = nullptr, size_t collection_index = -1, const Vector2d<float>& pos = Vector2d<float>());
    Sprite(const Sprite& spr);
    

    Sprite& operator= (const Sprite& spr);

    // Métodos
    void drawSprite(const Vector2d<float>& view_pos = Vector2d<float>());

    // Setters
    void setSprite(SpriteManager* man, size_t collection_index);
    void setRawManager(SpriteManager* man);
    void setPosition(const Vector2d<float>& pos);
    void setRotation(float angle);
    void setScale(const Vector2d<float>& scale);
    void setCenter(const Vector2d<float>& center);
    void setDepth(float depth);

    // Getters
    size_t getIndex() const;
    SpriteManager* getManager() const;
    const Vector2d<float>& getPosition() const;
    Vector2d<float> getSpritePosition() const;
    Vector2d<float> getCenter() const;
    Vector2d<float> getCenterPosition() const;
    Vector2d<size_t> getSize() const;

    // Destructor
    ~Sprite();

private:

    size_t index;
    Vector2d<float> position;
    SpriteManager* manager;
    C2D_Sprite sprite;
    

};

#endif