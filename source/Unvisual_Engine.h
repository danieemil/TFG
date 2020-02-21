#ifndef _UNVISUAL_ENGINE_
#define _UNVISUAL_ENGINE_

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include "Utilities.h"
#include "Screen.h"
#include "Timepoint.h"

namespace unvisual
{
    // Gestión de librerías y dependencias
    void init();
    void deInit();


    // Consola de depuración
    void initDebugger();
    extern Debugger* debugger;


    // Renderizado
    void drawBegin();
    void drawOnScreen(Screen* sc);
    void prepare2D(Screen* sc);
    void drawEnd();


    // Tiempo
    void addTimepoint(Timepoint* t);
    void eraseTimepoint(Timepoint* t);
    void clearAllTimepoints();
    void stopClock();
    void resumeClock();
    float getTimeStopped();
    bool clockStopped();
    u64 getPausedPoint();
    




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

        utilities::Vector2d<u16> getPositionTouched();

        void IM_deInit();

    }



}
#endif