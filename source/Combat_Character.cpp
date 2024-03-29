#include "Combat_Character.h"
#include "World.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Combat_Character::Combat_Character(int l, const Vector2d<float>& pos, Sprite* spr, World* w,
    Shape* sh, CollisionFlag type_flag, CollisionFlag interests_flag,
    const Vector2d<float>& ori, const Vector2d<float>& max_vel, const Vector2d<float>& max_accel,
    const Vector2d<float>& frict, Weapon* wp, float st_time, float inv_time)
: Character(pos, spr, w, sh, type_flag, interests_flag, ori, max_vel, max_accel, frict),
    equipped(wp), attacked(false), stunned(false), stun_time(st_time), stun_timing(),
    invincible(false), invincibility_time(inv_time), invincibility_timing(), life(l), max_life(l)
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

    if(invincible)
    {
        if(invincibility_timing.getElapsed()>invincibility_time)
        {
            invincible = false;
            if(body!=nullptr)
            {
                body->setActive(true);
            }
        }
    }

    // Si está aturdido no puede acelerar (moverse como quiere), tampoco puede aturdirse
    if(stunned)
    {
        Entity::update();
        if(stun_timing.getElapsed()>stun_time)
        {
            stunned = false;
            if(attacked) attacked = false;
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

void Combat_Character::manageAnimations()
{
    Character::manageAnimations();
    if(equipped!=nullptr)
    {
        equipped->manageAnimations();
    }
}

void Combat_Character::collision(void* ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getEntityType()==EntityType::e_weapon)
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

            // Se marca como que ha sido atacado
            attacked = true;

            // El ataque lo aturde por un corto periodo de tiempo(stun_time)
            stunned = true;
            stun_timing.reset();
            
            // Se hace invencible por un corto periodo de tiempo(invincibility_time)
            invincible = true;
            invincibility_timing.reset();

            cancelAttack();

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

void Combat_Character::cancelAttack()
{
    if(equipped!=nullptr)
    {
        equipped->cancelAttack();
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
    if(!stunned && (equipped==nullptr || !equipped->getAttacking()))
    {
        Character::setOrientation(ori);
    }
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
        for (auto &&w_eapon : weapons)
        {
            if(w_eapon!=nullptr)
            {
                if(wp->getWeaponType() == w_eapon->getWeaponType())
                {
                    return false;
                }
            }
        }
        weapons.emplace_back(wp);

        if(equipped==nullptr)
        {
            equipped = wp;
        }

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
    if(equipped!=nullptr && equipped->getAttacking())
    {
        return;
    }

    if(index < weapons.size() && index >= (size_t)0)
    {
        equipped = weapons[index];
    }
}

void Combat_Character::equipNextWeapon()
{
    if(weapons.empty())
    {
        return;
    }

    size_t index = 0;

    size_t i = 0;
    for (auto &&weap : weapons)
    {
        if(weap==equipped)
        {
            i++;
            if(i < weapons.size())
            {
                index = i;
            }
            break;
        }
        i++;
    }

    equipWeapon(index);

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

bool Combat_Character::increaseLife(int l)
{
    if(life<max_life)
    {
        setLife(life + l);
        return true;
    }
    return false;
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

const EntityType& Combat_Character::getEntityType() const
{
    return Character::getEntityType();
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

bool Combat_Character::getInvincible() const
{
    return invincible;
}

int Combat_Character::getLife() const
{
    return life;
}

int Combat_Character::getMaxLife() const
{
    return max_life;
}

bool Combat_Character::hasWeapon(const WeaponType& wt) const
{
    for (auto &&weapon : weapons)
    {
        if(weapon!=nullptr)
        {
            if(weapon->getWeaponType()==wt)
            {
                return true;
            }
        }
    }
    
    return false;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Combat_Character::~Combat_Character()
{
    for (auto &&weapon : weapons)
    {
        if(weapon!=nullptr)
        {
            delete weapon;
        }
    }
    weapons.clear();

    equipped = nullptr;
}