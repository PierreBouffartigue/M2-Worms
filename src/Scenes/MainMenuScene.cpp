#include "MainMenuScene.h"
#include "../UI/Button.h"

MainMenuScene::MainMenuScene(Game& game) : IScene(game) {
    loadAssets();
    addButton("Quit", [this](auto && Btn) { m_game.closeGame(); });
}

MainMenuScene::~MainMenuScene() {
    delete m_font;

    for (auto & button : m_buttons) {
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
    while(m_game.getWindow()->pollEvent( event ))
    {
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

void MainMenuScene::update() {

}

void MainMenuScene::render() {
    m_game.getWindow()->clear();

    for (auto &button : m_buttons) {
        button->render(m_game.getWindow());
    }
}

void MainMenuScene::addButton(const sf::String &Text, const IButton::EventType& OnClick) {
    auto newButton = new Button(Text, *m_font, 100.f, 40.f, 30.f);
    m_buttons.push_back(newButton);
    newButton->setPosition(30, 10);

    if (nullptr != OnClick)
        newButton->setOnClick(OnClick);
}