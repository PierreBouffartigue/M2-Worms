#include "Ground.h"

Ground::Ground() : m_destroyRadius(10.0f) {}

void Ground::regenerate(sf::RenderWindow *window) {
    if (isFlatModEnable) {
        curve_ = Curve(1, 10.f);
    } else {
        curve_ = Curve(Utils::getRandomNumber(1, 4), static_cast<float>(Utils::getRandomNumber(20, 80)));
    }

    m_groundPixels.clear();
    m_groundPixels.setPrimitiveType(sf::Points);
    const sf::Vector2u windowSize = window->getSize();

    std::vector<sf::Vector2f> curveVertices;
    for (int x = 0; x < windowSize.x; x++) {
        float y = 0;
        for (int i = 0; i < curve_.getNumCurves(); i++) {
            float frequency = static_cast<float>(i + 1) * 0.5f;
            y += static_cast<float>(curve_.getCurveHeights() *
                                    sin(2 * 3.14159265358979323846 * frequency * x / windowSize.x));
        }
        curveVertices.emplace_back(static_cast<float>(x), static_cast<float>(windowSize.y) / 2 + y);
    }

    std::uint8_t foundCurveStart = false;
    for (auto &curveVertex: curveVertices) {
        if (!foundCurveStart && curveVertex.y > static_cast<float>(windowSize.y) / 2) {
            foundCurveStart = true;
        }
        if (foundCurveStart) {
            for (int y = static_cast<int>(curveVertex.y); y < windowSize.y; y++) {
                m_groundPixels.append(
                        sf::Vertex(sf::Vector2f(curveVertex.x, static_cast<float>(y)), sf::Color::Green));
            }
        }
    }
}

void Ground::processInput(sf::RenderWindow *window) {

}

void Ground::update(sf::RenderWindow *window) {
    m_curve = curve_.generate(static_cast<int>(window->getSize().x), static_cast<int>(window->getSize().y));
}

void Ground::render(sf::RenderWindow *window) {
    window->draw(m_curve);
    window->draw(m_groundPixels);
}

sf::VertexArray Ground::getGroundPixels() {
    return m_groundPixels;
}

float Ground::getDestroyRadius() const {
    return m_destroyRadius;
}

void Ground::destroyGroundPixel(sf::Vertex pixel) {
    pixel.color = sf::Color::Transparent;
    pixel.position = sf::Vector2f(-10000.f, -10000.f);
}

void Ground::changeFlatMode() {
    isFlatModEnable = !isFlatModEnable;
    std::cout << "Flat mod : " + std::to_string(isFlatModEnable) << std::endl;
}
