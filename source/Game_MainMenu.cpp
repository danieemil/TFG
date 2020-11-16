#include "Game_MainMenu.h"
#include "Game.h"
#include "LevelFactory.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_MainMenu::Game_MainMenu()
: Game_State()
{
    type = state_type::menu;

    //unvisual::debugger->print("He creado el estado Menú Principal");
    //unvisual::debugger->nextLine();
}

Game_MainMenu::Game_MainMenu(const Game_MainMenu& gmm)
: Game_State(gmm), menu_title(gmm.menu_title)
{

}

Game_MainMenu& Game_MainMenu::operator= (const Game_MainMenu& gmm)
{
    Game_State::operator=(gmm);
    menu_title = gmm.menu_title;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================
void Game_MainMenu::init()
{

    unvisual::getCurrentScreen()->setBackgroundColor(255,255,255,255);

    Vector2d<float> sc_size = unvisual::getCurrentScreenSize();
    Vector2d<float> sc_center = sc_size / 2;

    Vector2d<float> but_pos = Vector2d<float>(sc_center.x - 10, sc_center.y / 1.5f);
    Vector2d<float> but_size = Vector2d<float>(107,18);
    Vector2d<float> but_padding = Vector2d<float>(0, 30);

    // Título
    Vector2d<float> menu_title_pos = Vector2d<float>(sc_center.x/1.5f,sc_center.y/5);
    const char* menu_title_text = "MENU PRINCIPAL";
    float text_height = 10.0f;
    menu_title = Text(menu_title_pos, menu_title_text, 16, text_height);

    const char* gui_sprites_path = "romfs:/gfx/gui.t3x";

    gui_sprite_manager.setSprites(gui_sprites_path);

    int default_button = 0;

    // Botón de iniciar juego
    GUI_Button* b1;
    Sprite* spr_b1 = gui_sprite_manager.createSprite(0);
    Vector2d<float> position_b1 = but_pos;
    Vector2d<size_t> size_spr_b1 = Vector2d<size_t>(but_size.x, but_size.y);

    if(spr_b1!=nullptr)
    {
        spr_b1->setScale(Vector2d<float>(1.05f, 1.0f));
        size_spr_b1 = spr_b1->getSize();
    }

    Vector2d<float> size_b1 = Vector2d<float>((float)size_spr_b1.x, (float)size_spr_b1.y);

    Call callback_b1 = [](){LevelFactory::resetSave();Game::Instance()->stateTransition<Game_Playing>();};
    const char* text_b1 = "Nueva partida";
    b1 = new GUI_Button(position_b1, size_b1, spr_b1, callback_b1, text_b1);
    gui_elements.addElement(b1);

    GUI_Button* b2 = nullptr;

    if(Game::Instance()->getSaved())
    {
        default_button = 1;
        // Botón de continuar partida   
        Sprite* spr_b2 = gui_sprite_manager.createSprite(0);
        but_pos += but_padding;
        Vector2d<float> position_b2 = but_pos;

        Vector2d<size_t> size_spr_b2;

        if(spr_b2!=nullptr)
        {
            spr_b2->setScale(Vector2d<float>(0.8f, 1.0f));
            size_spr_b2 = spr_b2->getSize();
        }

        Vector2d<float> size_b2 = Vector2d<float>((float)size_spr_b2.x, (float)size_spr_b2.y);

        Call callback_b2 = [](){Game::Instance()->stateTransition<Game_Playing>();};

        b2 = new GUI_Button(position_b2, size_b2, spr_b2, callback_b2, "Continuar");
        gui_elements.addElement(b2);
    }


    // Botón de salir del juego
    GUI_Button* b3;
    Sprite* spr_b3 = gui_sprite_manager.createSprite(0);
    but_pos += but_padding;
    Vector2d<float> position_b3 = but_pos;

    Vector2d<size_t> size_spr_b3;

    if(spr_b3!=nullptr)
    {
        spr_b3->setScale(Vector2d<float>(0.6f, 1.0f));
        size_spr_b3 = spr_b3->getSize();
    }

    Vector2d<float> size_b3 = Vector2d<float>((float)size_spr_b3.x, (float)size_spr_b3.y);

    Call callback_b3 = [](){Game::Instance()->stopRunning();};

    b3 = new GUI_Button(position_b3, size_b3, spr_b3, callback_b3, "Salir");
    gui_elements.addElement(b3);

    // No se pueden seleccionar los botones con el panel táctil -> (Pantalla de arriba)
    gui_elements.setUntouchable(true);
    // La opción de continuar está por defecto seleccionada cuando presionamos EL BOTÓN
    
    gui_elements.setSelectedDefault(default_button);
}

void Game_MainMenu::processInput()
{
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_L))
    {
        Game::Instance()->stateTransition<Game_Playing>();
        return;
    }

    gui_elements.processInput();
}

void Game_MainMenu::update()
{
    gui_elements.update();
}

void Game_MainMenu::render()
{
    gui_elements.render();

    menu_title.render();
}

void Game_MainMenu::deInit()
{
    delete this;
}

void Game_MainMenu::processEvents()
{
    Game_State::processEvents();
}

void Game_MainMenu::addEvent(Event e)
{
    Game_State::addEvent(e);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================




//=========================================
//=               GETTERS   	    	  =
//=========================================
state_type Game_MainMenu::getStateType() const
{
    return Game_State::getStateType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Game_MainMenu::~Game_MainMenu()
{
    //unvisual::debugger->print("He destruido el estado Menú Principal");
    //unvisual::debugger->nextLine();
}