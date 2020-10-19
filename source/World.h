#ifndef _WORLD_
#define _WORLD_

#include "Player.h"
#include "Enemy.h"
#include "Tilemap.h"
#include <vector>

class World
{

public:
    // Constructores
    World(const char* tileset_path = nullptr, Player* p = nullptr, const char* tileset_ent = nullptr);
    World(const World& w);

    World& operator= (const World& w);

    // Métodos
    void addEntity(Entity* e);
    void deleteEntity(Entity* e);
    void eraseEntity(Entity* e);

    void erasePlayer();

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

    void eraseWorld();

    // Setters
    void setTilemap(Tilemap* t);
    void setEntities(const std::vector<Entity*>& v);
    void setPlayer(Player* p);
    void setSpriteManager(const char* tileset);

    // Getters
    Tilemap* getTilemap() const;
    const std::vector<Entity*>& getEntities() const;
    Player* getPlayer() const;
    SpriteManager* getSpriteManager() const;

    // Destructor
    ~World();

private:

    std::vector<Entity*> entities;
    Player* player;
    Tilemap* tilemap;
    SpriteManager* manager;

    Vector2d<float> scroll_vel;

};

#endif