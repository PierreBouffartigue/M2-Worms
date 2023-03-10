#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../../GameEngine/UI/IButton.h"
#include "../GameObjects/Player.h"
#include "../Ground/Ground.h"

class MouseEvents {
protected:
    bool bIsMouseLeftPressed = false;

    virtual ~MouseEvents() = default;

    // Button Event
    void handleOnMouseHover(sf::Vector2f mousePosition, std::vector<IButton*>& buttons);
    void handleOnMouseLeftClick(sf::Event& event, std::vector<IButton*>& buttons);

    // Button Player
    void handleOnMouseRightClick(sf::Event& event, sf::Vector2f mousePosition, Player& player);

    // Button Ground
    void handleOnMouseLeftClick(sf::Vector2f mousePosition, sf::VertexArray& groundPixels);

    void setMousePressed(sf::Event& Event);
};
