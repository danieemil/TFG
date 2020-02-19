#include "InputManager.h"
#include "Debugger.h"

namespace input
{

    namespace
    {

        touchPosition t_position;

        std::map<N3DS_buttons,u32> key_mapping = 
        {
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_A,KEY_A),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_B,KEY_B),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_Select,KEY_SELECT),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_Start,KEY_START),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_DRight,KEY_DRIGHT),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_DLeft,KEY_DLEFT),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_DUp,KEY_DUP),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_DDown,KEY_DDOWN),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_R,KEY_R),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_L,KEY_L),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_X,KEY_X),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_Y,KEY_Y),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_Touch,KEY_TOUCH),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_CPAD_Right,KEY_CPAD_RIGHT),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_CPAD_Left,KEY_CPAD_LEFT),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_CPAD_Up,KEY_CPAD_UP),
            std::pair<N3DS_buttons,u32>(N3DS_buttons::Key_CPAD_Down,KEY_CPAD_DOWN),
        };
    }


    void IM_init()
    {
        hidInit();
    }

    void IM_scan()
    {
        hidScanInput();
    }

    bool isPressed(N3DS_buttons key)
    {
        auto it = key_mapping.find(key);
        u32 key_mapped = it->second;

        return (hidKeysDown() & key_mapped);
    }

    bool isHeld(N3DS_buttons key)
    {

        auto it = key_mapping.find(key);
        u32 key_mapped = it->second;

        return (hidKeysHeld() & key_mapped);
    }

    bool isReleased(N3DS_buttons key)
    {
        auto it = key_mapping.find(key);
        u32 key_mapped = it->second;

        return (hidKeysUp() & key_mapped);
    }

    Vector2d<u16> getPositionTouched()
    {
        hidTouchRead(&t_position);
        return Vector2d<u16>(t_position.px,t_position.py);
    }

    void IM_deInit()
    {
        hidExit();
    }
}