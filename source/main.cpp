#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <3ds.h>
#include "vshader_shbin.h"
#include <citro2d.h>
#include "image_bin.h"



///////////////////////////////////////////////////////
// 						NOTAS                        //
///////////////////////////////////////////////////////
/*



	-	Para dibujar 2D y 3D por pantalla hay que primero preparar la GPU para dibujar
		en el modo y luego dibujar. Las preparaciones del modo se borran cada vez
		que se prepara el otro modo, por lo que se tienen que volver a hacer.
		3D -> void bindC3D();
		2D -> void C2D_Prepare();

	-	PrintConsole no puede estar en la misma pantalla con el 2D y/o 3D a nivel
		básico.


Investigaciones y recursos:

	-	Investigar 3D	: LearnOpenGL, Documentación de Citro3D, Ejemplos DevkitPro
	-	Investigar 2D	: Documentación de Citro2D, Ejemplos DevkitPro.
	-	Investigar N3DS	: Completar todos los ejemplos de DevkitPro entendiendolos y
						  comentándolos.(Eso implica acabar las investigaciones previas)

*/


///////////////////////////////////////////////////////
// 						Texto2D                      //
///////////////////////////////////////////////////////

// Texto a mostrar
static const char text[] =
"Esto es un texto en 2D"
;

// Variables necesarias que se usan para DIBUJAR texto
C2D_TextBuf b_static;	// Se crea y se define una vez
C2D_TextBuf b_dynamic;	// Se crea y se define una vez por frame
C2D_Text texts[2];





///////////////////////////////////////////////////////
// 						Shaders                      //
///////////////////////////////////////////////////////

#define CLEAR_COLOR 0x68D0D8FF

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

// Definimos lo que es una Posición (tiene coordenadas x, y, z)
struct position
{
	float x;
	float y;
	float z;
};

struct color
{
	float r;
	float g;
	float b;
	float a;
};

struct vertex
{
	position p;
	color c;
};


// Los vértices de manera muy básica los tomamos como posiciones en el espacio
static const vertex vertex_list[] =
{
	{{	 0.0f, 220.0f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}},
	{{-100.0f,  60.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}},
	{{+100.0f,  60.0f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}},
	{{-100.0f, 180.0f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}},
	{{+100.0f, 180.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}},
	{{	 0.0f,  20.0f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}},
};

// Los índices de los vértices definidos arriba
static const s16 index_list[] =
{
	5,
	4,
	3,
	2,
	1,
	0,
};

// Punto de acceso a todos los datos de un shader
static DVLB_s* shader_dvlb;

// Programa que gestiona vertex y geometry shader
static shaderProgram_s program;

// Identificador que le dice al programa dónde está, dentro del vertex shader,
// el uniform de las matrices de proyección
static int uLoc_projection;

// Matrices de 4x4 (estas matrices las usamos para respresentar las proyecciones en los shaders)
static C3D_Mtx projection_top, projection_bot;

// Configura el paso de atributos al shader
static C3D_AttrInfo attrInfo;

// Zona de datos de donde coge los datos de los vértices para pasárselos al shader
static C3D_BufInfo bufInfo;

// Apunta al principio de donde guardamos los vértices
static void* vbo_data; 			// Vertex Buffer Object

// Aquí guardamos los índices de los vértices
static void* index_data;


// Número de vértices que tendrá
#define vboCount (sizeof(vertex_list)/sizeof(vertex_list[0]))
#define indexCount (sizeof(index_list)/sizeof(index_list[0]))


/////////////
// Sprites //
/////////////

// Hoja que contiene todos los sprites
static C2D_SpriteSheet all_sprites;

// Sprite de prueba
static C2D_Sprite test_sprite;

// Filtro para pintar las esquinas del sprite
static C2D_ImageTint tint;



// Dependiendo del modo, se muestra lo que he aprendido de las librerías de la n3ds
static int mode = -1;

// Configura las consolas para poder escribir texto
void defineConsoles()
{
	//Creamos consolas vacías
	PrintConsole bottom;

	// Asignamos estas consolas vacías a su pantalla
	consoleInit(GFX_BOTTOM, &bottom);

	// Seleccionamos la consola por la que queremos que se
	// imprima el texto
	consoleSelect(&bottom);

	// Imprimirmos texto en la fila 15, columna 19 de la consola
	std::cout << "\x1b[15;19H" << "Hello lower world!" << std::endl;
	std::cout << "\x1b[17;05H" << "Este vbo tiene "<< vboCount << " vertices" << std::endl;

	consoleClear();

}


