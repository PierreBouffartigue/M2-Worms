#pragma once

#include "Projectile.h"
#include "../Utils/Math.h"
#include "../../GameEngine/GameObjects/IGameObject.h"

class Player : public IGameObject {
public:
    Player(const sf::Texture *texture, const sf::Vector2f position, const sf::Vector2f size);

    ~Player() override;

    void processInput() override;
    void update(float deltaTime) override;
    void update(float deltaTime, const sf::VertexArray &map, sf::RenderWindow* window);
    void render(sf::RenderWindow* window) override;

    sf::Rect<float> getGlobalBounds();

    void setPosition(float x, float y) override;
    sf::Vector2<float> getPosition() override;

    void move(sf::Vector2<float> position);

    void playerCollision(const float deltaTime, const sf::VertexArray &map, sf::RenderWindow* window);

    void takeDamage(const float damage);

    void heal(const float heal);

    const std::vector<Projectile *> &getListOfProjectile() const;
    void addProjectileInList(Projectile* projectile);

    void removeProjectile(Projectile *projectile);

private:
    sf::Vector2f m_velocity;
    const float m_speed = 100.f;
    const sf::Texture* m_texture;
    sf::Sprite m_sprite;

    float m_health = 100.f;

    std::vector<Projectile*> m_listOfProjectile;
};
