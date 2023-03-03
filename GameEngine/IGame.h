#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

template<typename SceneType, typename SceneNameEnum>
class IGame {
    static_assert(std::is_enum<SceneNameEnum>::value, "SceneNameEnum must be enum");

public:
    explicit IGame(const int &width, const int &height, const std::string &title) : m_width(width), m_height(height) {
        m_window.create(sf::VideoMode(m_width, m_height), title);
        m_window.setFramerateLimit(60);
    }

    virtual ~IGame() { delete m_currentScene; }

    void run() {
        sf::Clock clock;
        m_deltaTime = 0.f;

        while (m_window.isOpen()) {
            processInput();

            m_deltaTime = clock.restart().asSeconds();
            update(m_deltaTime);

            render();
        }
    }

    sf::RenderWindow *getWindow() { return &m_window; }

    void closeGame() { m_window.close(); }

    float getDeltaTime() { return m_deltaTime; }

protected:
    void processInput() {
        if (nullptr == m_currentScene)
            return;

        m_currentScene->processInput();
    }

    void update(const float &deltaTime) {
        if (nullptr == m_currentScene)
            return;

        m_currentScene->update(deltaTime);
    }

    void render() {
        if (nullptr == m_currentScene)
            return;

        m_currentScene->render();

        m_window.display();
    }

    sf::RenderWindow m_window;
    const int m_width;
    const int m_height;

    float m_deltaTime{};

    SceneType m_currentScene;
};
