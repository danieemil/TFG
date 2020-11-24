#ifndef _WEAPON_MANAGER_
#define _WEAPON_MANAGER_

#include "Dagger.h"
#include "Sword.h"
#include "Pickaxe.h"
#include "SpriteManager.h"

#define DAGGER_ICON 0
#define DAGGER_ANIM_START 1
#define DAGGER_ANIM_SIZE 3

#define SWORD_ICON 4
#define SWORD_ANIM_START 5
#define SWORD_ANIM_SIZE 6

#define PICKAXE_ICON 11
#define PICKAXE_ANIM_START 12
#define PICKAXE_ANIM_SIZE 0


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
    Sword* createSword(Combat_Character* cc);
    Pickaxe* createPickaxe(Combat_Character* cc);

    // Setters
    void setSprites(const char* tileset);

    // Getters

    // Destructor
    ~WeaponManager();

private:

    SpriteManager sprites_manager;

};

#endif