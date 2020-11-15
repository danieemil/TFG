#include "InteractableManager.h"

#include "Unvisual_Engine.h"

//Mapa que relaciona las armas que se pueden crear junto con su método de creación
const std::unordered_map<InteractableType, std::function<Interactable* (InteractableManager*, World*, const Vector2d<float>&)>> interactables_map = 
{
    {InteractableType::exit, &InteractableManager::createExit},
};

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

InteractableManager::InteractableManager(const char* interactable_sprites_path)
: sprites_manager(interactable_sprites_path)
{

}

InteractableManager::InteractableManager(const InteractableManager& im)
: sprites_manager(im.sprites_manager)
{

}

InteractableManager& InteractableManager::operator= (const InteractableManager& im)
{
    sprites_manager = im.sprites_manager;
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Interactable* InteractableManager::createInteractable(InteractableType it, World* w, const Vector2d<float>& pos)
{
    if(w!=nullptr)
    {
        auto iter = interactables_map.find(it);
        if(iter != interactables_map.end())
        {
            if(iter->second!=nullptr)
            {
                return iter->second(this, w, pos);
            }
        }
    }
    return nullptr;
}


Interactable* InteractableManager::createExit(World* w, const Vector2d<float>& pos)
{

    return nullptr;
}





//=========================================
//=               SETTERS   	    	  =
//=========================================

void InteractableManager::setSprites(const char* tileset)
{
    sprites_manager.setSprites(tileset);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================



//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

InteractableManager::~InteractableManager()
{
    
}