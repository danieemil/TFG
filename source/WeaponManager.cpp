#include "WeaponManager.h"

#include "functional"
#include <unordered_map>
#include "Unvisual_Engine.h"

//Mapa que relaciona las armas que se pueden crear junto con su método de creación
const std::unordered_map<weapon_type, std::function<Weapon* (WeaponManager*)>> weapons_map = 
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

Weapon* WeaponManager::createWeapon(weapon_type wt)
{
    auto it = weapons_map.find(wt);
    if(it != weapons_map.end())
    {
        if(it->second!=nullptr)
        {
            Weapon* w = it->second(this);
            if(w!=nullptr)
            {
                weapons.push_back(w);
            }
            return w;
        }
    }

    return nullptr;
}

void WeaponManager::deleteWeapon(Weapon* w)
{
    if (w != nullptr)
    {
        for (auto it = weapons.begin(); it != weapons.end(); it++)
        {
            Weapon* we = *it;
            if(we == w)
            {
                delete w;
                weapons.erase(it);
                return;
            }
        }
    }
    
}


Weapon* WeaponManager::createDagger()
{

    unvisual::breakpoint();

    return nullptr;
}





//=========================================
//=               SETTERS   	    	  =
//=========================================




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
            delete it;
        }
    }

    weapons.clear();
    
}