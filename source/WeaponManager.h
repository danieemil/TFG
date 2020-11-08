#ifndef _WEAPON_MANAGER_
#define _WEAPON_MANAGER_

#include "Weapon.h"
#include "SpriteManager.h"


// Tipos de armas instanciables
enum class weapon_type
{
    dagger,
    other,
};



class WeaponManager
{

public:
    // Constructores
    WeaponManager(const char* weapon_sprites_path);
    WeaponManager(const WeaponManager& wm);

    WeaponManager& operator= (const WeaponManager& wm);

    // Métodos
    Weapon* createWeapon(weapon_type wt);
    void deleteWeapon(Weapon* w);

    Weapon* createDagger();

    // Setters

    // Getters

    // Destructor
    ~WeaponManager();

private:

    SpriteManager sprites_manager;
    std::vector<Weapon*> weapons;


};

#endif