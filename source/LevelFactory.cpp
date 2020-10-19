#include "LevelFactory.h"
#include "AI_Engine.h"
#include "Game.h"
#include <unordered_map>

//Mapa conversor de key (int) a la Enemy-Definition correspondiente.
const std::unordered_map<int, const char*> levels_map = 
{
    {0, "romfs:/maps/testMap.mp"},
    {1, "romfs:/maps/testMap2.mp"},
};


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

LevelFactory::LevelFactory(World* w)
: world(w)
{

}

LevelFactory::LevelFactory(const LevelFactory& lf)
: world(lf.world)
{

}

LevelFactory& LevelFactory::operator= (const LevelFactory& lf)
{
    world = lf.world;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void LevelFactory::init(int level)
{

    if(world==nullptr) return;


    // Encontramos el archivo .mp en función del nivel en el que estamos
    auto it = levels_map.find(level);
    if(it!=levels_map.end())
    {
        const char* level_file = it->second;

        // Cargamos del archivo .mp el tilemap, su tileset y sus físicas
	    readBin(level_file);
    }

    // Esto debería estar incluido en el .mp que indica todos los datos sobre el nivel.
	const char* sprites_path = "romfs:/gfx/sprites.t3x";
	const char* tileset_path = "romfs:/gfx/TileSet.t3x";

	// Configuramos el tileset que queremos usar
	world->setSpriteManager(sprites_path);

	SpriteManager* manager = world->getSpriteManager();


    // CREACIÓN DE ENTIDADES

    /* Creamos una entidad(al parecer es instanciable :/)
	Vector2d<float> entity_position = Vector2d<float>(140, 180);

		// Gráficos de la entidad
	Sprite* entity_sprite = manager->createSprite(0);

		// Posibles colisiones de la entidad(Probando)
	Vector2d<size_t> entity_size = entity_sprite->getSize();
	Shape* entity_rect2 = new AABB(Vector2d<float>(0,0), Vector2d<float>(entity_size.x, entity_size.y/2.0f));
	Shape* entity_rect1 = new AABB(Vector2d<float>(0,0), Vector2d<float>(entity_size.x/5.0f,entity_size.y));
	Shape* entity_circ1 = new Circle(Vector2d<float>(entity_size.x/2.0f,entity_size.y/4.0f), entity_size.x*8.0f);
	Collider* entity_body = new Collider(entity_position, entity_circ1, CollisionFlag::enemy, CollisionType::col_static);
	Entity* entity = new Entity(entity_position, entity_sprite, world, entity_body);
	world->addEntity(entity);
    */

    //Creamos un enemigo genérico
	Vector2d<float> enemy_position = Vector2d<float>(140, 180);

		// Gráficos de la entidad
	Sprite* enemy_sprite = manager->createSprite(2);

		// Posibles colisiones de la entidad(Probando)
	Vector2d<size_t> enemy_size = enemy_sprite->getSize();
	Shape* enemy_shape = physics::getSpriteShape(enemy_sprite->getManager()->getPath(), enemy_sprite->getIndex());
	Collider* enemy_body = new Collider(enemy_position, enemy_shape, CollisionFlag::enemy_hit, CollisionFlag::player_hurt, CollisionType::col_dynamic);
	
    // Otros atributos del enemigo
    int enemy_life = 30;
	Vector2d<float> enemy_max_vel = Vector2d<float>(500.0f,500.0f);
	Vector2d<float> enemy_max_accel = Vector2d<float>(INFINITY, INFINITY);
	Vector2d<float> enemy_friction = Vector2d<float>(20.0f,20.0f);
    Vector2d<float> enemy_init_orientation = Vector2d<float>(0.0f,-1.0f);
    float enemy_stunned_time = 0.5f;

    // Comportamiento del enemigo
    BinaryTree* bt = AI::getBehaviour(AI::bt_types::enemy_agressive);

	Enemy* enemy = new Enemy(enemy_life, enemy_position, enemy_sprite, world, enemy_body, enemy_init_orientation, enemy_max_vel, enemy_max_accel, enemy_friction, nullptr, enemy_stunned_time, bt);
	world->addEntity(enemy);

	// Creamos al jugador
	Vector2d<float> player_position = Vector2d<float>(250.5f,150.5f);

		// Gráficos del jugador
	Sprite* player_sprite = manager->createSprite(0);
    player_sprite->setCenter(Vector2d<float>(0.5f,0.5f));

		// Colisiones del jugador
	Shape* player_shape = physics::getSpriteShape(player_sprite->getManager()->getPath(), player_sprite->getIndex());
	Collider* player_body = new Collider(player_position, player_shape, CollisionFlag::player_hit, CollisionFlag::enemy_hit | CollisionFlag::enemy_hurt, CollisionType::col_dynamic);
    Vector2d<float> player_center = player_sprite->getCenter();
    player_body->setRotationCenter(player_center);


		// Otros atributos del jugador
    int player_life = 100;
	Vector2d<float> player_max_vel = Vector2d<float>(400.0f,400.0f);
	Vector2d<float> player_max_accel = Vector2d<float>(INFINITY, INFINITY); // Máximo de fuerza que se le puede aplicar a un cuerpo
	Vector2d<float> player_frict = Vector2d<float>(40.0f,40.0f);
    Vector2d<float> player_init_orientation = Vector2d<float>(0.0f,-1.0f);
    float player_stunned_time = 0.5f;
	Player* player = new Player(player_life, player_position, player_sprite, world, player_body, player_init_orientation, player_max_vel, player_max_accel, player_frict, nullptr, player_stunned_time);
	world->setPlayer(player);

        // Arma del jugador
        Sprite* weapon_sprite = manager->createSprite(1);
        auto w_s = weapon_sprite->getSize();
        weapon_sprite->setCenter(Vector2d<float>(0.5f,0.5f));

        Shape* weapon_shape = physics::getSpriteShape(weapon_sprite->getManager()->getPath(), weapon_sprite->getIndex());
        Collider* weapon_body = new Collider(player_position, weapon_shape, CollisionFlag::player_hurt, CollisionFlag::enemy_hit, CollisionType::col_none);

        int weapon_damage = 10;
        float weapon_knockback = 200.0f;
        float weapon_time_attack = 0.2f;
        Vector2d<float> weapon_relative_position_attacking = Vector2d<float>(0.0f,-10.0f);
        Weapon* player_weapon = new Weapon(weapon_damage, weapon_knockback, weapon_time_attack, weapon_relative_position_attacking, weapon_sprite, nullptr, weapon_body, player_init_orientation, player);
        player->equipWeapon(0);

    // La pantalla se moverá para intentar poner al jugador en el centro de la pantalla
    unvisual::setCurrentScreenTarget(&player->getRenderPosition());
}

void LevelFactory::deInit()
{
    if(world!=nullptr)
    {
        world->eraseWorld();
    }
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
void LevelFactory::readBin(const char* file_path)
{
    // Tilemap
	const char* tileset_path = "romfs:/gfx/TileSet.t3x";

	Vector2d<int> num_tiles = Vector2d<int>();
	Vector2d<int> tile_size = Vector2d<int>();
	int** level = nullptr;
	Tilemap* t_map = nullptr;

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

	t_map = new Tilemap(tileset_path, num_tiles, level, tile_size);

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
}