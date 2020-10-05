#include "AI_Engine.h"
#include "Enemy.h"

using namespace std::placeholders;

namespace AI
{
    namespace
    {
        std::map<bt_types, BinaryTree*> b_trees;
    }

    void init()
    {
        BTInit();
    }
    
    void BTInit()
    {
        // Árbol binario de un enemigo que solo se acerca

        BinaryTree* agressive = new BinaryTree();

        // Nivel 1
        Node* n1 = agressive->createActionNode(std::bind(&Enemy::actionTowardsPlayer, _1));
        Node* n2 = agressive->createActionNode(std::bind(&Enemy::actionStop, _1));

        // Nivel 2
        Node* n3 = agressive->createCheckNode(std::bind(&Enemy::checkFarPlayer, _1, 40.0f), n1, n2);
        
        // Nivel 3
        Node* n4 = agressive->createCheckNode(std::bind(&Enemy::checkNearPlayer, _1, 80.0f), n3, n2);
        
        agressive->setInitialNode(n3);

        b_trees.emplace(make_pair<bt_types, BinaryTree*>(bt_types::enemy_agressive, std::move(agressive)));

        // Árbol binario de un enemigo que solo se aleja




    }

    BinaryTree* getBehaviour(bt_types id)
    {
        auto it = b_trees.find(id);

        if (it != b_trees.end())
        {
            return it->second;
        }
        
        return nullptr;
    }

    void BTDeInit()
    {
        for (auto it = b_trees.begin(); it != b_trees.end(); it++)
        {
            delete it->second;
        }
        
        b_trees.clear();
    }

    void deInit()
    {
        BTDeInit();
    }

}