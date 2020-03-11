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
	const char* tileset_path = "romfs:/gfx/tileset.t3x";
	const char* tilemap_path = "romfs:/maps/testMap.mp";

	// Creamos el juego
	game = new Game();
	game->setSpriteManager(sprites_path);

	// Creamos el fondo
	game->getWorld()->setTilemap(tileset_path, tilemap_path);
	//game->getWorld()->getTilemap()->setPosition(Vector2d<float>(20,15));

	// Creamos al jugador
	Sprite* spr = game->getSpriteManager()->createSprite(0);
	game->getWorld()->addPlayer(new Player(Vector2d<float>(50,50), spr));
	
	// Creamos entidades
	game->getWorld()->addEntity(new Entity(Vector2d<float>(140, 180),
	game->getSpriteManager()->createSprite(0)));
	


	Vector2d<size_t> sc_size = Vector2d<size_t>(MAX_WIDTH_DOWN, MAX_HEIGHT_DOWN);

	// Creamos una "Ventana" para dibujos en 3D y la ubicamos en la pantalla de abajo
	Screen* sc = new Screen(sc_size.x, sc_size.y, N3DS_screenV::N3DS_BOTTOM);
	sc->setBackground(255,0,0,255);
	
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
		unvisual::drawOnScreen(sc);
		unvisual::prepare2D(sc);

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
