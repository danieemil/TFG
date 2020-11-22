#ifndef _INTERACTABLE_MANAGER_
#define _INTERACTABLE_MANAGER_

#include "functional"
#include <unordered_map>
#include "Exit.h"
#include "Health.h"
#include "I_Weapon.h"
#include "SpriteManager.h"


class InteractableManager
{

public:
    // Constructores
    InteractableManager(const char* interactable_sprites_path);
    InteractableManager(const InteractableManager& im);

    InteractableManager& operator= (const InteractableManager& im);

    // Métodos
    Interactable* createInteractable(InteractableType it, const Vector2d<float>& pos = Vector2d<float>(), int value = 0);

    Exit* createExit(const Vector2d<float>& pos = Vector2d<float>(), int value = 0);
    Health* createHealth(const Vector2d<float>& pos = Vector2d<float>(), int value = 0);
    I_Weapon* createWeapon(const Vector2d<float>& pos = Vector2d<float>(), int value = -1);

    // Setters
    void setSprites(const char* tileset);

    // Getters

    // Destructor
    ~InteractableManager();

private:

    SpriteManager sprites_manager;

};

#endif