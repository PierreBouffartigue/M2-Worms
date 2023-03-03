#include <iostream>
#include "PlayGameScene.h"
#include "../UI/Button.h"

PlayGameScene::PlayGameScene(Game &game) : IScene(game), m_ground(std::make_unique<Ground>()) {
    loadAssets();

    m_background.setTexture(*m_textures.at(PlayGameTextureName::Background));

    m_ground->regenerate(m_game.getWindow());
    m_playerOne = new Player(m_textures.at(PlayGameTextureName::PlayerWorm), {0, 0});
    m_playerTwo = new Player(m_textures.at(PlayGameTextureName::PlayerWorm), {100, 0});

    addButton("Quit", [this](auto &&btn) { m_game.closeGame(); },
              sf::Vector2f(static_cast<float>(m_game.getWindow()->getSize().x) - 150.f, 30));
    addButton("End Turn", [this](auto &&btn) { changeTurn(); },
              sf::Vector2f(static_cast<float>(m_game.getWindow()->getSize().x) - 350.f, 30), 150.f);
    addButton("Save Game", [this](auto &&btn) { Utils::saveGame(m_ground->getGroundPixels(), *m_playerOne, *m_playerTwo);; },
              sf::Vector2f(static_cast<float>(m_game.getWindow()->getSize().x) - 550.f, 30), 170.f);
    addButton("Regenerate Ground", [this](auto &&btn) { m_ground->regenerate(m_game.getWindow()); },
              sf::Vector2f(static_cast<float>(m_game.getWindow()->getSize().x) - 850.f, 30), 270.f);
    addButton("Flat Mode", [this](auto &&btn) { m_ground->changeFlatMode(); },
              sf::Vector2f(static_cast<float>(m_game.getWindow()->getSize().x) - 1050.f, 30), 170.f);
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
    newTexturePlayer->loadFromFile("./assets/textures/player.png");
    m_textures.insert({PlayGameTextureName::PlayerWorm, newTexturePlayer});
}

void PlayGameScene::processInput() {
    sf::Event event{};
    auto mouseCoords = m_game.getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*m_game.getWindow()));

    while (m_game.getWindow()->pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            m_game.closeGame();
            continue;
        }

        //handleOnMouseRightClick(event, mouseCoords, *m_ground);
        m_ground->processInput(m_game.getWindow());

        if (isFirstPlayerTurn) {
            handleOnMouseRightClick(event, mouseCoords, *m_playerOne);
            m_playerOne->processInput();
        } else {
            handleOnMouseRightClick(event, mouseCoords, *m_playerTwo);
            m_playerTwo->processInput();
        }

        handleOnMouseLeftClick(event, m_buttons);
    }
    handleOnMouseHover(mouseCoords, m_buttons);
}

void PlayGameScene::update(float deltaTime) {
    m_ground->update(m_game.getWindow());
    m_playerOne->update(deltaTime, m_ground->getGroundPixels(), m_game.getWindow());
    m_playerTwo->update(deltaTime, m_ground->getGroundPixels(), m_game.getWindow());
}

void PlayGameScene::render() {
    m_game.getWindow()->clear(sf::Color::Cyan);

    m_game.getWindow()->draw(m_background);

    m_ground->render(m_game.getWindow());

    for (auto &button: m_buttons) {
        button->render(m_game.getWindow());
    }

    m_playerOne->render(m_game.getWindow());
    m_playerTwo->render(m_game.getWindow());
}

void
PlayGameScene::addButton(const sf::String &Text, const IButton::EventType &OnClick, sf::Vector2f position, float width,
                         float height, unsigned int characterSize) {
    auto newButton = new Button(Text, *m_font, width, height, characterSize);
    m_buttons.push_back(newButton);
    newButton->setPosition(position.x, position.y);

    if (nullptr != OnClick)
        newButton->setOnClick(OnClick);
}

void PlayGameScene::changeTurn() {
    isFirstPlayerTurn = !isFirstPlayerTurn;
}
