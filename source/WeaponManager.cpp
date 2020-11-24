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
    {WeaponType::pickaxe, &WeaponManager::createPickaxe},
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
    Sprite* weapon_sprite = sprites_manager.createSprite(DAGGER_ICON);

    Sprite* dagger_sprite = sprites_manager.createSprite(DAGGER_ANIM_START);
    Vector2d<float> dagger_sprite_size;
    if(dagger_sprite!=nullptr)
    {
        dagger_sprite->setCenter(Vector2d<float>(0.5f,0.5f));
        auto s = dagger_sprite->getSize();
        dagger_sprite_size = Vector2d<float>(s.x, s.y);
    }

    Vector2d<float> cc_center_rel;
    Sprite* cc_spr = cc->getSprite();

    if(cc_spr!=nullptr)
    {
        cc_center_rel = cc_spr->getCenter();
    }

    Vector2d<float> weapon_relative_position_attacking =
    (Vector2d<float>(0,-cc_center_rel.y) - Vector2d<float>(dagger_sprite_size.x/2, dagger_sprite_size.y));


    // Colisiones de la daga

    Vector2d<float> shape_padding = Vector2d<float>(0,0);

    Vector2d<float> min_pos_rel = weapon_relative_position_attacking - (shape_padding/2.0f);
    Vector2d<float> max_pos_rel = weapon_relative_position_attacking + dagger_sprite_size + (shape_padding/2.0f);

    // Caja sin rotaciones (menos precisa / menos costosa de comprobar)
    //Shape* weapon_shape = new AABB(min_pos_rel, max_pos_rel);


    // Caja con rotaciones (más preciso / más costosa de comprobar)
    std::vector<Vector2d<float>> vertices =
    {
        {min_pos_rel},
        {max_pos_rel.x, min_pos_rel.y},
        {max_pos_rel},
        {min_pos_rel.x, max_pos_rel.y}
    };

    Shape* weapon_shape = new Convex(vertices);


    // Animaciones de la daga
    Animation* weapon_anim = new Animation();
        // Daga a medio camino
        weapon_anim->addBackSprite(dagger_sprite,0.01f);
        // Daga al final del camino
        weapon_anim->addBackSprite(sprites_manager.createSprite(2),0.1f);
        // Daga a medio camino
        weapon_anim->addBackSprite(sprites_manager.createSprite(1),0.05f);
        // Daga guardada
        weapon_anim->addBackSprite(sprites_manager.createSprite(3),0.05);



    // Crear la daga
    int weapon_damage = 2;
    float weapon_knockback = 150.0f;
    float weapon_time_attack = 0.3f;
    weapon_relative_position_attacking += Vector2d<float>(0.25f, -0.25f); //Soluciona bugs visuales
    Vector2d<float> ori = cc->getOrientation();
    Dagger* d = new Dagger(weapon_damage, weapon_knockback, weapon_time_attack, weapon_relative_position_attacking, weapon_sprite, nullptr, weapon_shape, CollisionFlag::none, CollisionFlag::none, ori, cc, weapon_anim);

    return d;
}

