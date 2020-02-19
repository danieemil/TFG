#ifndef _WORLD_
#define _WORLD_

#include "Player.h"
#include <vector>

class World
{

public:
    // Constructores
    World();
    World(const World&);
    World(const std::vector<Entity*>& v, Player* p = nullptr);

    World& operator= (const World&);

    // Métodos

    void addEntity(Entity* e);
    void addPlayer(Player* p);
    void deleteEntity(Entity* e);
    void eraseEntity(Entity* e);

    void processInput();

    void render();
    void renderEntities();
    void renderPlayer();

    void update();
    void updateEntities();
    void updatePlayer();

    // Setters
    void setEntities(const std::vector<Entity*>& v);
    void setPlayer(Player* p);

    // Getters
    const std::vector<Entity*>& getEntities() const;
    Player* getPlayer() const;

    // Destructor
    ~World();

private:

    std::vector<Entity*> entities;
    Player* player;

};

#endif