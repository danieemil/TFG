#include "ActionNode.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

ActionNode::ActionNode(Action action)
: Node(), actionCallback(action)
{

}

ActionNode::ActionNode(const ActionNode& an)
: Node(an), actionCallback(an.actionCallback)
{

}

ActionNode& ActionNode::operator= (const ActionNode& an)
{
    Node::operator=(an);
    
    actionCallback = an.actionCallback;

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
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void ActionNode::setActionFunction(Action action)
{
    actionCallback = action;
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