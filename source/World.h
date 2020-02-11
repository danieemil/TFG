#ifndef _WORLD_
#define _WORLD_

#include "Combat_Character.h"
#include <vector>

class World
{

public:
    // Constructores
    World();
    World(const World&);
    World(const std::vector<Entity*>& v);

    World& operator= (const World&);

    // Métodos
    void addEntity(Entity* e);
    void deleteEntity(Entity* e);
    void eraseEntity(Entity* e);

    void render();
    void update();

    // Setters
    void setEntities(const std::vector<Entity*>& v);

    // Getters
    const std::vector<Entity*>& getEntities() const;

    // Destructor
    ~World();

private:

    std::vector<Entity*> entities;

};

#endif