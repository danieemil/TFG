#ifndef _INPUT_MANAGER_
#define _INPUT_MANAGER_

#include "iostream"
#include "3ds.h"
#include <map>


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

    void init();

    



    void deInit();

    namespace
    {
        std::map<N3DS_buttons,u32> key_mapping;
    }


}
#endif