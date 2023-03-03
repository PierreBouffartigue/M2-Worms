#include "Utils.h"

int Utils::getRandomNumber(const int minNumber, const int maxNumber) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(minNumber, maxNumber);

    return dis(gen);
}

void Utils::saveGame(const sf::VertexArray &pixels, Player &firstPlayer, Player &secondPlayer) {
    std::ofstream outputFile("save.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening save file" << std::endl;
        return;
    }

    outputFile << "GroundPixels\n";
    for (unsigned int i = 0; i < pixels.getVertexCount(); i++) {
        const sf::Vector2f &pos = pixels[i].position;
        outputFile << pos.x << "," << pos.y << "\n";
    }

    outputFile << "FirstPlayer\n";
    const sf::Vector2f &firstPlayerPos = firstPlayer.getPosition();
    outputFile << firstPlayerPos.x << "," << firstPlayerPos.y << "\n";

    outputFile << "SecondPlayer\n";
    const sf::Vector2f &secondPlayerPos = secondPlayer.getPosition();
    outputFile << secondPlayerPos.x << "," << secondPlayerPos.y << "\n";

    outputFile.close();
    std::cout << "Saved game" << std::endl;
}

void Utils::loadGame() {
    std::cout << "Load game - WIP" << std::endl;
}
