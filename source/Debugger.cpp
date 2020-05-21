#include "Debugger.h"




Debugger::Debugger(N3DS_screenV screen)
{
    consoleInit((gfxScreen_t)((u8)screen), &console);
    consoleSelect(&console);
    
    row = 1;
    column = 1;
}

void Debugger::setColumn(int l_column)
{
    if(l_column>0) column = l_column;
    else column = 1;
}

void Debugger::setRow(int l_row)
{
    if(l_row>0) row = l_row;
    else row = 1;
}

int Debugger::getColumn() const
{
    return column;
}

int Debugger::getRow() const
{
    return row;
}

void Debugger::clear()
{
    consoleClear();
    row = 1;
    column = 1;
}

void Debugger::print(int p)
{
    printLocation();
    column += std::to_string(p).length();
    column++;
    std::cout<<std::to_string(p);
}

void Debugger::print(u8 u)
{
    printLocation();
    column += std::to_string(u).length();
    column++;
    std::cout<<std::to_string(u);
}

void Debugger::print(u32 u)
{
    printLocation();
    column += std::to_string(u).length();
    column++;
    std::cout<<std::to_string(u);
}

void Debugger::print(u64 u)
{
    printLocation();
    column += std::to_string(u).length();
    column++;
    std::cout<<std::to_string(u);
}

void Debugger::print(float f)
{
    printLocation();
    column += std::to_string(f).length();
    column++;
    std::cout<<std::to_string(f);
}

void Debugger::print(double d)
{
    printLocation();
    column += std::to_string(d).length();
    column++;
    std::cout<<std::to_string(d);
}

void Debugger::print(std::string s)
{
    printLocation();
    column += s.length();
    column++;
    std::cout<<s;
}

void Debugger::print(void* v)
{
    printLocation();
    column = column + 10;
    std::cout<<v;
}

void Debugger::nextLine()
{
    row++;
    column = 1;
}

Debugger::~Debugger()
{
    consoleClear();
}

void Debugger::printLocation()
{
    std::string location = "\x1b["+std::to_string(row)+";"+std::to_string(column)+"H";

    std::cout<<location;
}

void Debugger::stop()
{
    while (true){}
    
}