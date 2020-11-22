#ifndef _WEAPON_MANAGER_
#define _WEAPON_MANAGER_

#include "Dagger.h"
#include "SpriteManager.h"



class WeaponManager
{

public:
    // Constructores
    WeaponManager(const char* weapon_sprites_path);
    WeaponManager(const WeaponManager& wm);

    WeaponManager& operator= (const WeaponManager& wm);

    // Métodos
    Weapon* createWeapon(WeaponType wt, Combat_Character* cc);

    Dagger* createDagger(Combat_Character* cc);
    Weapon* createSword(Combat_Character* cc);

    // Setters
    void setSprites(const char* tileset);

    // Getters

    // Destructor
    ~WeaponManager();

private:

    SpriteManager sprites_manager;

};

#endif