#ifndef _PHYSICS_ENGINE_
#define _PHYSICS_ENGINE_

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include "Collider.h"


namespace physics
{

    void addStatic(Collider* c);
    void addCinematic(Collider* c);
    void addDynamic(Collider* c);

    bool removeStatic(Collider* c);
    bool removeCinematic(Collider* c);
    bool removeDynamic(Collider* c);

    bool removeCollider(Collider* c);

    void collideWithStatics(Collider* c);
    void collideWithCinematics(Collider* c);
    void collideWithDynamics(Collider* c);

    void step();
}

#endif