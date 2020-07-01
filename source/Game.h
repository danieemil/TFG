#ifndef _GAME_
#define _GAME_

#include "World.h"
#include "SpriteManager.h"

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

    // Setters
    void setWorldEntity(Entity* e);
    void setWorldPlayer(Player* p);
    void setSpriteManager(const char* spr_path);

    // Getters
    World* getWorld() const;
    SpriteManager* getSpriteManager() const;
    float getDeltaTime() const;
    float getUpdateTime() const;
    const float getUpd() const;

    static Game* Instance(); 

    // Destructor(Singleton)
    void over();

protected:

    // Constructores
    Game();

    // Destructor
    ~Game();

private:

    World* world;
    SpriteManager* manager;
    Screen screen;

    bool running;
    float dt;
    //const float upd = 15.0f/60.0f;
    const float upd = 0.0166;

	Timepoint delta_time;
    Timepoint update_time;

    static Game* p_instance;

};

#endif