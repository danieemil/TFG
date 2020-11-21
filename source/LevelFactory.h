#ifndef _LEVELFACTORY_
#define _LEVELFACTORY_

#include "World.h"
#include "EntityManager.h"

class LevelFactory
{

public:
    // Constructores
    LevelFactory(World* w = nullptr);
    LevelFactory(const LevelFactory& lf);

    LevelFactory& operator= (const LevelFactory& lf);

    // Métodos
    void init();
    void loadSave();
    void save();
    void nextLevel();
    void deInit();

    static bool checkSave();
    static void resetSave();

    // Setters
    void setWorld(World* w);


    // Getters
    World* getWorld() const;

    // Destructor
    ~LevelFactory();

    static int max_levels;


private:

    World* world;


    // Datos del archivo de guardado
    int actual_level;

    struct PlayerData
    {
        int max_life;
        int life;
    };

    PlayerData player_data;

    void readBin(const char* tilemap_path, const char* tileset_path);

    template<class T>
    static void file2mem(ifstream &in, T* n)
    {
        unsigned long hSize = sizeof(T);
        char* buffer = new char[hSize];
        in.read(buffer, hSize);

        memcpy(n,buffer,hSize);

        delete[] buffer;
    }

    template<class T>
    static void mem2file(ofstream &out, T n)
    {
        unsigned long hSize = sizeof(n);

        char* bData  = reinterpret_cast<char*>(&n);

        out.write(bData, hSize);
    }
    

};

#endif