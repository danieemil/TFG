#ifndef _INTERACTABLE_MANAGER_
#define _INTERACTABLE_MANAGER_

#include "functional"
#include <unordered_map>
#include "World.h"
#include "SpriteManager.h"


// Tipos de armas instanciables
enum class InteractableType
{
    exit,
    health,
};



class InteractableManager
{

public:
    // Constructores
    InteractableManager(const char* interactable_sprites_path);
    InteractableManager(const InteractableManager& im);

    InteractableManager& operator= (const InteractableManager& im);

    // Métodos
    Interactable* createInteractable(InteractableType it, World* w, const Vector2d<float>& pos = Vector2d<float>(), int value = 0);

    Exit* createExit(World* w, const Vector2d<float>& pos = Vector2d<float>(), int value = 0);
    Health* createHealth(World* w, const Vector2d<float>& pos = Vector2d<float>(), int value = 0);

    // Setters
    void setSprites(const char* tileset);

    // Getters

    // Destructor
    ~InteractableManager();

private:

    SpriteManager sprites_manager;

};

#endif