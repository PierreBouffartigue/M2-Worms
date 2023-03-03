#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "../Utils/Utils.h"
#include "Curve.h"

class Ground {
public:
    Ground();

    ~Ground() = default;

    void regenerate(sf::RenderWindow *window);

    void processInput(sf::RenderWindow *window);

    void update(sf::RenderWindow *window);

    void render(sf::RenderWindow *window);


    sf::VertexArray& getGroundPixels();

    float getDestroyRadius() const;

    void destroyGroundPixel(sf::Vertex pixel);

    void changeFlatMode();

private:
    std::uint8_t isFlatModEnable = false;
    float m_destroyRadius;
    sf::VertexArray m_curve;
    sf::VertexArray m_groundPixels;
    Curve curve_{Utils::getRandomNumber(1, 4), static_cast<float>(Utils::getRandomNumber(20, 80))};
};
