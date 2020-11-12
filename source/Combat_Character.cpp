#include "Combat_Character.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Combat_Character::Combat_Character(int l, const Vector2d<float>& pos, Sprite* spr, World* w,
    CollisionFlag type_flag, CollisionFlag interests_flag,
    const Vector2d<float>& ori, const Vector2d<float>& max_vel, const Vector2d<float>& max_accel,
    const Vector2d<float>& frict, Weapon* wp, float st_time)
: Character(pos, spr, w, type_flag, interests_flag, ori, max_vel, max_accel, frict), equipped(wp), attacked(false),
    stunned(false), stun_time(st_time), life(l), max_life(l)
{
    if(wp!=nullptr)
    {
        weapons.emplace_back(wp);
    }
}

Combat_Character::Combat_Character(const Combat_Character& cc)
: Character(cc), equipped(nullptr), attacked(cc.attacked), stunned(cc.stunned),
    stun_time(cc.stun_time), life(cc.life)
{

}

Combat_Character& Combat_Character::operator= (const Combat_Character& cc)
{
    Character::operator=(cc);
    equipped = nullptr;
    attacked = cc.attacked;
    stunned = cc.stunned;
    stun_time = cc.stun_time;
    life = cc.life;
    
    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Combat_Character::render(const Vector2d<float>& view_pos)
{
    Character::render(view_pos);
    if(equipped!=nullptr)
    {
        equipped->render(view_pos);
    }
}

void Combat_Character::update()
{
    if(life <= 0)
    {
        die();
        return;
    }
    // Si está aturdido no puede acelerar (moverse como quiere), tampoco puede aturdirse
    if(stunned)
    {
        Entity::update();
        if(stun_timing.getElapsed()>stun_time)
        {
            stunned = false;
            if(attacked) attacked = false;
            if(body!=nullptr)
            {
                body->setActive(true);
            }
        }
    }else if((equipped==nullptr || !equipped->getAttacking()))
    {
        Character::update();
    }

    if(equipped!=nullptr)
    {
        equipped->update();
    }
}

void Combat_Character::updateFromCollider()
{
    Character::updateFromCollider();
    if(equipped!=nullptr)
    {
        equipped->updateFromCollider();
    }
}

void Combat_Character::interpolate(float rp)
{
    Character::interpolate(rp);
    if(equipped!=nullptr)
    {
        equipped->interpolate(rp);
    }
}

void Combat_Character::collision(void* ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getClassId()==Class_Id::e_weapon)
        {
            Weapon* w = static_cast<Weapon*>(e);
            // He colisionado con un arma, eso significa que me han atacado

            Vector2d<float> dir = w->getOrientation();

            // Se orienta en dirección al atacante
            // setOrientation(dir*(-1));

            if(body!=nullptr)
            {
                body->setImpulse(dir * w->getKnockback());
                body->setVelocity(Vector2d<float>(0.0f,0.0f));
                body->setAcceleration(Vector2d<float>(0.0f, 0.0f));
                body->setActive(false);
            }
            stun_timing.reset();
            stunned = true;
            attacked = true;

            life = life - w->getDamage();
        }
    }

    Character::collision(ent);
}

void Combat_Character::attack()
{
    if(!stunned)
    {
        if(equipped!=nullptr)
        {
            if(body!=nullptr)
            {
                body->setVelocity(Vector2d<float>(0.0f,0.0f));
                body->setAcceleration(Vector2d<float>(0.0f, 0.0f));
            }
            equipped->attack();
        }
    }
}

