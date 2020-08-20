#include "Weapon.h"
#include "Combat_Character.h"
#include "World.h"
#include "Unvisual_Engine.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Weapon::Weapon(float t_attack, const Vector2d<float>& rel_attack, float angl, Sprite* spr, World* w, Collider* c, Combat_Character* cc)
: Entity(rel_attack, angl, spr, w, c), character(cc), attack_rel_position(rel_attack), attacking(false), attack_time(t_attack)
{
    id = Class_Id::e_weapon;

    position = attack_rel_position;

    if(character!=nullptr)
    {
        position += character->getPosition();
        character->addWeapon(this);
    }

}

Weapon::Weapon(const Weapon& w)
: Entity(w), character(w.character), attack_rel_position(w.attack_rel_position), attacking(false), attack_time(w.attack_time)
{
    position = attack_rel_position;

    if(character!=nullptr)
    {
        position += character->getPosition();
        character->addWeapon(this);
    }
}

Weapon& Weapon::operator= (const Weapon& w)
{
    this->Entity::operator=(w);
    character = w.character;

    if(character!=nullptr)
    {
        character->addWeapon(this);
    }

    attacking = false;
    attack_time = w.attack_time;
    attack_rel_position = w.attack_rel_position;

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Weapon::render(const Vector2d<float>& view_pos)
{
    Entity::render(view_pos);

    if(body!=nullptr)
    {
        body->setPosition(character->getCenter());
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
        setAngle(character->getAngle());

        // Ponemos el centro del sprite del arma en el centro de su portador
        // De esta forma puede rotar alrededor de su portador

        if(sprite!=nullptr)
        {
            Vector2d<float> spr_size((float)sprite->getSize().x, (float)sprite->getSize().y);

            Sprite* spr = character->getSprite();
            Vector2d<float> cent(0.5,0.5);

            if(spr!=nullptr)
            {
                Vector2d<float> spr_pos = spr->getCenterPosition();
                Vector2d<float> rel_cent = spr_pos - position;

                cent = rel_cent / spr_size;

                //unvisual::debugger->clear();
                //unvisual::debugger->print("X = " + std::to_string(cent.x));
	            //unvisual::debugger->nextLine();
                //unvisual::debugger->print("Y = " + std::to_string(cent.y));
                //unvisual::debugger->nextLine();
                //unvisual::debugger->breakpoint();
            }

            

            sprite->setCenter(cent);
        }
    }

    Entity::update();
}

void Weapon::updateFromCollider()
{
    
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
}

void Weapon::setCharacter(Combat_Character* cc)
{

    position = Vector2d<float>();

    if(attacking)
    {
        position += attack_rel_position;
    }

    if(character!=nullptr)
    {
        character->removeWeapon(this);
    }

    character = cc;

    if(character!=nullptr)
    {
        position += character->getPosition();
        character->addWeapon(this);
    }
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

const Class_Id& Weapon::getClassId() const
{
    return Entity::getClassId();
}

float Weapon::getAngle() const
{
    return Entity::getAngle();
}

Combat_Character* Weapon::getCharacter() const
{
    return character;
}

const Vector2d<float>& Weapon::getRelativePosition() const
{
    return attack_rel_position;
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Weapon::~Weapon()
{
    
}