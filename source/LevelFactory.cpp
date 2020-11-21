#include "LevelFactory.h"
#include "AI_Engine.h"
#include "Game.h"
#include <unordered_map>

//Mapa que relaciona el nivel con los archivos que contienen los datos del nivel
const std::unordered_map<int, std::pair<const char*, const char*>> levels_map = 
{
    {0, {"romfs:/maps/testMap.mp","romfs:/gfx/TileSet.t3x"}},
    {1, {"romfs:/maps/testMap2.mp","romfs:/gfx/TileSet.t3x"}},
};

int LevelFactory::max_levels = levels_map.size();

// Archivo de guardado
const char* save_file = "save.sf";

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

LevelFactory::LevelFactory(World* w)
: world(w), actual_level(0)
{

}

LevelFactory::LevelFactory(const LevelFactory& lf)
: world(lf.world), actual_level(lf.actual_level)
{

}

LevelFactory& LevelFactory::operator= (const LevelFactory& lf)
{
    world = lf.world;
    actual_level = lf.actual_level;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void LevelFactory::init()
{

    if(world==nullptr) return;

    // Encontramos el archivo .mp en función del nivel en el que estamos
    auto it = levels_map.find(actual_level);
    if(it!=levels_map.end())
    {
        const char* level_file = it->second.first;
        const char* tileset_file = it->second.second;

        // Cargamos del archivo .mp el tilemap, su tileset y sus físicas
	    readBin(level_file, tileset_file);
    }
}

void LevelFactory::loadSave()
{
    ifstream in(save_file, std::ios::binary | std::ios::ate);
    in.seekg(0, std::ios::beg);

    // Obtener el nivel del archivo de guardado
    file2mem(in, &actual_level);

    // Obtener datos del jugador
    file2mem(in, &player_data.max_life);
    file2mem(in, &player_data.life);
    
    in.close();
}

void LevelFactory::save()
{
    ofstream out;
    out.open(save_file, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

    // Guardar nivel actual
    mem2file(out, actual_level);

    // Si el jugador no tiene vida se guarda el estado anterior
    if(world!=nullptr)
    {
        Player* player = world->getPlayer();
        if(player!=nullptr)
        {
            int max_life = player->getMaxLife();
            int life = player->getLife();
            if(life > 0)
            {
                player_data.max_life = max_life;
                player_data.life = life;
            }
        }
    }

    // Guardar vida máxima del jugador
    mem2file(out, player_data.max_life);

    // Guardar vida actual del jugador
    mem2file(out, player_data.life);

    out.close();
}

void LevelFactory::nextLevel()
{
    actual_level++;
    if(actual_level>=max_levels)
    {
        actual_level = 0;
    }
}

void LevelFactory::deInit()
{
    if(world!=nullptr)
    {
        world->deleteLevel();
    }
}

bool LevelFactory::checkSave()
{
    ifstream in;
    in.open(save_file, std::ofstream::binary);

    if(!in.is_open() || in.fail())
    {
        in.close();
        return false;
    }

    in.close();
    return true;
}

void LevelFactory::resetSave()
{
    ofstream out;
    out.open(save_file, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

    int level = 0;
    int max_life = 8;
    int life = 8;

    // Guardar primer nivel
    mem2file(out, level);

    // Guardar vida máxima del jugador
    mem2file(out, max_life);

    // Guardar vida inicial del jugador
    mem2file(out, life);


    out.close();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void LevelFactory::setWorld(World* w)
{
    world = w;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

World* LevelFactory::getWorld() const
{
    return world;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

LevelFactory::~LevelFactory()
{

}

//=========================================
//=               PRIVATE   	    	  =
//=========================================
void LevelFactory::readBin(const char* tilemap_path, const char* tileset_path)
{
    // Tilemap

	Vector2d<int> num_tiles = Vector2d<int>();
	Vector2d<int> tile_size = Vector2d<int>();
	int** level = nullptr;
	Tilemap* t_map = nullptr;

    ifstream in(tilemap_path, std::ios::binary | std::ios::ate);
    in.seekg(0, std::ios::beg);

    file2mem(in, &num_tiles.x);
    file2mem(in, &num_tiles.y);

    file2mem(in, &tile_size.x);
    file2mem(in, &tile_size.y);

    level = new int*[num_tiles.y];

    for (int i = 0; i < num_tiles.y; i++)
    {
        level[i] = new int[num_tiles.x];
        for (int j = 0; j < num_tiles.x; j++)
        {
            file2mem(in, &level[i][j]);
        }
    }

	t_map = new Tilemap(tileset_path, num_tiles, level, tile_size);

    for (int i = 0; i < num_tiles.y; i++)
    {
        delete[] level[i];
    }
    delete[] level;

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

        t_map->addCollider(new Collider(position, new AABB(min,max), CollisionFlag::none, CollisionFlag::none, CollisionType::col_static));
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

        t_map->addCollider(new Collider(position, new Circle(center,radius), CollisionFlag::none, CollisionFlag::none, CollisionType::col_static));
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
        
        t_map->addCollider(new Collider(position, new Convex(vertices), CollisionFlag::none, CollisionFlag::none, CollisionType::col_static));
    }

    world->setTilemap(t_map);

    // Entidades
        // Jugador
	Vector2d<float> player_position = Vector2d<float>(250.5f,150.5f);
    int player_weapon_type = -1;

    file2mem(in, &player_position.x);
    file2mem(in, &player_position.y);

    file2mem(in, &player_weapon_type);

    Player* player = world->getPlayer();

    if(player==nullptr)
    {
        player = world->createPlayer(player_position);
    }

    if(player->getWeapons().empty())
    {
        // Creamos el arma inicial del jugador
        world->createWeapon((WeaponType)player_weapon_type, player);
        if(player!=nullptr)
        {
            player->equipWeapon(0);
        }
    }

    player->setPosition(player_position);

    player->setMaxLife(player_data.max_life);
    player->setLife(player_data.life);

    

    // La pantalla se moverá para intentar poner al jugador en el centro de la pantalla
    unvisual::setCurrentScreenTarget(&player->getRenderPosition());
    unvisual::getCurrentScreen()->setPosition(Vector2d<float>(0,0));


        // Enemigos
    int number = 0;
    file2mem(in, &number);

    for (int i = 0; i < number; i++)
    {
        Vector2d<float> enemy_position = Vector2d<float>();
        int enemy_weapon_type = -1;
        int enemy_type = 0;

        file2mem(in, &enemy_position.x);
        file2mem(in, &enemy_position.y);

        file2mem(in, &enemy_weapon_type);

        file2mem(in, &enemy_type);

        // Crear al tipo de enemigo instanciable con su posición inicial
        Enemy* enemy = world->createEnemy((EnemyType)enemy_type, enemy_position);

        // Crear su arma y asignársela
        world->createWeapon((WeaponType)enemy_weapon_type, enemy);

        if(enemy!=nullptr)
        {
            enemy->equipWeapon(0);
        }
    }


    // Interactables
    file2mem(in, &number);

    for (int i = 0; i < number; i++)
    {

        Vector2d<float> interactable_position = Vector2d<float>();
        int interactable_type = -1;
        int interactable_value = 0;

        file2mem(in, &interactable_position.x);
        file2mem(in, &interactable_position.y);

        file2mem(in, &interactable_type);

        file2mem(in, &interactable_value);

        // Crear interactuable con los datos proporcionados

        Interactable* inter = world->createInteractable((InteractableType)interactable_type, interactable_position, interactable_value);

    }

    in.close();
}