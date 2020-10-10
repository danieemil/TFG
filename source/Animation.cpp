#include "Animation.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Animation::Animation(const Vector2d<float>& pos, Sprite* spr)
: position(pos)
{
    if(spr!=nullptr)
    {
        sprites.push_back(spr);
    }
    index = 0;
}

Animation::Animation(const Animation& a)
: position(a.position), sprites(a.sprites), index(a.index)
{

}

Animation& Animation::operator= (const Animation& a)
{
    position = a.position;
    sprites = a.sprites;
    index = a.index;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Animation::render(const Vector2d<float>& view_pos)
{
    if(!sprites.empty())
    {
        Sprite* spr = sprites.at(index);
        spr->setPosition(position);
        spr->drawSprite(view_pos);
    }
}

void Animation::addBackSprite(Sprite* spr)
{
    if(spr!=nullptr)
    {
        sprites.push_back(spr);
    }
}

void Animation::moveIndex(int offset)
{
    int sprs_size = (int)sprites.size();

    if(sprs_size!=0)
    {
        index = (size_t)clamp(0,sprs_size - 1, offset + (int)index);
        return;
    }
    index = (size_t)0;
}

bool Animation::atEnd() const
{
    return (index == sprites.size() - (size_t)1);
}

bool Animation::hasSprites() const
{
    return !sprites.empty();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Animation::setPosition(const Vector2d<float>& pos)
{
    position = pos;
}

void Animation::setIndex(size_t i)
{
    size_t sprs_size = sprites.size();

    if(sprs_size == (size_t)0)
    {
        index = 0;
        return;
    }

    if(i >= sprs_size)
    {
        i = sprs_size - (size_t)1;
    }

    index = i;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& Animation::getPosition() const
{
    return position;
}

Sprite* Animation::getActualSprite() const
{
    if (!sprites.empty())
    {
        return sprites.at(index);
    }

    return nullptr;
}

Sprite* Animation::getSpriteAt(size_t i) const
{
    size_t ind = sprites.size();

    if(ind != 0)
    {
        if(i >= ind)
        {
            return sprites.at(ind - (size_t)1);
        }
        return sprites.at(i);
    }
    return nullptr;
}

size_t Animation::getIndex() const
{
    return index;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Animation::~Animation()
{
    for (auto &&spr : sprites)
    {
        if (spr!=nullptr)
        {
            delete spr;
        }
    }
    sprites.clear();
}