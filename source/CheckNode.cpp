#include "CheckNode.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

CheckNode::CheckNode(Check check, Node* t_node, Node* f_node)
: Node(), true_node(t_node), false_node(f_node), checkCallback(check)
{

}

CheckNode::CheckNode(const CheckNode& cn)
: Node(cn), true_node(cn.true_node), false_node(cn.false_node), checkCallback(cn.checkCallback)
{

}

CheckNode& CheckNode::operator= (const CheckNode& cn)
{
    Node::operator=(cn);

    true_node = cn.true_node;
    false_node = cn.false_node;
    checkCallback = cn.checkCallback;

    return *this;
}


//========c=================================
//=               MÉTODOS   	    	  =
//=========================================

void CheckNode::update(Enemy* e)
{

    if(checkCallback != nullptr)
    {
        if(checkCallback(e))
        {
            if(true_node != nullptr)
                true_node->update(e);
        }
        else
        {
            if(false_node != nullptr)
                false_node->update(e);
        }
    }
    
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void CheckNode::setTrueNode(Node* n)
{
    true_node = n;
}

void CheckNode::setFalseNode(Node* n)
{
    false_node = n;
}

void CheckNode::setCheckCallback(Check check)
{
    checkCallback = check;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Node* CheckNode::getTrueNode() const
{
    return true_node;
}

Node* CheckNode::getFalseNode() const
{
    return false_node;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

CheckNode::~CheckNode()
{
    
}