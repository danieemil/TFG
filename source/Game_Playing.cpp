#include "Game_Playing.h"
#include "Game.h"

using namespace unvisual::input;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Game_Playing::Game_Playing()
: Game_State(), world(nullptr), update_time(), level_factory(), level(1),
hud(nullptr, "romfs:/gfx/hud.t3x")
{
    type = state_type::playing;

    //unvisual::debugger->print("He creado el estado Jugando");
    //unvisual::debugger->nextLine();
}

Game_Playing::Game_Playing(const Game_Playing& gp)
: Game_State(gp), world(gp.world), update_time(gp.update_time), level_factory(gp.level_factory), level(gp.level)
{

}

Game_Playing& Game_Playing::operator= (const Game_Playing& gp)
{

    Game_State::operator=(gp);

    world = gp.world;
    update_time = gp.update_time;
    level_factory = gp.level_factory;
    level = gp.level;

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Game_Playing::init()
{
    unvisual::getCurrentScreen()->setBackgroundColor(255,255,255,255);
    if(world==nullptr)
    {
        world = new World();
        level_factory.setWorld(world);
        level_factory.init(level);
        if(world!=nullptr)
        {
            hud.setPlayer(world->getPlayer());
        }
    }
}

void Game_Playing::processInput()
{
    // Botón para resetear el nivel
    if(isPressed(N3DS_buttons::Key_L))
    {
        resetLevel();
    }

    if(world!=nullptr)
    {
        world->processInput();
    }
}

void Game_Playing::update()
{
    if(update_time.getElapsed()>upd)
    {
        update_time.reset();
        if(world!=nullptr)
        {
            world->updateEntities();
            world->updateEntitiesCollisions();
        }
    }
    if(world!=nullptr)
    {
        world->updatePlayer();
        if(Game::Instance()->getPlayer()==nullptr) return;
        world->updatePlayerCollisions();
    }

    updateCollisions();
}

void Game_Playing::updateCollisions()
{
    float dt = Game::Instance()->getDeltaTime();
    physics::step(dt);
}

void Game_Playing::interpolate()
{
    float rp = clamp(0.0f,1.0f,update_time.getElapsed()/upd);
    if(world!=nullptr)
    {
        world->interpolate(rp);
    }
}

void Game_Playing::render()
{
    interpolate();

    if(world!=nullptr)
    {
        world->render();
    }

    hud.render();
}


void Game_Playing::deInit()
{
    if (Game::Instance()->getPostState() != state_type::paused)
    {
        delete this;
    }
}

void Game_Playing::resetLevel()
{
    level_factory.deInit();
    level_factory.init(level);
    if(world!=nullptr)
    {
        hud.setPlayer(world->getPlayer());
    }
}

void Game_Playing::erasePlayer()
{
    if(world!=nullptr)
    {
        world->erasePlayer();
    }

    hud.setPlayer(nullptr);

}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Game_Playing::setLevel(int l)
{
    level = l;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================
state_type Game_Playing::getStateType() const
{
    return Game_State::getStateType();
}

World* Game_Playing::getWorld() const
{
    return world;
}

float Game_Playing::getUpdateTime() const
{
    float u = update_time.getElapsed();
    if(u>upd)
        return upd;
    return u;
}

const float Game_Playing::getUpd() const
{
    return upd;
}

Player* Game_Playing::getPlayer() const
{
    if(world!=nullptr)
    {
        return world->getPlayer();
    }
    return nullptr;
}

int Game_Playing::getLevel() const
{
    return level;
}



//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Game_Playing::~Game_Playing()
{
    if(world!=nullptr)
    {
        delete world;
    }

    //unvisual::debugger->print("He destruido el estado Jugando");
    //unvisual::debugger->nextLine();
}