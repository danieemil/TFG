#ifndef _ACTIONNODE_
#define _ACTIONNODE_

#include "Node.h"

using Action = std::function<void (Enemy*)>;

class ActionNode : public Node
{

public:
    // Constructores
    ActionNode(Action action = nullptr, Node* next = nullptr);
    ActionNode(const ActionNode& cn);

    ActionNode& operator= (const ActionNode& cn);

    // Métodos
    void update(Enemy* e) override;

    // Setters
    void setActionFunction(Action action);
    void setNextNode(Node* next);

    // Getters

    // Destructor
    ~ActionNode();

private:

    Action actionCallback;
    Node* nextNode;

};

#endif