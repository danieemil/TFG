#ifndef _GAME_STATE_
#define _GAME_STATE_


#include <stack>
#include <functional>
#include "SpriteManager.h"

using Event = std::function<void()>;

enum class state_type
{
    none,
    menu,
    playing,
    paused,
    options,
    credits,
};


class Game_State
{

public:
    // Constructores
    Game_State();
    Game_State(const Game_State& gs);

    Game_State& operator= (const Game_State& gs);

    // Métodos
    virtual void init() = 0;
    virtual void processInput() = 0;
    virtual void update() = 0;
    virtual void renderTop();
    virtual void renderBottom();
    virtual void manageAnimations() = 0;
    virtual void deInit() = 0;
    virtual void processEvents();
    virtual void addEvent(Event e);

    // Setters
    virtual void setTopBackground(Sprite* spr);
    virtual void setBottomBackground(Sprite* spr);

    // Getters
    virtual state_type getStateType() const;

    // Destructor
    virtual ~Game_State();

protected:

    state_type type;
    std::stack<Event> events;

    Sprite* top_background;
    Sprite* bottom_background;

private:

};

#endif