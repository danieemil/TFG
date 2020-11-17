#ifndef _WORLD_
#define _WORLD_

#include "Exit.h"
#include "Health.h"
#include "Player.h"
#include "Enemy.h"
#include "Tilemap.h"
#include <vector>

class World
{

public:
    // Constructores
    World(Player* p = nullptr);
    World(const World& w);

    World& operator= (const World& w);

    // Métodos
    void addEntity(Entity* e);
    void deleteEntity(Entity* e);
    void eraseEntity(Entity* e);

    void deletePlayer();
    void erasePlayer();

    void deleteLevel();
    void deleteWorld();

    void processInput();

    Vector2d<float> scroll2D();

    void render();
    void renderTilemap(const Vector2d<float>& view_pos = Vector2d<float>());
    void renderEntities(const Vector2d<float>& view_pos = Vector2d<float>());
    void renderPlayer(const Vector2d<float>& view_pos = Vector2d<float>());

    void interpolate(float rp = 0.0f);
    void interpolateEntities(float rp = 0.0f);
    void interpolatePlayer(float rp = 0.0f);

    void update();
    void updateEntities();
    void updatePlayer();

    void updateCollisions();
    void updateEntitiesCollisions();
    void updatePlayerCollisions();

    // Setters
    void setTilemap(Tilemap* t);
    void setEntities(const std::vector<Entity*>& v);
    void setPlayer(Player* p);

    // Getters
    Tilemap* getTilemap() const;
    const std::vector<Entity*>& getEntities() const;
    Player* getPlayer() const;

    // Destructor
    ~World();

private:

    std::vector<Entity*> entities;
    Player* player;
    Tilemap* tilemap;

    Vector2d<float> scroll_vel;

    friend class LevelFactory;

};

#endif