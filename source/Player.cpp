#include "Player.h"
#include "World.h"

#include "Game.h"

using namespace unvisual;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Player::Player(const Vector2d<float>& pos, float angl, Sprite* spr, World* w, Collider* c,
    const Vector2d<float>& max_vel, const Vector2d<float>& accel, const Vector2d<float>& decel, Weapon* wp)
: Combat_Character(pos, angl, spr, w, c, max_vel, accel, decel, wp)
{
    id = Class_Id::e_player;
    orientation = Vector2d<float>(0.0f,-1.0f);
}

Player::Player(const Player& p)
: Combat_Character(p), orientation(p.orientation)
{

}

Player& Player::operator= (const Player& p)
{
    Combat_Character::operator=(p);

    orientation = p.orientation;

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Player::render(const Vector2d<float>& view_pos)
{
    Combat_Character::render(view_pos);
}

void Player::update()
{
    Combat_Character::update();
}

void Player::updateFromCollider()
{
    Combat_Character::updateFromCollider();
}

void Player::interpolate(float rp)
{
    Combat_Character::interpolate(rp);
}

void Player::collision(void* ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getClassId()==Class_Id::e_enemy)
        {
            
        }
    }
}

void Player::processInput()
{

    heading = Vector2d<float>();

    if( input::isPressed(input::N3DS_buttons::Key_DUp)
    ||
        input::isHeld(input::N3DS_buttons::Key_DUp))
    {
        unvisual::debugger->setRow(1);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Up");;
        heading.y += -1.0f;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DRight)
    ||
        input::isHeld(input::N3DS_buttons::Key_DRight))
    {
        unvisual::debugger->setRow(2);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Right");
        heading.x += 1.0f;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DDown)
    ||
        input::isHeld(input::N3DS_buttons::Key_DDown))
    {
        unvisual::debugger->setRow(3);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Down");
        heading.y += 1.0f;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DLeft)
    ||
        input::isHeld(input::N3DS_buttons::Key_DLeft))
    {
        unvisual::debugger->setRow(4);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Left");
        heading.x += -1.0f;
    }

    if( input::isPressed(input::N3DS_buttons::Key_A))
    {
        attack();
    }


    acceleration = max_acceleration * heading;

    // Si no se está moviendo en un eje, le aplicamos fricción a ese eje

    if(heading.x == 0)
    {
        acceleration.x = clamp(0.0f, abs(velocity.x), deceleration.x) * sign(velocity.x) * (-1);
    }

    if(heading.y == 0)
    {
        acceleration.y = clamp(0.0f, abs(velocity.y), deceleration.y) * sign(velocity.y) * (-1);
    }

    unvisual::debugger->setRow(6);
    unvisual::debugger->setColumn(1);
    unvisual::debugger->print("Player position:");
    unvisual::debugger->nextLine();
    unvisual::debugger->print("X = " + std::to_string(position.x));
    unvisual::debugger->nextLine();
    unvisual::debugger->print("Y = " + std::to_string(position.y));
    unvisual::debugger->nextLine();
    unvisual::debugger->print("Vel_X = " + std::to_string(velocity.x));
    unvisual::debugger->nextLine();
    unvisual::debugger->print("Vel_Y = " + std::to_string(velocity.y));
    unvisual::debugger->nextLine();
    if(equipped!=nullptr)
    {
        unvisual::debugger->print("Weapon position:");
        unvisual::debugger->nextLine();
	    unvisual::debugger->print("X = " + std::to_string(equipped->getPosition().x));
	    unvisual::debugger->nextLine();
        unvisual::debugger->print("Y = " + std::to_string(equipped->getPosition().y));
        unvisual::debugger->nextLine();
        unvisual::debugger->print(equipped->getCharacter());
        unvisual::debugger->nextLine();
    }
	
    if(heading!=Vector2d<float>())
    {
        orientation = heading;
    }

    if(orientation.x!=0.0f)
    {
        setAngle((90.0f*orientation.x) + (45.0f*orientation.x*orientation.y));
    }
    else
    {
        setAngle(90.0f + 90.0f*orientation.y);
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Player::setSprite(Sprite* spr)
{
    Combat_Character::setSprite(spr);
}

void Player::setPosition(const Vector2d<float>& pos)
{
    Combat_Character::setPosition(pos);
}

void Player::setWorld(World* w)
{
    Combat_Character::setWorld(w);
}

void Player::setBody(Collider* c)
{
    if(body!=nullptr)
    {
        delete body;
    }
    body = c;
}

void Player::setVelocity(const Vector2d<float>& vel)
{
    Combat_Character::setVelocity(vel);
}

void Player::setAngle(float angl)
{
    Combat_Character::setAngle(angl);
}

void Player::addWeapon(Weapon* wp)
{
    Combat_Character::addWeapon(wp);
}

void Player::removeWeapon(Weapon* wp)
{
    Combat_Character::removeWeapon(wp);
}

void Player::equipWeapon(size_t index)
{
    Combat_Character::equipWeapon(index);
}

//=========================================
//=               GETTERS   	    	  =
//=========================================

Sprite* Player::getSprite() const
{
    return Combat_Character::getSprite();
}

const Vector2d<float>& Player::getPosition() const
{
    return Combat_Character::getPosition();
}

World* Player::getWorld() const
{
    return Combat_Character::getWorld();
}

Collider* Player::getBody() const
{
    return Combat_Character::getBody();
}

const Vector2d<float>& Player::getVelocity() const
{
    return Combat_Character::getVelocity();
}

const Vector2d<float>& Player::getPrePosition() const
{
    return Combat_Character::getPrePosition();
}

const Vector2d<float>& Player::getRenderPosition() const
{
    return Combat_Character::getRenderPosition();
}

const Class_Id& Player::getClassId() const
{
    return Combat_Character::getClassId();
}

float Player::getAngle() const
{
    return Combat_Character::getAngle();
}

const std::vector<Weapon*>& Player::getWeapons() const
{
    return Combat_Character::getWeapons();
}

Weapon* Player::getWeaponEquipped() const
{
    return Combat_Character::getWeaponEquipped();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Player::~Player()
{
    
}