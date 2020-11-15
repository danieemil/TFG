#include "EnemyManager.h"

#include "AI_Engine.h"
#include "Unvisual_Engine.h"

//Mapa que relaciona las armas que se pueden crear junto con su método de creación
const std::unordered_map<EnemyType, std::function<Enemy* (EnemyManager*, World*, const Vector2d<float>&)>> enemies_map = 
{
    {EnemyType::miner, &EnemyManager::createMiner},
};

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

EnemyManager::EnemyManager(const char* enemy_sprites_path)
: sprites_manager(enemy_sprites_path)
{

}

EnemyManager::EnemyManager(const EnemyManager& em)
: sprites_manager(em.sprites_manager)
{

}

EnemyManager& EnemyManager::operator= (const EnemyManager& em)
{
    sprites_manager = em.sprites_manager;
    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

Enemy* EnemyManager::createEnemy(EnemyType et, World* w, const Vector2d<float>& pos)
{
    if(w!=nullptr)
    {
        auto it = enemies_map.find(et);
        if(it != enemies_map.end())
        {
            if(it->second!=nullptr)
            {
                return it->second(this, w, pos);
            }
        }
    }
    return nullptr;
}


Enemy* EnemyManager::createMiner(World* w, const Vector2d<float>& pos)
{
    // Gráficos del enemigo minero
    Sprite* enemy_sprite = sprites_manager.createSprite(2);

    // Colisiones del enemigo minero
    CollisionFlag enemy_interests = CollisionFlag::player_hurt;
    
    // Otros atributos del enemigo minero
    int enemy_life = 30;
    Vector2d<float> enemy_max_vel = Vector2d<float>(500.0f,500.0f);
    Vector2d<float> enemy_max_accel = Vector2d<float>(INFINITY, INFINITY);
    Vector2d<float> enemy_friction = Vector2d<float>(20.0f,20.0f);
    Vector2d<float> enemy_init_orientation = Vector2d<float>(0.0f,-1.0f);
    float enemy_stunned_time = 0.5f;

    // Comportamiento del enemigo minero
    BinaryTree* bt = AI::getBehaviour(AI::bt_types::enemy_agressive);

    // Creación final del enemigo minero
    Enemy* enemy = new Enemy(enemy_life, pos, enemy_sprite, w,
    enemy_interests, enemy_init_orientation, enemy_max_vel, enemy_max_accel,
    enemy_friction, nullptr, enemy_stunned_time, bt);
    w->addEntity(enemy);

    return enemy;
}





//=========================================
//=               SETTERS   	    	  =
//=========================================

void EnemyManager::setSprites(const char* tileset)
{
    sprites_manager.setSprites(tileset);
}


//=========================================
//=               GETTERS   	    	  =
//=========================================



//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

EnemyManager::~EnemyManager()
{
    
}