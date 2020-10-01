#include <iostream>
#include <string>
#include <vector>
#include "player.h"

template<typename T>
static void print(T message) {
    std::cout << message << std::endl;
}

int Player::getAttribute(const char* message) {
    std::string input;
    int points;

    print(message);
    while (true) {
        std::getline(std::cin, input);
        try {
            points = std::stoi(input);
        }
        catch (std::invalid_argument) {
            print("Enter a number.");
            continue;
        }

        if (points > totalPoints) {
            print("You don't have enough points");
            continue;
        }
        else {
            totalPoints -= points;
            break;
        }
    }

    return points;
}

void Player::attributes(Player& player, const char* intro) {
    int totalPoints = 10;

    print(intro);

    player.stealth = getAttribute("How many points would you like to add to your stealth attribute?:");
    player.luck = getAttribute("How many points would you like to add to your luck attribute?:");
    player.speed = getAttribute("How many points would you like to add to your speed attribute?:");
}


bool Player::sneak(unsigned int dif) {
    if (stealth >= dif) {
        return true;
    }
    else {
        return false;
    }
}

bool Player::lucky(unsigned int dif) {
    if (luck >= dif) {
        return true;
    }
    else {
        return false;
    }
}

bool Player::run(unsigned int dif) {
    if (speed >= dif) {
        return true;
    }
    else {
        return false;
    }
}