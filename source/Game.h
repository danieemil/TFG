#ifndef _GAME_
#define _GAME_

#include "World.h"
#include "SpriteManager.h"

// Configuración de la ventana de render
#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

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