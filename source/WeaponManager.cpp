#include "WeaponManager.h"

#include "Combat_Character.h"

#include "functional"
#include <unordered_map>
#include "Unvisual_Engine.h"

//Mapa que relaciona las armas que se pueden crear junto con su método de creación
const std::unordered_map<WeaponType, std::function<Weapon* (WeaponManager*, Combat_Character*)>> weapons_map = 
{
    {WeaponType::dagger, &WeaponManager::createDagger},
    {WeaponType::sword, &WeaponManager::createSword},
};

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

WeaponManager::WeaponManager(const char* weapon_sprites_path)
: sprites_manager(weapon_sprites_path)
{

}

WeaponManager::WeaponManager(const WeaponManager& wm)
: sprites_manager(wm.sprites_manager)
{

}

WeaponManager& WeaponManager::operator= (const WeaponManager& wm)
{
    sprites_manager = wm.sprites_manager;
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Weapon* WeaponManager::createWeapon(WeaponType wt, Combat_Character* cc)
{
    if(cc!=nullptr)
    {
        if (!cc->hasWeapon(wt))
        {
            auto it = weapons_map.find(wt);
            if(it != weapons_map.end())
            {
                if(it->second!=nullptr)
                {
                    return it->second(this, cc);
                }
            }
        }
    }
    return nullptr;
}


Dagger* WeaponManager::createDagger(Combat_Character* cc)
{
    // Gráficos de la daga
    Sprite* weapon_sprite = sprites_manager.createSprite(0);
    if(weapon_sprite!=nullptr)
    {
        weapon_sprite->setCenter(Vector2d<float>(0.5f,0.5f));
    }

    // Colisiones de la daga
    Vector2d<float> min_pos_rel = Vector2d<float>(-5, -20);
    Vector2d<float> max_pos_rel = Vector2d<float>(5,-10);
    AABB* weapon_shape = new AABB(min_pos_rel, max_pos_rel);


    // Animaciones de la daga
    Animation* weapon_anim = new Animation();
        // Daga a medio camino
        weapon_anim->addBackSprite(sprites_manager.createSprite(1),0.01f);
        // Daga al final del camino
        weapon_anim->addBackSprite(sprites_manager.createSprite(2),0.1f);
        // Daga a medio camino
        weapon_anim->addBackSprite(sprites_manager.createSprite(1),0.05f);
        // Daga guardada
        weapon_anim->addBackSprite(sprites_manager.createSprite(3),0.05);

    // Crear la daga
    int weapon_damage = 2;
    float weapon_knockback = 200.0f;
    float weapon_time_attack = 0.3f;
    Vector2d<float> weapon_relative_position_attacking = Vector2d<float>(1.25f,-12.25f);
    Vector2d<float> ori = cc->getOrientation();
    Dagger* d = new Dagger(weapon_damage, weapon_knockback, weapon_time_attack, weapon_relative_position_attacking, weapon_sprite, nullptr, weapon_shape, CollisionFlag::none, CollisionFlag::none, ori, cc, weapon_anim);

    return d;
}

Sword* WeaponManager::createSword(Combat_Character* cc)
{

    // Gráficos de la daga
    Sprite* weapon_sprite = sprites_manager.createSprite(0);
    if(weapon_sprite!=nullptr)
    {
        weapon_sprite->setCenter(Vector2d<float>(0.5f,0.5f));
    }

    // Colisiones de la daga
    Vector2d<float> min_pos_rel = Vector2d<float>(-15,-20);
    Vector2d<float> max_pos_rel = Vector2d<float>(15,1);
    AABB* weapon_shape = new AABB(min_pos_rel, max_pos_rel);


    // Animaciones de la daga
    Animation* weapon_anim = new Animation();
        // Daga a medio camino
        weapon_anim->addBackSprite(sprites_manager.createSprite(1),0.05f);
        // Daga al final del camino
        weapon_anim->addBackSprite(sprites_manager.createSprite(2),0.1f);
        // Daga a medio camino
        weapon_anim->addBackSprite(sprites_manager.createSprite(1),0.05f);
        // Daga guardada
        weapon_anim->addBackSprite(sprites_manager.createSprite(3),0.05);

    // Crear la daga
    int weapon_damage = 1;
    float weapon_knockback = 200.0f;
    float weapon_time_attack = 0.7f;
    Vector2d<float> weapon_relative_position_attacking = Vector2d<float>(-5.0f,-10.0f);
    Vector2d<float> ori = cc->getOrientation();
    Sword* w = new Sword(weapon_damage, weapon_knockback, weapon_time_attack, weapon_relative_position_attacking, weapon_sprite, nullptr, weapon_shape, CollisionFlag::none, CollisionFlag::none, ori, cc, weapon_anim);

    return w;
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void WeaponManager::setSprites(const char* tileset)
{
    sprites_manager.setSprites(tileset);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================



//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

WeaponManager::~WeaponManager()
{
    
}