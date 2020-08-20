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
                    tiles[i][j]->render(view_pos);
                }
            }
        }
    }
}

void Tilemap::update(const Vector2d<float>& pos_dif)
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

    for (auto &&collider : colliders)
    {
        if(collider!=nullptr)
        {
            collider->setPosition(collider->getPosition() + pos_dif);
        }
    }
    
}

void Tilemap::loadTilemap(const char* tilemap)
{
    destroyLevel();
    destroyTilemap();
    destroyPhysics();

    readBin(tilemap);

    generateTiles();
    update(position);

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
                            tiles[i][j] = new Tile(p, 0.0f, sp);
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
    position = position + pos;
    update(pos);
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


//=========================================
//=               PRIVATE   	    	  =
//=========================================
void Tilemap::readBin(const char* file_path)
{
    // Tiles

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

    // Físicas
    int c_number = 0;
    Vector2d<float> position, center, max, min;
    float radius = 0.0f;

    // Rectángulos
    file2mem(in, &c_number);

    for (int i = 0; i < c_number; i++)
    {
        file2mem(in, &position.x);
        file2mem(in, &position.y);

        file2mem(in, &min.x);
        file2mem(in, &min.y);

        file2mem(in, &max.x);
        file2mem(in, &max.y);

        colliders.push_back(new Collider(position, new AABB(min,max), CollisionFlag::none, CollisionFlag::none, CollisionType::col_static));
    }

    // Círculos
    file2mem(in, &c_number);

    for (int i = 0; i < c_number; i++)
    {
        file2mem(in, &position.x);
        file2mem(in, &position.y);

        file2mem(in, &center.x);
        file2mem(in, &center.y);

        file2mem(in, &radius);

        colliders.push_back(new Collider(position, new Circle(center,radius), CollisionFlag::none, CollisionFlag::none, CollisionType::col_static));
    }

    // Convexos
    file2mem(in, &c_number);
    for (int i = 0; i < c_number; i++)
    {
        file2mem(in, &position.x);
        file2mem(in, &position.y);

        int s_number = 0;
        file2mem(in, &s_number);

        std::vector<Vector2d<float>> vertices;
        Vector2d<float> vertex;
        for (int j = 0; j < s_number; j++)
        {
            file2mem(in, &vertex.x);
            file2mem(in, &vertex.y);
            vertices.push_back(vertex);
        }
        
        colliders.push_back(new Collider(position, new Convex(vertices), CollisionFlag::none, CollisionFlag::none, CollisionType::col_static));
    }
}