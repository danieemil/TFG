#ifndef _GAME_STATE_
#define _GAME_STATE_

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
    virtual void render() = 0;
    virtual void deInit() = 0;

    // Setters

    // Getters
    virtual state_type getStateType() const;

    // Destructor
    virtual ~Game_State();

protected:

    state_type type;

private:

};

#endif