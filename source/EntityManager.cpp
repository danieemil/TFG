#include "EntityManager.h"



//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

EntityManager::EntityManager(const char* entity_sprites_path,
    const char* weapon_sprites_path, const char* enemy_sprites_path,
    const char* interactable_sprites_path)
: sprites_manager(entity_sprites_path), weapon_manager(weapon_sprites_path),
    enemy_manager(enemy_sprites_path), interactable_manager(interactable_sprites_path)
{
    if (enemy_sprites_path == nullptr)
    {
        enemy_manager.setSprites(entity_sprites_path);
    }
    if (weapon_sprites_path == nullptr)
    {
        weapon_manager.setSprites(entity_sprites_path);
    }
    if (interactable_sprites_path == nullptr)
    {
        interactable_manager.setSprites(entity_sprites_path);
    }
}

EntityManager::EntityManager(const EntityManager& em)
: sprites_manager(em.sprites_manager), weapon_manager(em.weapon_manager),
    enemy_manager(em.enemy_manager), interactable_manager(em.interactable_manager)
{

}

EntityManager& EntityManager::operator= (const EntityManager& em)
{
    sprites_manager = em.sprites_manager;
    weapon_manager = em.weapon_manager;
    enemy_manager = em.enemy_manager;
    interactable_manager = em.interactable_manager;
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Weapon* EntityManager::createWeapon(WeaponType wt, Combat_Character* cc)
{
    return weapon_manager.createWeapon(wt, cc);
}

Player* EntityManager::createPlayer(World* w, const Vector2d<float>& pos)
{
    // Gráficos del jugador
    Sprite* player_sprite = sprites_manager.createSprite(0);
    player_sprite->setCenter(Vector2d<float>(0.5f,0.5f));
    Vector2d<float> player_center = player_sprite->getCenter();

    // Colisiones del jugador
    CollisionFlag player_interests = CollisionFlag::enemy_hit | CollisionFlag::enemy_hurt;

    // Otros atributos del jugador
    int player_life = 11;
    Vector2d<float> player_max_vel = Vector2d<float>(400.0f,400.0f);
    Vector2d<float> player_max_accel = Vector2d<float>(INFINITY, INFINITY); // Máximo de fuerza que se le puede aplicar a un cuerpo
    Vector2d<float> player_frict = Vector2d<float>(40.0f,40.0f);
    Vector2d<float> player_init_orientation = Vector2d<float>(0.0f,-1.0f);
    float player_stunned_time = 0.5f;

    // Creación final del jugador
    Player* player = new Player(player_life, pos, player_sprite, w, player_interests, player_init_orientation, player_max_vel, player_max_accel, player_frict, nullptr, player_stunned_time);
    player->getBody()->setRotationCenter(player_center);
    w->setPlayer(player);

    return player;
}

Enemy* EntityManager::createEnemy(EnemyType et, World* w, const Vector2d<float>& pos)
{
    return enemy_manager.createEnemy(et, w, pos);
}

Interactable* EntityManager::createInteractable(InteractableType it, World* w, const Vector2d<float>& pos, int value)
{
    return interactable_manager.createInteractable(it, w, pos, value);
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void EntityManager::setSprites(const char* entity_tileset, const char* weapon_tileset,
    const char* enemy_tileset, const char* interactable_tileset)
{
    if(weapon_tileset==nullptr)
    {
        weapon_tileset = entity_tileset;
    }
    if(enemy_tileset==nullptr)
    {
        enemy_tileset = entity_tileset;
    }
    if(interactable_tileset==nullptr)
    {
        interactable_tileset = entity_tileset;
    }

    sprites_manager.setSprites(entity_tileset);
    weapon_manager.setSprites(weapon_tileset);
    enemy_manager.setSprites(enemy_tileset);
    interactable_manager.setSprites(interactable_tileset);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================



//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

EntityManager::~EntityManager()
{
    
}