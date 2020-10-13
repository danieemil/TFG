#include "GUI_Element_List.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

GUI_Element_List::GUI_Element_List()
: selected(-1)
{

}

GUI_Element_List::GUI_Element_List(const GUI_Element_List& gel)
{

}

GUI_Element_List& GUI_Element_List::operator= (const GUI_Element_List& gel)
{

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
        }
    }



    // Procesar el panel táctil
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_Touch))
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
        elements.at(selected)->select();
    }
}

void GUI_Element_List::unSelectActual()
{
    if(selected > -1 && selected < (int)elements.size())
    {
        elements.at(selected)->unSelect();
    }
}