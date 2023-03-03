#pragma once

#include "Projectile.h"
#include "../Utils/Math.h"
#include "../../GameEngine/GameObjects/IGameObject.h"

class Player : public IGameObject {
public:
    Player(const sf::Texture *texture, sf::Vector2f position);

    ~Player() override;

    void processInput() override;

    void update(float deltaTime) override;

    void update(float deltaTime, const sf::VertexArray &map, sf::RenderWindow *window);

    void render(sf::RenderWindow *window) override;

    sf::Rect<float> getGlobalBounds();

    void setPosition(float x, float y) override;

    sf::Vector2<float> getPosition() override;

    void move(sf::Vector2<float> position);

    void playerCollision(float deltaTime, const sf::VertexArray &map, sf::RenderWindow *window);

    void takeDamage(float damage);

    void heal(float heal);

    const std::vector<Projectile *> &getListOfProjectile() const;

    void addProjectileInList(Projectile *projectile);

    void removeProjectile(Projectile *projectile);

    void createProjectile(Vector2D spe, Vector2D acc);

private:
    sf::Vector2f m_velocity;
    sf::Vector2f m_acc;
    const float m_speed = 100.f;
    const sf::Texture *m_texture;
    sf::Sprite m_sprite;

    float m_health = 100.f;

    std::vector<Projectile *> m_listOfProjectile;
    std::vector<BlackHole *> m_listOfBH;
};
