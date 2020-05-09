#include "Game.h"

using namespace std;
using namespace unvisual::input;


Game* game;

int main(int argc, char* argv[])
{

	//Inicializamos todo
	unvisual::init();
	unvisual::initDebugger();

	const char* sprites_path = "romfs:/gfx/sprites.t3x";
	const char* tileset_path = "romfs:/gfx/TileSet.t3x";
	const char* tilemap_path = "romfs:/maps/testMap.mp";
	const char* tilemap_path2 = "romfs:/maps/testMap2.mp";

	// Creamos el juego
	game = new Game();
	game->setSpriteManager(sprites_path);

	World* game_world = game->getWorld();

	// Creamos el fondo
	game_world->setTilemap(tileset_path, tilemap_path2);
	//game_world->getTilemap()->setPosition(Vector2d<float>(20,15));

	auto ms = game_world->getTilemap()->getMapSize();

	// Creamos al jugador
	Vector2d<float> player_position = Vector2d<float>(50,50);
	Sprite* player_sprite = game->getSpriteManager()->createSprite(0);
	Vector2d<size_t> player_size = player_sprite->getSize();
	Collider* player_body = new Collider(player_position, new AABB(Vector2d<float>(0,0), Vector2d<float>(player_size.x, player_size.y/2.0f)));
	player_body->addShape(new AABB(Vector2d<float>(0,player_size.y/2.0f), Vector2d<float>(player_size.x/5.0f,player_size.y)));
	Player* player = new Player(player_position, player_sprite, game_world, player_body);
	game_world->addPlayer(player);

	const Vector2d<float>* p_position = &player->getPosition();
	
	// Creamos entidades

	Vector2d<float> entity_position = Vector2d<float>(140, 180);
	Sprite* entity_sprite = game->getSpriteManager()->createSprite(0);
	Vector2d<size_t> entity_size = entity_sprite->getSize();
	Collider* entity_body = new Collider(entity_position, new AABB(Vector2d<float>(0,0), Vector2d<float>(entity_size.x, entity_size.y/2.0f)));
	entity_body->addShape(new AABB(Vector2d<float>(0,entity_size.y/2.0f), Vector2d<float>(entity_size.x/5.0f,entity_size.y)));
	Entity* entity = new Entity(entity_position, entity_sprite, game_world, entity_body);
	game_world->addEntity(entity);
	physics::addStatic(entity_body);


	Vector2d<size_t> sc_size = Vector2d<size_t>(MAX_WIDTH_DOWN, MAX_HEIGHT_DOWN);

	// Creamos una "Ventana" para dibujos en 3D y la ubicamos en la pantalla de abajo
	Screen* sc = new Screen(sc_size.x, sc_size.y, N3DS_screenV::N3DS_BOTTOM);
	sc->setBackground(255,0,0,255);
	sc->setTargetPosition(p_position);
	unvisual::setCurrentScreen(sc);
	
	// Delta time
	float dt = 0.0f;
	Timepoint initTimeLoop;
	Timepoint total;
	Timepoint limit;
	float seg = 0.0f;

	limit.operator+(100.0f);

	// Main loop
	while (aptMainLoop() && game->isRunning())
	{
		
		dt = initTimeLoop.getElapsed();
		initTimeLoop.reset();



		seg = total.getElapsed();
		
		unvisual::debugger->setColumn(1);
		unvisual::debugger->setRow(10);
		unvisual::debugger->print("Time: ");
		unvisual::debugger->print(std::to_string(svcGetSystemTick()));
		unvisual::debugger->nextLine();
		unvisual::debugger->print("Max :  ");
		unvisual::debugger->print("18446744073709551615");
		unvisual::debugger->nextLine();
		unvisual::debugger->nextLine();
		unvisual::debugger->print("Delta Time:");
		unvisual::debugger->print(dt);
		unvisual::debugger->nextLine();
		unvisual::debugger->nextLine();
		unvisual::debugger->print("Time(seg):");
		unvisual::debugger->print(seg);
		unvisual::debugger->nextLine();
		unvisual::debugger->nextLine();
		unvisual::debugger->print("Left(seg):");
		unvisual::debugger->print(limit - initTimeLoop);


		// Escaneamos las teclas pulsadas(Inputs de la N3DS)
		IM_scan();
		
		
		game->processInput();

		if(limit.getElapsed()!=-1 && !unvisual::clockStopped())
		{
			break;
		}

		game->update();

		unvisual::drawBegin();
		unvisual::drawOnCurrentScreen();
		unvisual::prepare2D();

		// Renderizamos el juego entero en la patnalla seleccionada
		game->render();

		unvisual::drawEnd();

	}
	unvisual::debugger->clear();
	unvisual::debugger->nextLine();

	if(true)
	{
		if(game!=nullptr)
		{
			delete game;
			game = nullptr;
		}
		
		initTimeLoop.~Timepoint();
		total.~Timepoint();
		limit.~Timepoint();
		
		unvisual::clearAllTimepoints();

		bool yes = true;

		while (yes)
		{
			IM_scan();

			if(isPressed(N3DS_buttons::Key_Select))
			{
				yes = false;
			}
		}
	}
	
	
	if(game!=nullptr)
	{
		delete game;
		game = nullptr;
	}
	
	if(sc!=nullptr)
	{
		delete sc;
		sc = nullptr;
	}
	
	// Deinicializar todo(si no se hace, habrán memory leaks)
	unvisual::deInit();

}
