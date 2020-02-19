#ifndef _DEBUGGER_
#define _DEBUGGER_

#include "iostream"
#include "3ds.h"

enum N3DS_screen
{
    N3DS_TOP = 0,
    N3DS_BOTTOM = 1
};

class Debugger
{
public:
    
    Debugger(N3DS_screen screen);

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