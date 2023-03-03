#include <iostream>
#include "Player.h"

Player::Player(const sf::Texture *texture, const sf::Vector2f position, const sf::Vector2f size) : m_texture(texture), m_sprite(sf::Sprite(*texture)), m_velocity(sf::Vector2f(0.f, 0.f)), m_speed(100.f) {
    m_sprite.setPosition(position);

    auto *newBH = new BlackHole(sf::Vector2f(50.f, 50.f), Vector2D(300.0f, 300.0f), 1000.0f);
    m_listOfBH.push_back(newBH);
}

Player::~Player() {
    delete m_texture;
}

void Player::processInput() {
    // Keyboard Event
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_velocity.x = -m_speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_velocity.x = m_speed;
    } else {
        m_velocity.x = 0.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_velocity.y = -m_speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_velocity.y = m_speed;
    } else {
        m_velocity.y = 0.f;
    }
}

void Player::update(float deltaTime) {

}

void Player::update(float deltaTime, const sf::VertexArray &map, sf::RenderWindow* window) {
    playerCollision(deltaTime, map, window);

    for (auto &i: m_listOfProjectile) {
        if (i != nullptr) {
            if(!i->getIsDeleted()){
                i->update(deltaTime);
            } else{
                removeProjectile(i);
            }
        }
    }
}

void Player::render(sf::RenderWindow *window) {
    window->draw(m_sprite);

    for(int i = 0; i < m_listOfProjectile.size(); ++i) {
        if(m_listOfProjectile[i] != nullptr)
            m_listOfProjectile[i]->render(window);
    }

    for (auto &i: m_listOfBH) {
        if (i != nullptr)
            window->draw(i->getShape());
    }
}

sf::Rect<float> Player::getGlobalBounds() {
    return m_sprite.getGlobalBounds();
}

void Player::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::Vector2<float> Player::getPosition() {
    return m_sprite.getPosition();
}

void Player::move(sf::Vector2<float> position) {
    m_sprite.move(position);
}

void Player::playerCollision(const float deltaTime, const sf::VertexArray &map, sf::RenderWindow* window) {
    Vector2D gravity = Vector2D(0.0f, 98.1f);
    sf::FloatRect playerBody = getGlobalBounds();
    m_acc += sf::Vector2f(0.f, gravity._y) * 0.5f * deltaTime * deltaTime;
    sf::Vector2f playerMove = m_acc + m_velocity * deltaTime;

    if (playerBody.left + playerMove.x < 0) {
        playerMove.x = -playerBody.left;
    } else if (playerBody.left + playerBody.width + playerMove.x > static_cast<float>(window->getSize().x)) {
        playerMove.x = static_cast<float>(window->getSize().x) - playerBody.left - playerBody.width;
    }
    if (playerBody.top + playerMove.y < 0) {
        playerMove.y = -playerBody.top;
    } else if (playerBody.top + playerBody.height + playerMove.y > static_cast<float>(window->getSize().y)) {
        playerMove.y = static_cast<float>(window->getSize().y) - playerBody.top - playerBody.height;
    }

    sf::FloatRect playerBodyBounds(
            std::min(playerBody.left, playerBody.left + playerMove.x),
            std::min(playerBody.top, playerBody.top + playerMove.y),
            std::abs(playerMove.x) + playerBody.width,
            std::abs(playerMove.y) + playerBody.height);

    std::uint8_t collision = false;

    for (unsigned int i = 0; i < map.getVertexCount(); i++) {
        sf::Vector2f mapPos = map[i].position;
        sf::FloatRect mapBounds(mapPos.x, mapPos.y, 1.f, 1.f);
        if (playerBodyBounds.intersects(mapBounds)) {
            sf::FloatRect intersection;
            if (playerBodyBounds.intersects(mapBounds, intersection)) {
                if (std::abs(intersection.width) < std::abs(intersection.height)) {
                    playerMove.x = intersection.left - playerBody.left;
                } else {
                    playerMove.y = intersection.top - playerBody.top;
                }
            }
            collision = true;
        }
    }

    if (!collision) {
        move(playerMove);
    } else {
        m_acc.y = 0;
        if (playerMove.x != 0.f) {
            m_velocity.x = 0.f;
        } else if (playerMove.y != 0.f) {
            m_velocity.y = 0.f;
        }
    }
}

void Player::takeDamage(const float damage) {
    m_health -= damage;
    if (m_health <= 0) {
        //TODO : Joueur mort
    }
}

void Player::heal(const float heal) {
    m_health += heal;
}

const std::vector<Projectile *> &Player::getListOfProjectile() const {
    return m_listOfProjectile;
}

void Player::addProjectileInList(Projectile* projectile) {
    m_listOfProjectile.push_back(projectile);
}

void Player::removeProjectile(Projectile *projectile) {
    m_listOfProjectile.erase(std::remove_if(m_listOfProjectile.begin(), m_listOfProjectile.end(),
                                            [projectile](Projectile *p) { return p == projectile; }),
                             m_listOfProjectile.end());
}

void Player::createProjectile(Vector2D spe, const Vector2D acc) {
    // Dans "ProjectionData", 1er vector = position, 2ème vector = vitesse initiale (vecteur directeur * force), 3ème vector = acceleration (ensemble des forces constantes)
    auto *newProjectile = new Projectile(
    ProjectionData(Vector2D(getPosition().x, getPosition().y), spe, acc, m_listOfBH), sf::Vector2(10.f, 10.f), 2.0f);
    m_listOfProjectile.push_back(newProjectile);
}