// Inicializadores para los shaders
void initShaders()
{
	// Relacionamos la variable que representa al vertex shader, con el archivo que lo define
	shader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);

	// Inicializamos el programa que gestionará los shaders
	shaderProgramInit(&program);

	// Establece dentro del programa de los shaders, qué vertex shader vamos a usar
	shaderProgramSetVsh(&program, shader_dvlb->DVLE);

	// Vinculamos Citro3D para que utilice "program"(los shaders que gestiona)
	C3D_BindProgram(&program);


	// Obtenemos la ubicación de los uniforms del vertex shader
	uLoc_projection = shaderInstanceGetUniformLocation(program.vertexShader, "projection");


	// Configuramos lo que va a recibir el vertex shader y como lo va a recibir
	
	// Posiciones y color

	// Inicializamos el """configurador de atributos"""
	AttrInfo_Init(&attrInfo);
	// En el primer registro de input de la GPU(v0) recibirá 3 Floats = posición 
	AttrInfo_AddLoader(&attrInfo, 0, GPU_FLOAT, 3);
	// En el segundo registro de input de la GPU(v1) recibirá "algo fijo"
	AttrInfo_AddLoader(&attrInfo, 1, GPU_FLOAT, 4);
	//AttrInfo_AddFixed(attrInfo, 1);
	// Ese "algo fijo" será el color cuyo rango en los shaders es (0.0 - 1.0)
	//C3D_FixedAttribSet(1,1.0,1.0,1.0,1.0f); //[Blanco]


	// Matrices de proyección

	// Esta función establece lo que se va a ver según los rangos que le pongamos.

	// Un vértice cuyas coordenadas -200<X<200, 0<Y<240, 0<Z<1 se podrá ver
	Mtx_OrthoTilt(&projection_top,-200.0f,200.0f,0.0f,240.0f,0.0f,1.0f,true);
	
	// Un vértice cuyas coordenadas -160<X<160, 0<Y<240, 0<Z<1 se podrá ver
	Mtx_OrthoTilt(&projection_bot,-160.0f,160.0f,0.0f,240.0f,0.0f,1.0f,true);

	// Reservamos espacio para los vértices y apuntamos al principio ("vbo")
	vbo_data = linearAlloc(sizeof(vertex_list));
	// Copiamos y pegamos nuestros vértices a donde hemos reservado
	memcpy(vbo_data, vertex_list, sizeof(vertex_list));

	// Hacemos lo mismo para los índices
	index_data = linearAlloc(sizeof(index_list));
	memcpy(index_data, index_list, sizeof(index_list));


	BufInfo_Init(&bufInfo);
	BufInfo_Add(&bufInfo, vbo_data, sizeof(vertex),2,0x210);


	C3D_TexEnv* env = C3D_GetTexEnv(0);
	C3D_TexEnvInit(env);
	C3D_TexEnvSrc(env,C3D_Both,GPU_PRIMARY_COLOR,GPU_PRIMARY_COLOR,GPU_PRIMARY_COLOR);
	C3D_TexEnvFunc(env,C3D_Both, GPU_REPLACE);

}

void init2D()
{
	// Inicializador de Citro2D(Gráficos especializados del 2D)
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

	C2D_Prepare();
}


void init3D()
{

	// Inicializador de Citro3D(Gráficos especializados del 3D y renderizado)
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	// Ahora vamos a los shaders
	initShaders();
}

void initText()
{
	// Creamos el buffer dónde estará el texto con tamaño 4096
	b_static = C2D_TextBufNew(4096);
	b_dynamic = C2D_TextBufNew(4096);

	// Ponemos el texto en el buffer y se lo asignamos a la variable "texts" que se puede dibujar
	C2D_TextParse(texts,b_static,text);

	// Optimiza, no hay más
	C2D_TextOptimize(texts);
	
}

