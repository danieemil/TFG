#ifndef _TEXT_
#define _TEXT_

#include <citro2d.h>
#include "Utilities.h"

#define TEXT_HEIGH 30.0f

using namespace utilities;

//The default 3DS system font has a glyph height of 30px, and the baseline is at 25px
class Text
{

public:
    // Constructores
    Text(const Vector2d<float>& pos, const char* t = nullptr, size_t text_buf_size = 100, float height = 15.0f, u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255);
    Text(const Text& t);

    Text& operator= (const Text& t);

    // Métodos
    void render(const Vector2d<float>& view_pos = Vector2d<float>());

    // Setters
    void setPosition(const Vector2d<float>& pos);
    void setText(const char* t);
    void setTextBufferSize(size_t text_buf_size);
    void setColor(u8 r, u8 g, u8 b, u8 a);
    void setHeight(float height);

    // Getters
    const Vector2d<float>& getPosition() const;
    const char* getText() const;
    size_t getTextBufferSize() const;

    // Destructor
    ~Text();

private:

    Vector2d<float> position;
    Vector2d<float> size;

    C2D_Text text;
    C2D_TextBuf text_buf;
    const char* text_data;

    u32 color;

    Vector2d<float> padding;

};

#endif