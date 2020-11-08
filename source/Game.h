#ifndef _GAME_
#define _GAME_

#include "Game_Playing.h"
#include "Game_MainMenu.h"
#include "Game_Paused.h"

//Clase Singleton para que todos puedan acceder a las variables de Game
class Game
{

public:

    // Métodos
    void init();
    void deInit();
    void render();
    void update();
    void updateCollisions();
    void interpolate();
    void loop();
    void processInput();
    bool isRunning();
    void stopRunning();

    void erasePlayer();

    template<class S>
    void stateTransition()
    {
        Game_State* s = new S();
        if(state!=nullptr)
        {
            prev_state = state->getStateType();
            post_state = s->getStateType();
            state->deInit();
        }else
        {
            prev_state = state_type::none;
        }
        s->init();
        state = s;
        return;
    }

    // Setters
    void setState(Game_State* s);

    // Getters
    float getDeltaTime() const;
    Player* getPlayer() const;
    state_type getPrevState() const;
    Game_State* getActualState() const;
    state_type getPostState() const;

    static Game* Instance(); 

    // Destructor(Singleton)
    void over();

protected:

    // Constructor
    Game();

    // Destructor
    ~Game();

private:

    static Game* p_instance;

    bool running;
    float dt;
    Timepoint delta_time;

    state_type prev_state;
    Game_State* state;
    state_type post_state;

    // Save file data

};

#endif