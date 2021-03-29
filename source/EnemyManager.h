#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER_

#include "functional"
#include <unordered_map>
#include "Miner.h"
#include "SpriteManager.h"



class EnemyManager
{

public:
    // Constructores
    EnemyManager(const char* enemy_sprites_path);
    EnemyManager(const EnemyManager& em);

    EnemyManager& operator= (const EnemyManager& em);

    // Métodos
    Enemy* createEnemy(EnemyType et, const Vector2d<float>& pos = Vector2d<float>());

    Miner* createMiner(const Vector2d<float>& pos = Vector2d<float>());

    // Setters
    void setSprites(const char* tileset);

    // Getters

    // Destructor
    ~EnemyManager();

private:

    SpriteManager sprites_manager;

};

#endif