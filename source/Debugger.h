#ifndef _DEBUGGER_
#define _DEBUGGER_

#include <iostream>
#include "3ds.h"

enum N3DS_screenV
{
    N3DS_TOP = 0,
    N3DS_BOTTOM = 1
};

enum N3DS_screenH
{
    N3DS_LEFT = 0,
    N3DS_RIGHT = 1
};

class Debugger
{
public:
    
    Debugger(N3DS_screenV screen);

    void setColumn(int l_column);
    void setRow(int l_row);

    int getColumn() const;
    int getRow() const;

    void clear();

    void print(int p);
    void print(u8 u);
    void print(u32 u);
    void print(float f);
    void print(double d);
    void print(std::string s);
    void print(void* v);

    void nextLine();

    ~Debugger();

private:
    PrintConsole console;
    int column = 0;
    int row = 0;

    void printLocation();

};
#endif