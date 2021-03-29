#ifndef _CHECKNODE_
#define _CHECKNODE_

#include "Node.h"

using Check = std::function<bool(Enemy*)>;


class CheckNode : public Node
{

public:
    // Constructores
    CheckNode(Check check = nullptr, Node* t_node = nullptr, Node* f_node = nullptr);
    CheckNode(const CheckNode& cn);

    CheckNode& operator= (const CheckNode& cn);

    // Métodos
    void update(Enemy* e) override;

    // Setters
    void setTrueNode(Node* n);
    void setFalseNode(Node* n);

    void setCheckCallback(Check check);

    // Getters
    Node* getTrueNode() const;
    Node* getFalseNode() const;

    // Destructor
    ~CheckNode();

private:
    Node* true_node;
    Node* false_node;

    Check checkCallback;

};

#endif