#include "WeaponManager.h"

#include "Combat_Character.h"

#include "functional"
#include <unordered_map>
#include "Unvisual_Engine.h"

//Mapa que relaciona las armas que se pueden crear junto con su método de creación
const std::unordered_map<WeaponType, std::function<Weapon* (WeaponManager*, Combat_Character*)>> weapons_map = 
{
    {WeaponType::dagger, &WeaponManager::createDagger},
    {WeaponType::other, &WeaponManager::createDagger},
};

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

WeaponManager::WeaponManager(const char* weapon_sprites_path)
: sprites_manager(weapon_sprites_path)
{

}

WeaponManager::WeaponManager(const WeaponManager& wm)
: sprites_manager(wm.sprites_manager)
{

}

WeaponManager& WeaponManager::operator= (const WeaponManager& wm)
{
    sprites_manager = wm.sprites_manager;
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Weapon* WeaponManager::createWeapon(WeaponType wt, Combat_Character* cc)
{
    if(cc!=nullptr)
    {
        auto it = weapons_map.find(wt);
        if(it != weapons_map.end())
        {
            if(it->second!=nullptr)
            {
                return it->second(this, cc);
            }
        }
    }
    return nullptr;
}


Weapon* WeaponManager::createDagger(Combat_Character* cc)
{

    // Gráficos del arma
    Sprite* weapon_sprite = sprites_manager.createSprite(0);
    if(weapon_sprite!=nullptr)
    {
        weapon_sprite->setCenter(Vector2d<float>(0.5f,0.5f));
    }

    // Colisiones del arma
    AABB* weapon_shape = new AABB(Vector2d<float>(-15,-20), Vector2d<float>(15,1));

    // Crear arma
    int weapon_damage = 10;
    float weapon_knockback = 200.0f;
    float weapon_time_attack = 0.2f;
    Vector2d<float> weapon_relative_position_attacking = Vector2d<float>(0.0f,-10.0f);
    Vector2d<float> ori = cc->getOrientation();
    Weapon* w = new Weapon(weapon_damage, weapon_knockback, weapon_time_attack, weapon_relative_position_attacking, weapon_sprite, nullptr, weapon_shape, CollisionFlag::none, CollisionFlag::none, ori);
    w->setCharacter(cc);

    return w;
}





//=========================================
//=               SETTERS   	    	  =
//=========================================

void WeaponManager::setSprites(const char* tileset)
{
    sprites_manager.setSprites(tileset);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================



//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

WeaponManager::~WeaponManager()
{
    
}