void initSprites()
{
	// Cargamos la hoja con todos los sprites
	all_sprites = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");

	// De la hoja de sprites sacamos el sprite con la imagen de prueba
	C2D_SpriteFromSheet(&test_sprite,all_sprites,0);

	// Pintamos de colores las esquinas del sprite

	u32 blue = C2D_Color32(0,0,255,255);
	u32 red = C2D_Color32(255,0,0,255);
	u32 green = C2D_Color32(0,255,0,255);
	u32 background_color = C2D_Color32(255,0,0,255);

	tint.corners[0].color = blue;
	tint.corners[0].blend = 0.75f;
	tint.corners[1].color = green;
	tint.corners[1].blend = 0.75f;
	tint.corners[2].color = red;
	tint.corners[2].blend = 0.75f;
	tint.corners[3].color = 0;
	tint.corners[3].blend = 0.75f;
}

// En esta función están todos los inicializadores necesarios
void init()
{
	// Inicializador por defecto de los gráficos básicos
	gfxInitDefault();

	// Inicializador del HID(Input)
	hidInit();

	init3D();

	init2D();
	
	//Configuramos el "texto"(text.h)
	initText();

	//Cargamos los sprites
	initSprites();
}


// Libera la memoria de las librerías que se usan en la N3DS
void deInit()
{

	// Liberamos datos asociados a los shaders
	// Liberamos el espacio que habíamos reservado para los vértices y sus índices
	linearFree(vbo_data);
	linearFree(index_data);
	shaderProgramFree(&program);
	DVLB_Free(shader_dvlb);


	// Limpia y destruye los buffers
	C2D_TextBufDelete(b_static);
	C2D_TextBufDelete(b_dynamic);

	// Liberamos la memoria de la hoja de sprites
	C2D_SpriteSheetFree(all_sprites);

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



// Dibujamos en la pantalla que nos pasen por parámetro en 2D
void sceneRender2D(C3D_RenderTarget* screen)
{
	// Habilita el dibujado en 2D e inhabilita el dibujado en 3D
	C2D_Prepare();

	// Esta función devuelve un número entero que representa el color que le pasas por R, G, B, A
	// En este caso el color es totalmente AZUL y OPACO
	int blue = C2D_Color32(0,0,255,255);
	int red = C2D_Color32(255,0,0,255);
	int green = C2D_Color32(0,255,0,255);
	int background_color = C2D_Color32(255,0,0,255);
		
	// Limpia lo que se ha seteado como "target"(en este caso es la pantalla de arriba)
	// También dibuja toda la pantalla del color "background_color"
	//C2D_TargetClear(screen, background_color);

	// Esta función hace se pueda dibujar en el "target"
	C2D_SceneBegin(screen);

	// Dibujamos el texto que ha sido asignado a "texts"
	C2D_DrawText(texts,0,0,0,0.5,1,1);

	// Dibuja un rectángulo con arriba a la izquierda con 300 píxeles de ancho y 30 de alto
	C2D_DrawRectSolid(10,120,0,300,30,blue);

	// Dibuja un rectángulo con cada borde de un color en específico, lo que crea un degradado
	C2D_DrawRectangle(10,180,0,300,30,red,blue,blue,red);

	C2D_DrawTriangle(200,100,red,215,80,green,230,100,blue,0);

	C2D_Flush();

}

// Habilita el dibujado en 3D e inhabilita el dibujado en 2D
void bindC3D()
{
	C3D_BindProgram(&program);
	C3D_SetAttrInfo(&attrInfo);
	C3D_SetBufInfo(&bufInfo);

	C3D_TexEnv* env = C3D_GetTexEnv(0);
	C3D_TexEnvInit(env);
	C3D_TexEnvSrc(env,C3D_Both,GPU_PRIMARY_COLOR,GPU_PRIMARY_COLOR,GPU_PRIMARY_COLOR);
	C3D_TexEnvFunc(env,C3D_Both, GPU_REPLACE);
}



// Dibujamos en la pantalla que nos pasen por parámetro en 3D
void sceneRender3D(C3D_RenderTarget* screen)
{

	bindC3D();

	C3D_FrameDrawOn(screen);

	// Le pasamos al vertex shader, la matriz de proyección(4x4) mediante uniforms
	// Su ubicación dentro del shader la obtenemos con "uLoc_projection"
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER,uLoc_projection,screen->screen ? &projection_bot : &projection_top);

	// Dibujamos el array de vértices almacenado en "vbo"
	//C3D_DrawArrays(GPU_TRIANGLE_STRIP,0,vboCount);

	// Dibujamos el array de vértices teniendo en cuenta sus índices
	C3D_DrawElements(GPU_TRIANGLES,indexCount,C3D_UNSIGNED_SHORT, index_data);
}

