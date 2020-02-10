#include "Debugger.h"


namespace debug
{
    int row;
    int column;

    namespace
    {

        PrintConsole console;

        void printLocation()
        {
            std::string location = "\x1b["+std::to_string(row)+";"+std::to_string(column)+"H";

            std::cout<<location;
        }

        void nextLine()
        {
            row++;
        }
    }

    void init(N3DS_screen screen)
    {
        consoleInit((gfxScreen_t)((u8)screen), &console);
        consoleSelect(&console);
        
        row = 1;
        column = 1;
    }

    void locate(int l_column, int l_row)
    {
        if(l_row>0) row = l_row;
        else row = 1;
        
        if(l_column>0) column = l_column;
        else column = 1;
    }

    void clear()
    {
        consoleClear();
        row = 1;
        column = 1;
    }

    void print(int p)
    {
        printLocation();
        std::cout<<std::to_string(p);
        nextLine();
    }

    void print(u8 u)
    {
        printLocation();
        std::cout<<std::to_string(u);
        nextLine();
    }

    void print(float f)
    {
        printLocation();
        std::cout<<std::to_string(f);
        nextLine();
    }

    void print(double d)
    {
        printLocation();
        std::cout<<std::to_string(d);
        nextLine();
    }

    void print(std::string s)
    {
        printLocation();
        std::cout<<s;
        nextLine();
    }

    void print(void* v)
    {
        printLocation();
        std::cout<<v;
        nextLine();
    }
}