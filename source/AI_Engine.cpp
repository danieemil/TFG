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
        // Árbol binario de un enemigo que solo se acerca si te está viendo y no está demasiado cerca

        BinaryTree* agressive = new BinaryTree();
        float near = 40.0f;
        float far = 80.0f;


        // Para crear las "Action" o "Check" (punteros a funciones de enemigos),
        // se puede hacer mediante funciones lambda o std::bind()

        // Lambda -> Action/Check x = [parámetro_constante](Enemy* enemigo){enemgio->función_del_enemigo(parámetro_constante);}
        // Más natural y permite hacer más que llamar a solo una función
        
        // std::bind -> Action/Check x = std::bind(&Enemy::funcion_del_enemigo, std::placeholders::_1, parámetro_constante);
        // Solo permite llamar a "funcion_del_enemigo", pero con el placeholder usado
        // se podría pasar por parámetro cualquier variable sin importar el tipo
        // (aunque eso no es necesario en este caso)

        // Al usar placeholders

        // Nivel 1
        Node* n1 = agressive->createActionNode([](Enemy* e){e->actionTowardsPlayer();});
        Node* n2 = agressive->createActionNode([](Enemy* e){e->actionStop();});

        // Nivel 2
        Node* n3 = agressive->createCheckNode([near](Enemy* e){return e->checkFarPlayer(near);}, n1, n2);
        
        // Nivel 3
        Node* n4 = agressive->createCheckNode([far](Enemy* e){return e->checkNearPlayer(far);}, n3, n2);
        
        agressive->setInitialNode(n4);

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