#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <3ds.h>
#include <citro2d.h>

int main(int argc, char* argv[])
{
	gfxInitDefault();
	hidInit();


	//Creamos las consolas dónde escribiremos el texto
	PrintConsole top, bottom;

	//Console init coge la consola que le pasamos por parámetro y le da los valores
	//acorde a dónde la queremos GFX_TOP/GFX_DOWN.
	consoleInit(GFX_TOP, &top);
	consoleInit(GFX_BOTTOM, &bottom);

	//consoleInit(GFX_BOTTOM, NULL) -> Devuelve un PrintConsole* que crea y la setea como actual.

	//The top screen has 30 rows and 50 columns
	//The bottom screen has 30 rows and 40 columns

	consoleSelect(&top);

	std::cout << "\x1b[15;19H" << "Hello upper world!" << std::endl;

	consoleSelect(&bottom);

	std::cout << "\x1b[15;14H" << "Hello lower world!" << std::endl;

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Your code goes here
		int kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu


		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();

	}

	gfxExit();
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
