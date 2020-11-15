#ifndef _GUI_ELEMENT_
#define _GUI_ELEMENT_

#include "Utilities.h"
#include "Unvisual_Engine.h"

using namespace utilities;


// Abstract class
class GUI_Element
{

public:
    // Constructores
    GUI_Element(const Vector2d<float>& pos, const Vector2d<float>& s);
    GUI_Element(const GUI_Element& ge);

    GUI_Element& operator= (const GUI_Element& ge);

    // Métodos
    virtual void processInput();
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool checkPressed(const Vector2d<float>& pos);

    virtual void select(u32 color);
    virtual void unSelect(u32 color);
    virtual void activate() = 0;

    // Setters
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setSize(const Vector2d<float>& s);

    // Getters
    virtual const Vector2d<float>& getPosition() const;
    virtual const Vector2d<float>& getSize() const;
    virtual bool getPressed() const;

    // Destructor
    virtual ~GUI_Element();

protected:

    Vector2d<float> position;
    Vector2d<float> size;

    bool pressed, selected;

};

#endif