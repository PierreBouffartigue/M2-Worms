#pragma once

#include "../../GameEngine/UI/IButton.h"

class Button : public IButton {
public:
    explicit Button(const sf::String& name, const sf::Font& font, float width = 50, float height = 50, unsigned int characterSize = 20);
    ~Button() override = default;

    void render(sf::RenderWindow *window) override;

    void ToggleActive(bool isActive);

    sf::Rect<float> getGlobalBounds() const override;
    void setPosition(float x, float y);
    sf::Vector2<float> getPosition() const;

protected:
    sf::Text m_name;
    sf::Color m_inactiveColor;
    sf::Color m_hoverColor;
    sf::Color m_activeColor;
    sf::RectangleShape m_border;

    const float m_borderThickness = 3.f;

    void onHoverStart(IButton *button) override;
    void onHoverEnd(IButton *button) override;
    void onClick(IButton *button) override;
};
