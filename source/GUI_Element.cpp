#include "GUI_Element.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

GUI_Element::GUI_Element(const Vector2d<float>& pos, const Vector2d<float>& s)
: position(pos), size(s)
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

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

bool GUI_Element::checkPressed(const Vector2d<float>& pos)
{
    return ((position.x <= pos.x) && (position.x + size.x >= pos.x)) && ((position.y <= pos.y) && (position.y + size.y >= pos.y));
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


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

GUI_Element::~GUI_Element()
{
    
}