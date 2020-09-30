#ifndef _GAME_PLAYING_
#define _GAME_PLAYING_

#include "Game_State.h"
#include "World.h"
#include "SpriteManager.h"

class Game_Playing : public Game_State
{

public:
    // Constructores
    Game_Playing();
    Game_Playing(const Game_Playing& gp);

    Game_Playing& operator= (const Game_Playing& gp);

    // Métodos
    void init() override;

    void loop() override;
        void processInput();
        void update();
        void updateCollisions();
        void interpolate();
        void render();
    
    void deInit() override;

    // Setters

    // Getters
    state_type getStateType() const override;
    World* getWorld() const;
    SpriteManager* getSpriteManager() const;
    float getUpdateTime() const;
    const float getUpd() const;
    Player* getPlayer() const;


    // Destructor
    ~Game_Playing();

protected:

    World* world;
    SpriteManager* manager;

    const float upd = 15.0f/60.0f;
    //const float upd = 0.0166;

    Timepoint update_time;

private:

};

#endif