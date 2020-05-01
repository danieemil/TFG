#include "Player.h"
#include "World.h"

using namespace unvisual;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Player::Player(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c, Weapon* wp, const Vector2d<float>& maxvel)
: Combat_Character(pos, spr, w, c, wp), max_velocity(maxvel)
{
    physics::addDynamic(c);
}

Player::Player(const Player& p)
: Combat_Character(p), max_velocity(p.max_velocity)
{

}

Player& Player::operator= (const Player& p)
{
    Combat_Character::operator=(p);

    max_velocity = p.max_velocity;

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

void Player::processInput()
{

    velocity.x = 0;
    velocity.y = 0;

    if( input::isPressed(input::N3DS_buttons::Key_DUp)
    ||
        input::isHeld(input::N3DS_buttons::Key_DUp))
    {
        unvisual::debugger->setRow(1);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Up");
        velocity.y = velocity.y - max_velocity.y;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DRight)
    ||
        input::isHeld(input::N3DS_buttons::Key_DRight))
    {
        unvisual::debugger->setRow(2);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Right");
        velocity.x = velocity.x + max_velocity.x;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DDown)
    ||
        input::isHeld(input::N3DS_buttons::Key_DDown))
    {
        unvisual::debugger->setRow(3);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Down");
        velocity.y = velocity.y + max_velocity.y;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DLeft)
    ||
        input::isHeld(input::N3DS_buttons::Key_DLeft))
    {
        unvisual::debugger->setRow(4);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Left");
        velocity.x = velocity.x - max_velocity.x;
    }

    unvisual::debugger->setRow(6);
    unvisual::debugger->setColumn(1);
    unvisual::debugger->print("Player position:");
    unvisual::debugger->nextLine();
    unvisual::debugger->print("X = " + std::to_string(position.x));
    unvisual::debugger->nextLine();
    unvisual::debugger->print("Y = " + std::to_string(position.y));
    unvisual::debugger->nextLine();

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
        physics::removeDynamic(body);
        delete body;
    }
    body = c;
    physics::addDynamic(body);
}

void Player::setVelocity(const Vector2d<float>& vel)
{
    Combat_Character::setVelocity(vel);
}

void Player::addWeapon(Weapon* wp)
{
    Combat_Character::addWeapon(wp);
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

const std::vector<Weapon*>& Player::getWeapons() const
{
    return Combat_Character::getWeapons();
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Player::~Player()
{
    
}