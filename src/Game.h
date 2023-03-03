#pragma once

#include "../GameEngine/IGame.h"
#include "Scenes/EScenes.h"
#include "../GameEngine/Scenes/IScene.h"


class Game : public IGame<IScene<Game> *, EScenes> {
public:
    Game(const int &width, const int &height, const std::string &title);

    IScene<Game> *createSceneFromName(EScenes sceneName);
};
