#include "Game.h"
#include "InputManager.h"

using namespace std;
using namespace input;



static Game game;


// En esta función están todos los inicializadores necesarios
void init()
{
	// Inicializador por defecto de los gráficos básicos
	gfxInitDefault();

	// Inicializador del InputManager
	IM_init();

	// Permitimos acceder a la ROMFS (Read Only Memory File System)
	// Eso significa que podemos acceder a la carpeta romfs poniendo "romfs:"
	romfsInit();

	// Inicializador de Citro3D(Gráficos especializados del 3D y renderizado)
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	// Inicializador de Citro2D(Gráficos especializados del 2D)
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

	C2D_Prepare();

	//Cargamos los sprites
	game.setSpriteManager("romfs:/gfx/sprites.t3x");
}


// Libera la memoria de las librerías que se usan en la N3DS
void deInit()
{

	// Liberamos la memoria de la librería Citro3D
	C3D_Fini();
	
	// Liberamos la memoria de la librería Citro2D
	C2D_Fini();

	// Liberamos la memoria del "InputManager"
	IM_deInit();

	// Liberamos la memoria que se usa para los gráficos básicos
	gfxExit();

	// Salimos de la Romfs
	romfsExit();
}


int main(int argc, char* argv[])
{

	//Inicializamos todo
	init();

	unvisual::init();


	game.getWorld()->addPlayer(new Player(Vector2d<float>(),
	game.getSpriteManager()->createSprite(1)));

	game.getWorld()->addEntity(new Entity(Vector2d<float>(),
	game.getSpriteManager()->createSprite(0)));

	

	

	// Creamos una "Ventana" para dibujos en 3D y la ubicamos en la pantalla de abajo
	C3D_RenderTarget* bot = C3D_RenderTargetCreate(240,320,GPU_RB_RGBA8,GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(bot, GFX_BOTTOM, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);
	
	// Delta time
	int dt = 0;
	u64 initTimeLoop = 0;


	// Main loop
	while (aptMainLoop() && game.isRunning())
	{
		
		dt = svcGetSystemTick() - initTimeLoop;
		initTimeLoop = svcGetSystemTick();
		




		// Escaneamos las teclas pulsadas(Inputs de la N3DS)
		IM_scan();
		
		

		game.processInput();

		game.update();

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

		// Cuando se llama a esta función establecemos que en el frame actual se pintará lo siguiente 
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		//Lo siguiente es todo lo que hay por debajo de esta línea de código hasta C3D_FrameEnd(0):

		// Limpiamos las dos pantallas antes de dibujar en ellas
		int background_color = C2D_Color32(255,0,0,255);
		C3D_FrameDrawOn(bot);
		C3D_RenderTargetClear(bot,C3D_CLEAR_ALL, background_color, 0);
		C2D_SceneBegin(bot);

		game.render();

		// Nos aseguramos que todo se ha dibujado 
		C2D_Flush();

		// A partir de esta línea acaba lo que se dibujaría en el frame actual y pasa al siguiente
		C3D_FrameEnd(0);

	}

	

	C3D_RenderTargetDelete(bot);

	
	

	// Deinicializar todo(si no se hace, habrán memory leaks)

	unvisual::deInit();

	deInit();

}
