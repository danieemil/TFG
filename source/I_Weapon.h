#ifndef _I_WEAPON_
#define _I_WEAPON_

#include "Interactable.h"


class I_Weapon : public Interactable
{

public:
    // Constructores
    I_Weapon(int val, const Vector2d<float>& pos = Vector2d<float>(), Sprite* spr = nullptr,
    World* w = nullptr, Shape* sh = nullptr,
    const Vector2d<float>& ori = Vector2d<float>(0.0f, -1.0f));
    I_Weapon(const I_Weapon& iw);

    I_Weapon& operator= (const I_Weapon& iw);

    // Métodos
        //Entity
    void render(const Vector2d<float>& view_pos = Vector2d<float>()) override;
    void update() override;
    void updateFromCollider() override;
    void interpolate(float rp = 0.0f) override;
    void manageAnimations() override;
    void collision(void * ent) override;
        //Interactable
        //I_Weapon

    // Setters
        //Entity
    void setSprite(Sprite* spr) override;
    void setPosition(const Vector2d<float>& pos) override;
    void setWorld(World* w) override;
    void setBody(Collider* c) override;
    void setVelocity(const Vector2d<float>& vel) override;
    void setAngle(float angl) override;
    void setOrientation(const Vector2d<float>& ori) override;
        //Interactable
    void setValue(int val) override;
    const InteractableType& getInteractableType() const override;
        //I_Weapon

    // Getters
        //Entity
    Sprite* getSprite() const override;
    const Vector2d<float>& getPosition() const override;
    World* getWorld() const override;
    Collider* getBody() const override;
    const Vector2d<float>& getVelocity() const override;
    const Vector2d<float>& getPrePosition() const override;
    const Vector2d<float>& getRenderPosition() const override;
    const EntityType& getEntityType() const override;
    float getAngle() const override;
    Vector2d<float> getCenter() const override;
    const Vector2d<float>& getOrientation() const override;
        //Interactable
    int getValue() const override;
        //I_Weapon

    // Destructor
    ~I_Weapon();

protected:


private:

};

#endif