#pragma once

#include <SFML/Graphics.hpp>

class IGameObject {
public:
    explicit IGameObject() = default;
    virtual ~IGameObject() = default;

    virtual void processInput() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow* window) = 0;

    virtual void setPosition(float x, float y) = 0;
    virtual sf::Vector2<float> getPosition() = 0;
};
