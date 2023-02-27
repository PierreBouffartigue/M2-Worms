#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>

class Utils {
public:
    static int GetRandomNumber(const int minNumber, const int maxNumber) {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dis(minNumber, maxNumber);

        return dis(gen);
    }
};

class Player {
public:
    Player(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color)
            : m_body(size), m_velocity(sf::Vector2f(0.f, 0.f)), m_speed(100.f) {
        m_body.setPosition(position);
        m_body.setFillColor(color);
    }

    ~Player() = default;

    void handleEvents(const float deltaTime, const sf::VertexArray &map) {
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

        for (unsigned int i = 0; i < map.getVertexCount(); i++) {
            sf::Vector2f mapPos = map[i].position;
            if (m_body.getGlobalBounds().intersects(sf::FloatRect(mapPos.x, mapPos.y, 1.f, 1.f))) {
                m_velocity.x = 0.f;
                m_velocity.y = 0.f;
                break;
            }
        }

        m_body.move(m_velocity * deltaTime);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(m_body);
    }

private:
    sf::RectangleShape m_body;
    sf::Vector2f m_velocity;
    const float m_speed = 100.f;
};

class Curve {
public:
    Curve(const int numCurves, const float &curveHeights)
            : m_numCurves(numCurves), m_curveHeights(curveHeights) {}

    ~Curve() = default;

    sf::VertexArray generate(const int width, const int height) const {
        sf::VertexArray curve(sf::LineStrip, width);

        float factor = static_cast<float>(2 * M_PI) / static_cast<float>(width);
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

class Ground {
public:
    Ground() : m_destroyRadius(10.0f) {};

    ~Ground() = default;

    void regenerate(sf::RenderWindow &m_window) {
        if (isFlatModEnable) {
            curve_ = Curve(1, 10.f);
        } else {
            curve_ = Curve(Utils::GetRandomNumber(1, 4), static_cast<float>(Utils::GetRandomNumber(20, 80)));
        }

        m_groundPixels.clear();
        m_groundPixels.setPrimitiveType(sf::Points);

        std::vector<sf::Vector2f> curveVertices;
        for (int x = 0; x < m_window.getSize().x; x++) {
            float y = 0;
            for (int i = 0; i < curve_.getNumCurves(); i++) {
                float frequency = static_cast<float>(i + 1) * 0.5f;
                y += static_cast<float>(curve_.getCurveHeights() *
                                        sin(2 * M_PI * frequency * x / static_cast<float>(m_window.getSize().x)));
            }
            curveVertices.emplace_back(static_cast<float>(x), static_cast<float>(m_window.getSize().y) / 2 + y);
        }

        bool foundCurveStart = false;
        for (auto &curveVertex: curveVertices) {
            if (!foundCurveStart && curveVertex.y > static_cast<float>(m_window.getSize().y) / 2) {
                foundCurveStart = true;
            }
            if (foundCurveStart) {
                for (int y = static_cast<int>(curveVertex.y); y < m_window.getSize().y; y++) {
                    m_groundPixels.append(
                            sf::Vertex(sf::Vector2f(curveVertex.x, static_cast<float>(y)), sf::Color::Green));
                }
            }
        }
    }

    void handleEvents(sf::RenderWindow &m_window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            const sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            for (int i = 0; i < m_groundPixels.getVertexCount(); i++) {
                const sf::Vertex &vertex = m_groundPixels[i];
                const float distance = std::hypotf(static_cast<float>(mousePos.x) - vertex.position.x,
                                                   static_cast<float>(mousePos.y) - vertex.position.y);
                if (distance < m_destroyRadius) {
                    m_groundPixels[i].color = sf::Color::Transparent;
                }
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            regenerate(m_window);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            isFlatModEnable = !isFlatModEnable;
            std::cout << "Flat mod : " + std::to_string(isFlatModEnable) << std::endl;
        }
    }

    void draw(sf::RenderWindow &m_window) {
        m_window.draw(m_curve);
        m_window.draw(m_groundPixels);
    }

    void update(sf::RenderWindow &m_window) {
        m_curve = curve_.generate(static_cast<int>(m_window.getSize().x), static_cast<int>(m_window.getSize().y));
    }

    sf::VertexArray GetGreenPixels() {
        return m_groundPixels;
    }

private:
    bool isFlatModEnable = false;
    float m_destroyRadius;
    sf::VertexArray m_curve;
    sf::VertexArray m_groundPixels;
    Curve curve_{Utils::GetRandomNumber(1, 4), static_cast<float>(Utils::GetRandomNumber(20, 80))};
};

class Window {
public:
    Window(const int &width, const int &height, const std::string &title)
            : m_width(width), m_height(height), m_deltaTime(0.f), m_ground(std::make_unique<Ground>()) {
        m_window.create(sf::VideoMode(m_width, m_height), title);
        m_window.setFramerateLimit(60);
        m_ground->regenerate(m_window);
    }

    void run() {
        while (m_window.isOpen()) {
            sf::Time elapsed = m_clock.restart();
            m_deltaTime = elapsed.asSeconds();
            handleEvents();
            update();
            render();
            display();
        }
    }

protected:
    void handleEvents() {
        sf::Event event{};
        player.handleEvents(m_deltaTime, m_ground->GetGreenPixels());
        m_ground->handleEvents(m_window);
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }
    }

    void update() {
        m_ground->update(m_window);
    }

    void render() {
        m_window.clear(sf::Color::Cyan);
        m_ground->draw(m_window);
        player.draw(m_window);
    }

    void display() {
        m_window.display();
    }

private:
    const int m_width;
    const int m_height;
    sf::RenderWindow m_window;
    std::unique_ptr<Ground> m_ground;
    Player player{{0, 0}, {20, 20}, sf::Color::Yellow};
    sf::Clock m_clock;
    float m_deltaTime;
};

int main() {
    Window window(static_cast<int>(sf::VideoMode::getDesktopMode().width / 1.4),
                  static_cast<int>(sf::VideoMode::getDesktopMode().height / 1.1), "Worms map");
    window.run();
    return 0;
}