#ifndef _GUI_ELEMENT_LIST_
#define _GUI_ELEMENT_LIST_

#include "GUI_Element.h"
#include "vector"

class GUI_Element_List
{
public:
    // Constructores
    GUI_Element_List();
    GUI_Element_List(const GUI_Element_List& gel);

    GUI_Element_List& operator= (const GUI_Element_List& gel);

    // Métodos
    void processInput();
    void update();
    void render();

    void addElement(GUI_Element* element);
    void removeElement(GUI_Element* element);

    void selectNextElement();
    void selectPrevElement();

    // Setters
    void setSelected(int s);

    // Getters
    int getSelected() const;
    GUI_Element* getElementSelected() const;

    // Destructor
    ~GUI_Element_List();

private:

    std::vector<GUI_Element*> elements;

    int selected = -1;

    void selectActual();
    void unSelectActual();

};

#endif