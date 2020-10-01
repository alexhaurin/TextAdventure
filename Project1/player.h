#pragma once
#include <iostream>
#include <string>
#include <vector>

class Player {
public:
    int totalPoints = 10;
    unsigned int stealth;
    unsigned int luck;
    unsigned int speed;

    std::vector<std::string> items;

public:
    int getAttribute(const char* message);

    void attributes(Player& player, const char* intro);

    bool sneak(unsigned int dif);

    bool lucky(unsigned int dif);

    bool run(unsigned int dif);
};


