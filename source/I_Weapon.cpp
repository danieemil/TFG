#include "I_Weapon.h"

#include "Game.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

I_Weapon::I_Weapon(int val, const Vector2d<float>& pos, Sprite* spr, World* w, Shape* sh,
    const Vector2d<float>& ori)
: Interactable(val, pos, spr, w, sh, CollisionFlag::player_hit, ori)
{
    sub_id = InteractableType::weapon;
}

I_Weapon::I_Weapon(const I_Weapon& iw)
: Interactable(iw)
{
    
}

I_Weapon& I_Weapon::operator= (const I_Weapon& iw)
{
    this->Interactable::operator=(iw);

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void I_Weapon::render(const Vector2d<float>& view_pos)
{
    Interactable::render(view_pos);
}

void I_Weapon::update()
{
    Interactable::update();
}

void I_Weapon::updateFromCollider()
{
    Interactable::updateFromCollider();
}

void I_Weapon::interpolate(float rp)
{
    Interactable::interpolate(rp);
}

void I_Weapon::manageAnimations()
{
    Interactable::manageAnimations();
}

void I_Weapon::collision(void* ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getEntityType()==EntityType::e_player)
        {
            Player* p = static_cast<Player*>(e);
            if(world!=nullptr)
            {
                Weapon* w = world->createWeapon((WeaponType)value, p);
                if(w!=nullptr)
                {
                    Game::Instance()->deleteEntityEvent(this);
                }
            }
        }
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void I_Weapon::setSprite(Sprite* spr)
{
    Interactable::setSprite(spr);
}

void I_Weapon::setPosition(const Vector2d<float>& pos)
{
    Interactable::setPosition(pos);
}

void I_Weapon::setWorld(World* w)
{
    Interactable::setWorld(w);
}

void I_Weapon::setBody(Collider* c)
{
    Interactable::setBody(c);
}

void I_Weapon::setVelocity(const Vector2d<float>& vel)
{
    Interactable::setVelocity(vel);
}

void I_Weapon::setAngle(float angl)
{
    Interactable::setAngle(angl);
}

void I_Weapon::setOrientation(const Vector2d<float>& ori)
{
    Interactable::setOrientation(ori);
}

void I_Weapon::setValue(int val)
{
    Interactable::setValue(val);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* I_Weapon::getSprite() const
{
    return Interactable::getSprite();
}

const Vector2d<float>& I_Weapon::getPosition() const
{
    return Interactable::getPosition();
}

World* I_Weapon::getWorld() const
{
    return Interactable::getWorld();
}

Collider* I_Weapon::getBody() const
{
    return Interactable::getBody();
}

const Vector2d<float>& I_Weapon::getVelocity() const
{
    return Interactable::getVelocity();
}

const Vector2d<float>& I_Weapon::getPrePosition() const
{
    return Interactable::getPrePosition();
}

const Vector2d<float>& I_Weapon::getRenderPosition() const
{
    return Interactable::getRenderPosition();
}

const EntityType& I_Weapon::getEntityType() const
{
    return Interactable::getEntityType();
}

float I_Weapon::getAngle() const
{
    return Interactable::getAngle();
}

Vector2d<float> I_Weapon::getCenter() const
{
    return Interactable::getCenter();
}

const Vector2d<float>& I_Weapon::getOrientation() const
{
    return Interactable::getOrientation();
}

int I_Weapon::getValue() const
{
    return Interactable::getValue();
}

const InteractableType& I_Weapon::getInteractableType() const
{
    return Interactable::getInteractableType();
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

I_Weapon::~I_Weapon()
{
    
}