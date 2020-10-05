#ifndef _BINARYTREE_
#define _BINARYTREE_

#include "CheckNode.h"
#include "ActionNode.h"
#include "vector"


class BinaryTree
{

public:
    // Constructores
    BinaryTree(Node* initial = nullptr);
    BinaryTree(const BinaryTree& bt);

    BinaryTree& operator= (const BinaryTree& bt);

    // Métodos
    void update(Enemy* e);

    CheckNode* createCheckNode(Check check, Node* trueNode, Node* falseNode);
    ActionNode* createActionNode(Action action, Node* next = nullptr);

    void deleteNode(Node* n);

    // Setters
    void setInitialNode(Node* initial);

    // Getters
    Node* getInitialNode() const;

    // Destructor
    ~BinaryTree();

private:

    Node* initialNode;
    std::vector<Node*> treeNodes;

};

#endif