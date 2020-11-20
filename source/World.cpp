#include "World.h"
#include "Game.h"

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

World::World(Player* p)
: player(p), tilemap(nullptr), scroll_vel(4.0f, 4.0f)
{

}

World::World(const World& w)
: player(w.player), tilemap(w.tilemap), scroll_vel(w.scroll_vel)
{

}

World& World::operator= (const World& w)
{

    player = nullptr;
    tilemap = nullptr;
    scroll_vel = w.scroll_vel;

    return *this;

}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void World::addEntity(Entity* e)
{
    if(e!=nullptr)
    {
        for(auto entity = entities.begin();entity!=entities.end();entity++)
        {
            Entity* ent = (*entity);
            if(e == ent)
            {
                return;
            }
        }

        entities.emplace_back(e);
        e->setWorld(this);
    }
}

void World::deleteEntity(Entity* e)
{
    if(e!=nullptr)
    {
        for(auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if((*entity)==e)
            {
                entities.erase(entity);
                delete e;
                break;
            }
        }
    }
}

void World::eraseEntity(Entity* e)
{
    if(e!=nullptr)
    {
        for(auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if((*entity)==e)
            {
                entities.erase(entity);
                break;
            }
            if(entity==entities.end())
            {
                break;
            }
        }
    }
}

void World::deletePlayer()
{
    if(player!=nullptr)
    {
        delete player;
        player = nullptr;
    }
}

void World::erasePlayer()
{
    player = nullptr;
}

void World::deleteLevel()
{
    if(tilemap!=nullptr)
    {
        delete tilemap;
        tilemap = nullptr;
    }

    auto entity = entities.begin();

    while (entity!=entities.end())
    {
        Entity* e = (*entity);

        if(e!=nullptr)
        {
            delete e;
        }
    }

    entities.clear();
}

void World::deleteWorld()
{
    deleteLevel();
    deletePlayer();
}

void World::processInput()
{
    if(player!=nullptr)
    {
        player->processInput();
    }
}

//Scroll 2D : Centramos al jugador en medio de la pantalla
Vector2d<float> World::scroll2D()
{
    Vector2d<float> view_pos;
    const Vector2d<float>* target = nullptr;

    Screen* sc = unvisual::getCurrentScreen();
    if(sc!=nullptr)
    {
        target = sc->getTargetPosition();

        if(target!=nullptr)
        {
            Vector2d<float> position = *target;
            Vector2d<float> sc_size = Vector2d<float>(sc->getWidth(), sc->getHeight());
            Vector2d<float> half_sc = sc_size/2.0f;
            Vector2d<float> sc_pos = position - half_sc;
            if(tilemap!=nullptr)
            {
                Vector2d<float> Tpos = tilemap->getPosition();
                Vector2d<int> auxInt = tilemap->getMapSize();
                Vector2d<float> Tsize = Vector2d<float>(float(auxInt.x),float(auxInt.y));
                Vector2d<float> TPSCM = Tpos + Tsize - sc_size;

                sc_pos.x = clamp(Tpos.x, TPSCM.x, sc_pos.x);
                sc_pos.y = clamp(Tpos.y, TPSCM.y, sc_pos.y);
            }

            // Establecer un máximo de velocidad a la que se puede hacer scroll
            Vector2d<float> pre_pos = sc->getPosition();
            Vector2d<float> dist = sc_pos - pre_pos;
            Vector2d<float> aux;
            aux.x = sign(dist.x) * scroll_vel.x;
            aux.y = sign(dist.y) * scroll_vel.y;
            Vector2d<float> sc_aux = pre_pos + aux;
            
            if(scroll_vel.x>abs(dist.x))
                sc_aux.x = sc_pos.x;
            if(scroll_vel.y>abs(dist.y))
                sc_aux.y = sc_pos.y;

            // Evitamos los errores de renderizado cuando es próximo a [X.5]
            float mx = (sc_aux.x - (int)sc_aux.x) - 0.5f;
            if (abs(mx)<0.05f)
            {
                sc_aux.x = sc_aux.x + 0.1f;
            }
            float my = (sc_aux.y - (int)sc_aux.y) - 0.5f;
            if (abs(my)<0.05f)
            {
                sc_aux.y = sc_aux.y + 0.1f;
            }

            sc_pos = Vector2d<float>(sc_aux.x, sc_aux.y);
            sc->setPosition(sc_pos);
            view_pos = sc_pos;
        }
        
    }
    return view_pos;
}

