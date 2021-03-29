#ifndef _ENTITY_MANAGER_
#define _ENTITY_MANAGER_

#include "WeaponManager.h"
#include "EnemyManager.h"
#include "InteractableManager.h"
#include "Player.h"



class EntityManager
{

public:
    // Constructores
    EntityManager(const char* entity_sprites_path, const char* weapon_sprites_path = nullptr,
    const char* enemy_sprites_path = nullptr, const char* interactable_sprites_path = nullptr);

    EntityManager(const EntityManager& em);

    EntityManager& operator= (const EntityManager& em);

    // Métodos
    Weapon* createWeapon(WeaponType wt, Combat_Character* cc);
    Player* createPlayer(const Vector2d<float>& pos = Vector2d<float>());
    Enemy* createEnemy(EnemyType et, const Vector2d<float>& pos = Vector2d<float>());
    Interactable* createInteractable(InteractableType it, const Vector2d<float>& pos = Vector2d<float>(), int value = 0);

    // Setters
    void setSprites(const char* entity_tileset, const char* weapon_tileset = nullptr,
        const char* enemy_tileset = nullptr, const char* interactable_tileset = nullptr);

    // Getters

    // Destructor
    ~EntityManager();

private:

    SpriteManager sprites_manager;
    WeaponManager weapon_manager;
    EnemyManager enemy_manager;
    InteractableManager interactable_manager;

};

#endif