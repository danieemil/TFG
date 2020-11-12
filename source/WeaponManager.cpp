#include "WeaponManager.h"

#include "functional"
#include <unordered_map>
#include "Unvisual_Engine.h"

//Mapa que relaciona las armas que se pueden crear junto con su método de creación
const std::unordered_map<weapon_type, std::function<Weapon* (WeaponManager*, Combat_Character*)>> weapons_map = 
{
    {weapon_type::dagger, &WeaponManager::createDagger},
    {weapon_type::other, &WeaponManager::createDagger},
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

Weapon* WeaponManager::createWeapon(weapon_type wt, Combat_Character* cc)
{
    if(cc!=nullptr)
    {
        auto it = weapons_map.find(wt);
        if(it != weapons_map.end())
        {
            if(it->second!=nullptr)
            {
                Weapon* w = it->second(this, cc);
                if(w!=nullptr)
                {
                    weapons.push_back(w);
                }
                return w;
            }
        }
    }
    return nullptr;
}

void WeaponManager::eraseWeapon(Weapon* w)
{
    if (w != nullptr)
    {
        for (auto it = weapons.begin(); it != weapons.end(); it++)
        {
            Weapon* we = *it;
            if(we == w)
            {
                weapons.erase(it);
                return;
            }
        }
    }
}


Weapon* WeaponManager::createDagger(Combat_Character* cc)
{

    // Gráficos del arma
    Sprite* weapon_sprite = sprites_manager.createSprite(1);
    auto w_s = weapon_sprite->getSize();
    weapon_sprite->setCenter(Vector2d<float>(0.5f,0.5f));

    // Crear arma
    int weapon_damage = 10;
    float weapon_knockback = 200.0f;
    float weapon_time_attack = 0.2f;
    Vector2d<float> weapon_relative_position_attacking = Vector2d<float>(0.0f,-10.0f);
    Weapon* w = new Weapon(weapon_damage, weapon_knockback, weapon_time_attack,
    weapon_relative_position_attacking, weapon_sprite, nullptr, CollisionFlag::none, CollisionFlag::none);
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
    for (auto &&it : weapons)
    {
        if(it!=nullptr)
        {
            //delete it;
        }
    }

    weapons.clear();
    
}