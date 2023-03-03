#pragma once

#include <random>
#include <fstream>
#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>
#include "../GameObjects/Player.h"

class Utils {
public:
    Utils() = default;

    ~Utils() = default;

    static int getRandomNumber(int minNumber, int maxNumber);

    static void saveGame(const sf::VertexArray &pixels, Player &firstPlayer, Player &secondPlayer);

    static void loadGame();
};
