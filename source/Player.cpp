#include "Player.h"
#include "World.h"

#include "Game.h"

using namespace unvisual;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Player::Player(int l, const Vector2d<float>& pos, Sprite* spr, World* w, Shape* sh,
    CollisionFlag interests_flag, const Vector2d<float>& ori, const Vector2d<float>& max_vel,
    const Vector2d<float>& max_accel, const Vector2d<float>& frict, Weapon* wp, float st_time,
    float inv_time)
: Combat_Character(l, pos, spr, w, sh, CollisionFlag::player_hit, interests_flag, ori, max_vel,
    max_accel, frict, wp, st_time, inv_time)
{
    id = EntityType::e_player;
}

Player::Player(const Player& p)
: Combat_Character(p)
{

}

Player& Player::operator= (const Player& p)
{
    Combat_Character::operator=(p);

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

    // Moverse en la dirección en la que se controla al personaje
    acceleration = Vector2d<float>(40.0f, 40.0f) * heading;

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

void Player::manageAnimations()
{
    Combat_Character::manageAnimations();
}

void Player::collision(void* ent)
{
    if(ent!=nullptr)
    {
        Entity* e = static_cast<Entity*>(ent);
        if(e->getEntityType()==EntityType::e_enemy)
        {
            Enemy* en = static_cast<Enemy*>(e);

            // El jugador ha colisionado con un enemigo

            Vector2d<float> dist = position - en->getPosition();

            Vector2d<float> dir = dist;
            dir.Normalize();

            Vector2d<int> ori = Vector2d<int>(sign(dir.x), sign(dir.y));

            if((dir.x * ori.x) > 0.5f) dir.x = 1.0f * ori.x;
            else dir.x = 0.0f;

            if((dir.y * ori.y) > 0.5f) dir.y = 1.0f * ori.y;
            else dir.y = 0.0f;

            // Se orienta en dirección al enemigo
            setOrientation(dir*(-1));

            if(body!=nullptr)
            {
                body->setImpulse(dir * 290.0f);
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

            life = life - 1;
        }
    }

    Combat_Character::collision(ent);
}

void Player::attack()
{
    Combat_Character::attack();
}

void Player::cancelAttack()
{
    Combat_Character::cancelAttack();
}

void Player::die()
{
    Game::Instance()->resetLevelEvent();
}

void Player::processInput()
{

    heading = Vector2d<float>();

    if( input::isPressed(input::N3DS_buttons::Key_DUp)
        || input::isPressed(input::N3DS_buttons::Key_CPAD_Up)
    ||
        input::isHeld(input::N3DS_buttons::Key_DUp)
        || input::isHeld(input::N3DS_buttons::Key_CPAD_Up))
    {
        heading.y += -1.0f;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DRight)
        || input::isPressed(input::N3DS_buttons::Key_CPAD_Right)
    ||
        input::isHeld(input::N3DS_buttons::Key_DRight)
        || input::isHeld(input::N3DS_buttons::Key_CPAD_Right))
    {
        heading.x += 1.0f;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DDown)
        || input::isPressed(input::N3DS_buttons::Key_CPAD_Down)
    ||
        input::isHeld(input::N3DS_buttons::Key_DDown)
        || input::isHeld(input::N3DS_buttons::Key_CPAD_Down))
    {
        heading.y += 1.0f;
    }
    if( input::isPressed(input::N3DS_buttons::Key_DLeft)
        || input::isPressed(input::N3DS_buttons::Key_CPAD_Left)
    ||
        input::isHeld(input::N3DS_buttons::Key_DLeft)
        || input::isHeld(input::N3DS_buttons::Key_CPAD_Left))
    {
        heading.x += -1.0f;
    }

    if( input::isPressed(input::N3DS_buttons::Key_A))
    {
        attack();
    }

    if( input::isPressed(input::N3DS_buttons::Key_Y))
    {
        equipNextWeapon();
    }

    // Si ha girado, no está aturdido y no está atacando, puede cambiar de orientación
    if(heading!=Vector2d<float>())
    {
        setOrientation(heading);
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
    if(angle == angl) return;

    Combat_Character::setAngle(angl);

    if(sprite!=nullptr)
    {
        sprite->setRotation(angle);
    }
}

void Player::setOrientation(const Vector2d<float>& ori)
{
    Combat_Character::setOrientation(ori);
}

void Player::setAcceleration(const Vector2d<float>& accel)
{
    Combat_Character::setAcceleration(accel);
}

void Player::setFriction(const Vector2d<float>& frict)
{
    Combat_Character::setFriction(frict);
}

bool Player::addWeapon(Weapon* wp)
{
    if(Combat_Character::addWeapon(wp))
    {
        // Colisiones del arma
        CollisionFlag weapon_type = CollisionFlag::player_hurt;
        CollisionFlag weapon_interests = CollisionFlag::enemy_hit;

        Collider* weapon_collider = wp->getBody();
        if(weapon_collider!=nullptr)
        {
            CollisionFlag type = weapon_collider->getTypeFlags();
            CollisionFlag interests = weapon_collider->getInterestedFlags();

            weapon_collider->setTypeFlags(weapon_type | type);
            weapon_collider->setIntersetedFlags(weapon_interests | interests);
        }

        return true;
    }
    return false;
}

void Player::removeWeapon(Weapon* wp)
{
    Combat_Character::removeWeapon(wp);
}

void Player::equipWeapon(size_t index)
{
    Combat_Character::equipWeapon(index);
}

void Player::equipNextWeapon()
{
    Combat_Character::equipNextWeapon();
}

void Player::setAttacked(bool at)
{
    Combat_Character::setAttacked(at);
}

void Player::setStunned(bool st)
{
    Combat_Character::setStunned(st);
}

void Player::setLife(int l)
{
    Combat_Character::setLife(l);
}

void Player::setMaxLife(int l)
{
    Combat_Character::setMaxLife(l);
}

bool Player::increaseLife(int l)
{
    return Combat_Character::increaseLife(l);
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

const EntityType& Player::getEntityType() const
{
    return Combat_Character::getEntityType();
}

float Player::getAngle() const
{
    return Combat_Character::getAngle();
}

Vector2d<float> Player::getCenter() const
{
    return Combat_Character::getCenter();
}

const Vector2d<float>& Player::getOrientation() const
{
    return Combat_Character::getOrientation();
}

const Vector2d<float>& Player::getAcceleration() const
{
    return Combat_Character::getAcceleration();
}

const std::vector<Weapon*>& Player::getWeapons() const
{
    return Combat_Character::getWeapons();
}

Weapon* Player::getWeaponEquipped() const
{
    return Combat_Character::getWeaponEquipped();
}

bool Player::getAttacking() const
{
    return Combat_Character::getAttacking();
}

bool Player::getAttacked() const
{
    return Combat_Character::getAttacked();
}

bool Player::getStunned() const
{
    return Combat_Character::getStunned();
}

bool Player::getInvincible() const
{
    return Combat_Character::getInvincible();
}

int Player::getLife() const
{
    return Combat_Character::getLife();
}

int Player::getMaxLife() const
{
    return Combat_Character::getMaxLife();
}

bool Player::hasWeapon(const WeaponType& wt) const
{
    return Combat_Character::hasWeapon(wt);
}

const Vector2d<float>& Player::getHeading() const
{
    return heading;
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Player::~Player()
{
    Game::Instance()->erasePlayer();

    auto sc = unvisual::getCurrentScreen();
    if(sc!=nullptr)
    {
        auto tp = sc->getTargetPosition();
        if(tp == (&position))
        {
            sc->setTargetPosition(nullptr);
        }
    }
}