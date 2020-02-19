#include "Unvisual_Engine.h"


namespace unvisual
{

    Debugger* debugger = nullptr;

    void init()
    {
        debugger = new Debugger(N3DS_screen::N3DS_TOP);
    }


    void deInit()
    {
        if(debugger!=nullptr)
        {
            delete debugger;
            debugger = nullptr;
        }
    }
}