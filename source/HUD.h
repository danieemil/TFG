#ifndef _HUD_
#define _HUD_

#include "Player.h"
#include "SpriteManager.h"
#include "Text.h"


class HUD
{

public:
    // Constructores
    HUD(Player* p = nullptr, const char* sprites_path = nullptr);
    HUD(const HUD& h);

    HUD& operator= (const HUD& h);

    // Métodos
    void render();

    // Setters
    void setPlayer(Player* p);
    void setTilesetPath(const char* sprites_path);

    // Getters
    Player* getPlayer() const;
    const SpriteManager* getSpriteManager() const;

    // Destructor
    ~HUD();

private:

    Player* player;
    SpriteManager manager;

    Vector2d<float> life_position;
    float heart_padding;
    
    Sprite* heart;
    Sprite* half_heart;
    Sprite* no_heart;

    Sprite* weapon_selector;

};

#endif