#ifndef _GAME_PAUSED_
#define _GAME_PAUSED_

#include "Game_Playing.h"

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
    void render() override;
    void deInit() override;

    // Setters

    // Getters
    state_type getStateType() const override;

    // Destructor
    ~Game_Paused();

protected:


private:

    Game_Playing* playingState;

};

#endif