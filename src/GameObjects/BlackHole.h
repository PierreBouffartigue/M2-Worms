#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "../Utils/Math.h"

class BlackHole {
public:
    BlackHole(const sf::Vector2f &size, Vector2D pos, float baseGForce = 1.0f);

    Vector2D getPos();

    float getGravitationalForce() const;

    sf::RectangleShape getShape();

private:
    Vector2D m_pos;
    float m_gravitationalForce;
    sf::RectangleShape m_shape;
};
