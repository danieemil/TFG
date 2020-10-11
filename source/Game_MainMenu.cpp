#include "Game_MainMenu.h"
#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_MainMenu::Game_MainMenu()
: Game_State(), menu_title(Vector2d<float>(94.0f,32.0f), "MENU PRINCIPAL", 16, 10.0f)
{
    type = state_type::menu;

    unvisual::debugger->print("He creado el estado Menú Principal");
    unvisual::debugger->nextLine();
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

    const char* gui_sprites_path = "romfs:/gfx/gui.t3x";

    gui_sprite_manager.setSprites(gui_sprites_path);

    // Botón de iniciar juego
    GUI_Button* b1;
    Sprite* spr_b1 = gui_sprite_manager.createSprite(0);
    Vector2d<float> position_b1 = Vector2d<float>(160.0f, 104.0f);

    Vector2d<size_t> size_spr_b1;

    if(spr_b1!=nullptr)
    {
        spr_b1->setScale(Vector2d<float>(0.8f, 1.0f));
        size_spr_b1 = spr_b1->getSize();
    }

    Vector2d<float> size_b1 = Vector2d<float>((float)size_spr_b1.x, (float)size_spr_b1.y);

    Call callback_b1 = [](){Game::Instance()->stateTransition<Game_Playing>();};

    b1 = new GUI_Button(position_b1, size_b1, spr_b1, callback_b1, "Nueva partida");
    gui_elements.push_back(b1);

    unvisual::debugger->setColumn(1);
    unvisual::debugger->setRow(1);


}

void Game_MainMenu::processInput()
{
    if(unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_L))
    {
        Game::Instance()->stateTransition<Game_Playing>();
        return;
    }

    if (unvisual::input::isPressed(unvisual::input::N3DS_buttons::Key_Touch))
    {
        auto t =  unvisual::input::getPositionTouched();
        Vector2d<float> pos = Vector2d<float>((float)t.x, (float)t.y);
        unvisual::debugger->setRow(9);
        unvisual::debugger->print("Position pressed: ");
        unvisual::debugger->nextLine();
        unvisual::debugger->print("X : " + std::to_string(pos.x));
        unvisual::debugger->nextLine();
        unvisual::debugger->print("Y : " + std::to_string(pos.y));
        unvisual::debugger->nextLine();
        for (auto &&element : gui_elements)
        {
            element->checkPressed(pos);
        }
    }
}

void Game_MainMenu::update()
{
    Game* g = Game::Instance();
    for (auto &&element : gui_elements)
    {
        element->update();
        if (g->getActualState()!=this)
        {
            return;
        }
    }
}

void Game_MainMenu::render()
{
    for (auto &&element : gui_elements)
    {
        element->render();
    }

    menu_title.render();
}

void Game_MainMenu::deInit()
{
    delete this;
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
    unvisual::debugger->print("He destruido el estado Menú Principal");
    unvisual::debugger->nextLine();
}