Sword* WeaponManager::createSword(Combat_Character* cc)
{

    // Gráficos de la espada
    Sprite* weapon_sprite = sprites_manager.createSprite(SWORD_ICON);

    Sprite* sword_sprite = sprites_manager.createSprite(SWORD_ANIM_START);

    Vector2d<float> sword_sprite_size;
    if(sword_sprite!=nullptr)
    {
        sword_sprite->setCenter(Vector2d<float>(0.5f,0.5f));
        auto s = sword_sprite->getSize();
        sword_sprite_size = Vector2d<float>(s.x, s.y);
    }

    Vector2d<float> cc_center_rel;
    Sprite* cc_spr = cc->getSprite();

    if(cc_spr!=nullptr)
    {
        cc_center_rel = cc_spr->getCenter();
    }

    Vector2d<float> weapon_relative_position_attacking =
    (Vector2d<float>(0,0) - Vector2d<float>(sword_sprite_size.x/2, sword_sprite_size.y));


    // Colisiones de la espada

    Vector2d<float> shape_padding = Vector2d<float>(0,0);

    Vector2d<float> min_pos_rel = weapon_relative_position_attacking - (shape_padding/2.0f);
    Vector2d<float> max_pos_rel = weapon_relative_position_attacking + sword_sprite_size + (shape_padding/2.0f);

    // Caja sin rotaciones (menos precisa / menos costosa de comprobar)
    //Shape* weapon_shape = new AABB(min_pos_rel, max_pos_rel);


    // Caja con rotaciones (más preciso / más costosa de comprobar)
    std::vector<Vector2d<float>> vertices =
    {
        {min_pos_rel},
        {max_pos_rel.x, min_pos_rel.y},
        {max_pos_rel},
        {min_pos_rel.x, max_pos_rel.y}
    };

    Shape* weapon_shape = new Convex(vertices);


    // Animaciones de la espada
    Animation* weapon_anim = new Animation();

    weapon_anim->addBackSprite(sword_sprite,0.1f);

    for (auto i = 1; i < SWORD_ANIM_SIZE - 2; i++)
    {
        weapon_anim->addBackSprite(sprites_manager.createSprite(i + SWORD_ANIM_START),0.025f);
    }

    weapon_anim->addBackSprite(sprites_manager.createSprite(SWORD_ANIM_START + SWORD_ANIM_SIZE - 2),0.1f);

    weapon_anim->addBackSprite(sprites_manager.createSprite(SWORD_ANIM_START + SWORD_ANIM_SIZE - 1),0.1f);

    // Crear la espada
    
    int weapon_damage = 1;
    float weapon_knockback = 200.0f;
    float weapon_time_attack = 0.5f;
    weapon_relative_position_attacking += Vector2d<float>(0.25f, -0.25f); //Soluciona bugs visuales
    Vector2d<float> ori = cc->getOrientation();
    Sword* s = new Sword(weapon_damage, weapon_knockback, weapon_time_attack, weapon_relative_position_attacking, weapon_sprite, nullptr, weapon_shape, CollisionFlag::none, CollisionFlag::none, ori, cc, weapon_anim);

    

    return s;
}

Pickaxe* WeaponManager::createPickaxe(Combat_Character* cc)
{

    // Gráficos del pico
    Sprite* weapon_sprite = sprites_manager.createSprite(PICKAXE_ICON);

    Sprite* pickaxe_sprite = sprites_manager.createSprite(PICKAXE_ANIM_START);
    Vector2d<float> pickaxe_sprite_size;
    if(pickaxe_sprite!=nullptr)
    {
        pickaxe_sprite->setCenter(Vector2d<float>(0.5f,0.5f));
        auto s = pickaxe_sprite->getSize();
        pickaxe_sprite_size = Vector2d<float>(s.x, s.y);
    }

    Vector2d<float> cc_center_rel;
    Sprite* cc_spr = cc->getSprite();

    if(cc_spr!=nullptr)
    {
        cc_center_rel = cc_spr->getCenter();
    }

    Vector2d<float> weapon_relative_position_attacking =
    (Vector2d<float>(0,0) - Vector2d<float>(pickaxe_sprite_size.x/2, pickaxe_sprite_size.y));


    // Colisiones del pico

    Vector2d<float> shape_padding = Vector2d<float>(0,0);

    Vector2d<float> min_pos_rel = weapon_relative_position_attacking - (shape_padding/2.0f);
    Vector2d<float> max_pos_rel = weapon_relative_position_attacking + pickaxe_sprite_size + (shape_padding/2.0f);

    // Caja sin rotaciones (menos precisa / menos costosa de comprobar)
    //Shape* weapon_shape = new AABB(min_pos_rel, max_pos_rel);


    // Caja con rotaciones (más preciso / más costosa de comprobar)
    std::vector<Vector2d<float>> vertices =
    {
        {min_pos_rel},
        {max_pos_rel.x, min_pos_rel.y},
        {max_pos_rel},
        {min_pos_rel.x, max_pos_rel.y}
    };

    Shape* weapon_shape = new Convex(vertices);


    // Animaciones del pico
    Animation* weapon_anim = new Animation();

    weapon_anim->addBackSprite(pickaxe_sprite,0.2f);

    for (auto i = 1; i < PICKAXE_ANIM_SIZE; i++)
    {
        weapon_anim->addBackSprite(sprites_manager.createSprite(i + PICKAXE_ANIM_START),0.15f);
    }


    // Crear el pico
    int weapon_damage = 1;
    float weapon_knockback = 250.0f;
    float weapon_time_attack = 1.0f;
    weapon_relative_position_attacking += Vector2d<float>(0.25f, -0.25f); //Soluciona bugs visuales
    Vector2d<float> ori = cc->getOrientation();
    Pickaxe* p = new Pickaxe(weapon_damage, weapon_knockback, weapon_time_attack, weapon_relative_position_attacking, weapon_sprite, nullptr, weapon_shape, CollisionFlag::none, CollisionFlag::none, ori, cc, weapon_anim);

    return p;
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