#include <iostream>
#include "Player.h"

Player::Player(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color) : m_body(size), m_velocity(sf::Vector2f(0.f, 0.f)), m_speed(100.f) {
    m_body.setPosition(position);
    m_body.setFillColor(color);
}

void Player::handleEvents(const float deltaTime, const sf::VertexArray &map, sf::RenderWindow &m_window) {
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Dans "ProjectionData", 1er vector = position, 2ème vector = vitesse initiale (vecteur directeur * force), 3ème vector = acceleration (ensemble des forces constantes)
        const sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        Vector2D vectorDir = Vector2D(mousePos.x - m_body.getPosition().x, mousePos.y - m_body.getPosition().y);
        Projectile* NewProjectile = new Projectile(ProjectionData(Vector2D(m_body.getPosition().x, m_body.getPosition().y), vectorDir * 2.500f, Vector2D(0.f, 98.1f)), sf::Vector2(10.f, 10.f));
        m_listOfProjectile.push_back(NewProjectile);

        std::cout << "Fire ! --> " << mousePos.x << " : " << mousePos.y << std::endl;
    }

    sf::FloatRect playerBody = m_body.getGlobalBounds();
    sf::Vector2f playerMove = m_velocity * deltaTime;

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
        m_body.move(playerMove);
    } else {
        if (playerMove.x != 0.f) {
            m_velocity.x = 0.f;
        } else if (playerMove.y != 0.f) {
            m_velocity.y = 0.f;
        }
    }

    for (int i = 0; i < m_listOfProjectile.size(); ++i)
    {
        if (m_listOfProjectile[i] != nullptr)
            m_listOfProjectile[i]->UpdateAndMove(deltaTime);
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(m_body);

    for(int i = 0; i < m_listOfProjectile.size(); ++i)
    {
        if(m_listOfProjectile[i] != nullptr)
            window.draw(m_listOfProjectile[i]->getShape());
    }
}

sf::RectangleShape Player::getPlayerBody() {
    return m_body;
}