void sceneRenderSprites(C3D_RenderTarget* screen)
{
	C2D_Prepare();
	C2D_SceneBegin(screen);

	// Dibujando los sprites
	C2D_DrawSpriteTinted(&test_sprite, &tint);
}


// Dibuja el texto dinámico que explica que se muestra en la pantalla de abajo
void textIt(C3D_RenderTarget* screen)
{
	C2D_Prepare();
	C2D_SceneBegin(screen);
	C2D_DrawText(&texts[1],0,25,110,0.5f,0.75f,0.75f);
	C2D_Flush();
}



int main(int argc, char* argv[])
{
	
	// Permitimos acceder a la ROMFS (Read Only Memory File System)
	// Eso significa que podemos acceder a la carpeta romfs poniendo "romfs:"
	romfsInit();

	//Inicializamos todo
	init();

	//Configuramos las "consolas"(console.h) y escribimos texto por pantalla
	//defineConsoles();

	// Creamos una "Ventana" para dibujos en 2D y la ubicamos en la pantalla de arriba
	C3D_RenderTarget* top = C3D_RenderTargetCreate(240,400,GPU_RB_RGBA8,GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(top, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

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
		
		// Si se pulsa 'start' se sale del programa
		if (kDown & KEY_START)
			break;
	
		if (kDown & KEY_A)
		{
			mode = 0;
		}else
		if (kDown & KEY_B)
		{
			mode = 1;
		}else
		if (kDown & KEY_X)
		{
			mode = 2;
		}else
		if (kDown & KEY_Y)
		{
			mode = 3;
		}
		

		// Cuando se llama a esta función establecemos que en el frame actual se pintará lo siguiente 
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		//Lo siguiente es todo lo que hay por debajo de esta línea de código hasta C3D_FrameEnd(0):

		// Limpiamos las dos pantallas antes de dibujar en ellas
		int background_color = C2D_Color32(255,0,0,255);

		C3D_FrameDrawOn(top);
		C3D_RenderTargetClear(top,C3D_CLEAR_ALL, background_color, 0);

		C3D_FrameDrawOn(bot);
		C3D_RenderTargetClear(bot,C3D_CLEAR_ALL, background_color, 0);

		textIt(top);


		switch (mode)
		{
		// Solo 2D y texto
		case 0:

			C2D_TextBufClear(b_dynamic);
			C2D_TextParse(&texts[1],b_dynamic,"Elementos de texto y figuras en 2D");
			C2D_TextOptimize(&texts[1]);

			sceneRender2D(bot);
			break;

		// Solo 3D
		case 1:

			C2D_TextBufClear(b_dynamic);
			C2D_TextParse(&texts[1],b_dynamic,"Triangulos basicos con shaders en 3D");
			C2D_TextOptimize(&texts[1]);

			sceneRender3D(bot);
			break;

		// 2D y 3D
		case 2:

			C2D_TextBufClear(b_dynamic);
			C2D_TextParse(&texts[1],b_dynamic,"Escena que tiene elementos en 2D y 3D");
			C2D_TextOptimize(&texts[1]);

			sceneRender3D(bot);
			sceneRender2D(bot);
			break;

		// Sprites
		case 3:
			
			C2D_TextBufClear(b_dynamic);
			C2D_TextParse(&texts[1],b_dynamic,"Sprite prueba con esquinas coloreadas");
			C2D_TextOptimize(&texts[1]);

			sceneRenderSprites(bot);
			break;

		default:
			C3D_FrameDrawOn(top);
			C3D_RenderTargetClear(top,C3D_CLEAR_ALL, background_color, 0);

			sceneRender3D(top);
			sceneRender2D(top);
			sceneRenderSprites(bot);
			break;
		}

		// A partir de esta línea acaba lo que se dibujaría en el frame actual y pasa al siguiente
		C3D_FrameEnd(0);

	}

	// Deinicializar todo(si no se hace, habrán memory leaks)
	deInit();
	C3D_RenderTargetDelete(top);
	C3D_RenderTargetDelete(bot);
	
	return 0;
}
