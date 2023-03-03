#include "Projectile.h"

Projectile::Projectile(ProjectionData data, const sf::Vector2f &size, const float lifeTime = 3.0f) : m_projData(data),
                                                                                                     m_shape(size),
                                                                                                     m_lifeTime(
                                                                                                             lifeTime) {
    m_shape.setPosition(sf::Vector2f(data.getPosition()._x, data.getPosition()._y));
    m_shape.setFillColor(sf::Color::Red);
}

sf::RectangleShape Projectile::getShape() {
    return m_shape;
}

void Projectile::processInput() {

}

void Projectile::update(float deltaTime) {
    m_lifeTime -= deltaTime;
    if (m_lifeTime < 0) {
        m_isDeleted = true;
    }

    m_projData.update(deltaTime);
    setPosition(m_projData.getPosition()._x, m_projData.getPosition()._y);
}

void Projectile::render(sf::RenderWindow *window) {
    window->draw(m_shape);
}

void Projectile::setPosition(float x, float y) {
    m_shape.setPosition(x, y);
}

sf::Vector2<float> Projectile::getPosition() {
    return m_shape.getPosition();
}

void Projectile::projectileCollision(sf::VertexArray &map) {
    sf::FloatRect projectileBounds = m_shape.getGlobalBounds();
    for (int i = 0; i < map.getVertexCount(); i++) {
        sf::Vector2f pixelPosition = map[i].position;
        if (projectileBounds.contains(pixelPosition)) {
            map[i].color = sf::Color::Transparent;
        }
    }
}

bool Projectile::getIsDeleted() const {
    return m_isDeleted;
}
