#include "AI_Engine.h"
#include "Enemy.h"

using namespace std::placeholders;

namespace AI
{
    namespace
    {
        std::unordered_map<bt_types, BinaryTree*> b_trees;
    }

    void init()
    {
        BTInit();
    }
    
    void BTInit()
    {

        // Para crear las "Action" o "Check" (punteros a funciones de enemigos),
        // se puede hacer mediante funciones lambda o std::bind()

        // Lambda -> Action/Check x = [parámetro_constante](Enemy* enemigo){enemgio->función_del_enemigo(parámetro_constante);}
        // Más natural y permite hacer más que llamar a solo una función
        
        // std::bind -> Action/Check x = std::bind(&Enemy::funcion_del_enemigo, std::placeholders::_1, parámetro_constante);
        // Solo permite llamar a "funcion_del_enemigo", pero con el placeholder usado
        // se podría pasar por parámetro cualquier variable sin importar el tipo
        // (aunque eso no es necesario en este caso)

        // Al usar placeholders es como si pusiéramos una variable Template que puede ser
        // de cualquier tipo hasta que se especifica.


        // Árbol binario del enemigo agresivo
        BinaryTree* agressive = new BinaryTree();
        float near = 40.0f;
        float far = 80.0f;

        // Nivel 1
        Node* agressive_n1 = agressive->createActionNode([](Enemy* e){e->actionMoveTowardsPlayer();});
        Node* agressive_n2 = agressive->createActionNode([](Enemy* e){e->actionStop();});

        // Nivel 2
        Node* agressive_n3 = agressive->createCheckNode([near](Enemy* e){return e->checkFarPlayer(near);}, agressive_n1, agressive_n2);
        
        // Nivel 3
        Node* agressive_n4 = agressive->createCheckNode([far](Enemy* e){return e->checkNearPlayer(far);}, agressive_n3, agressive_n2);
        
        agressive->setInitialNode(agressive_n4);

        b_trees.emplace(make_pair<bt_types, BinaryTree*>(bt_types::enemy_agressive, std::move(agressive)));


        // Árbol binario del enemigo minero
        BinaryTree* miner = new BinaryTree();
        
        // Nivel 1
        Node* miner_n1 = miner->createActionNode([](Enemy* e){e->attack();});

        // Nivel 2
        Node* miner_n2 = miner->createActionNode([](Enemy* e){e->actionOrientateToPlayer();}, miner_n1);
        Node* miner_n3 = miner->createActionNode([](Enemy* e){e->actionMoveTowardsPlayer();});

        // Nivel 3
        Node* miner_n4 = miner->createCheckNode([](Enemy* e){return e->checkPlayerInWeaponRange();}, miner_n2, miner_n3);
        Node* miner_n5 = miner->createActionNode([](Enemy* e){e->actionStop();});

        // Nivel 4
        Node* miner_n6 = miner->createCheckNode([](Enemy* e){return e->checkSeePlayer();}, miner_n4, miner_n5);

        miner->setInitialNode(miner_n6);

        b_trees.emplace(make_pair<bt_types, BinaryTree*>(bt_types::enemy_miner, std::move(miner)));
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
        for (auto &&tree : b_trees)
        {
            if(tree.second!=nullptr)
            {
                delete tree.second;
            }
        }
        
        b_trees.clear();
    }

    void deInit()
    {
        BTDeInit();
    }

}