void Combat_Character::die()
{
    delete this;
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Combat_Character::setSprite(Sprite* spr)
{
    Character::setSprite(spr);
}

void Combat_Character::setPosition(const Vector2d<float>& pos)
{
    Character::setPosition(pos);
}

void Combat_Character::setWorld(World* w)
{
    Character::setWorld(w);
}

void Combat_Character::setBody(Collider* c)
{
    Character::setBody(c);
}

void Combat_Character::setVelocity(const Vector2d<float>& vel)
{
    Character::setVelocity(vel);
}

void Combat_Character::setAngle(float angl)
{
    Character::setAngle(angl);
}

void Combat_Character::setOrientation(const Vector2d<float>& ori)
{
    Character::setOrientation(ori);
}

void Combat_Character::setAcceleration(const Vector2d<float>& accel)
{
    Character::setAcceleration(accel);
}

void Combat_Character::setFriction(const Vector2d<float>& frict)
{
    Character::setFriction(frict);
}

bool Combat_Character::addWeapon(Weapon* wp)
{
    if(wp!=nullptr)
    {
        for (auto w_eapon : weapons)
        {
            if(w_eapon==wp)
            {
                return false;
            }
        }
        weapons.emplace_back(wp);
        return true;
    }
    return false;
}

void Combat_Character::removeWeapon(Weapon* wp)
{
    if(wp!=nullptr)
    {
        for (auto it = weapons.begin(); it != weapons.end(); it++)
        {
            Weapon* w_eapon = (*it);
            if(w_eapon==wp)
            {
                if(w_eapon==equipped)
                {
                    equipped = nullptr;
                }
                weapons.erase(it);
                return;
            }
        }
        
    }
}

void Combat_Character::equipWeapon(size_t index)
{
    if(weapons.empty())
    {
        equipped = nullptr;
        return;
    }

    size_t ind = index;

    if(ind >= weapons.size())
    {
        ind = weapons.size() - 1;
    }

    equipped = weapons[ind];
    
}

void Combat_Character::setAttacked(bool at)
{
    attacked = at;
}

void Combat_Character::setStunned(bool st)
{
    stunned = st;

    if(stunned)
    {
        stun_timing.reset();
    }
}

void Combat_Character::setLife(int l)
{
    life = clamp(0, max_life, l);
}

void Combat_Character::setMaxLife(int l)
{
    // La vida máxima no puede ser negativa ni 0
    if(l > 0)   
    {
        // La vida actual no puede superar la vida máxima
        if(life >= l)
        {
            life = l;
        }
        max_life = l;
    }
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Combat_Character::getSprite() const
{
    return Character::getSprite();
}

const Vector2d<float>& Combat_Character::getPosition() const
{
    return Character::getPosition();
}

World* Combat_Character::getWorld() const
{
    return Character::getWorld();
}

Collider* Combat_Character::getBody() const
{
    return Character::getBody();
}

const Vector2d<float>& Combat_Character::getVelocity() const
{
    return Character::getVelocity();
}

const Vector2d<float>& Combat_Character::getPrePosition() const
{
    return Character::getPrePosition();
}

const Vector2d<float>& Combat_Character::getRenderPosition() const
{
    return Character::getRenderPosition();
}

const Class_Id& Combat_Character::getClassId() const
{
    return Character::getClassId();
}

float Combat_Character::getAngle() const
{
    return Character::getAngle();
}

Vector2d<float> Combat_Character::getCenter() const
{
    return Character::getCenter();
}

const Vector2d<float>& Combat_Character::getOrientation() const
{
    return Character::getOrientation();
}

const Vector2d<float>& Combat_Character::getAcceleration() const
{
    return Character::getAcceleration();
}

const std::vector<Weapon*>& Combat_Character::getWeapons() const
{
    return weapons;
}

Weapon* Combat_Character::getWeaponEquipped() const
{
    return equipped;
}

bool Combat_Character::getAttacking() const
{
    if(equipped!=nullptr)
    {
        return equipped->getAttacking();
    }
    return false;
}

bool Combat_Character::getAttacked() const
{
    return attacked;
}

bool Combat_Character::getStunned() const
{
    return stunned;
}

int Combat_Character::getLife() const
{
    return life;
}

int Combat_Character::getMaxLife() const
{
    return max_life;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Combat_Character::~Combat_Character()
{

    auto weapon = weapons.begin();

    while (weapon!=weapons.end())
    {
        Weapon* w = (*weapon);
        if(w!=nullptr)
        {
            delete w;
        }
        weapons.erase(weapon);
    }
    
}