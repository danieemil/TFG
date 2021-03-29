#include <iostream>
#include <sstream>
#include <fstream>
#include "tinyxml2.h"
#include "vector"

using namespace tinyxml2;
using namespace std;


// Le pasas por donde estás leyendo y dónde lo quieres almacenar
template<class T>
void file2mem(ifstream &in, T* n)
{
    unsigned long hSize = sizeof(T);
    char* buffer = new char[hSize];
    in.read(buffer, hSize);
    
    memcpy(n,buffer,hSize);

    delete [] buffer;
}



template<class T>
void mem2file(ofstream &out, T n)
{
    unsigned long hSize = sizeof(n);

    char* bData  = reinterpret_cast<char*>(&n);

    out.write(bData, hSize);
}