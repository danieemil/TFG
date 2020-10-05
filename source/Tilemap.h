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
    Tilemap(const char* tileset = nullptr, const Vector2d<int>& n_tiles = Vector2d<int>(), int** tilemap = nullptr, const Vector2d<int>& s_tiles = Vector2d<int>());
    Tilemap(const Tilemap&);

    Tilemap& operator= (const Tilemap&);

    // Métodos
    void render(const Vector2d<float>& view_pos = Vector2d<float>());
    void update(const Vector2d<float>& pos_dif);
    void generateTilemap();
    void generateTiles();
    void destroyTilemap();
    void destroyLevel();
    void destroyPhysics();
    void addCollider(Collider* c);

    // Setters
    void setTileset(const char* tileset);
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
    std::vector<Collider*> colliders;

    Vector2d<int> tile_size;
    Vector2d<int> map_size;
    Vector2d<int> num_tiles;

    Vector2d<float> position;

};

#endif