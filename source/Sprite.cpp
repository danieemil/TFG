#include "Sprite.h"
#include "SpriteManager.h"
#include "Unvisual_Engine.h"


using namespace unvisual;


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Sprite::Sprite(SpriteManager* man, size_t collection_index, const Vector2d<float>& pos)
: index(collection_index), position(pos), manager(man), sprite()
{
    if(manager!=nullptr)
    {
        C2D_SpriteFromSheet(&sprite, manager->getSpriteCollection(), index);
    }
}

Sprite::Sprite(const Sprite& spr)
: index(spr.index), position(spr.position), manager(nullptr), sprite()
{

}

Sprite& Sprite::operator= (const Sprite& spr)
{
    index = spr.index;
    position = spr.position;
    manager = nullptr;
    
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Sprite::drawSprite(const Vector2d<float>& view_pos)
{
    Screen* s = unvisual::getCurrentScreen();
    
    float h = (float)s->getHeight();
    float w = (float)s->getWidth();

    Vector2d<float> cent = Vector2d<float>(sprite.params.center.x, sprite.params.center.y); 

    // Necesario para aplicar scroll 2D personalizado
    Vector2d<float> p = position - view_pos + cent;
    if((p.x + sprite.params.pos.w) > 0.0f && p.x < w)
        if((p.y + sprite.params.pos.h) > 0.0f && p.y < h)
        {
            C2D_SpriteSetPos(&sprite, p.x, p.y);
            C2D_DrawSprite(&sprite);
        }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Sprite::setSprite(SpriteManager* man, size_t collection_index)
{

    if(man!= nullptr)
    {
        auto sprite_collection = man->getSpriteCollection();

        if(sprite_collection!=NULL)
        {
            if(collection_index < C2D_SpriteSheetCount(sprite_collection)
            && collection_index >= 0)
            {
                C2D_SpriteFromSheet(&sprite, sprite_collection, index);

                if(manager!=nullptr)
                {
                    manager->eraseSprite(this);
                }
                manager = man;
                index = collection_index;

                manager->addSprite(this);
            }
        }
    }
}

void Sprite::setRawManager(SpriteManager* man)
{
    manager = man;
}

void Sprite::setPosition(const Vector2d<float>& pos)
{
    position = pos;
}

void Sprite::setRotation(float angle)
{
    C2D_SpriteSetRotationDegrees(&sprite, angle);
}

void Sprite::setScale(const Vector2d<float>& scale)
{
    C2D_SpriteSetScale(&sprite, scale.x, scale.y);
}

void Sprite::setCenter(const Vector2d<float>& center)
{
    C2D_SpriteSetCenter(&sprite, center.x, center.y);
}

void Sprite::setDepth(float depth)
{
    C2D_SpriteSetDepth(&sprite, depth);
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

size_t Sprite::getIndex() const
{
    return index;
}

SpriteManager* Sprite::getManager() const
{
    return manager;
}

const Vector2d<float>& Sprite::getPosition() const
{
    return position;
}

Vector2d<float> Sprite::getCenter() const
{
    return Vector2d<float>(sprite.params.center.x, sprite.params.center.y);
}

Vector2d<float> Sprite::getCenterPosition() const
{
    Vector2d<float> center_pos = position;
    
    center_pos += Vector2d<float>(sprite.params.center.x, sprite.params.center.y);

    return center_pos;
}

Vector2d<size_t> Sprite::getSize() const
{
    return Vector2d<size_t>(sprite.params.pos.w, sprite.params.pos.h);
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Sprite::~Sprite()
{   
    if(manager!=nullptr)
    {
        manager->eraseSprite(this);
    }
}