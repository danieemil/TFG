#ifndef _AI_ENGINE_
#define _AI_ENGINE_

#include "BinaryTree.h"
#include "map"

namespace AI
{

    enum class bt_types
    {
        enemy_agressive,
        enemy_fearful
    };

    void init();
    void deInit();

    // BinaryTrees
    void BTInit();

    BinaryTree* getBehaviour(bt_types type);

    void BTDeInit();
}

#endif