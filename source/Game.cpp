#include "Game.h"
#include "Colliders_data.h"

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


	// Creamos al jugador
	Vector2d<float> player_position = Vector2d<float>(250.5f,150.5f);

		// Gráficos del jugador
	Sprite* player_sprite = manager->createSprite(0);

		// Colisiones del jugador
	Shape* player_shape = physics::getSpriteShape(player_sprite->getManager()->getPath(), player_sprite->getIndex());
	Collider* player_body = new Collider(player_position, player_shape, CollisionFlag::player, CollisionType::col_dynamic);

		// Otros atributos del jugador
	Vector2d<float> player_max_vel = Vector2d<float>(40.0f,40.0f);
	Vector2d<float> player_accel = Vector2d<float>(10.0f, 10.0f);
	Vector2d<float> player_decel = Vector2d<float>(10.0f,10.0f);
	Player* player = new Player(player_position, player_sprite, world, player_body, player_max_vel, player_accel, player_decel);
	world->setPlayer(player);

        // Arma del jugador
        Sprite* weapon_sprite = manager->createSprite(1);
        Weapon* player_weapon = new Weapon(1.0f, Vector2d<float>(0.0f, -10.0f), Vector2d<float>(), weapon_sprite, nullptr, nullptr, player);
        player->equipWeapon(0);

    // La pantalla se moverá para intentar poner al jugador en el centro de la pantalla
    screen.setTargetPosition(&player->getRenderPosition());
	

	// Creamos una entidad(al parecer es instanciable :/)
	Vector2d<float> entity_position = Vector2d<float>(140, 180);

		// Gráficos de la entidad
	Sprite* entity_sprite = manager->createSprite(0);

		// Posibles colisiones de la entidad(Probando)
	Vector2d<size_t> entity_size = entity_sprite->getSize();
	//Shape* entity_rect2 = new AABB(Vector2d<float>(0,0), Vector2d<float>(entity_size.x, entity_size.y/2.0f));
	//Shape* entity_rect1 = new AABB(Vector2d<float>(0,0), Vector2d<float>(entity_size.x/5.0f,entity_size.y));
	//Shape* entity_circ1 = new Circle(Vector2d<float>(entity_size.x/2.0f,entity_size.y/4.0f), entity_size.x*8.0f);
	//Collider* entity_body = new Collider(entity_position, entity_circ1, CollisionFlag::enemy, CollisionType::col_static);
	//Entity* entity = new Entity(entity_position, entity_sprite, world, entity_body);
	//world->addEntity(entity);

	
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
        }
    }
    if(world!=nullptr)
    {
        world->updatePlayer();
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
		
        Debugger* debug = unvisual::debugger;

		debug->setColumn(1);
		debug->setRow(14);
		debug->print("Time: ");
		debug->print(std::to_string(svcGetSystemTick()));
		debug->nextLine();
        debug->setColumn(1);
		debug->setRow(15);
		debug->print("Max :  ");
		debug->print("18446744073709551615");
		debug->nextLine();
		debug->nextLine();
        debug->setColumn(1);
		debug->setRow(17);
		debug->print("Delta Time:");
		debug->print(dt);
		debug->nextLine();
        debug->setColumn(1);
		debug->setRow(18);
        debug->print("Screen x:");
		debug->print(unvisual::getCurrentScreen()->getPosition().x);
		debug->nextLine();
        debug->setColumn(1);
		debug->setRow(19);
        debug->print("Screen y:");
		debug->print(unvisual::getCurrentScreen()->getPosition().y);
		debug->nextLine();


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