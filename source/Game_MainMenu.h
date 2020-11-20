#ifndef _GAME_MAIN_MENU_
#define _GAME_MAIN_MENU_

#include "Game_State.h"
#include "GUI_Button.h"
#include "GUI_Element_List.h"

class Game_MainMenu : public Game_State
{

public:
    // Constructores
    Game_MainMenu();
    Game_MainMenu(const Game_MainMenu& gmm);

    Game_MainMenu& operator= (const Game_MainMenu& gmm);

    // Métodos
    void init() override;
    void processInput() override;
    void update() override;
    void renderTop() override;
    void renderBottom() override;
    void deInit() override;
    void processEvents() override;
    void addEvent(Event e) override;

    // Setters

    // Getters
    state_type getStateType() const override;

    // Destructor
    ~Game_MainMenu();

protected:
    GUI_Element_List gui_elements;
    SpriteManager gui_sprite_manager;

    Text menu_title;

private:

    

};

#endif