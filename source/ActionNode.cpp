#include "ActionNode.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

ActionNode::ActionNode(Action action, Node* next)
: Node(), actionCallback(action), nextNode(next)
{

}

ActionNode::ActionNode(const ActionNode& an)
: Node(an), actionCallback(an.actionCallback), nextNode(an.nextNode)
{

}

ActionNode& ActionNode::operator= (const ActionNode& an)
{
    Node::operator=(an);
    
    actionCallback = an.actionCallback;
    nextNode = an.nextNode;

    return *this;
}


//========c=================================
//=               MÉTODOS   	    	  =
//=========================================

void ActionNode::update(Enemy* e)
{
    if(actionCallback != nullptr)
    {
        actionCallback(e);
    }

    if(nextNode!=nullptr)
    {
        nextNode->update(e);
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void ActionNode::setActionFunction(Action action)
{
    actionCallback = action;
}

void ActionNode::setNextNode(Node* next)
{
    nextNode = next;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================



//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

ActionNode::~ActionNode()
{
    
}