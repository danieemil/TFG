#ifndef _UNVISUAL_ENGINE_
#define _UNVISUAL_ENGINE_

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include "Screen.h"
#include "Timepoint.h"

namespace unvisual
{
    // Gestión de librerías y dependencias
    void init();
    void initAPT();
    void deInit();
    void deInitAPT();

    // Monitor de APT STATE
    void aptState(APT_HookType hook, void* param);

    // Consola de depuración
    void initDebugger();
    void deInitDebugger();
    extern Debugger* debugger;


    // Renderizado
    void drawBegin();
    void drawOnCurrentScreen();
    void prepare2D();
    void drawEnd();

    void drawRectangle(const utilities::Vector2d<float>& pos, float depth, const utilities::Vector2d<float>& dimensions, u8 r, u8 g, u8 b, u8 a);
    void drawCircle(const utilities::Vector2d<float>& pos, float depth, float radius, u8 r, u8 g, u8 b, u8 a);

    void setCurrentScreen(Screen* sc);
    Screen* getCurrentScreen();


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