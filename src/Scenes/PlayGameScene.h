#pragma once

#include "../Game.h"
#include "../Inputs/MouseEvents.h"
#include "../Ground/Ground.h"

enum PlayGameTextureName {
    Background,
    PlayerWorm
};

class PlayGameScene : public IScene<Game>, public MouseEvents {
public:
    explicit PlayGameScene(Game& game);
    ~PlayGameScene() override;

    void loadAssets();
    void processInput() override;
    void update(float deltaTime) override;
    void render() override;

    void addButton(const sf::String &Text, const IButton::EventType& OnClick, sf::Vector2f position, float width = 100.f, float height = 55.f, unsigned int characterSize = 30);

    void changeTurn();

private:
    sf::Font* m_font;
    std::map<PlayGameTextureName, sf::Texture*> m_textures;
    std::vector<IButton*> m_buttons;

    sf::Sprite m_background;

    std::unique_ptr<Ground> m_ground;
    Player* m_playerOne;
    Player* m_playerTwo;

    std::uint8_t isFirstPlayerTurn{};
};
