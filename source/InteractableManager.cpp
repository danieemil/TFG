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


Exit* InteractableManager::createExit(World* w, const Vector2d<float>& pos)
{

    Vector2d<float> ori = Vector2d<float>(0.0f,-1.0f);
    Sprite* spr = sprites_manager.createSprite(3);

    Exit* exit = new Exit(pos, spr, w, ori);
    w->addEntity(exit);

    return exit;
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