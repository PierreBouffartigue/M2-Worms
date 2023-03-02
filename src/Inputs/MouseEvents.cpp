#include "MouseEvents.h"

void MouseEvents::handleOnMouseHover(sf::Vector2f mousePosition, std::vector<IButton *> &buttons) {
    for (auto & button : buttons) {
        button->hover(button->getGlobalBounds().contains(mousePosition));
    }
}

void MouseEvents::handleOnMouseLeftClick(sf::Event &event, std::vector<IButton *> &buttons) {
    if (sf::Event::MouseButtonPressed == event.type && sf::Mouse::Button::Left == event.mouseButton.button) {
        for (auto & button : buttons) {
            if (!button->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                continue;

            button->click();
        }
    }
}

void MouseEvents::setMousePressed(sf::Event &Event) {
    if (sf::Event::MouseButtonPressed == Event.type && sf::Mouse::Button::Left == Event.mouseButton.button) {
        bIsMouseLeftPressed = true;
        return;
    }
    if (sf::Event::MouseButtonReleased == Event.type && sf::Mouse::Button::Left == Event.mouseButton.button) {
        bIsMouseLeftPressed = false;
        return;
    }
}
