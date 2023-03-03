#pragma once

#include <SFML/System/Vector2.hpp>
#include "../Utils/Math.h"
#include "../../GameEngine/GameObjects/IGameObject.h"

struct ProjectionData {
    ProjectionData(const Vector2D pos, const Vector2D spe, const Vector2D acc) :
            m_pos(pos),
            m_spe(spe),
            m_acc(acc)
    {}

    void update(const float time) {
        float tmpsVitx = m_acc._x * time + m_spe._x;
        float tmpsVity = m_acc._y * time + m_spe._y;

        m_pos._x += m_acc._x * time * time * 0.5f + m_spe._x * time;
        m_pos._y += m_acc._y * time * time * 0.5f + m_spe._y * time;
        m_spe._x = tmpsVitx;
        m_spe._y = tmpsVity;
    }

    Vector2D getPosition() { return m_pos; }

    Vector2D getSpeed() { return m_spe; }

    Vector2D getAcc() { return m_acc; }

private:
    Vector2D m_pos;
    Vector2D m_spe;
    Vector2D m_acc;
};

class Projectile : public IGameObject {
public:
    Projectile(ProjectionData data, const sf::Vector2f size, const float lifeTime);

    ~Projectile() override = default;

    void processInput() override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow* window) override;

    sf::RectangleShape getShape();

    void setPosition(float x, float y) override;
    sf::Vector2<float> getPosition() override;

    void projectileCollision(const float deltaTime, sf::VertexArray &map);

private:
    ProjectionData m_projData;
    sf::RectangleShape m_shape;
    float m_lifeTime;
};
