#include <iostream>
#include "Game.h"

int main() {
    //std::cout << "Good" << std::endl;

    std::unique_ptr<Game> game = std::make_unique<Game>(static_cast<int>(sf::VideoMode::getDesktopMode().width / 1.4), static_cast<int>(sf::VideoMode::getDesktopMode().height / 1.1), "Test Worms");
    game->run();

    return 0;
}
