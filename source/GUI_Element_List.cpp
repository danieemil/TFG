#include "GUI_Element_List.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

GUI_Element_List::GUI_Element_List(u32 unsel_color, u32 sel_color, bool no_touch, int def)
: selected(-1), unselected_color(unsel_color), selected_color(sel_color),
untouchable(no_touch), selected_default(def)
{

}

GUI_Element_List::GUI_Element_List(const GUI_Element_List& gel)
: selected(-1), unselected_color(gel.selected_color), selected_color(gel.selected_color),
untouchable(gel.untouchable), selected_default(gel.selected_default)
{

}

GUI_Element_List& GUI_Element_List::operator= (const GUI_Element_List& gel)
{
    unselected_color = gel.unselected_color;
    selected_color = gel.selected_color;

    untouchable = gel.untouchable;
    selected_default = gel.selected_default;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void GUI_Element_List::processInput()
{

    // Procesar las teclas
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_DDown))
    {
        selectNextElement();
    }

    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_DUp))
    {
        selectPrevElement();
    }

    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_A))
    {
        if(selected>-1)
        {
            auto e = elements.at(selected);
            e->activate();
        }else
        {
            selected = selected_default - 1;
            selectNextElement();
        }
    }



    // Procesar el panel táctil
    if(!untouchable && unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_Touch))
    {
        unSelectActual();
        selected = -1;
        int s = 0;
        for (auto &&element : elements)
        {
            element->processInput();
            if (element->getPressed())
            {
                selected = s;
                selectActual();
                break;
            }
            s++;
        }
    }

    if(selected>-1)
    {
        elements.at(selected)->processInput();
    }
}

void GUI_Element_List::update()
{
    if(selected>-1)
    {
        elements.at(selected)->update();
        return;
    }
}

void GUI_Element_List::render()
{
    for (auto &&element : elements)
    {
        element->render();
    }
}

void GUI_Element_List::addElement(GUI_Element* element)
{
    if(element!=nullptr)
    {
        elements.push_back(element);
    }
}

void GUI_Element_List::removeElement(GUI_Element* element)
{
    if(element!=nullptr)
    {
        int s = 0;
        for (auto it = elements.begin(); it != elements.end(); it++)
        {
            GUI_Element* el = (*it);
            if(el==element)
            {
                delete element;
                elements.erase(it);
                if(selected >= s)
                {
                    unSelectActual();
                    selected--;
                    selectActual();
                }
                break;
            }
            s++;
        }
    }
}

void GUI_Element_List::selectNextElement()
{
    if(selected<(int)elements.size() - 1)
    {
        unSelectActual();
        selected++;
        selectActual();
    }
}

void GUI_Element_List::selectPrevElement()
{
    if(selected>0)
    {
        unSelectActual();
        selected--;
        selectActual();
    }
    else if(!elements.empty())
    {
        selected = 0;
        selectActual();
    }
    else
    {
        unSelectActual();
        selected = -1;
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void GUI_Element_List::setSelected(int s)
{
    unSelectActual();
    int size = (int)elements.size();
    selected = clamp(0,size - 1, s);
    selectActual();
}

void GUI_Element_List::setSelectedColor(u8 r, u8 g, u8 b, u8 a)
{
    selected_color = unvisual::getColor2D(r, g, b, a);
    
}

void GUI_Element_List::setUnselectedColor(u8 r, u8 g, u8 b, u8 a)
{
    unselected_color = unvisual::getColor2D(r, g, b, a);
}

void GUI_Element_List::setUntouchable(bool no_touch)
{
    untouchable = no_touch;
}

void GUI_Element_List::setSelectedDefault(int def)
{
    selected_default = def;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

int GUI_Element_List::getSelected() const
{
    return selected;
}

GUI_Element* GUI_Element_List::getElementSelected() const
{
    if(selected > -1)
    {
        return elements.at(selected);
    }
    return nullptr;
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

GUI_Element_List::~GUI_Element_List()
{
    for (auto &&element : elements)
    {
        if(element!=nullptr)
        {
            delete element;
            element = nullptr;
        }
    }

    elements.clear();
}

//=========================================
//=                 PRIVADO   	    	  =
//=========================================

void GUI_Element_List::selectActual()
{
    if(selected > -1 && selected < (int)elements.size())
    {
        elements.at(selected)->select(selected_color);
    }
}

void GUI_Element_List::unSelectActual()
{
    if(selected > -1 && selected < (int)elements.size())
    {
        elements.at(selected)->unSelect(unselected_color);
    }
}