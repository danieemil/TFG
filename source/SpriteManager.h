#ifndef _SPRITEMANAGER_
#define _SPRITEMANAGER_

#include "Sprite.h"

class SpriteManager
{

public:
    // Constructores
    SpriteManager(const char* sprites_path = nullptr);
    SpriteManager(const SpriteManager&);

    SpriteManager& operator= (const SpriteManager&);

    // Métodos
    Sprite* createSprite(size_t collection_index);
    void addSprite(Sprite* spr);
    void deleteSprite(Sprite* spr);
    void eraseSprite(Sprite* spr);

    // Setters
    void setSprites(const char* sprites_path);

    // Getters
    C2D_SpriteSheet getSpriteCollection() const;
    const std::vector<Sprite*>& getSprites() const;

    // Destructor
    ~SpriteManager();

private:

    C2D_SpriteSheet sprite_collection;
    std::vector<Sprite*> sprites;

};

#endif