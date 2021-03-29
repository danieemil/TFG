#ifndef _NODE_
#define _NODE_

#include "functional"

class Enemy;

class Node
{

public:
    // Constructores
    Node();
    Node(const Node& n);

    Node& operator= (const Node& n);

    // Métodos
    virtual void update(Enemy* e) = 0;

    // Setters

    // Getters

    // Destructor
    virtual ~Node();

private:

    static unsigned int nodes_id;

    unsigned int id;

};

#endif