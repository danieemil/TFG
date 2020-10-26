#ifndef _GUI_ELEMENT_LIST_
#define _GUI_ELEMENT_LIST_

#include "GUI_Element.h"
#include "vector"

class GUI_Element_List
{
public:
    // Constructores
    GUI_Element_List(u32 unsel_color = unvisual::getColor2D(0,0,0,255),
    u32 sel_color = unvisual::getColor2D(255,0,0,255), bool untouchable = true, int def = 0);
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
    void setSelectedColor(u8 r, u8 g, u8 b, u8 a);
    void setUnselectedColor(u8 r, u8 g, u8 b, u8 a);
    void setUntouchable(bool no_touch);
    void setSelectedDefault(int def);

    // Getters
    int getSelected() const;
    GUI_Element* getElementSelected() const;

    // Destructor
    ~GUI_Element_List();

private:

    std::vector<GUI_Element*> elements;

    int selected = -1;

    u32 unselected_color;
    u32 selected_color;

    bool untouchable = true;

    int selected_default;

    void selectActual();
    void unSelectActual();

};

#endif