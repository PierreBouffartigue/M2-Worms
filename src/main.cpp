#include <iostream>
#include "Game.h"

int main() {
    //std::cout << "Good" << std::endl;

    std::unique_ptr<Game> game = std::make_unique<Game>(1000, 700, "Test Worms");
    game->run();

    return 0;
}
