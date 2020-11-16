#include "Exit.h"

#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Exit::Exit(const Vector2d<float>& pos, Sprite* spr, World* w,
    const Vector2d<float>& ori)
: Interactable(pos, spr, w, CollisionFlag::exit_hit, CollisionFlag::player_hit, ori)
{
    id = EntityType::e_exit;
}

Exit::Exit(const Exit& c)
: Interactable(c)
{
    id = EntityType::e_exit;
}

Exit& Exit::operator= (const Exit& c)
{
    this->Interactable::operator=(c);

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


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Exit::~Exit()
{
    
}