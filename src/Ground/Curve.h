#pragma once

#include <SFML/Graphics/VertexArray.hpp>

class Curve {
public:
    Curve(const int numCurves, const float &curveHeights);

    ~Curve() = default;

    sf::VertexArray generate(const int width, const int height) const;

    int getNumCurves() const;

    float getCurveHeights() const;

private:
    int m_numCurves;
    float m_curveHeights;
};
