#ifndef _GAME_PAUSED_
#define _GAME_PAUSED_

#include "Game_Playing.h"
#include "GUI_Button.h"
#include "GUI_Element_List.h"

class Game_Paused : public Game_State
{

public:
    // Constructores
    Game_Paused();
    Game_Paused(const Game_Paused& gp);

    Game_Paused& operator= (const Game_Paused& gp);

    // Métodos
    void init() override;
    void processInput() override;
    void update() override;
    void renderTop() override;
    void renderBottom() override;
    void manageAnimations() override;
    void deInit() override;
    void processEvents() override;
    void addEvent(Event e) override;

    // Setters
    void setTopBackground(Sprite* spr) override;
    void setBottomBackground(Sprite* spr) override;

    // Getters
    state_type getStateType() const override;

    // Destructor
    ~Game_Paused();

protected:
    GUI_Element_List gui_elements;
    SpriteManager gui_sprite_manager;

    Text menu_title;

private:

    Game_Playing* playingState;
    Vector2d<float> background_position;
    Vector2d<float> background_size;

};

#endif