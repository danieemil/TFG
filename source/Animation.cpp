#include "Animation.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Animation::Animation()
: sprites(), timer(), ended(false), index(0)
{

}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Animation::update()
{
    if(hasSprites())
    {
        std::pair<Sprite*, float> spr = sprites[index];

        if(timer.getElapsed() > spr.second)
        {
            nextSprite();
        }
    }
    else
    {
        ended = true;
    }
}

void Animation::addBackSprite(Sprite* spr, float dur)
{
    if(spr!=nullptr)
    {
        sprites.push_back(make_pair(spr,dur));
    }
}

void Animation::resetAnimation()
{
    index = 0;
    ended = false;
    timer.reset();
}

void Animation::endAnimation()
{
    size_t s = sprites.size();
    if(s>0)
    {
        index = s - 1;
    }
    ended = true;
}

void Animation::nextSprite()
{
    size_t i = index + 1;
    if(i >= sprites.size())
    {
        ended = true;
        return;
    }

    index = i;
    timer.reset();
}

bool Animation::hasEnded() const
{
    return ended;
}

bool Animation::hasSprites() const
{
    return !(sprites.empty());
}

//=========================================
//=               SETTERS   	    	  =
//=========================================

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

Sprite* Animation::getActualSprite() const
{
    if (hasSprites())
    {
        return sprites[index].first;
    }

    return nullptr;
}

Sprite* Animation::getSpriteAt(size_t i) const
{
    size_t ind = sprites.size();

    if(i >= 0)
    {
        if(i < ind)
        {
            return sprites[i].first;
        }
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
        if (spr.first!=nullptr)
        {
            delete spr.first;
        }
    }
    sprites.clear();
}