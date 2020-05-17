#ifndef _TILEMAP_
#define _TILEMAP_

#include "SpriteManager.h"
#include "Tile.h"
#include <iostream>
#include <sstream>
#include <fstream>


class Tilemap
{

public:
    // Constructores
    Tilemap(const char* tileset = nullptr, const char* tilemap = nullptr);
    Tilemap(const Tilemap&);

    Tilemap& operator= (const Tilemap&);

    // Métodos
    void render(const Vector2d<float>& view_pos = Vector2d<float>());
    void update();
    void loadTilemap(const char* tilemap);
    void generateTiles();
    void destroyTilemap();
    void destroyLevel();

    // Setters
    void setTileset(const char* spr_sheet);
    void setPosition(const Vector2d<float>& pos);

    // Getters
    const Vector2d<int>& getMapSize() const;
    const Vector2d<int>& getTileSize() const;
    const Vector2d<int>& getNumTiles() const;
    const Vector2d<float>& getPosition() const;

    // Destructor
    ~Tilemap();

private:

    SpriteManager manager;
    Tile*** tiles;
    int** level;

    Vector2d<int> tile_size;
    Vector2d<int> map_size;
    Vector2d<int> num_tiles;

    Vector2d<float> position;

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