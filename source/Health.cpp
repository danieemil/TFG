#include "Health.h"

#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Health::Health(int val, const Vector2d<float>& pos, Sprite* spr, World* w, Shape* sh,
    const Vector2d<float>& ori)
: Interactable(val, pos, spr, w, sh, CollisionFlag::player_hit, ori)
{
    sub_id = InteractableType::health;
}

Health::Health(const Health& h)
: Interactable(h)
{
    
}

Health& Health::operator= (const Health& h)
{
    this->Interactable::operator=(h);

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Health::render(const Vector2d<float>& view_pos)
{
    Interactable::render(view_pos);
}

void Health::update()
{
    Interactable::update();
}

void Health::updateFromCollider()
{
    Interactable::updateFromCollider();
}

void Health::interpolate(float rp)
{
    Interactable::interpolate(rp);
}

void Health::manageAnimations()
{
    Interactable::manageAnimations();
}

void Health::collision(void* ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getEntityType()==EntityType::e_player)
        {
            Player* p = static_cast<Player*>(e);
            if(p->increaseLife(value))
            {
                Game::Instance()->deleteEntityEvent(this);
            }
        }
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Health::setSprite(Sprite* spr)
{
    Interactable::setSprite(spr);
}

void Health::setPosition(const Vector2d<float>& pos)
{
    Interactable::setPosition(pos);
}

void Health::setWorld(World* w)
{
    Interactable::setWorld(w);
}

void Health::setBody(Collider* c)
{
    Interactable::setBody(c);
}

void Health::setVelocity(const Vector2d<float>& vel)
{
    Interactable::setVelocity(vel);
}

void Health::setAngle(float angl)
{
    Interactable::setAngle(angl);
}

void Health::setOrientation(const Vector2d<float>& ori)
{
    Interactable::setOrientation(ori);
}

void Health::setValue(int val)
{
    Interactable::setValue(val);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Health::getSprite() const
{
    return Interactable::getSprite();
}

const Vector2d<float>& Health::getPosition() const
{
    return Interactable::getPosition();
}

World* Health::getWorld() const
{
    return Interactable::getWorld();
}

Collider* Health::getBody() const
{
    return Interactable::getBody();
}

const Vector2d<float>& Health::getVelocity() const
{
    return Interactable::getVelocity();
}

const Vector2d<float>& Health::getPrePosition() const
{
    return Interactable::getPrePosition();
}

const Vector2d<float>& Health::getRenderPosition() const
{
    return Interactable::getRenderPosition();
}

const EntityType& Health::getEntityType() const
{
    return Interactable::getEntityType();
}

float Health::getAngle() const
{
    return Interactable::getAngle();
}

Vector2d<float> Health::getCenter() const
{
    return Interactable::getCenter();
}

const Vector2d<float>& Health::getOrientation() const
{
    return Interactable::getOrientation();
}

int Health::getValue() const
{
    return Interactable::getValue();
}

const InteractableType& Health::getInteractableType() const
{
    return Interactable::getInteractableType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Health::~Health()
{
    
}