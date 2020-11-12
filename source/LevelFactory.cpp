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
: world(w), actual_level(0), manager("romfs:/gfx/sprites.t3x"),
weapon_manager("romfs:/gfx/sprites.t3x")
{

}

LevelFactory::LevelFactory(const LevelFactory& lf)
: world(lf.world), actual_level(lf.actual_level), manager(lf.manager), weapon_manager(lf.weapon_manager)
{

}

LevelFactory& LevelFactory::operator= (const LevelFactory& lf)
{
    world = lf.world;
    actual_level = lf.actual_level;
    manager = lf.manager;
    weapon_manager = lf.weapon_manager;

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
    
    in.close();
}

void LevelFactory::save()
{


    ofstream out;
    out.open(save_file, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

    unvisual::debugger->print("Guardado en:");
    unvisual::debugger->print(save_file);
    unvisual::debugger->nextLine();
    unvisual::breakpoint();

    //Guardar nivel actual
    mem2file(out, actual_level);

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
        world->eraseWorld();
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

    int l = 0;

    //Guardar primer nivel
    mem2file(out, l);

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

    // Entidades
	
	// Configuramos el tileset que queremos usar
    const char* sprites_path = "romfs:/gfx/sprites.t3x";
	manager.setSprites(sprites_path);
    weapon_manager.setSprites(sprites_path);

        // Jugador
	Vector2d<float> player_position = Vector2d<float>(250.5f,150.5f);
    int player_weapon_type = -1;

    file2mem(in, &player_position.x);
    file2mem(in, &player_position.y);

    file2mem(in, &player_weapon_type);

    Player* player = world->getPlayer();

    Vector2d<float> player_init_orientation = Vector2d<float>(0.0f,-1.0f);

    if(player==nullptr)
    {
            // Gráficos del jugador
        Sprite* player_sprite = manager.createSprite(0);
        player_sprite->setCenter(Vector2d<float>(0.5f,0.5f));
        Vector2d<float> player_center = player_sprite->getCenter();

            // Colisiones del jugador
        CollisionFlag player_interests = CollisionFlag::enemy_hit | CollisionFlag::enemy_hurt;

            // Otros atributos del jugador
        int player_life = 11;
        Vector2d<float> player_max_vel = Vector2d<float>(400.0f,400.0f);
        Vector2d<float> player_max_accel = Vector2d<float>(INFINITY, INFINITY); // Máximo de fuerza que se le puede aplicar a un cuerpo
        Vector2d<float> player_frict = Vector2d<float>(40.0f,40.0f);
        float player_stunned_time = 0.5f;
        player = new Player(player_life, player_position, player_sprite, world, player_interests, player_init_orientation, player_max_vel, player_max_accel, player_frict, nullptr, player_stunned_time);
        player->getBody()->setRotationCenter(player_center);
        world->setPlayer(player);
    }

    player->setPosition(player_position);


    // Creamos el arma inicial del jugador
    Weapon* player_weapon = weapon_manager.createWeapon((weapon_type)player_weapon_type, player);
    player->equipWeapon(0);

    // La pantalla se moverá para intentar poner al jugador en el centro de la pantalla
    unvisual::setCurrentScreenTarget(&player->getRenderPosition());


        // Enemigos
    int number = 0;
    file2mem(in, &number);

    for (int i = 0; i < number; i++)
    {
        Vector2d<float> enemy_position = Vector2d<float>();
        int enemy_weapon_type = -1;
        int enemy_behaviour_type = 0;

        file2mem(in, &enemy_position.x);
        file2mem(in, &enemy_position.y);

        file2mem(in, &enemy_weapon_type);

        file2mem(in, &enemy_behaviour_type);

        // Gráficos del enemigo
        Sprite* enemy_sprite = manager.createSprite(2);

            // Colisiones del enemigo
        CollisionFlag enemy_interests = CollisionFlag::player_hurt;
        
        // Otros atributos del enemigo
        int enemy_life = 30;
        Vector2d<float> enemy_max_vel = Vector2d<float>(500.0f,500.0f);
        Vector2d<float> enemy_max_accel = Vector2d<float>(INFINITY, INFINITY);
        Vector2d<float> enemy_friction = Vector2d<float>(20.0f,20.0f);
        Vector2d<float> enemy_init_orientation = Vector2d<float>(0.0f,-1.0f);
        float enemy_stunned_time = 0.5f;

        // Comportamiento del enemigo
        BinaryTree* bt = AI::getBehaviour((AI::bt_types)enemy_behaviour_type);

        Enemy* enemy = new Enemy(enemy_life, enemy_position, enemy_sprite, world, enemy_interests, enemy_init_orientation, enemy_max_vel, enemy_max_accel, enemy_friction, nullptr, enemy_stunned_time, bt);
        world->addEntity(enemy);

    }

    in.close();

	world->setTilemap(t_map);
}