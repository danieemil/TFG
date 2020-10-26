#include "Screen.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Screen::Screen()
: width(0), height(0), position(), target_position(nullptr)
{
    renderer = nullptr;
}

Screen::Screen(int s_width, int s_height, N3DS_screenV scv, N3DS_screenH sch, const utilities::Vector2d<float>* t_pos)
: width(s_width), height(s_height), position(), target_position(t_pos)
{
    renderer = C3D_RenderTargetCreate(height,width,GPU_RB_RGBA8,GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(renderer, (gfxScreen_t)(scv), (gfx3dSide_t)(sch), DISPLAY_TRANSFER_FLAGS);
}

Screen::Screen(const Screen& sc)
: width(sc.width), height(sc.height), position(sc.position), target_position(nullptr), renderer(nullptr)
{

}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================




//=========================================
//=               SETTERS   	    	  =
//=========================================
void Screen::setScreen(int s_width, int s_height, N3DS_screenV scv, N3DS_screenH sch)
{
    if(renderer!=nullptr)
    {
        C3D_RenderTargetDelete(renderer);
        renderer = nullptr;
    }

    width = s_width;
    height = s_height;

    renderer = C3D_RenderTargetCreate(height,width,GPU_RB_RGBA8,GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(renderer, (gfxScreen_t)(scv), (gfx3dSide_t)(sch), DISPLAY_TRANSFER_FLAGS);
}

void Screen::setBackgroundColor(u8 r, u8 g, u8 b, u8 a)
{
    background_color = C2D_Color32(r,g,b,a);
}

void Screen::setPosition(const utilities::Vector2d<float>& pos)
{
    position = pos;
}

void Screen::setTargetPosition(const utilities::Vector2d<float>* t_pos)
{
    target_position = t_pos;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================
C3D_RenderTarget* Screen::getRenderer() const
{
    return renderer;
}

int Screen::getWidth() const
{
    return width;
}

int Screen::getHeight() const
{
    return height;
}

u32 Screen::getBackgroundColor() const
{
    return background_color;
}

const utilities::Vector2d<float>& Screen::getPosition() const
{
    return position;
}

const utilities::Vector2d<float>* Screen::getTargetPosition() const
{
    return target_position;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Screen::~Screen()
{
    if(renderer!=nullptr)
    {
        C3D_RenderTargetDelete(renderer);
        renderer = nullptr;
    }

    
    
}