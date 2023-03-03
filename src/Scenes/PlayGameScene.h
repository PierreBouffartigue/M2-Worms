#pragma once

#include "../Game.h"
#include "../Inputs/MouseEvents.h"
#include "../Ground/Ground.h"

enum PlayGameTextureName {
    Background,
    PlayerRed
};

class PlayGameScene : public IScene<Game>, public MouseEvents {
public:
    explicit PlayGameScene(Game& game);
    ~PlayGameScene() override;

    void loadAssets();
    void processInput() override;
    void update(float deltaTime) override;
    void render() override;

private:
    sf::Font* m_font;
    std::map<PlayGameTextureName, sf::Texture*> m_textures;

    sf::Sprite m_background;

    std::unique_ptr<Ground> m_ground;
    Player* m_player;
};
