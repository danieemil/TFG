#ifndef _DEBUGGER_
#define _DEBUGGER_

#include "iostream"
#include "3ds.h"


namespace debug
{
    enum N3DS_screen
    {
        N3DS_TOP = 0,
        N3DS_BOTTOM = 1
    };

    extern int column;
    extern int row;

    void init(N3DS_screen screen);

    void locate(int l_column, int l_row);

    void clear();

    void print(int p);
    void print(u8 u);
    void print(float f);
    void print(double d);
    void print(std::string s);
    void print(void* v);

}
#endif