#include "BinaryTree.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

BinaryTree::BinaryTree(Node* initial)
: initialNode(initial)
{

}

BinaryTree::BinaryTree(const BinaryTree& bt)
: initialNode(bt.initialNode), treeNodes(bt.treeNodes)
{

}

BinaryTree& BinaryTree::operator= (const BinaryTree& bt)
{
    initialNode = bt.initialNode;
    treeNodes = bt.treeNodes;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void BinaryTree::update(Enemy* e)
{
    if(initialNode != nullptr && e != nullptr)
    {
        initialNode->update(e);
    }
}

CheckNode* BinaryTree::createCheckNode(Check check, Node* trueNode, Node* falseNode)
{
    CheckNode* ch = new CheckNode(check, trueNode, falseNode);
    treeNodes.push_back(ch);
    return ch;
}

ActionNode* BinaryTree::createActionNode(Action action, Node* next)
{
    ActionNode* an = new ActionNode(action, next);
    treeNodes.push_back(an);
    return an;
}

void BinaryTree::deleteNode(Node* n)
{
    for (auto it = treeNodes.begin(); it != treeNodes.end(); it++)
    {
        Node* node = (*it);
        if(node == n)
        {
            delete node;
            treeNodes.erase(it);
            break;
        }
    }
    
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void BinaryTree::setInitialNode(Node* initial)
{
    initialNode = initial;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Node* BinaryTree::getInitialNode() const
{
    return initialNode;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

BinaryTree::~BinaryTree()
{
    auto it = treeNodes.begin();

    while (it!=treeNodes.end())
    {
        Node* n = (*it);

        if(n!=nullptr)
        {
            delete n;
        }
        treeNodes.erase(it);
    }
    
}