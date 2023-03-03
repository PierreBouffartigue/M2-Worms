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

    Vector2D getNormalized()
    {
        const float norm = sqrt(_x * _x + _y * _y);
        const float x = _x / norm;
        const float y = _y / norm;

        return Vector2D(x, y);
    }

    void Normalize()
    {
        const float norm = sqrt(_x * _x + _y * _y);
        _x /= norm;
        _y /= norm;
    }

    float _x;
    float _y;
};

struct BlackHole
{
public:
    BlackHole(const sf::Vector2f& size, const Vector2D pos, const float baseGForce = 1.0f) :
        m_pos(pos),
        m_gravitationalForce(baseGForce),
        m_shape(size)
    {
        m_shape.setPosition(sf::Vector2f(pos._x, pos._y));
        m_shape.setFillColor(sf::Color::Black);
    }

    const Vector2D getPos()
    {
        return m_pos;
    }

    const float getGravitationalForce()
    {
        return m_gravitationalForce;
    }

    sf::RectangleShape getShape() {
        return m_shape;
    }

private:
    Vector2D m_pos;
    float m_gravitationalForce;
    sf::RectangleShape m_shape;
};

struct ProjectionData {
    ProjectionData(const Vector2D pos, const Vector2D spe, const Vector2D acc, std::vector<BlackHole*>& listOfBH) :
            m_pos(pos),
            m_spe(spe),
            m_acc(acc),
            m_listOfBH(listOfBH)
    {}

    void Update(const float time) {
        float tmpsAccx = m_acc._x;
        float tmpsAccy = m_acc._y;

        for (int i = 0; i < m_listOfBH.size(); ++i)
        {
            Vector2D vectorG(m_listOfBH.at(i)->getPos()._x - m_pos._x, m_listOfBH.at(i)->getPos()._y - m_pos._y);
            vectorG.Normalize();

            tmpsAccx += vectorG._x * m_listOfBH.at(i)->getGravitationalForce();
            tmpsAccy += vectorG._y * m_listOfBH.at(i)->getGravitationalForce();
        }

        const float tmpsSpeedx = tmpsAccx * time + m_spe._x;
        const float tmpsSpeedy = tmpsAccy * time + m_spe._y;

        m_pos._x += tmpsAccx * time * time * 0.5f + m_spe._x * time;
        m_pos._y += tmpsAccy * time * time * 0.5f + m_spe._y * time;
        m_spe._x = tmpsSpeedx;
        m_spe._y = tmpsSpeedy;
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
    std::vector<BlackHole*>& m_listOfBH;
};

class Projectile {
public:
    Projectile(ProjectionData data, const sf::Vector2f &size, const float lifeTime = 3.0f) :
            m_projData(data),
            m_shape(size),
            m_lifeTime(lifeTime)
    {
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
            m_isDeleted= true;
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
                    m_isDeleted= true;
                    //map[i].color = sf::Color::Transparent;
                    //map[i].position = sf::Vector2f(-10000.f, -10000.f);
                }
            }
        }
    }

    bool getIsDeleted() const{
        return m_isDeleted;
    }

private:
    ProjectionData m_projData;
    sf::RectangleShape m_shape;
    float m_lifeTime;
    bool m_isDeleted = false;
};

// My Things End