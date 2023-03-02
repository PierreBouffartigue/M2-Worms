#include "Projectile.h"

Projectile::Projectile(ProjectionData data, const sf::Vector2f size) : m_projData(data), m_shape(size) {
    m_shape.setPosition(sf::Vector2f(data.getPosition()._x, data.getPosition()._y));
    m_shape.setFillColor(sf::Color::Red);
}

sf::RectangleShape Projectile::getShape() {
    return m_shape;
}

void Projectile::UpdateAndMove(const float deltaTime) {
    m_projData.Update(deltaTime);
    m_shape.setPosition(sf::Vector2(m_projData.getPosition()._x, m_projData.getPosition()._y));
}
