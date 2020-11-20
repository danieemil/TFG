#include "InteractableManager.h"

#include "Unvisual_Engine.h"

//Mapa que relaciona las armas que se pueden crear junto con su método de creación
const std::unordered_map<InteractableType, std::function<Interactable* (InteractableManager*, World*, const Vector2d<float>&, int)>> interactables_map = 
{
    {InteractableType::exit, &InteractableManager::createExit},
    {InteractableType::health, &InteractableManager::createHealth},
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

Interactable* InteractableManager::createInteractable(InteractableType it, World* w, const Vector2d<float>& pos, int value)
{
    if(w!=nullptr)
    {
        auto iter = interactables_map.find(it);
        if(iter != interactables_map.end())
        {
            if(iter->second!=nullptr)
            {
                return iter->second(this, w, pos, value);
            }
        }
    }
    return nullptr;
}


Exit* InteractableManager::createExit(World* w, const Vector2d<float>& pos, int value)
{
    // Gráficos de la salida
    Vector2d<float> ori = Vector2d<float>(0.0f,-1.0f);
    Sprite* spr = sprites_manager.createSprite(0);
    AABB* exit_shape = nullptr;

    // Físicas de la salida
    if(spr!=nullptr)
    {
        exit_shape = spr->createSpriteCollisionShape();
    }

    // Crear la salida
    Exit* exit = new Exit(pos, spr, w, exit_shape, ori);
    w->addEntity(exit);

    return exit;
}

Health* InteractableManager::createHealth(World* w, const Vector2d<float>& pos, int value)
{
    // Gráficos de la salud
    Vector2d<float> ori = Vector2d<float>(0.0f,-1.0f);
    Sprite* spr = sprites_manager.createSprite(1);
    AABB* health_shape = nullptr;

    // Físicas de la salud
    if(spr!=nullptr)
    {
        health_shape = spr->createSpriteCollisionShape();
    }

    // Crear la salud
    Health* health = new Health(value, pos, spr, w, health_shape, ori);
    w->addEntity(health);

    return health;
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