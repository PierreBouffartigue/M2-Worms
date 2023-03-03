#include "Button.h"

Button::Button(const sf::String &name, const sf::Font &font, float width, float height, unsigned int characterSize)
        : m_name(sf::Text(name, font, characterSize)), m_border(sf::RectangleShape(sf::Vector2f(width, height))),
          m_inactiveColor(sf::Color::White), m_hoverColor(sf::Color::Cyan), m_activeColor(sf::Color::White) {
    m_border.setFillColor(sf::Color::Black);
    m_border.setOutlineThickness(-m_borderThickness);
    ToggleActive(m_isActive);
    setPosition(m_border.getPosition().x, m_border.getPosition().y);
}

void Button::render(sf::RenderWindow *window) {
    window->draw(m_border);
    window->draw(m_name);
}

void Button::ToggleActive(bool isActive) {
    m_isActive = isActive;
    auto color = m_isActive ? m_activeColor : m_inactiveColor;
    m_border.setOutlineColor(color);
    m_name.setFillColor(color);
}

sf::Rect<float> Button::getGlobalBounds() const {
    return m_border.getGlobalBounds();
}

void Button::setPosition(float x, float y) {
    m_border.setPosition(x, y);
    auto borderBounds = m_border.getGlobalBounds();
    m_name.setPosition(borderBounds.left + borderBounds.width / 2 - m_name.getGlobalBounds().width / 2,
                       borderBounds.top + borderBounds.height / 2 - m_name.getGlobalBounds().height);
}

sf::Vector2<float> Button::getPosition() const {
    return m_border.getPosition();
}

void Button::onHoverStart(IButton *button) {
    IButton::onHoverStart(button);
    m_border.setOutlineColor(m_hoverColor);
    m_name.setFillColor(m_hoverColor);
}

void Button::onHoverEnd(IButton *button) {
    IButton::onHoverEnd(button);
    ToggleActive(m_isActive);
}

void Button::onClick(IButton *button) {
    IButton::onClick(button);
    ToggleActive(!m_isActive);
}
