#ifndef _GAME_MAIN_MENU_
#define _GAME_MAIN_MENU_

#include "Game_State.h"

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
    void render() override;
    void deInit() override;

    // Setters

    // Getters
    state_type getStateType() const override;

    // Destructor
    ~Game_MainMenu();

protected:


private:

};

#endif