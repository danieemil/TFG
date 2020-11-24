#ifndef _GAME_END_GAME_
#define _GAME_END_GAME_

#define END_SCREEN_DURATION 3.0f

#include "Game_State.h"

class Game_EndGame : public Game_State
{

public:
    // Constructores
    Game_EndGame();
    Game_EndGame(const Game_EndGame& geg);

    Game_EndGame& operator= (const Game_EndGame& geg);

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
    ~Game_EndGame();

protected:

    Timepoint timer;

private:

    

};

#endif