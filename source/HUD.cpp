#include "HUD.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

HUD::HUD(Player* p, const char* sprites_path)
: player(p), manager(sprites_path), life(manager.createSprite(0))
{
    if(life!=nullptr)
    {
        auto ls = life->getSize();
        life->setPosition(Vector2d<float>(24.0f,MAX_HEIGHT_DOWN - (float)ls.y - 24));
    }
}

HUD::HUD(const HUD& h)
: player(h.player), manager(h.manager), life(manager.createSprite(0))
{
    if(h.life!=nullptr && life!=nullptr)
    {
        life->setPosition(h.life->getPosition());
    }
}

HUD& HUD::operator= (const HUD& h)
{
    player = h.player;
    manager = h.manager;
    life = manager.createSprite(0);
    if(h.life!=nullptr && life!=nullptr)
    {
        life->setPosition(h.life->getPosition());
    }
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void HUD::render()
{
    if(player!=nullptr)
    {
        if(life!=nullptr)
        {
            u32 black = C2D_Color32(0,0,0,255);
            u32 red = C2D_Color32(50,0,0,255);
            
            u32 color = black;

            float strength = 1.0f - (player->getLife()/(float)player->getMaxLife());

            if(strength >= 0.75f)
            {
                color = red;
                strength = strength - 0.1f;
            }

            life->drawTintedSprite(color, strength);
        }
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void HUD::setPlayer(Player* p)
{
    player = p;
}

void HUD::setTilesetPath(const char* sprites_path)
{
    manager.setSprites(sprites_path);

    life = manager.createSprite(0);
    if(life!=nullptr)
    {
        auto ls = life->getSize();
        life->setPosition(Vector2d<float>(24.0f,MAX_HEIGHT_DOWN - (float)ls.y - 24));
    }
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Player* HUD::getPlayer() const
{
    return player;
}

const SpriteManager* HUD::getSpriteManager() const
{
    return &manager;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

HUD::~HUD()
{
    player = nullptr;
    life = nullptr;
}