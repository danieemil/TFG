#ifndef _GAME_
#define _GAME_

#include "World.h"
#include "SpriteManager.h"


class Game
{

public:
    // Constructores
    Game(SpriteManager* man = nullptr, World* w = nullptr);
    Game(const Game&);

    Game& operator= (const Game&);

    // Métodos
    void render();
    void update();

    // Setters
    void setWorld(World* w);
    void setSpriteManager(SpriteManager* man);

    // Getters
    World* getWorld() const;
    SpriteManager* getSpriteManager() const;

    // Destructor
    ~Game();

private:

    World* world;
    SpriteManager* manager;

};

#endif