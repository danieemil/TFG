#ifndef _WORLD_
#define _WORLD_

#include "Player.h"
#include "Tilemap.h"
#include <vector>

class World
{

public:
    // Constructores
    World(const char* tileset_path = nullptr, Player* p = nullptr);
    World(const World&);

    World& operator= (const World&);

    // Métodos

    void addEntity(Entity* e);
    void deleteEntity(Entity* e);
    void eraseEntity(Entity* e);

    void processInput();

    Vector2d<float> scroll2D();

    void render(float rp = 0.0f);
    void renderTilemap(const Vector2d<float>& view_pos = Vector2d<float>());
    void renderEntities(float rp = 0.0f, const Vector2d<float>& view_pos = Vector2d<float>());
    void renderPlayer(float rp = 0.0f, const Vector2d<float>& view_pos = Vector2d<float>());

    void update();
    void updateEntities();
    void updatePlayer();

    void updateCollisions();
    void updateEntitiesCollisions();
    void updatePlayerCollisions();

    // Setters
    void setTilemap(const char* tileset_path, const char* tilemap_path);
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

};

#endif