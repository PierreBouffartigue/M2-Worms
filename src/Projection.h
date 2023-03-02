#pragma once

// My Things Start
#include <SFML/Graphics.hpp>
#include <utility>

struct Vector2D {
    Vector2D(const float x, const float y) :
            _x(x),
            _y(y) {}

    Vector2D &operator+(Vector2D val) {
        _x += val._x;
        _y += val._y;

        return *this;
    }

    Vector2D &operator*(float val) {
        _x *= val;
        _y *= val;

        return *this;
    }

    float _x;
    float _y;
};

struct ProjectionData {
    ProjectionData(const Vector2D pos, const Vector2D spe, const Vector2D acc) :
            m_pos(pos),
            m_spe(spe),
            m_acc(acc) {}

    void Update(const float time) {
        float tmpsVitx = m_acc._x * time + m_spe._x;
        float tmpsVity = m_acc._y * time + m_spe._y;

        m_pos._x += m_acc._x * time * time * 0.5f + m_spe._x * time;
        m_pos._y += m_acc._y * time * time * 0.5f + m_spe._y * time;
        m_spe._x = tmpsVitx;
        m_spe._y = tmpsVity;
    }

    Vector2D getPosition() {
        return m_pos;
    }

    Vector2D getSpeed() {
        return m_spe;
    }

    Vector2D getAcc() {
        return m_acc;
    }

private:
    Vector2D m_pos;
    Vector2D m_spe;
    Vector2D m_acc;
};

class Projectile {
public:
    Projectile(ProjectionData data, const sf::Vector2f &size, const float lifeTime = 3.0f) :
            m_projData(data),
            m_shape(size),
            m_lifeTime(lifeTime) {
        m_shape.setPosition(sf::Vector2f(data.getPosition()._x, data.getPosition()._y));
        m_shape.setFillColor(sf::Color::Red);
    }

    ~Projectile() = default;

    sf::RectangleShape getShape() {
        return m_shape;
    }

    void UpdateAndMove(const float deltaTime, sf::VertexArray &map) {
        m_lifeTime -= deltaTime;
        if (m_lifeTime < 0) {
            //delete this;
        }

        m_projData.Update(deltaTime);
        m_shape.setPosition(sf::Vector2(m_projData.getPosition()._x, m_projData.getPosition()._y));
        //projectileCollision(deltaTime, map);
    }

    void projectileCollision(const float deltaTime, sf::VertexArray &map) {
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
                    std::cout << "Destruction" << std::endl;
                    //map[i].color = sf::Color::Transparent;
                    //map[i].position = sf::Vector2f(-10000.f, -10000.f);
                }
            }
        }
    }

private:
    ProjectionData m_projData;
    sf::RectangleShape m_shape;
    float m_lifeTime;
};

// My Things End