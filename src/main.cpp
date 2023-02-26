#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>

class Utils {
public:
    static int GetRandomNumber(const int minNumber, const int maxNumber) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minNumber, maxNumber);

        return dis(gen);
    }
};

class Curve {
public:
    Curve(const int numCurves, const float &curveHeights)
            : m_numCurves(numCurves), m_curveHeights(curveHeights) {}

    sf::VertexArray generate(const int width, const int height) const {
        sf::VertexArray curve(sf::LineStrip, width);

        for (int x = 0; x < width; x++) {
            float y = 0;
            for (int i = 0; i < m_numCurves; i++) {
                float frequency = static_cast<float>(i + 1) * 0.5f;
                y += static_cast<float>(m_curveHeights * sin(2 * M_PI * frequency * x / static_cast<float>(width)));
            }
            curve[x].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(height) / 2 + y);
            curve[x].color = sf::Color::Transparent;
        }

        return curve;
    }

    int getNumCurves() const {
        return m_numCurves;
    }

    float getCurveHeights() const {
        return m_curveHeights;
    }

private:
    int m_numCurves;
    float m_curveHeights;
};

class Window {
public:
    Window(const int width, const int height, const std::string &title)
            : m_width(width), m_height(height),
              m_destroyRadius(10.0f) {
        m_window.create(sf::VideoMode(m_width, m_height), title);
        regenerate();
    }

    void run() {
        while (m_window.isOpen()) {
            handleEvents();
            update();
            render();
            display();
        }
    }

private:
    int m_width;
    int m_height;
    sf::RenderWindow m_window;
    sf::VertexArray m_curve;
    sf::VertexArray m_greenPixels;
    float m_destroyRadius;
    bool isFlatModEnable = false;

    Curve curve_{Utils::GetRandomNumber(1, 4), static_cast<float>(Utils::GetRandomNumber(20, 80))};

    void handleEvents() {
        sf::Event event{};
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                const sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                for (int i = 0; i < m_greenPixels.getVertexCount(); i++) {
                    const sf::Vertex &vertex = m_greenPixels[i];
                    const float distance = std::hypotf(static_cast<float>(mousePos.x) - vertex.position.x,
                                                       static_cast<float>(mousePos.y) - vertex.position.y);
                    if (distance < m_destroyRadius) {
                        m_greenPixels[i].color = sf::Color::Transparent;
                    }
                }
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                regenerate();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
                isFlatModEnable = !isFlatModEnable;
                std::cout << "Flat mod : " + std::to_string(isFlatModEnable) << std::endl;
            }
        }
    }

    void update() {
        m_curve = curve_.generate(m_width, m_height);
    }

    void render() {
        m_window.clear(sf::Color::Cyan);
        m_window.draw(m_greenPixels);
        m_window.draw(m_curve);
    }

    void display() {
        m_window.display();
    }

    void regenerate() {
        if (isFlatModEnable) {
            curve_ = Curve(1, 10.f);
        } else {
            curve_ = Curve(Utils::GetRandomNumber(1, 4), static_cast<float>(Utils::GetRandomNumber(20, 80)));
        }

        m_greenPixels.clear();
        m_greenPixels.setPrimitiveType(sf::Points);

        std::vector<sf::Vector2f> curveVertices;
        for (int x = 0; x < m_width; x++) {
            float y = 0;
            for (int i = 0; i < curve_.getNumCurves(); i++) {
                float frequency = static_cast<float>(i + 1) * 0.5f;
                y += static_cast<float>(curve_.getCurveHeights() *
                                        sin(2 * M_PI * frequency * x / static_cast<float>(m_width)));
            }
            curveVertices.emplace_back(static_cast<float>(x), static_cast<float>(m_height) / 2 + y);
        }

        bool foundCurveStart = false;
        for (auto &curveVertice: curveVertices) {
            if (!foundCurveStart && curveVertice.y > static_cast<float>(m_height) / 2) {
                foundCurveStart = true;
            }
            if (foundCurveStart) {
                for (int y = static_cast<int>(curveVertice.y); y < m_height; y++) {
                    m_greenPixels.append(
                            sf::Vertex(sf::Vector2f(curveVertice.x, static_cast<float>(y)), sf::Color::Green));
                }
            }
        }
    }
};

int main() {
    Window window(static_cast<int>(sf::VideoMode::getDesktopMode().width / 1.4),
                  static_cast<int>(sf::VideoMode::getDesktopMode().height / 1.1), "Worms map");
    window.run();

    return 0;
}