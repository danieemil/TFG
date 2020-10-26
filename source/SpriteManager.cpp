#include "SpriteManager.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================
SpriteManager::SpriteManager(const char* sprites_path)
{
    sprite_collection = NULL;

    if(sprites_path!=nullptr)
    {
        path = sprites_path;
    }else
    {
        path.clear();
    }

    if(!path.empty())
    {
        sprite_collection = C2D_SpriteSheetLoad(path.data());
    }
    
    sprites.clear();
}

SpriteManager::SpriteManager(const SpriteManager& spr)
{
    sprite_collection = NULL;
    sprites.clear();
}

SpriteManager& SpriteManager::operator= (const SpriteManager& s)
{
    sprite_collection = NULL;
    sprites.clear();

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Sprite* SpriteManager::createSprite(size_t collection_index)
{

    Sprite* spr = nullptr;

    if(sprite_collection!=NULL)
    {
        if(collection_index < C2D_SpriteSheetCount(sprite_collection)
        && collection_index >= 0)
        {
            spr = new Sprite(this, collection_index);
        }
    }

    return spr;
}

void SpriteManager::addSprite(Sprite* spr)
{
    if(spr!=nullptr)
    {
        sprites.emplace_back(spr);
    }
}

void SpriteManager::deleteSprite(Sprite* spr)
{
    if(spr!=nullptr)
    {
        for(auto sprite = sprites.begin(); sprite != sprites.end(); ++sprite)
        {
            if((*sprite)== spr)
            {
                sprites.erase(sprite);
                delete spr;
                break;
            }
        }
    }
}

void SpriteManager::eraseSprite(Sprite* spr)
{
    if(spr!=nullptr)
    {
        for(auto sprite = sprites.begin(); sprite != sprites.end(); ++sprite)
        {
            if((*sprite)== spr)
            {
                sprites.erase(sprite);
                break;
            }
        }
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void SpriteManager::setSprites(const char* sprites_path)
{
    if(sprite_collection!=NULL)
    {
        C2D_SpriteSheetFree(sprite_collection);
    }
    
    if(sprites_path!=nullptr)
    {
        path = sprites_path;
        sprite_collection = C2D_SpriteSheetLoad(path.data());
    }
    else
    {
        path.clear();
    }
    
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

C2D_SpriteSheet SpriteManager::getSpriteCollection() const
{
    return sprite_collection;
}

const std::vector<Sprite*>& SpriteManager::getSprites() const
{
    return sprites;
}

std::string SpriteManager::getPath() const
{
    return path;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

SpriteManager::~SpriteManager()
{

    auto sprite = sprites.begin();

    while (sprite!=sprites.end())
    {
        Sprite* spr = (*sprite);

        if(spr!=nullptr)
        {
            delete spr;
        }

        if((*sprite)==spr && sprite!=sprites.end())
        {
            sprites.erase(sprite);
        }
    }

    if(sprite_collection!=NULL)
    {
        C2D_SpriteSheetFree(sprite_collection);
    }
}