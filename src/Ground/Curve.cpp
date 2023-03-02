#include "Curve.h"

Curve::Curve(const int numCurves, const float &curveHeights): m_numCurves(numCurves), m_curveHeights(curveHeights) {}

sf::VertexArray Curve::generate(const int width, const int height) const {
    sf::VertexArray curve(sf::LineStrip, width);

    //float factor = static_cast<float>(2 * M_PI) / static_cast<float>(width);
    float factor = static_cast<float>(2 * 3.14159265358979323846) / static_cast<float>(width);

    float heightFactor = static_cast<float>(height) / 2;

    for (int x = 0; x < width; x++) {
        float y = 0;
        for (int i = 0; i < m_numCurves; i++) {
            float frequency = static_cast<float>(i + 1) * 0.5f;
            y += static_cast<float>(m_curveHeights * sin(frequency * factor * static_cast<double>(x)));
        }
        curve[x] = sf::Vector2f(static_cast<float>(x), heightFactor + y);
        curve[x].color = sf::Color::Transparent;
    }

    return curve;
}

int Curve::getNumCurves() const {
    return m_numCurves;
}

float Curve::getCurveHeights() const {
    return m_curveHeights;
}
