#ifndef _INPUT_MANAGER_
#define _INPUT_MANAGER_

#include "map"
#include "3ds.h"
#include "Utilities.h"

using namespace utilities;


namespace input
{
    enum class N3DS_buttons
    {
        Key_A,
        Key_B,
        Key_Select,
        Key_Start,
        Key_DRight,
        Key_DLeft,
        Key_DUp,
        Key_DDown,
        Key_R,
        Key_L,
        Key_X,
        Key_Y,
        Key_Touch,
        Key_CPAD_Right,
        Key_CPAD_Left,
        Key_CPAD_Up,
        Key_CPAD_Down,
    };

    void IM_init();

    void IM_scan();

    bool isPressed(N3DS_buttons key);
    bool isHeld(N3DS_buttons key);
    bool isReleased(N3DS_buttons key);

    Vector2d<u16> getPositionTouched();

    void IM_deInit();


}
#endif