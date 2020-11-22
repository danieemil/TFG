#include "Weapon.h"
#include "Combat_Character.h"
#include "World.h"
#include "Unvisual_Engine.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Weapon::Weapon(int dam, float knock, float t_attack, const Vector2d<float>& rel_attack,
    Sprite* spr, World* w, Shape* sh, CollisionFlag type_flag, CollisionFlag interests_flag,
    const Vector2d<float>& ori, Combat_Character* cc, Animation* at_anim)
: Entity(rel_attack, spr, w,
    new Collider(Vector2d<float>(), sh, type_flag, interests_flag, CollisionType::col_none), ori),
    character(cc), attack_rel_position(rel_attack), center_rel(0.5f, 0.5f), attacking(false),
    attack_time(t_attack), damage(dam), knockback(knock), attack_animation(at_anim)
{
    id = EntityType::e_weapon;

    calculateCenter();
    
    if(character!=nullptr)
    {
        character->addWeapon(this);
    }

    if(body!=nullptr)
    {
        body->setActive(false);
    }

}

Weapon::Weapon(const Weapon& w)
: Entity(w), character(w.character), attack_rel_position(w.attack_rel_position),
    center_rel(w.center_rel), attacking(false), attack_time(w.attack_time), damage(w.damage),
    knockback(w.knockback), attack_animation(w.attack_animation), sub_id(w.sub_id)
{
    calculateCenter();
    
    if(character!=nullptr)
    {
        character->addWeapon(this);
    }
}

Weapon& Weapon::operator= (const Weapon& w)
{
    this->Entity::operator=(w);
    character = w.character;

    calculateCenter();
    
    if(character!=nullptr)
    {
        character->addWeapon(this);
    }

    attacking = false;
    attack_time = w.attack_time;
    attack_rel_position = w.attack_rel_position;

    damage = w.damage;
    knockback = w.knockback;

    attack_animation = w.attack_animation;
    sub_id = w.sub_id;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Weapon::render(const Vector2d<float>& view_pos)
{
    if(attacking)
    {
        rendering->setCenter(center_rel);
        Entity::render(view_pos);
    
        if(body!=nullptr)
        {
            body->setPosition(character->getCenter());
        }
    }
}

void Weapon::update()
{

    position = Vector2d<float>();

    if(attacking)
    {
        if (time_attacking.getElapsed()>attack_time)
        {
            attacking = false;
            if(body!=nullptr)
            {
                body->setActive(false);
            }
        }else
        {
            position += attack_rel_position;
        }
    }

    if(character!=nullptr)
    {
        position += character->getPosition();
        setOrientation(character->getOrientation());
    }

    Entity::update();
}

void Weapon::updateFromCollider()
{
    return;
}

void Weapon::interpolate(float rp)
{
    render_position = Vector2d<float>();
    
    if(attacking)
    {
        render_position = attack_rel_position;
    }

    if(character!=nullptr)
    {
        render_position += character->getRenderPosition();
    }
}

void Weapon::manageAnimations()
{
    Entity::manageAnimations();

    // Gestionar animaciones del arma
    if(attack_animation!=nullptr)
    {
        if(attack_animation->hasSprites())
        {
            if(!attack_animation->hasEnded())
            {
                attack_animation->update();
                rendering = attack_animation->getActualSprite();
            }
        }
    }
}

void Weapon::collision(void * ent)
{
    
}

void Weapon::attack()
{
    if(!attacking)
    {
        attacking = true;
        time_attacking.reset();
        if(body!=nullptr)
        {
            body->setActive(true);
        }
        if(attack_animation!=nullptr && attack_animation->hasSprites())
        {
            attack_animation->resetAnimation();
        }
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Weapon::setSprite(Sprite* spr)
{
    Entity::setSprite(spr);
}

void Weapon::setPosition(const Vector2d<float>& pos)
{
    Entity::setPosition(pos);
}

void Weapon::setWorld(World* w)
{
    Entity::setWorld(w);
}

void Weapon::setBody(Collider* c)
{
    Entity::setBody(c);
}

void Weapon::setVelocity(const Vector2d<float>& vel)
{
    Entity::setVelocity(vel);
}

void Weapon::setAngle(float angl)
{
    Entity::setAngle(angl);

    if(body!=nullptr)
    {
        body->setGlobalRotation(angle);
    }
}

void Weapon::setOrientation(const Vector2d<float>& ori)
{
    Entity::setOrientation(ori);
}

void Weapon::setCharacter(Combat_Character* cc)
{

    if(character!=nullptr && character!=cc)
    {
        character->removeWeapon(this);
    }

    character = cc;

    calculateCenter();
    
    if(character!=nullptr)
    {
        character->addWeapon(this);
    }
}

void Weapon::setRelativePosition(const Vector2d<float>& rl_pos)
{
    attack_rel_position = rl_pos;

    calculateCenter();
}

void Weapon::setAttackingTime(float at_time)
{
    attack_time = at_time;
}

void Weapon::setDamage(int dam)
{
    damage = dam;
}

void Weapon::setKnockback(float knock)
{
    knockback = knock;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Weapon::getSprite() const
{
    return Entity::getSprite();
}

const Vector2d<float>& Weapon::getPosition() const
{
    return Entity::getPosition();
}

World* Weapon::getWorld() const
{
    return Entity::getWorld();
}

Collider* Weapon::getBody() const
{
    return Entity::getBody();
}

const Vector2d<float>& Weapon::getVelocity() const
{
    return Entity::getVelocity();
}

const Vector2d<float>& Weapon::getPrePosition() const
{
    return Entity::getPrePosition();
}

const Vector2d<float>& Weapon::getRenderPosition() const
{
    return Entity::getRenderPosition();
}

const EntityType& Weapon::getEntityType() const
{
    return Entity::getEntityType();
}

float Weapon::getAngle() const
{
    return Entity::getAngle();
}

Vector2d<float> Weapon::getCenter() const
{
    return Entity::getCenter();
}

const Vector2d<float>& Weapon::getOrientation() const
{
    return Entity::getOrientation();
}

Combat_Character* Weapon::getCharacter() const
{
    return character;
}

const Vector2d<float>& Weapon::getRelativePosition() const
{
    return attack_rel_position;
}

bool Weapon::getAttacking() const
{
    return attacking;
}

int Weapon::getDamage() const
{
    return damage;
}

float Weapon::getKnockback() const
{
    return knockback;
}

const WeaponType& Weapon::getWeaponType() const
{
    return sub_id;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Weapon::~Weapon()
{
    if(attack_animation!=nullptr)
    {
        delete attack_animation;
        attack_animation = nullptr;
    }
}


//=========================================
//=               PRIVATE   	    	  =
//=========================================

// Ponemos el centro del sprite del arma en el centro de su portador
// De esta forma puede rotar alrededor de su portador
void Weapon::calculateCenter()
{
    position = attack_rel_position;
    if(character!=nullptr)
    {
        position += character->getPosition();
        Sprite* spr = character->getSprite();
        if(spr!=nullptr && sprite!=nullptr)
        {
            Vector2d<float> spr_size((float)sprite->getSize().x, (float)sprite->getSize().y);

            Vector2d<float> spr_pos = spr->getCenter();
            Vector2d<float> rel_cent = spr_pos - attack_rel_position;

            center_rel = rel_cent / spr_size;
        }
    }
}