#ifndef _SCREEN_
#define _SCREEN_

#include <citro2d.h>
#include "Debugger.h"

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

#define MAX_WIDTH_UP 400
#define MAX_HEIGHT_UP 240
#define MAX_WIDTH_DOWN 320
#define MAX_HEIGHT_DOWN 240

class Screen
{

public:
    // Constructores
    Screen(int s_width, int s_height, N3DS_screenV scv, N3DS_screenH sch = N3DS_screenH::N3DS_LEFT);
    Screen(const Screen&);

    // Métodos

    // Setters
    void setScreen(int s_width, int s_height, N3DS_screenV scv, N3DS_screenH sch = N3DS_screenH::N3DS_LEFT);
    void setBackground(u8 r, u8 g, u8 b, u8 a);

    // Getters
    C3D_RenderTarget* getTarget() const;
    int getWidth() const;
    int getHeight() const;
    int getBackground() const;

    // Destructor
    ~Screen();

private:
    C3D_RenderTarget* target;
    int width, height;
    int background_color;

};

#endif