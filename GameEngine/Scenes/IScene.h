#pragma once


#include "../IGame.h"

template<typename GameType>
class IScene {
public:
    explicit IScene(GameType &game) : m_game(game) {}

    virtual ~IScene() = default;

    virtual void processInput() = 0;

    virtual void update(float deltaTime) = 0;

    virtual void render() = 0;

protected:
    GameType &m_game;
};
