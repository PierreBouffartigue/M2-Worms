#pragma once

#include <SFML/System/Vector2.hpp>
#include "../Utils/Math.h"
#include "../../GameEngine/GameObjects/IGameObject.h"
#include "BlackHole.h"

struct ProjectionData {
    ProjectionData(const Vector2D pos, const Vector2D spe, const Vector2D acc, std::vector<BlackHole *> &listOfBH) :
            m_pos(pos),
            m_spe(spe),
            m_acc(acc),
            m_listOfBH(listOfBH) {}

    void update(const float time) {
        float tmpsAccx = m_acc._x;
        float tmpsAccy = m_acc._y;

        for (auto &i: m_listOfBH) {
            Vector2D vectorG(i->getPos()._x - m_pos._x, i->getPos()._y - m_pos._y);
            vectorG.Normalize();

            tmpsAccx += vectorG._x * i->getGravitationalForce();
            tmpsAccy += vectorG._y * i->getGravitationalForce();
        }

        const float tmpsSpeedx = tmpsAccx * time + m_spe._x;
        const float tmpsSpeedy = tmpsAccy * time + m_spe._y;

        m_pos._x += tmpsAccx * time * time * 0.5f + m_spe._x * time;
        m_pos._y += tmpsAccy * time * time * 0.5f + m_spe._y * time;
        m_spe._x = tmpsSpeedx;
        m_spe._y = tmpsSpeedy;
    }

    Vector2D getPosition() { return m_pos; }

    Vector2D getSpeed() { return m_spe; }

    Vector2D getAcc() { return m_acc; }

private:
    Vector2D m_pos;
    Vector2D m_spe;
    Vector2D m_acc;
    std::vector<BlackHole *> &m_listOfBH;
};

class Projectile : public IGameObject {
public:
    Projectile(ProjectionData data, const sf::Vector2f &size, float lifeTime);

    ~Projectile() override = default;

    void processInput() override;

    void update(float deltaTime) override;

    void render(sf::RenderWindow *window) override;

    sf::RectangleShape getShape();

    void setPosition(float x, float y) override;

    sf::Vector2<float> getPosition() override;

    void projectileCollision(sf::VertexArray &map);

    bool getIsDeleted() const;

private:
    ProjectionData m_projData;
    sf::RectangleShape m_shape;
    float m_lifeTime;
    bool m_isDeleted = false;
};
