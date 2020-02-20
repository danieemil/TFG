#include "Sprite.h"
#include "SpriteManager.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Sprite::Sprite()
{
    index = -1;
    manager = nullptr;
}

Sprite::Sprite(const Sprite& spr)
{
    index = spr.index;
    manager = nullptr;
}

Sprite::Sprite(SpriteManager* man, size_t collection_index)
{

    index = collection_index;
    manager = man;
    C2D_SpriteFromSheet(&sprite, manager->getSpriteCollection(), index);
}

Sprite& Sprite::operator= (const Sprite& s)
{
    index = s.index; 
    
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Sprite::drawSprite()
{
    C2D_DrawSprite(&sprite);
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

void Sprite::setPosition(const Vector2d<float>& position)
{
    C2D_SpriteSetPos(&sprite, position.x, position.y);
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

Vector2d<float> Sprite::getPosition() const
{
    return Vector2d<float>(sprite.params.pos.x, sprite.params.pos.y);
}

Vector2d<float> Sprite::getCenter() const
{
    return Vector2d<float>(sprite.params.center.x, sprite.params.center.y);
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Sprite::~Sprite()
{
    unvisual::debugger->print("Borrando sprite:");
    unvisual::debugger->print(this);
    unvisual::debugger->nextLine();
    
    if(manager!=nullptr)
    {
        manager->eraseSprite(this);
    }
}