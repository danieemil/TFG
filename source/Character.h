#ifndef _CHARACTER_
#define _CHARACTER_

#include "Entity.h"


class Character : public Entity
{

public:
    // Constructores
    Character(const Character&);
    Character(const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr, World* w = nullptr);

    Character& operator= (const Character&);

    // Métodos
        //Entity
    virtual void render();
    virtual void update() override;
        //Character

    // Setters
        //Entity
    virtual void setSprite(Sprite* spr);
    virtual void setPosition(const Vector2d<float>& pos);
    virtual void setWorld(World* w);
        //Character

    // Getters
        //Entity
    virtual Sprite* getSprite() const;
    virtual const Vector2d<float>& getPosition() const;
    virtual World* getWorld() const;
        //Character

    // Destructor
    virtual ~Character();

protected:


private:

};

#endif