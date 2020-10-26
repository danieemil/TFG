#include "HUD.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

HUD::HUD(Player* p, const char* sprites_path)
: player(p), manager(sprites_path), life_position(10.0f, 10.0f), heart_padding(4.0f),
heart(manager.createSprite(0)), half_heart(manager.createSprite(1)), no_heart(manager.createSprite(2)),
weapon_selector(manager.createSprite(3))
{
    if(weapon_selector!=nullptr)
    {
        Vector2d<float> sc_size = unvisual::getCurrentScreenSize();
        Vector2d<size_t> ws_size = weapon_selector->getSize();
        weapon_selector->setPosition(sc_size - Vector2d<float>(8,8) - Vector2d<float>(ws_size.x, ws_size.y));
    }
}

HUD::HUD(const HUD& h)
: player(h.player), manager(h.manager), life_position(h.life_position), heart_padding(h.heart_padding),
heart(manager.createSprite(0)), half_heart(manager.createSprite(1)), no_heart(manager.createSprite(2)),
weapon_selector(manager.createSprite(3))
{

}

HUD& HUD::operator= (const HUD& h)
{
    player = h.player;
    manager = h.manager;

    life_position = h.life_position;
    heart_padding = h.heart_padding;

    heart = manager.createSprite(0);
    half_heart = manager.createSprite(1);
    no_heart = manager.createSprite(2);
    weapon_selector = manager.createSprite(3);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void HUD::render()
{
    if(player!=nullptr)
    {
        if(heart!=nullptr)
        {
            Vector2d<float> pos = life_position;

            int half_hearts =   player->getLife();
            int max_hearts  =   player->getMaxLife();
            int no_hearts = max_hearts - half_hearts;
            no_hearts = no_hearts + (no_hearts % 2);



            Sprite* rendering = heart;

            start:
            while (half_hearts > 0)
            {
                
                if(half_hearts < 2)
                {
                    rendering = half_heart;
                }

                rendering->setPosition(pos);
                rendering->drawSprite();

                float end_x = rendering->getEndPosition().x;
                pos.x = end_x + heart_padding;

                half_hearts -= 2;
            }

            if(no_hearts > 0)
            {
                rendering = no_heart;
                half_hearts = no_hearts;
                no_hearts = 0.0f;
                goto start;
            }

            if(weapon_selector!=nullptr)
            {
                weapon_selector->drawSprite();

                Weapon* w = player->getWeaponEquipped();
                if(w!=nullptr)
                {
                    Sprite* w_spr = w->getSprite();

                    if (w_spr!=nullptr)
                    {
                        float not_attacking = 0.0f;
                        u32 white = unvisual::getColor2D(255,255,255,255);
                        u32 black = unvisual::getColor2D(0,0,0,255);

                        auto temp = weapon_selector->getSize();
                        Vector2d<float> container_size = Vector2d<float>(temp.x, temp.y);
                        temp = w_spr->getSize();
                        Vector2d<float> w_size = Vector2d<float>(temp.x, temp.y);
                        Vector2d<float> w_pos = w_spr->getPosition();
                        
                        Vector2d<float> w_hud_pos = weapon_selector->getPosition() + ((container_size - w_size)/2);
                        w_spr->setPosition(w_hud_pos);
                        float w_rot = w_spr->getRotationRadians();
                        w_spr->setRotationRadians(0.0f);

                        if(player->getAttacking() || player->getStunned())
                        {
                            not_attacking = 0.75f;
                        }

                        w_spr->drawTintedSprite(black, not_attacking);
                        w_spr->setPosition(w_pos);
                        w_spr->setRotationRadians(w_rot);
                    }
                }
            }
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

    heart = manager.createSprite(0);

    half_heart = manager.createSprite(1);

    no_heart = manager.createSprite(2);

    weapon_selector = manager.createSprite(3);
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
    heart = nullptr;
    half_heart = nullptr;
    no_heart = nullptr;
}