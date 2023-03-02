#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../../GameEngine/Scenes/IScene.h"
#include "../Game.h"
#include "../../GameEngine/UI/IButton.h"
#include "../Inputs/MouseEvents.h"

class MainMenuScene : public IScene<Game>, public MouseEvents {
public:
    explicit MainMenuScene(Game& game);
    ~MainMenuScene() override;

    void loadAssets();
    void processInput() override;
    void update() override;
    void render() override;

    void addButton(const sf::String &Text, const IButton::EventType& OnClick);
private:
    sf::Font* m_font;
    std::vector<IButton*> m_buttons;
};
