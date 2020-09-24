#include "Game.h"
#include "Colliders_data.h"
#include "AI_Engine.h"

using namespace std;
using namespace unvisual::input;



// Singleton
Game* Game::p_instance = 0;
Game* Game::Instance()
{
    if(p_instance)
    {
        return p_instance;
    }else
    {
        p_instance = new Game();
        return p_instance;
    }
}



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game::Game()
{
    manager = new SpriteManager();
    world = new World();
    running = true;

    init();
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Game::init()
{

    running = true;

    // Creamos una "Ventana" para dibujos en 3D y la ubicamos en la pantalla de abajo
	screen.setScreen(MAX_WIDTH_DOWN, MAX_HEIGHT_DOWN, N3DS_screenV::N3DS_BOTTOM);
	screen.setBackground(u8(255),u8(255),u8(255),u8(255));
	unvisual::setCurrentScreen(&screen);


	const char* sprites_path = "romfs:/gfx/sprites.t3x";
	const char* tileset_path = "romfs:/gfx/TileSet.t3x";
	const char* tilemap_path = "romfs:/maps/testMap.mp";
	const char* tilemap_path2 = "romfs:/maps/testMap2.mp";

    // Configuramos el tileset que queremos usar
	setSpriteManager(sprites_path);

	// Creamos el fondo con el tileset que necesita el mapa.
	world->setTilemap(tileset_path, tilemap_path2);


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
    screen.setTargetPosition(&player->getRenderPosition());
	
	// Delta time
	dt = 0.0f;
	delta_time.reset();

    // Ya que solo se están usando gráficos en 2D
    unvisual::prepare2D();
}

void Game::render()
{
    if(world!=nullptr)
    {
        world->render();
    }
}

void Game::update()
{
    if(update_time.getElapsed()>upd)
    {
        update_time.reset();
        if(world!=nullptr)
        {
            world->updateEntities();
            world->updateEntitiesCollisions();
        }
    }
    if(world!=nullptr)
    {
        world->updatePlayer();
        world->updatePlayerCollisions();
    }
    
}

void Game::updateCollisions()
{
    physics::step(dt);
}

void Game::interpolate()
{
    float rp = clamp(0.0f,1.0f,update_time.getElapsed()/upd);
    if(world!=nullptr)
    {
        world->interpolate(rp);
    }
}

void Game::loop()
{
    // Main loop
	while (aptMainLoop() && running)
	{
		
		dt = delta_time.getElapsed();
		delta_time.reset();

		// Escaneamos las teclas pulsadas(Inputs de la N3DS)
		IM_scan();
		
		processInput();

        update();

        updateCollisions();

        interpolate();

		unvisual::drawBegin();
		unvisual::drawOnCurrentScreen();

		// Renderizamos el juego entero en la patnalla seleccionada
		render();

		unvisual::drawEnd();
	}
}

void Game::processInput()
{

    if(aptIsHomePressed() || true)
    {
        unvisual::resumeClock();
    }

    // Si se pulsa 'start' se sale del programa
    if (isPressed(N3DS_buttons::Key_Start))
    {
        running = false;
        return;
    }

    if(isPressed(N3DS_buttons::Key_X))
    {
        if(unvisual::clockStopped())
        {
            unvisual::debugger->setRow(20);
            unvisual::debugger->print(unvisual::getTimeStopped());
            unvisual::resumeClock();
        }
        else
        {
            unvisual::debugger->setRow(20);
            unvisual::debugger->print(unvisual::getTimeStopped());
            unvisual::stopClock();
        }
        
    }

    if(isHeld(N3DS_buttons::Key_A) || isPressed(N3DS_buttons::Key_A))
    {
        unvisual::debugger->clear();
    }
    
    if(isPressed(N3DS_buttons::Key_B))
    {
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("He pulsado la B " + std::to_string(unvisual::debugger->getRow()) + " veces");
        unvisual::debugger->nextLine();
    }

    if(world!=nullptr)
    {
        world->processInput();
    }
}

bool Game::isRunning()
{
    return running;
}

void Game::stopRunning()
{
    running = false;
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Game::setWorldEntity(Entity* e)
{
    world->addEntity(e);
}

void Game::setWorldPlayer(Player* p)
{
    world->setPlayer(p);
}

void Game::setSpriteManager(const char* spr_path)
{
    manager->setSprites(spr_path);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

World* Game::getWorld() const
{
    return world;
}

SpriteManager* Game::getSpriteManager() const
{
    return manager;
}

float Game::getDeltaTime() const
{
    return dt;
}

float Game::getUpdateTime() const
{
    float u = update_time.getElapsed();
    if(u>upd) u = upd;
    return u;
}

const float Game::getUpd() const
{
    return upd;
}

Player* Game::getPlayer() const
{

    if(world!=nullptr)
    {
        return world->getPlayer();
    }

    return nullptr;
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

void Game::over()
{
    delete this;
}

Game::~Game()
{
    if(world!=nullptr)
    {
        delete world;
    }

    if(manager!=nullptr)
    {
        delete manager;
    }
}