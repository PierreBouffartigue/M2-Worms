#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

class IButton {
public:
    using EventType = std::function<void(IButton*)>;

    explicit IButton();
    virtual ~IButton() = default;

    void hover(bool isHovered);
    void click();

    virtual void render(sf::RenderWindow* window) = 0;

    void setOnHover(const EventType &onHoverStart, const IButton::EventType &onHoverEnd);
    void setOnClick(const EventType &onClick);

    virtual sf::Rect<float> getGlobalBounds() const = 0;

protected:
    EventType m_onHoverStart;
    EventType m_onHoverEnd;
    EventType m_onClick;

    bool m_isHovered = false;
    bool m_isActive = true;

    virtual void onHoverStart(IButton* button);
    virtual void onHoverEnd(IButton* button);
    virtual void onClick(IButton* button);
};
