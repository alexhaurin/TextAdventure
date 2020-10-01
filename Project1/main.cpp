#include <iostream>
#include <string>
#include <vector>
#include "rooms.h"
#include "player.h"

template<typename T>
static void print(T message) {
	std::cout << message << std::endl;
}



int main() {
	
	Player player;

	static std::string intro{ "Congratulations! You have succesfully stolen the king's precious crown. \n\
Just one tiny thing left to do - escape past all of the king's guards while avoiding countless traps and deadends. \n\
But first you need to choose your attributes. But your better hurry, I think i can hear the guards coming now..." };
	print(intro);

    player.attributes(player, "");
	castle("", player);
}