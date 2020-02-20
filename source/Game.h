#ifndef _GAME_
#define _GAME_

#include "World.h"
#include "SpriteManager.h"

// Configuración de la ventana de render

class Game
{

public:
    // Constructores
    Game(const char* spr_path = nullptr);

    // Métodos
    void init(const char* spr_path = nullptr);
    void deInit();
    void render();
    void update();
    void loop();
    void processInput();
    bool isRunning();

    // Setters
    void setWorldEntity(Entity* e);
    void setWorldPlayer(Player* p);
    void setSpriteManager(const char* spr_path);

    // Getters
    World* getWorld() const;
    SpriteManager* getSpriteManager() const;

    // Destructor
    ~Game();

private:

    World* world;
    SpriteManager* manager;

    bool running;

};

#endif