#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../../GameEngine/UI/IButton.h"

class MouseEvents {
protected:
    bool bIsMouseLeftPressed = false;

    virtual ~MouseEvents() = default;

    void handleOnMouseHover(sf::Vector2f mousePosition, std::vector<IButton*>& buttons);
    void handleOnMouseLeftClick(sf::Event& event, std::vector<IButton*>& buttons);

    void setMousePressed(sf::Event& Event);
};
