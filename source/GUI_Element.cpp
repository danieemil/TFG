#include "GUI_Element.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

GUI_Element::GUI_Element(const Vector2d<float>& pos, const Vector2d<float>& s)
: position(pos), size(s), pressed(false), selected(false)
{

}

GUI_Element::GUI_Element(const GUI_Element& ge)
: GUI_Element(ge.position, ge.size)
{

}

GUI_Element& GUI_Element::operator= (const GUI_Element& ge)
{
    position = ge.position;
    size = ge.size;
    pressed = ge.pressed;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void GUI_Element::processInput()
{
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_Touch))
    {
        auto pos = unvisual::input::getPositionTouched();
        checkPressed(Vector2d<float>(pos.x, pos.y));
    }
}

bool GUI_Element::checkPressed(const Vector2d<float>& pos)
{
    pressed = ((position.x <= pos.x) && (position.x + size.x >= pos.x)) && ((position.y <= pos.y) && (position.y + size.y >= pos.y));
    return pressed;
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void GUI_Element::setPosition(const Vector2d<float>& pos)
{
    position = pos;
}

void GUI_Element::setSize(const Vector2d<float>& s)
{
    size = s;
}

void GUI_Element::select()
{
    selected = true;
}

void GUI_Element::unSelect()
{
    selected = false;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<float>& GUI_Element::getPosition() const
{
    return position;
}

const Vector2d<float>& GUI_Element::getSize() const
{
    return size;
}

bool GUI_Element::getPressed() const
{
    return pressed;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

GUI_Element::~GUI_Element()
{
    
}