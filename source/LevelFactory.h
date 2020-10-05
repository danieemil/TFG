#ifndef _LEVELFACTORY_
#define _LEVELFACTORY_

#include "World.h"

class LevelFactory
{

public:
    // Constructores
    LevelFactory(World* w = nullptr);
    LevelFactory(const LevelFactory& lf);

    LevelFactory& operator= (const LevelFactory& lf);

    // Métodos
    void init(int level);
    void deInit();

    // Setters
    void setWorld(World* w);


    // Getters
    World* getWorld() const;

    // Destructor
    ~LevelFactory();

protected:

    World* world;

private:

    void readBin(const char* file_path);

    template<class T>
    void file2mem(ifstream &in, T* n)
    {
        unsigned long hSize = sizeof(T);
        char* buffer = new char[hSize];
        in.read(buffer, hSize);

        memcpy(n,buffer,hSize);
    }

};

#endif