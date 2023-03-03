#include "Projectile.h"

Projectile::Projectile(ProjectionData data, const sf::Vector2f &size, const float lifeTime = 3.0f) : m_projData(data), m_shape(size), m_lifeTime(lifeTime) {
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
        m_isDeleted= true;
    }

    m_projData.update(deltaTime);
    setPosition(m_projData.getPosition()._x, m_projData.getPosition()._y);
    //projectileCollision(deltaTime, map);
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

void Projectile::projectileCollision(const float deltaTime, sf::VertexArray &map) {
    sf::FloatRect projectileBody = m_shape.getGlobalBounds();
    sf::Vector2f projectileMove = reinterpret_cast<const sf::Vector2<float> &>(m_projData.getSpeed() * deltaTime);

    sf::FloatRect projectileBodyBounds(
            std::min(projectileBody.left, projectileBody.left + projectileMove.x),
            std::min(projectileBody.top, projectileBody.top + projectileMove.y),
            std::abs(projectileMove.x) + projectileBody.width,
            std::abs(projectileMove.y) + projectileBody.height);

    std::uint8_t collision = false;

    for (unsigned int i = 0; i < map.getVertexCount(); i++) {
        sf::Vector2f mapPos = map[i].position;
        sf::FloatRect mapBounds(mapPos.x, mapPos.y, 1.f, 1.f);
        if (projectileBodyBounds.intersects(mapBounds)) {
            sf::FloatRect intersection;
            if (projectileBodyBounds.intersects(mapBounds, intersection)) {
                if (std::abs(intersection.width) < std::abs(intersection.height)) {
                    projectileMove.x = intersection.left - projectileBody.left;
                } else {
                    projectileMove.y = intersection.top - projectileBody.top;
                }
            }
            collision = true;
        }
    }

    if (!collision) {
        m_shape.move(projectileMove);
    } else {
        for (int i = 0; i < map.getVertexCount(); i++) {
            sf::Vertex &vertex = map[i];
            float distance = std::hypotf(m_shape.getPosition().x - vertex.position.x,
                                         m_shape.getPosition().y - vertex.position.y);
            if (distance < 10.f) {
                m_isDeleted= true;
                //map[i].color = sf::Color::Transparent;
                //map[i].position = sf::Vector2f(-10000.f, -10000.f);
            }
        }
    }
}

bool Projectile::getIsDeleted() const {
    return m_isDeleted;
}
