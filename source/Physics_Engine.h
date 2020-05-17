#ifndef _PHYSICS_ENGINE_
#define _PHYSICS_ENGINE_

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include "Collider.h"


namespace physics
{

    void addCollider(Collider* c);
    void addStatic(Collider* c);
    void addDynamic(Collider* c);

    bool removeCollider(Collider* c);
    bool removeStatic(Collider* c);
    bool removeDynamic(Collider* c);

    void step();

    void setManager(void (*manager)(Collider* colliderA, Collider* colliderB));

    const std::vector<Collider*>& getColliders();
}

#endif