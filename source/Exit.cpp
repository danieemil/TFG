#include "Exit.h"

#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Exit::Exit(const Vector2d<float>& pos, Sprite* spr, World* w, Shape* sh,
    const Vector2d<float>& ori)
: Interactable(0, pos, spr, w, sh, CollisionFlag::exit_hit, CollisionFlag::player_hit, ori)
{
    
}

Exit::Exit(const Exit& e)
: Interactable(e)
{

}

Exit& Exit::operator= (const Exit& e)
{
    this->Interactable::operator=(e);

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Exit::render(const Vector2d<float>& view_pos)
{
    Interactable::render(view_pos);
}

void Exit::update()
{
    Interactable::update();
}

void Exit::updateFromCollider()
{
    Interactable::updateFromCollider();
}

void Exit::interpolate(float rp)
{
    Interactable::interpolate(rp);
}

void Exit::manageAnimations()
{
    Interactable::manageAnimations();
}

void Exit::collision(void* ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getEntityType()==EntityType::e_player)
        {
            nextLevel();
        }
    }
}

void Exit::nextLevel()
{
    Game::Instance()->nextLevelEvent();
}



//=========================================
//=               SETTERS   	    	  =
//=========================================

void Exit::setSprite(Sprite* spr)
{
    Interactable::setSprite(spr);
}

void Exit::setPosition(const Vector2d<float>& pos)
{
    Interactable::setPosition(pos);
}

void Exit::setWorld(World* w)
{
    Interactable::setWorld(w);
}

void Exit::setBody(Collider* c)
{
    Interactable::setBody(c);
}

void Exit::setVelocity(const Vector2d<float>& vel)
{
    Interactable::setVelocity(vel);
}

void Exit::setAngle(float angl)
{
    Interactable::setAngle(angl);
}

void Exit::setOrientation(const Vector2d<float>& ori)
{
    Interactable::setOrientation(ori);
}

void Exit::setValue(int val)
{
    Interactable::setValue(val);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Exit::getSprite() const
{
    return Interactable::getSprite();
}

const Vector2d<float>& Exit::getPosition() const
{
    return Interactable::getPosition();
}

World* Exit::getWorld() const
{
    return Interactable::getWorld();
}

Collider* Exit::getBody() const
{
    return Interactable::getBody();
}

const Vector2d<float>& Exit::getVelocity() const
{
    return Interactable::getVelocity();
}

const Vector2d<float>& Exit::getPrePosition() const
{
    return Interactable::getPrePosition();
}

const Vector2d<float>& Exit::getRenderPosition() const
{
    return Interactable::getRenderPosition();
}

const EntityType& Exit::getEntityType() const
{
    return Interactable::getEntityType();
}

float Exit::getAngle() const
{
    return Interactable::getAngle();
}

Vector2d<float> Exit::getCenter() const
{
    return Interactable::getCenter();
}

const Vector2d<float>& Exit::getOrientation() const
{
    return Interactable::getOrientation();
}

int Exit::getValue() const
{
    return Interactable::getValue();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Exit::~Exit()
{
    
}