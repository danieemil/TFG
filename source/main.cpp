#include "Game.h"
#include "Debugger.h"

using namespace std;


// Configuración de la ventana de render
#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

/////////////
// Sprites //
/////////////

static Game game;
static SpriteManager manager;
static World world;

void initSprites()
{

	manager.setSprites("romfs:/gfx/sprites.t3x");
	game.setSpriteManager(&manager);
	game.setWorld(&world);

}

// En esta función están todos los inicializadores necesarios
void init()
{
	// Inicializador por defecto de los gráficos básicos
	gfxInitDefault();

	// Inicializador del HID(Input)
	hidInit();

	// Permitimos acceder a la ROMFS (Read Only Memory File System)
	// Eso significa que podemos acceder a la carpeta romfs poniendo "romfs:"
	romfsInit();

	// Inicializador de Citro3D(Gráficos especializados del 3D y renderizado)
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	// Inicializador de Citro2D(Gráficos especializados del 2D)
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

	C2D_Prepare();

	//Cargamos los sprites
	initSprites();
}


// Libera la memoria de las librerías que se usan en la N3DS
void deInit()
{

	// Liberamos la memoria de la librería Citro3D
	C3D_Fini();
	
	// Liberamos la memoria de la librería Citro2D
	C2D_Fini();

	// Liberamos la memoria del "InputManager"
	hidExit();

	// Liberamos la memoria que se usa para los gráficos básicos
	gfxExit();

	// Salimos de la Romfs
	romfsExit();
}



void sceneRenderSprites(C3D_RenderTarget* screen)
{
	C2D_Prepare();
	C2D_SceneBegin(screen);

	game.getWorld()->render();

	C2D_Flush();
}



int main(int argc, char* argv[])
{

	//Inicializamos todo
	init();

	game.getWorld()->addEntity(new Combat_Character(Vector2d<float>(),
	game.getSpriteManager()->createSprite(0)));

	debug::init(debug::N3DS_screen::N3DS_TOP);


	// Creamos una "Ventana" para dibujos en 3D y la ubicamos en la pantalla de abajo
	C3D_RenderTarget* bot = C3D_RenderTargetCreate(240,320,GPU_RB_RGBA8,GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(bot, GFX_BOTTOM, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);
	

	// Main loop
	while (aptMainLoop())
	{
		// Escaneamos las teclas pulsadas(Inputs de la N3DS)
		hidScanInput();

		// Guardamos en 'kDown' todos los inputs pulsados
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		
		// Si se pulsa 'start' se sale del programa
		if (kDown & KEY_START)
			break;
		
		if(kDown & KEY_A || kHeld & KEY_A)
			game.update();
		
		if(kDown & KEY_B)
		{
			debug::column = 1;
			debug::print("He pulsado la B " + std::to_string(debug::row) + " veces");
		}
			
		

		// Cuando se llama a esta función establecemos que en el frame actual se pintará lo siguiente 
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		//Lo siguiente es todo lo que hay por debajo de esta línea de código hasta C3D_FrameEnd(0):

		// Limpiamos las dos pantallas antes de dibujar en ellas
		int background_color = C2D_Color32(255,0,0,255);
		C3D_FrameDrawOn(bot);
		C3D_RenderTargetClear(bot,C3D_CLEAR_ALL, background_color, 0);

		sceneRenderSprites(bot);

		// A partir de esta línea acaba lo que se dibujaría en el frame actual y pasa al siguiente
		C3D_FrameEnd(0);

	}

	C3D_RenderTargetDelete(bot);

	// Deinicializar todo(si no se hace, habrán memory leaks)
	deInit();
	
	
	return 0;
}
