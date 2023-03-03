#include "BlackHole.h"

BlackHole::BlackHole(const sf::Vector2f &size, const Vector2D pos, const float baseGForce) : m_pos(pos),
                                                                                             m_gravitationalForce(
                                                                                                     baseGForce),
                                                                                             m_shape(size) {
    m_shape.setPosition(sf::Vector2f(pos._x, pos._y));
    m_shape.setFillColor(sf::Color::Black);
}

Vector2D BlackHole::getPos() {
    return m_pos;
}

float BlackHole::getGravitationalForce() const {
    return m_gravitationalForce;
}

sf::RectangleShape BlackHole::getShape() {
    return m_shape;
}
