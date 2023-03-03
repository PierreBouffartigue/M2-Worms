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

void MouseEvents::handleOnMouseLeftClick(sf::Event &event, sf::Vector2f mousePosition, Player &player) {
    if (sf::Event::MouseButtonPressed == event.type && sf::Mouse::Button::Left == event.mouseButton.button) {
        Vector2D vectorDir = Vector2D(mousePosition.x - player.getPosition().x, mousePosition.y - player.getPosition().y);
        const float force = 2.0f;

        Vector2D gravity = Vector2D(0.0f, 981.0f);
        Vector2D wind = Vector2D(-100.0f, 0);
        Vector2D accVector = gravity + wind;

        // Dans "ProjectionData", 1er vector = position, 2ème vector = vitesse initiale (vecteur directeur * force), 3ème vector = acceleration (ensemble des forces constantes)
        auto *NewProjectile = new Projectile(
                ProjectionData(Vector2D(player.getPosition().x, player.getPosition().y), vectorDir * force,
                               accVector), sf::Vector2(10.f, 10.f), 0.5f);
        player.addProjectileInList(NewProjectile);
    }
}

void MouseEvents::handleOnMouseLeftClick(sf::Event &event, sf::Vector2f mousePosition, Ground &ground) {
    if (sf::Event::MouseButtonPressed == event.type && sf::Mouse::Button::Left == event.mouseButton.button) {
        for (int i = 0; i < ground.getGroundPixels().getVertexCount(); i++) {
            const sf::Vertex &vertex = ground.getGroundPixels()[i];
            const float distance = std::hypotf(static_cast<float>(mousePosition.x) - vertex.position.x,
                                               static_cast<float>(mousePosition.y) - vertex.position.y);
            if (distance < ground.getDestroyRadius()) {
                ground.destroyGroundPixel(vertex);
            }
        }
    }
}
