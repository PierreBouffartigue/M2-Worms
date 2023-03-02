#include <iostream>
#include "PlayGameScene.h"

PlayGameScene::PlayGameScene(Game &game) : IScene(game), m_ground(std::make_unique<Ground>()) {
    loadAssets();
    std::cout << "PlayGameScene" << std::endl;
    m_ground->regenerate(*m_game.getWindow());
}

PlayGameScene::~PlayGameScene() {
    delete m_font;
}

void PlayGameScene::loadAssets() {
    auto newFont = new sf::Font;
    newFont->loadFromFile("./assets/fonts/JosefinSans-Thin.ttf");
    m_font = newFont;
}

void PlayGameScene::processInput() {
    sf::Event event{};
    while(m_game.getWindow()->pollEvent( event ))
    {
        if (sf::Event::Closed == event.type) {
            m_game.closeGame();
            continue;
        }
        m_ground->handleEvents(*m_game.getWindow());
    }
}

void PlayGameScene::update() {
    m_ground->update(*m_game.getWindow());
}

void PlayGameScene::render() {
    m_game.getWindow()->clear(sf::Color::Cyan);

    m_ground->draw(*m_game.getWindow());
    player.draw(*m_game.getWindow());
}
