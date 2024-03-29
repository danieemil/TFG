#ifndef _GAME_PLAYING_
#define _GAME_PLAYING_

#include "Game_State.h"
#include "World.h"
#include "LevelFactory.h"
#include "HUD.h"

class Game_Playing : public Game_State
{

public:
    // Constructores
    Game_Playing();
    Game_Playing(const Game_Playing& gp);

    Game_Playing& operator= (const Game_Playing& gp);

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

    void updateCollisions();
    void interpolate();
    
    void resetLevel();
    void nextLevel();

    void erasePlayer();

    // Setters
    void setTopBackground(Sprite* spr) override;
    void setBottomBackground(Sprite* spr) override;

    // Getters
    state_type getStateType() const override;
    World* getWorld() const;
    float getUpdateTime() const;
    const float getUpd() const;
    Player* getPlayer() const;


    // Destructor
    ~Game_Playing();

protected:

    World* world;

    //const float upd = 15.0f/60.0f;
    const float upd = 0.0166;

    Timepoint update_time;

    LevelFactory level_factory;

    HUD hud;

private:

};

#endif