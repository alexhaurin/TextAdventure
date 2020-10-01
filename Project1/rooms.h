#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "player.h"


template<typename T>
void print(T message);

void caught(const char* intro);
void travel(std::vector<std::string>& availablePlaces, std::string place1, std::string place2, Player& player);
void puzzle(const char* intro, int num);
void fightDragon(const char* intro, Player& player);

void catacombs(const char* intro, Player& player);
void tower(const char* intro, Player& player);
void alleys(const char* intro, Player& player);
void walls(const char* intro, Player& player);
void room(const char* intro, Player& player);
void castle(const char* intro, Player& player);