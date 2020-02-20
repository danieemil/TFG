#include "Screen.h"
#include "Unvisual_Engine.h"

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Screen::Screen(int s_width, int s_height, N3DS_screenV scv, N3DS_screenH sch)
{

    width = s_width;
    height = s_height;

    target = C3D_RenderTargetCreate(height,width,GPU_RB_RGBA8,GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(target, (gfxScreen_t)(scv), (gfx3dSide_t)(sch), DISPLAY_TRANSFER_FLAGS);
}

Screen::Screen(const Screen& d)
{
    width = d.width;
    height = d.height;

    target = nullptr;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================




//=========================================
//=               SETTERS   	    	  =
//=========================================
void Screen::setScreen(int s_width, int s_height, N3DS_screenV scv, N3DS_screenH sch)
{
    if(target!=nullptr)
    {
        C3D_RenderTargetDelete(target);
        target = nullptr;
    }

    width = s_width;
    height = s_height;

    target = C3D_RenderTargetCreate(height,width,GPU_RB_RGBA8,GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(target, (gfxScreen_t)(scv), (gfx3dSide_t)(sch), DISPLAY_TRANSFER_FLAGS);
}

void Screen::setBackground(u8 r, u8 g, u8 b, u8 a)
{
    background_color = C2D_Color32(r,g,b,a);
}



//=========================================
//=               GETTERS   	    	  =
//=========================================
C3D_RenderTarget* Screen::getTarget() const
{
    return target;
}

int Screen::getWidth() const
{
    return width;
}

int Screen::getHeight() const
{
    return height;
}

int Screen::getBackground() const
{
    return background_color;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Screen::~Screen()
{
    C3D_RenderTargetDelete(target);
    target = nullptr;
}