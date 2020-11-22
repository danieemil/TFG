#include "Game_Paused.h"
#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_Paused::Game_Paused()
: Game_State()
{
    type = state_type::paused;

    //unvisual::debugger->print("He creado el estado Pausa");
    //unvisual::debugger->nextLine();
}

Game_Paused::Game_Paused(const Game_Paused& gp)
: Game_State(gp), playingState(gp.playingState)
{

}

Game_Paused& Game_Paused::operator= (const Game_Paused& gp)
{
    Game_State::operator=(gp);

    playingState = gp.playingState;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================
void Game_Paused::init()
{

    playingState = static_cast<Game_Playing*>(Game::Instance()->getActualState());

    unvisual::setCurrentScreen(N3DS_screenV::N3DS_BOTTOM);
    Vector2d<float> sc_bottom_size = unvisual::getCurrentScreenSize();
    Vector2d<float> sc_bottom_center = sc_bottom_size / 2;

    unvisual::setCurrentScreen(N3DS_screenV::N3DS_TOP);
    Vector2d<float> sc_top_size = unvisual::getCurrentScreenSize();
    Vector2d<float> sc_top_center = sc_top_size / 2;

    background_position = sc_top_center + Vector2d<float>(-sc_top_center.x/1.5f, -5.0f);
    background_size = sc_top_size - Vector2d<float>(sc_top_size.x/4, sc_top_size.y/1.2f);


    Vector2d<float> but_pos = Vector2d<float>(sc_bottom_center.x - 10, sc_bottom_center.y / 1.5f);
    Vector2d<float> but_size = Vector2d<float>(107,18);
    Vector2d<float> but_padding = Vector2d<float>(0, 30);

    const char* gui_sprites_path = "romfs:/gfx/gui.t3x";

    gui_sprite_manager.setSprites(gui_sprites_path);

    Vector2d<float> menu_title_pos = background_position + Vector2d<float>(background_size.x/3, background_size.y/5);
    const char* menu_title_text = "PAUSA";
    float text_height = 15.0f;
    menu_title = Text(menu_title_pos, menu_title_text, 16, text_height, 255, 255, 255, 255);

    // Botón de iniciar juego
    GUI_Button* b1;
    Sprite* spr_b1 = gui_sprite_manager.createSprite(0);
    Vector2d<float> position_b1 = Vector2d<float>(90.0f, 74.0f);

    Vector2d<size_t> size_spr_b1;

    if(spr_b1!=nullptr)
    {
        spr_b1->setScale(Vector2d<float>(0.8f, 1.0f));
        size_spr_b1 = spr_b1->getSize();
    }

    Vector2d<float> size_b1 = Vector2d<float>((float)size_spr_b1.x, (float)size_spr_b1.y);

    Call callback_b1 = [this](){Game::Instance()->setState(playingState);};

    b1 = new GUI_Button(position_b1, size_b1, spr_b1, callback_b1, "Continuar");
    b1->setTextColor(0,0,0,255);
    gui_elements.addElement(b1);


    // Botón de volver al menú principal
    GUI_Button* b2;
    Sprite* spr_b2 = gui_sprite_manager.createSprite(0);
    Vector2d<float> position_b2 = Vector2d<float>(90.0f, 104.0f);

    Vector2d<size_t> size_spr_b2;

    if(spr_b2!=nullptr)
    {
        spr_b2->setScale(Vector2d<float>(1.3f, 1.0f));
        size_spr_b2 = spr_b2->getSize();
    }

    Vector2d<float> size_b2 = Vector2d<float>((float)size_spr_b2.x, (float)size_spr_b2.y);

    Call callback_b2 = [](){Game::Instance()->stateTransition<Game_MainMenu>();};

    b2 = new GUI_Button(position_b2, size_b2, spr_b2, callback_b2, "Menú principal");
    b2->setTextColor(0,0,0,255);
    gui_elements.addElement(b2);

    gui_elements.setUnselectedColor(0,0,0,255);
    gui_elements.setUntouchable(false);
    gui_elements.setSelectedDefault(0);
}

void Game_Paused::processInput()
{
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_R))
    {
        Game::Instance()->setState(playingState);
        return;
    }

    gui_elements.processInput();
}

void Game_Paused::update()
{
    gui_elements.update();
}

void Game_Paused::renderTop()
{
    Game_State::renderTop();

    if(playingState!=nullptr)
    {
        playingState->renderTop();
    }

    unvisual::drawRectangle(background_position, 0.1f, background_size, 0,0,0,200);

    menu_title.render();
}

void Game_Paused::renderBottom()
{
    Game_State::renderBottom();

    gui_elements.render();
}

void Game_Paused::manageAnimations()
{
    
}

void Game_Paused::deInit()
{
    if(playingState!=nullptr)
    {
        delete playingState;
    }

    delete this;
}

void Game_Paused::processEvents()
{
    Game_State::processEvents();
}

void Game_Paused::addEvent(Event e)
{
    Game_State::addEvent(e);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Game_Paused::setTopBackground(Sprite* spr)
{
    Game_State::setTopBackground(spr);
}

void Game_Paused::setBottomBackground(Sprite* spr)
{
    Game_State::setBottomBackground(spr);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================
state_type Game_Paused::getStateType() const
{
    return Game_State::getStateType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Game_Paused::~Game_Paused()
{
    //unvisual::debugger->print("He destruido el estado Pausa");
    //unvisual::debugger->nextLine();
}