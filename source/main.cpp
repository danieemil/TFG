#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <3ds.h>
#include <citro2d.h>


// Texto a mostrar
static const char text[] =
"This text is in the font of the system!\n"
"Right?\n"
;


// Variables necesarias que se usan para DIBUJAR texto
C2D_TextBuf b_static;	// Se crea y se define una vez
C2D_TextBuf b_dynamic;	// Se crea y se define una vez por frame
C2D_Text texts[1];


// Configura las consolas para poder escribir texto
void defineConsoles()
{
	//Creamos consolas vacías
	PrintConsole top, bottom;

	// Asignamos estas consolas vacías a su pantalla
	consoleInit(GFX_TOP, &top);
	consoleInit(GFX_BOTTOM, &bottom);

	// Seleccionamos la consola por la que queremos que se
	// imprima el texto
	consoleSelect(&top);

	// Imprimirmos texto en la fila 15, columna 19 de la consola
	std::cout << "\x1b[15;19H" << "Hello upper world!" << std::endl;

	//Hacemos lo mismo con la consola de la pantalla de abajo
	consoleSelect(&bottom);
	std::cout << "\x1b[15;14H" << "Hello lower world!" << std::endl;

}

// En esta función están todos los inicializadores necesarios
void init()
{
	// Inicializador por defecto de los gráficos básicos
	gfxInitDefault();

	// Inicializador del HID(Input)
	hidInit();

	// Inicializador de Citro3D(Gráficos especializados del 3D)
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	// Inicializador de Citro2D(Gráficos especializados del 2D)
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

	// Setea la GPU para que pueda trabajar con Citro2D
	C2D_Prepare();
}

// Libera la memoria de las librerías que se usan en la N3DS
void deInit()
{
	// Limpia y destruye los buffers
	C2D_TextBufDelete(b_static);
	C2D_TextBufDelete(b_dynamic);

	// Liberamos la memoria de la librería Citro3D
	C3D_Fini();
	
	// Liberamos la memoria de la librería Citro2D
	C2D_Fini();

	// Liberamos la memoria del "InputManager"
	hidExit();

	// Liberamos la memoria que se usa para los gráficos básicos
	gfxExit();
}

void defineText()
{
	// Creamos el buffer dónde estará el texto con tamaño 4096
	b_static = C2D_TextBufNew(4096);

	// Ponemos el texto en el buffer y se lo asignamos a la variable "texts" que se puede dibujar
	C2D_TextParse(texts,b_static,text);

	// Optimiza, no hay más
	C2D_TextOptimize(texts);
	
}


void drawText()
{
	// Dibujamos el texto que ha sido asignado a "texts"
	C2D_DrawText(texts,0,0,0,0,1,1);
}



int main(int argc, char* argv[])
{
	
	//Inicializamos todo
	init();

	//Configuramos el "texto"(text.h)
	defineText();

	//Configuramos las "consolas"(console.h)
	defineConsoles();

	

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


		// Ponemos los dos buffers con el mismo contenido
		gfxFlushBuffers();

		// Intercambiamos los buffers (concepto de doblebuffer)
		gfxSwapBuffers();

		// Esperamos a que se haya dibujado todo por pantalla
		gspWaitForVBlank();

	}

	// Deinicializar todo(si no se hace, habrán memory leaks)
	deInit();
	
	return 0;
}



/** 
 * @brief Código copiado de https://github.com/xem/3DShomebrew/blob/gh-pages/functions/functions.c
 */ 
void gfxDrawSprite(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y) {
  //This function includes documantation so you might be able to figure out what the function is doing, you don't need to understand this to use it!
  if(!spriteData)return; //check if the function has sprite data, if not stop!

  u16 fbWidth, fbHeight; //set variables for width and height
  u8* fbAdr = gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight); //get framebuffer for the screen and side used.

  if(x + width < 0 || x >= fbWidth)return; //check invalid x cords
  if(y + height < 0 ||y >= fbHeight)return; //check invalid y cords

  u16 xOffset = 0, yOffset = 0; //set offset for x and y
  u16 widthDrawn = width, heightDrawn = height; //set width/height vars that for drawing

  if(x < 0) xOffset = -x; //use offset
  if(y < 0) yOffset = -y; //use offset
  if(x + width >= fbWidth) widthDrawn = fbWidth - x;
  if(y + height >= fbHeight) heightDrawn = fbHeight - y;
  widthDrawn -=xOffset;
  heightDrawn -=yOffset;

  int j;
  for(j = yOffset; j < yOffset + heightDrawn; j++) { //for loop for drawing image
    memcpy(&fbAdr[ ((x + xOffset) + (y + j) * fbWidth) * 3 ], &spriteData[ ((xOffset + j) * width) * 3 ], widthDrawn * 3); //copy imagedata into memory
  }
}
