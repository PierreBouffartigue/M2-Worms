#pragma once

#include "../Game.h"
#include "../Inputs/MouseEvents.h"
#include "../Ground/Ground.h"

class PlayGameScene : public IScene<Game>, public MouseEvents {
public:
    explicit PlayGameScene(Game& game);
    ~PlayGameScene() override;

    void loadAssets();
    void processInput() override;
    void update() override;
    void render() override;

private:
    sf::Font* m_font;

    std::unique_ptr<Ground> m_ground;
    Player player{{0, 0}, {20, 20}, sf::Color::Yellow};
};
