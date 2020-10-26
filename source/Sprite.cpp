#include "Sprite.h"
#include "SpriteManager.h"
#include "Unvisual_Engine.h"


using namespace unvisual;


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Sprite::Sprite(SpriteManager* man, size_t collection_index, const Vector2d<float>& pos)
: index(collection_index), position(pos), manager(man)
{
    if(manager!=nullptr)
    {
        C2D_SpriteFromSheet(&sprite, manager->getSpriteCollection(), index);
        setDepth(SPRITE_DEPTH);
        manager->addSprite(this);
    }
}

Sprite::Sprite(const Sprite& spr)
: Sprite(spr.manager, spr.index, spr.position)
{
    
}

Sprite& Sprite::operator= (const Sprite& spr)
{
    index = spr.index;
    position = spr.position;
    manager = spr.manager;

    if (manager!=nullptr)
    {
        C2D_SpriteFromSheet(&sprite, manager->getSpriteCollection(), index);
        setDepth(SPRITE_DEPTH);
        manager->addSprite(this);
    }
    
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Sprite::drawSprite(const Vector2d<float>& view_pos)
{
    if(viewPositioning(view_pos))
    {
        C2D_DrawSprite(&sprite);
    }
}

void Sprite::drawTintedSprite(u32 color, float strength, const Vector2d<float>& view_pos)
{
    if(viewPositioning(view_pos))
    {
        C2D_ImageTint tint;
        C2D_PlainImageTint(&tint, color, strength);
        C2D_DrawSpriteTinted(&sprite, &tint);
    }
}

void Sprite::drawOutlinedSrpite(u32 color, const Vector2d<float>& view_pos)
{
    //Vector2d<float> spr_size1 = Vector2d<float>(sprite.params.pos.w, sprite.params.pos.h);
    //Vector2d<float> spr_size2 = spr_size1 + Vector2d<float>(2,2);
    //Vector2d<float> spr_scale = spr_size2 / spr_size1;

    sprite.params.pos.w = 2 + sprite.image.subtex->width;
	sprite.params.pos.h = 2 + sprite.image.subtex->height;
    position -= Vector2d<float>(1,1);

    drawTintedSprite(color, 1.0f, view_pos);

    sprite.params.pos.w = sprite.image.subtex->width;
	sprite.params.pos.h = sprite.image.subtex->height;
    position += Vector2d<float>(1,1);
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
                if(manager!=nullptr)
                {
                    manager->eraseSprite(this);
                }
                manager = man;
                index = collection_index;
                
                C2D_SpriteFromSheet(&sprite, sprite_collection, index);
                setDepth(SPRITE_DEPTH);

                manager->addSprite(this);
            }
        }
    }
}

// Esta función se carga la integridad del juego, pero...
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

void Sprite::setRotationRadians(float radians)
{
    sprite.params.angle = radians;
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

float Sprite::getRotationRadians() const
{
    return sprite.params.angle;
}

Vector2d<float> Sprite::getSpritePosition() const
{
    return Vector2d<float>(sprite.params.pos.x, sprite.params.pos.y);
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

Vector2d<float> Sprite::getEndPosition() const
{
    return Vector2d<float>(position.x + sprite.params.pos.w, position.y + sprite.params.pos.h);
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


//=========================================
//=                PRIVADO       	      =
//=========================================
// Actualiza la posición visible del sprite en base a la vista y devuelve si está dentro
// de la pantalla
bool Sprite::viewPositioning(const Vector2d<float>& view_pos)
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
            return true;
        }
    return false;
}