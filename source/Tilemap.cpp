#include "Tilemap.h"
#include "Physics_Engine.h"
using namespace std;


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Tilemap::Tilemap(const char* tileset, const Vector2d<int>& n_tiles, int** tilemap, const Vector2d<int>& s_tiles)
{
    if(tileset!=nullptr)
    {
        manager.setSprites(tileset);
    }

    num_tiles = n_tiles;
    tile_size = s_tiles;

    if(tilemap!=nullptr)
    {
        level = new int*[num_tiles.y];
        for (int i = 0; i < num_tiles.y; i++)
        {
            level[i] = new int[num_tiles.x];
            for (int j = 0; j < num_tiles.x; j++)
            {
                level[i][j] = tilemap[i][j];
            }
        }
        
    }

    map_size = num_tiles * tile_size;

    if(level!=nullptr)
    {
        generateTiles();
    }

}

Tilemap::Tilemap(const Tilemap& d)
{
    manager = d.manager;

    tiles = nullptr;
    level = d.level;

    tile_size = d.tile_size;
    map_size = d.map_size;
    num_tiles = d.num_tiles;
}

Tilemap& Tilemap::operator= (const Tilemap& d)
{
    manager = d.manager;

    destroyTilemap();

    tile_size = d.tile_size;
    map_size = d.map_size;
    num_tiles = d.num_tiles;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Tilemap::render(const Vector2d<float>& view_pos)
{
    if(tiles!=nullptr)
    {
        for (int i = 0; i < num_tiles.y; i++)
        {
            for (int j = 0; j < num_tiles.x; j++)
            {
                if(tiles[i][j]!=nullptr)
                {
                    tiles[i][j]->render(view_pos);
                }
            }
        }
    }
}

void Tilemap::moveTilemap(const Vector2d<float>& dif)
{

    position = position + dif;

    if(tiles!=nullptr)
    {
        Vector2d<float> pos = position;

        for (int i = 0; i < num_tiles.y; i++)
        {
            pos.x = position.x;
            for (int j = 0; j < num_tiles.x; j++)
            {
                if(tiles[i][j]!=nullptr)
                {
                    tiles[i][j]->setPosition(pos);
                }
                pos.x = pos.x + tile_size.x;
            }
            pos.y = pos.y + tile_size.y;
        }
    }

    for (auto &&collider : colliders)
    {
        if(collider!=nullptr)
        {
            collider->setPosition(collider->getPosition() + dif);
        }
    }
}

void Tilemap::generateTiles()
{
    if(manager.getSpriteCollection()!=NULL)
    {
        if(tile_size.x > 0 && tile_size.y > 0)
        {
            if(num_tiles.x > 0 && num_tiles.y > 0)
            {
                Vector2d<float> p = position;

                tiles = new Tile**[num_tiles.y];
                for (int i = 0; i < num_tiles.y; i++)
                {
                    p.x = position.x;
                    tiles[i] = new Tile*[num_tiles.x];
                    for (int j = 0; j < num_tiles.x; j++)
                    {
                        int sprite_id = level[i][j] - 1;
                        Sprite* sp = manager.createSprite(sprite_id);
                        tiles[i][j] = nullptr;
                        if(sp!=nullptr)
                        {
                            tiles[i][j] = new Tile(p, sp);
                        }
                        p.x = p.x + tile_size.x;
                    }
                    p.y = p.y + tile_size.y;
                }
            }
        }
    }
}

void Tilemap::destroyTilemap()
{
    if(tiles!=nullptr)
    {
        for (int i = 0; i < num_tiles.y; i++)
        {
            for (int j = 0; j < num_tiles.x; j++)
            {
                delete tiles[i][j];
            }
            
            delete[] tiles[i];
        }
        delete[] tiles;
    }
    tiles = nullptr;
}

void Tilemap::destroyLevel()
{
    if(level!=nullptr)
    {
        for (int i = 0; i < num_tiles.y; i++)
        {
            delete[] level[i];
        }

        delete[] level;
    }
    level = nullptr;
}

void Tilemap::destroyPhysics()
{
    for (auto &&collider : colliders)
    {
        if(collider!=nullptr)
        {
            delete collider;
            collider = nullptr;
        }
    }
    colliders.clear();
}

void Tilemap::addCollider(Collider* c)
{
    colliders.push_back(c);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Tilemap::setTileset(const char* tileset)
{

    destroyTilemap();

    tiles = nullptr;

    if(tileset!=nullptr)
    {
        manager.setSprites(tileset);
    }

    if(level!=nullptr)
    {
        generateTiles();
    }
}

void Tilemap::setPosition(const Vector2d<float>& pos)
{
    Vector2d<float> dif = pos - position;
    moveTilemap(dif);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

const Vector2d<int>& Tilemap::getMapSize() const
{
    return map_size;
}

const Vector2d<int>& Tilemap::getTileSize() const
{
    return tile_size;
}

const Vector2d<int>& Tilemap::getNumTiles() const
{
    return num_tiles;
}

const Vector2d<float>& Tilemap::getPosition() const
{
    return position;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Tilemap::~Tilemap()
{
    destroyLevel();
    destroyTilemap();
    destroyPhysics();
}