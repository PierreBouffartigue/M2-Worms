#include <iostream>
#include "MainMenuScene.h"
#include "../UI/Button.h"

MainMenuScene::MainMenuScene(Game &game) : IScene(game) {
    loadAssets();

    //addButton("Play", [this](auto && btn) { m_game.loadScene(EScenes::PlayGame); }, sf::Vector2f(30, 10));
    addButton("Quit", [this](auto &&btn) { m_game.closeGame(); }, sf::Vector2f(30, 100));
}

MainMenuScene::~MainMenuScene() {
    delete m_font;

    for (auto &button: m_buttons) {
        delete button;
    }
}

void MainMenuScene::loadAssets() {
    auto newFont = new sf::Font;
    newFont->loadFromFile("./assets/fonts/JosefinSans-Thin.ttf");
    m_font = newFont;
}

void MainMenuScene::processInput() {
    sf::Event event{};
    while (m_game.getWindow()->pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            m_game.closeGame();
            continue;
        }

        auto buttons = m_buttons;
        handleOnMouseLeftClick(event, buttons);
    }
    auto mouseCoords = m_game.getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*m_game.getWindow()));
    auto buttons = m_buttons;
    handleOnMouseHover(mouseCoords, buttons);
}

void MainMenuScene::update(float deltaTime) {

}

void MainMenuScene::render() {
    m_game.getWindow()->clear();

    for (auto &button: m_buttons) {
        button->render(m_game.getWindow());
    }
}

void MainMenuScene::addButton(const sf::String &Text, const IButton::EventType &OnClick, sf::Vector2f position) {
    auto newButton = new Button(Text, *m_font, 100.f, 55.f, 30.f);
    m_buttons.push_back(newButton);
    newButton->setPosition(position.x, position.y);

    if (nullptr != OnClick)
        newButton->setOnClick(OnClick);
}