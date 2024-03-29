#include "GUI_Button.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

GUI_Button::GUI_Button(const Vector2d<float>& pos, const Vector2d<float>& s, Sprite* spr, Call cb,
const char* t, size_t t_size)
: GUI_Element(pos, s), sprite(spr), enabled(true), active(false),
callback(cb),text(Vector2d<float>(pos.x, pos.y),t,t_size, s.y)
{
    if(sprite!=nullptr)
    {
        sprite->setPosition(position);
    }
    Vector2d<float> padding = Vector2d<float>(2.0f, 4.5f);
    text.setPosition(position + padding);
    text.setHeight(s.y - padding.y*2.0f);
}

GUI_Button::GUI_Button(const GUI_Button& ge)
: GUI_Button(ge.position, ge.size, ge.sprite, ge.callback, ge.text.getText(), ge.text.getTextBufferSize())
{

}

GUI_Button& GUI_Button::operator= (const GUI_Button& ge)
{
    GUI_Element::operator=(ge);
    sprite = ge.sprite;
    if(sprite!=nullptr)
    {
        sprite->setPosition(position);
    }

    pressed = ge.pressed;
    selected = ge.selected;
    enabled = ge.enabled;
    active = ge.active;
    callback = ge.callback;

    text = ge.text;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void GUI_Button::processInput()
{
    if(pressed)
    {
        if(unvisual::input::isReleased(unvisual::input::N3DS_buttons::Key_Touch))
        {
            auto pos = unvisual::input::getLastPositionTouched();
            if(checkPressed(Vector2d<float>((float)pos.x, (float)pos.y)))
            {
                active = true;
            }
            else active = false;
        }
    }
    else
    {
        GUI_Element::processInput();
    }
}


void GUI_Button::update()
{
    if(active)
    {
        if(callback!=nullptr)
        {
            callback();
        }
    }
}

void GUI_Button::render()
{
    if(sprite!=nullptr)
    {
        sprite->drawSprite();
    }

    text.render();
}

bool GUI_Button::checkPressed(const Vector2d<float>& pos)
{
    if(GUI_Element::checkPressed(pos))
    {
        pressed = true;
        return pressed;
    }
    pressed = false;
    return pressed;
}

void GUI_Button::activate()
{
    active = true;
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void GUI_Button::setPosition(const Vector2d<float>& pos)
{
    GUI_Element::setPosition(pos);
    if(sprite!=nullptr)
    {
        sprite->setPosition(position);
    }
}

void GUI_Button::setSize(const Vector2d<float>& s)
{
    GUI_Element::setSize(s);
}

void GUI_Button::select(u32 color)
{
    GUI_Element::select(color);
    text.setColor(color);
}

void GUI_Button::unSelect(u32 color)
{
    GUI_Element::unSelect(color);
    text.setColor(color);
}

void GUI_Button::setSprite(Sprite* spr)
{
    sprite = spr;
    if(sprite!=nullptr)
    {
        sprite->setPosition(position);
    }
}

void GUI_Button::setPressed(bool p)
{
    pressed = p;
}

void GUI_Button::setEnabled(bool e)
{
    enabled = e;
}

void GUI_Button::setCallback(Call cb)
{
    callback = cb;
}

void GUI_Button::setText(const char* t)
{
    text.setText(t);
}

void GUI_Button::setTextColor(u8 r, u8 g, u8 b, u8 a)
{
    text.setColor(unvisual::getColor2D(r, g, b, a));
}



//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& GUI_Button::getPosition() const
{
    return GUI_Element::getPosition();
}

const Vector2d<float>& GUI_Button::getSize() const
{
    return GUI_Element::getSize();
}

Sprite* GUI_Button::getSprite() const
{
    return sprite;
}

bool GUI_Button::getPressed() const
{
    return pressed;
}

bool GUI_Button::getSelected() const
{
    return selected;
}

bool GUI_Button::getEnabled() const
{
    return enabled;
}

Call GUI_Button::getCallback() const
{
    return callback;
}

const char* GUI_Button::getText() const
{
    return text.getText();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

GUI_Button::~GUI_Button()
{
    if(sprite!=nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
}