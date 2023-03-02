#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "../Utils/Math.h"

class Player {
public:
    Player(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color);

    ~Player() = default;

    void handleEvents(const float deltaTime, const sf::VertexArray &map, sf::RenderWindow& m_window);

    void draw(sf::RenderWindow &window);

    sf::RectangleShape getPlayerBody();

private:
    sf::RectangleShape m_body;
    sf::Vector2f m_velocity;
    const float m_speed = 100.f;

    std::vector<Projectile*> m_listOfProjectile;
};
