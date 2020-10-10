#include "GUI_Button.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

GUI_Button::GUI_Button(const Vector2d<float>& pos, const Vector2d<float>& s, Sprite* spr, Call cb)
: GUI_Element(pos, s), sprite(spr), pressed(false), selected(false), enabled(true), active(false), callback(cb)
{
    if(sprite!=nullptr)
    {
        sprite->setPosition(position);
    }
}

GUI_Button::GUI_Button(const GUI_Button& ge)
: GUI_Button(ge.position, ge.size, ge.sprite, ge.callback)
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

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void GUI_Button::update()
{
    if (pressed)
    {
        active = true;
    }
    else if(active)
    {
        active = false;
        activate();
    }
    pressed = false;
}

void GUI_Button::render()
{
    if(sprite!=nullptr)
    {
        sprite->drawSprite();
    }
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
    if(callback!=nullptr)
    {
        callback();
    }
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

void GUI_Button::setSelected(bool s)
{
    selected = s;
}

void GUI_Button::setEnabled(bool e)
{
    enabled = e;
}

void GUI_Button::setCallback(Call cb)
{
    callback = cb;
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