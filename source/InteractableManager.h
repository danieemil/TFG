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
};



class InteractableManager
{

public:
    // Constructores
    InteractableManager(const char* interactable_sprites_path);
    InteractableManager(const InteractableManager& im);

    InteractableManager& operator= (const InteractableManager& im);

    // Métodos
    Interactable* createInteractable(InteractableType it, World* w, const Vector2d<float>& pos = Vector2d<float>());

    Exit* createExit(World* w, const Vector2d<float>& pos = Vector2d<float>());

    // Setters
    void setSprites(const char* tileset);

    // Getters

    // Destructor
    ~InteractableManager();

private:

    SpriteManager sprites_manager;

};

#endif