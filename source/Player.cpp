#include "Player.h"
#include "World.h"

using namespace unvisual;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Player::Player(const Vector2d<float>& pos, Sprite* spr, World* w, Collider* c, Weapon* wp) : Combat_Character(pos, spr, w, c, wp)
{
    physics::addDynamic(c);
}

Player::Player(const Player& p) : Combat_Character(p)
{

}

Player& Player::operator= (const Player& p)
{
    this->Combat_Character::operator=(p);

    return *this;
}

//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Player::render()
{
    Combat_Character::render();
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

    Vector2d<float> dir = Vector2d<float>(0,0);

    u8 vel = 2;

    if( input::isPressed(input::N3DS_buttons::Key_DUp)
    ||
        input::isHeld(input::N3DS_buttons::Key_DUp))
    {
        unvisual::debugger->setRow(1);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Up");
        dir.y = dir.y - vel;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DRight)
    ||
        input::isHeld(input::N3DS_buttons::Key_DRight))
    {
        unvisual::debugger->setRow(2);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Right");
        dir.x = dir.x + vel;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DDown)
    ||
        input::isHeld(input::N3DS_buttons::Key_DDown))
    {
        unvisual::debugger->setRow(3);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Down");
        dir.y = dir.y + vel;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DLeft)
    ||
        input::isHeld(input::N3DS_buttons::Key_DLeft))
    {
        unvisual::debugger->setRow(4);
        unvisual::debugger->setColumn(1);
        unvisual::debugger->print("Left");
        dir.x = dir.x - vel;
    }

    position.x += dir.x;
    position.y += dir.y;

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