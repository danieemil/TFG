#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER_

#include "functional"
#include <unordered_map>
#include "Enemy.h"
#include "SpriteManager.h"


// Tipos de armas instanciables
enum class EnemyType
{
    miner,
};



class EnemyManager
{

public:
    // Constructores
    EnemyManager(const char* enemy_sprites_path);
    EnemyManager(const EnemyManager& em);

    EnemyManager& operator= (const EnemyManager& em);

    // Métodos
    Enemy* createEnemy(EnemyType et, const Vector2d<float>& pos = Vector2d<float>());

    Enemy* createMiner(const Vector2d<float>& pos = Vector2d<float>());

    // Setters
    void setSprites(const char* tileset);

    // Getters

    // Destructor
    ~EnemyManager();

private:

    SpriteManager sprites_manager;

};

#endif