#include "Text.h"
#include "Unvisual_Engine.h"

using namespace unvisual;


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Text::Text(const Vector2d<float>& pos, const char* t, size_t text_size, float height,
u8 r, u8 g, u8 b, u8 a)
: position(pos), text(), text_buf(C2D_TextBufNew(text_size)), text_data(t),
color(unvisual::getColor2D(r, g, b, a)),
size(Vector2d<float>((height*2.0f)/TEXT_HEIGH, (height*2.0f)/TEXT_HEIGH)),
padding(Vector2d<float>(0.0f, 6.0f * size.y))
{
    if(t!=nullptr)
    {
        C2D_TextParse(&text, text_buf, t);
        C2D_TextOptimize(&text);
    }
}

Text::Text(const Text& t)
: Text(t.position, t.text_data, t.getTextBufferSize(), (t.size.x * TEXT_HEIGH)/2.0f)
{
    color = t.color;
}

Text& Text::operator= (const Text& t)
{
    position = t.position;
    size = t.size;

    setTextBufferSize(t.getTextBufferSize());
    setText(t.text_data);
    
    color = t.color;

    padding = t.padding;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Text::render(const Vector2d<float>& view_pos)
{

    Vector2d<float> pos = (position - view_pos) - padding;
    C2D_DrawText(&text, C2D_WithColor, pos.x, pos.y, 1.0f, size.x, size.y, color);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Text::setPosition(const Vector2d<float>& pos)
{
    position = pos;
}

void Text::setText(const char* t)
{
    C2D_TextBufClear(text_buf);
    text_data = t;
    C2D_TextParse(&text, text_buf, t);
    C2D_TextOptimize(&text);
}

void Text::setTextBufferSize(size_t text_buf_size)
{
    C2D_TextBufResize(text_buf, text_buf_size);
}

void Text::setColor(u32 c)
{
    color = c;
}

void Text::setHeight(float height)
{
    float scale_h = (height * 2.0f) / TEXT_HEIGH;
    size = Vector2d<float>(scale_h, scale_h);

    padding.y = 6.0f * size.y;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& Text::getPosition() const
{
    return position;
}

const char* Text::getText() const
{
    return text_data;
}

size_t Text::getTextBufferSize() const
{
    return C2D_TextBufGetNumGlyphs(text_buf);
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Text::~Text()
{
    C2D_TextBufDelete(text_buf);
}