void World::render()
{
    Vector2d<float> view_pos;
    view_pos = scroll2D();
    renderTilemap(view_pos);
    renderEntities(view_pos);
    renderPlayer(view_pos);
    //physics::render(view_pos);
}

void World::renderTilemap(const Vector2d<float>& view_pos)
{
    tilemap->render(view_pos);
}

void World::renderEntities(const Vector2d<float>& view_pos)
{
    for(auto ent = entities.begin();ent!=entities.end();ent++)
    {
        (*ent)->render(view_pos);
    }
}

void World::renderPlayer(const Vector2d<float>& view_pos)
{
    if(player!=nullptr)
    {
        player->render(view_pos);
    }
}

void World::interpolate(float rp)
{
    interpolateEntities(rp);
    interpolatePlayer(rp);
}

void World::interpolateEntities(float rp)
{
    for(auto ent = entities.begin();ent!=entities.end();ent++)
    {
        (*ent)->interpolate(rp);
    }
}

void World::interpolatePlayer(float rp)
{
    if(player!=nullptr)
    {
        player->interpolate(rp);
    }
}

void World::update()
{
    updateEntities();
    updatePlayer();
}

void World::updateEntities()
{
    auto ent = entities.begin();

    while(ent!=entities.end())
    {
        Entity* updating = (*ent);
        
        if(updating!=nullptr)
        {
            updating->update();
        }

        Entity* updated = (*ent);

        if((ent!=entities.end())&&(updating==updated))
        {
            ent++;
        }
    }
}

void World::updatePlayer()
{
    if(player!=nullptr)
    {
        player->update();
    }
}

// Actualiza la posición de todas las entidades a la corregida por las físicas
void World::updateCollisions()
{
    updatePlayerCollisions();
    updateEntitiesCollisions();
}

void World::updateEntitiesCollisions()
{
    for (auto it = entities.begin(); it!=entities.end(); it++)
    {
        Entity* e = (*it);
        if(e!=nullptr)
        {
            e->updateFromCollider();
        }
    }
}

void World::updatePlayerCollisions()
{
    if(player!=nullptr)
    {
        player->updateFromCollider();
    }
}

void World::manageAnimations()
{
    managePlayerAnimations();
    manageEntitiesAnimations();
}

void World::manageEntitiesAnimations()
{
    for (auto &&ent : entities)
    {
        if(ent!=nullptr)
        {
            ent->manageAnimations();
        }   
    }
}

void World::managePlayerAnimations()
{
    if(player!=nullptr)
    {
        player->manageAnimations();
    }
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void World::setTilemap(Tilemap* t)
{
    if(tilemap!=nullptr && t!=tilemap)
    {
        delete tilemap;
    }

    tilemap = t;
}

void World::setEntities(const std::vector<Entity*>& v)
{
    entities = v;
    for (auto &&entity : entities)
    {
        if(entity!=nullptr)
        {
            entity->setWorld(this);
        }
    }
    
}

void World::setPlayer(Player* p)
{
    if(player!=nullptr && p!=player)
    {
        delete player;
    }
    player = p;
    if(player!=nullptr)
    {
        player->setWorld(this);
    }
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Tilemap* World::getTilemap() const
{
    return tilemap;
}

const std::vector<Entity*>& World::getEntities() const
{
    return entities;
}

Player* World::getPlayer() const
{
    return player;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

World::~World()
{
    deleteWorld();
}