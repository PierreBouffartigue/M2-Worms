#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

template<typename SceneType, typename SceneNameEnum>
class IGame {
    static_assert(std::is_enum<SceneNameEnum>::value, "SceneNameEnum must be enum");

public:
    explicit IGame(const int& width, const int& height, const std::string& title) : m_width(width), m_height(height) {
        m_window.create(sf::VideoMode(m_width, m_height), title);
        m_window.setFramerateLimit(60);
    }

    virtual ~IGame() { delete m_currentScene; }

    void run() {
        sf::Clock clock;
        float deltaTime = 0.f;
        float frameTimeElapsed;

        while (m_window.isOpen()) {
            processInput();

            deltaTime += clock.restart().asSeconds();
            while (frameTimeElapsed > deltaTime) {
                frameTimeElapsed -= deltaTime;
                update(deltaTime);
            }
            render();
        }
    }

    sf::RenderWindow* getWindow() { return &m_window; }

    void closeGame() { m_window.close(); }

protected:
    void processInput() {
        m_currentScene->processInput();
    }

    void update(const float& deltaTime) {
        m_currentScene->update();
    }

    void render() {
        m_currentScene->render();

        m_window.display();
    }

    sf::RenderWindow m_window;
    const int m_width;
    const int m_height;

    SceneType m_currentScene;
};
