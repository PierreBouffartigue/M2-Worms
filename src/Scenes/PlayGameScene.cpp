#include <iostream>
#include "PlayGameScene.h"

PlayGameScene::PlayGameScene(Game &game) : IScene(game), m_ground(std::make_unique<Ground>()) {
    loadAssets();

    m_background.setTexture(*m_textures.at(PlayGameTextureName::Background));

    m_ground->regenerate(m_game.getWindow());
    m_player = new Player(m_textures.at(PlayGameTextureName::PlayerRed), {0, 0}, {20, 20});
}

PlayGameScene::~PlayGameScene() {
    delete m_font;
}

void PlayGameScene::loadAssets() {
    auto newFont = new sf::Font;
    newFont->loadFromFile("./assets/fonts/JosefinSans-Thin.ttf");
    m_font = newFont;

    auto newTextureBackground = new sf::Texture;
    newTextureBackground->loadFromFile("./assets/textures/background.png");
    m_textures.insert({PlayGameTextureName::Background, newTextureBackground});

    auto newTexturePlayer = new sf::Texture;
    newTexturePlayer->loadFromFile("./assets/textures/PlayerRed.png");
    m_textures.insert({PlayGameTextureName::PlayerRed, newTexturePlayer});
}

void PlayGameScene::processInput() {
    sf::Event event{};
    while(m_game.getWindow()->pollEvent( event ))
    {
        if (sf::Event::Closed == event.type) {
            m_game.closeGame();
            continue;
        }
        m_ground->processInput(m_game.getWindow());
        m_player->processInput();
        auto mouseCoords = m_game.getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*m_game.getWindow()));
        //handleOnMouseLeftClick(event, mouseCoords, *m_ground);
        handleOnMouseLeftClick(event, mouseCoords, *m_player);
    }
}

void PlayGameScene::update(float deltaTime) {
    m_ground->update(m_game.getWindow());
    m_player->update(deltaTime, m_ground->getGroundPixels(), m_game.getWindow());
}

void PlayGameScene::render() {
    m_game.getWindow()->clear(sf::Color::Cyan);

    m_game.getWindow()->draw(m_background);

    m_ground->render(m_game.getWindow());
    m_player->render(m_game.getWindow());
}
