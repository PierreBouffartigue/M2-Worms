#include "Game.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/PlayGameScene.h"


Game::Game(const int &width, const int &height, const std::string &title) : IGame(width, height, title) {
    m_currentScene = createSceneFromName(EScenes::PlayGame);
}

IScene<Game> *Game::createSceneFromName(EScenes sceneName) {
    switch (sceneName) {
        case EScenes::MainMenu:
            return new MainMenuScene(*this);
            /*case EScenes::LevelEditor:
                return new LevelEditorScene(m_window);*/
        case EScenes::PlayGame:
            return new PlayGameScene(*this);
        default:
            throw std::runtime_error("SceneName not found");
    }
}
