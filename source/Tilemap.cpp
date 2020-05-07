#include "Tilemap.h"
#include "Physics_Engine.h"
using namespace std;


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Tilemap::Tilemap(const char* spr_sheet, const char* tilemap)
{
    if(spr_sheet!=nullptr)
    {
        manager.setSprites(spr_sheet);
    }

    tiles = nullptr;

    level = nullptr;

    if(tilemap!=nullptr)
    {
        loadTilemap(tilemap);
    }
}

Tilemap::Tilemap(const Tilemap& d)
{
    manager = d.manager;

    tiles = nullptr;

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
                    tiles[i][j]->drawSprite(view_pos);
                }
            }
        }
    }
}

void Tilemap::update()
{
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
}

void Tilemap::loadTilemap(const char* tilemap)
{
    destroyLevel();
    destroyTilemap();

    readBin(tilemap);

    generateTiles();

}

void Tilemap::generateTiles()
{
    if(manager.getSpriteCollection()!=NULL)
    {
        if(tile_size.x > 0 && tile_size.y > 0)
        {
            if(num_tiles.x > 0 && num_tiles.y > 0)
            {

                map_size.x = num_tiles.x * tile_size.x;
                map_size.y = num_tiles.y * tile_size.y;

                Vector2d<float> p;

                p.x = position.x;
                p.y = position.y;

                tiles = new Sprite**[num_tiles.y];
                for (int i = 0; i < num_tiles.y; i++)
                {
                    p.x = position.x;
                    tiles[i] = new Sprite*[num_tiles.x];
                    for (int j = 0; j < num_tiles.x; j++)
                    {
                        int sprite_id = level[i][j] - 1;
                        tiles[i][j] = manager.createSprite(sprite_id);
                        if(tiles[i][j]!=nullptr)
                        {
                            tiles[i][j]->setPosition(p);
                            tiles[i][j]->setDepth(-1);

                            physics::addStatic(new Collider(new AABB(p, Vector2d<float>(0,0), Vector2d<float>(tile_size.x, tile_size.y))));
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
                manager.deleteSprite(tiles[i][j]);
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


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Tilemap::setTileset(const char* spr_sheet)
{

    destroyTilemap();

    tiles = nullptr;

    if(spr_sheet!=nullptr)
    {
        manager.setSprites(spr_sheet);
    }

    if(level!=nullptr)
    {
        generateTiles();
    }
}

void Tilemap::setPosition(const Vector2d<float>& pos)
{
    position = pos;
    update();
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
}


//=========================================
//=               PRIVATE   	    	  =
//=========================================
void Tilemap::readBin(const char* file_path)
{
    ifstream in(file_path, std::ios::binary | std::ios::ate);
    in.seekg(0, std::ios::beg);

    file2mem(in, &num_tiles.x);
    file2mem(in, &num_tiles.y);

    file2mem(in, &tile_size.x);
    file2mem(in, &tile_size.y);

    level = new int*[num_tiles.y];

    for (int i = 0; i < num_tiles.y; i++)
    {
        level[i] = new int[num_tiles.x];
    }

    for (int i = 0; i < num_tiles.y; i++)
    {
        for (int j = 0; j < num_tiles.x; j++)
        {
            file2mem(in, &level[i][j]);
        }
    }
}