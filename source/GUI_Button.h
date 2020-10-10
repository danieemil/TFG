#ifndef _GUI_BUTTON_
#define _GUI_BUTTON_

#include "GUI_Element.h"
#include "SpriteManager.h"
#include "functional"

using Call = std::function<void()>;


class GUI_Button : public GUI_Element
{

public:
    // Constructores
    GUI_Button(const Vector2d<float>& pos, const Vector2d<float>& s, Sprite* spr = nullptr, Call cb = nullptr);
    GUI_Button(const GUI_Button& gb);

    GUI_Button& operator= (const GUI_Button& gb);

    // Métodos
    void update() override;
    void render() override;

    bool checkPressed(const Vector2d<float>& pos) override;

    void activate();

    // Setters
    void setPosition(const Vector2d<float>& pos) override;
    void setSize(const Vector2d<float>& s) override;
    void setSprite(Sprite* spr);
    void setPressed(bool p);
    void setSelected(bool s);
    void setEnabled(bool e);
    void setCallback(Call cb);

    // Getters
    const Vector2d<float>& getPosition() const override;
    const Vector2d<float>& getSize() const override;
    Sprite* getSprite() const;
    bool getPressed() const;
    bool getSelected() const;
    bool getEnabled() const;
    Call getCallback() const;

    // Destructor
    ~GUI_Button();

private:

    Sprite* sprite;

    bool pressed, selected, enabled, active;

    Call callback;

};

#endif