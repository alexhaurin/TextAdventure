#include <iostream>
#include <string>
#include <vector>
#include "rooms.h"

template<typename T>
static void print(T message) {
    std::cout << message << std::endl;
}

std::vector<std::string> rooms{ "castleRoom", "walls", "alleys", "tower", "catacombs" };
std::vector<std::string> shopItems{ "wand", "potion" };
std::vector<std::string> availablePlaces{};

void caught(const char* intro) {
    print(intro);
    print("You lost.");
}

void travel(std::vector<std::string>& availablePlaces, std::string place1, std::string place2, Player& player) {
    availablePlaces.clear();
    availablePlaces.push_back(place1);
    availablePlaces.push_back(place2);
    std::string input;

    std::cout << "Where do you go to next? " << place1 << ", " << place2 << std::endl;

    std::getline(std::cin, input);
    while (!std::count(availablePlaces.begin(), availablePlaces.end(), input)) {
        print("Enter a valid option");
        travel(availablePlaces, place1, place2, player);
    }

    if (input == "walls") {
        walls("Patrolling the wall, you see two more guards on top of the castle walls.How will you get past them? {hide, run, cutladder}:", player);
    }
    else if (input == "alleys") {
        alleys("", player);
    }
    else if (input == "tower") {
        tower("", player);
    }
    else if (input == "room") {
        room("", player);
    }
    else if (input == "catacombs") {
        catacombs("This place looks dangerous.Do you want to keep exploring or come back?:", player);
    }
}

void puzzle(const char* intro, int num) {
    std::string input;
    std::vector<int> answers(54, 100);
    std::vector<std::string> questions{ "Whats 2*27?" "whats 2*50" };
    int answer;

    print(intro);
    print(questions[num]);
    std::getline(std::cin, input);

    try {
        answer = std::stoi(input);
    }
    catch (std::invalid_argument) {
        print("enter a number dumbass");
    }

    if (answer == answers[num]) {
        print("Good job! You got it right");
    }
    else {
        caught("You didn't get it right and the guards caught up to you");
    }
}

void fightDragon(const char* intro, Player& player) {
    std::string input;
    print(intro);

    if (player.items.empty()) {
        caught("In a fruitless attempt, you run up and start swinging at the dragon with your bare hands. The dragon flicks you away with its tail.");
    }

    print("What do you use?:");
    std::getline(std::cin, input);
    while (!std::count(player.items.begin(), player.items.end(), input)) {
        print("You don't have that");
        std::getline(std::cin, input);
    }

    if (input == "wand") {
        print("You wip out your magic wand and blast the dragon with a magical beam, transforming it into a frog. You walk past the it as it croaks angrily at you, escaping through the catacombs");
    }
    else {
        print("You drink the mysterious potion and begin to see yourself slowly disappearing. You walk pass the dragon with ease, and escape through the catacombs.");
    }

    print("Congratualtions, you win!");

}

void catacombs(const char* intro, Player& player) {
    std::vector<std::string> choices1{ "come back", "keep exploring" };
    std::vector<std::string> choices2{ "run", "sneak", "fight" };
    std::string input;

    print(intro);
    std::getline(std::cin, input);

    while (!std::count(choices1.begin(), choices1.end(), input)) {
        catacombs("Enter a valid option. {come back, explore}:", player);
    }
    if (input == choices1[0]) {
        travel(availablePlaces, "alleys", "walls", player);
    }

    print("Congratulations! You have succesfully esca - wait, you see something in the distance. All you can make out is its large figure, so you walk closer to get a better look. Its a dragon! How do you get past it? {run, sneak, fight}:");
    std::getline(std::cin, input);

    while (!std::count(choices2.begin(), choices2.end(), input)) {
        catacombs("Enter a valid option. {run, sneak, fight}:", player);
    }

    if (input == choices2[0]) {
        caught("You try to run past but the dragon awakens and blocks your path. You attempt to run back but you are not fast enough and you are killed by the dragon.");
    }
    else if (input == choices2[1]) {
        caught("You crouch and began to slowly make your way up to the dragon, hugging the wall. But the dragon smells you in its sleep. You try to run back but you are not fast enough and are killed by the dragon.");
    }
    else {
        fightDragon("You decide to fight the dragon.", player);
    }
}

void tower(const char* intro, Player& player) {
    std::vector<std::string> choices{ "yes" };
    std::string input;

    print(intro);
    print("You make your way into the tower and find a closed door. You try to open it but find that it is locked.");
    if (std::find(player.items.begin(), player.items.end(), "keys") != player.items.end()) {
        print("You test out your keys and open the door, finding a mysterious and magical looking stick.");
        player.items.push_back("wand");
    }
    else {
        print("You can return later or keep trying to open it.");

        while (true) {
            std::getline(std::cin, input);
            if (input == "give up") {
                break;
            }
            else if (input == "keep trying") {
                caught("You slam yourself into the door, attempting to break it. You crash through creating a loud sound that alerts the nearby guards, who run up and capture you!");
            }
            else {
                print("Enter something valid {keep trying, give up}:");
            }
        }

        print("Enter something valid");
        std::getline(std::cin, input);
    }

    print("Where do you head to next?:");
    travel(availablePlaces, "room", "catacombs", player);
}

void alleys(const char* intro, Player& player) {
    std::vector<std::string> choices{ "sneak", "run" };
    std::string input;

    print(intro);
    print("You see a guard patrolling the front of the alley. He seems alert - you need to get past him. How do you do it? {sneak, run}:");
    std::getline(std::cin, input);

    while (!std::count(choices.begin(), choices.end(), input)) {
        alleys("pick a valid options", player);
    }

    if (input == choices[0]) {
        if (!player.sneak(3)) {
            caught("You stepped on a dry leaf, alerting the guard who turns around and captures you.");
        }
        else {
            print("Nice! you succsefully snuck past the guard.");
        }
    }
    else if (input == choices[1]) {
        if (!player.run(3)) {
            caught("As you ran past the guard hurried behind you, but you were not fast enough so he caught up and captured you!");
        }
        else {
            print("Nice! you succsefully ran past the guard, but now you're being followed.");
        }
    }

    travel(availablePlaces, "tower", "walls", player);
}

void walls(const char* intro, Player& player) {
    std::vector<std::string> choices{ "hide", "run", "cutladder" };
    std::string input;

    print(intro);
    std::getline(std::cin, input);

    while (!std::count(choices.begin(), choices.end(), input)) {
        walls("pick a valid options", player);
    }

    if (input == choices[0]) {
        if (!player.sneak(3)) {
            caught("As you tried sneaking, you stepped on a dried leaf and were heard by a guard, who captures you.");
        }
        else {
            print("You began to crawl past the guard, who you find asleep and succesfully make it past him without eveninterupting his nap.");
        }
    }
    else if (input == choices[1]) {
        if (!player.run(3)) {
            caught("As you ran past the guard hurried behind you, but you were not fast enough so he caught up and captured you!");
        }
        else {
            print("You sprint past the guard who you find asleep, and just as he wakes up you round the corner and he loses you.");
        }
    }
    else if (input == choices[2]) {
        if (!player.lucky(3)) {
            caught("You reach for your knife to cut the ladder - but you dropped while escaping the castle! The guards catch up to you.");
        }
        else {
            print("You start cutting the ladder just as you hear guards running to follow behind you, and succesfully cut, just as they were about to reach the top.");
        }
    }

    print("You made it past the guards! On your way out you see a mysterious potion and pick it up - this might be useful later");
    player.items.push_back("potion");

    travel(availablePlaces, "tower", "room", player);
}

void room(const char* intro, Player& player) {
    std::vector<std::string> choices{ "floor", "travel" };
    std::string input;

    print(intro);
    print("There might be something in here - enter places you would like to search or enter travel to go somewhere else.");
    std::getline(std::cin, input);

    while (!std::count(choices.begin(), choices.end(), input)) {
        room("You found nothing there - keep searching.", player);
    }

    if (input == choices[0]) {
        if (player.lucky(2)) {
            print("You search under the floor and find a box with a set of keys - these might be useful later.");
            player.items.push_back("keys");
        }
        else {
            caught("You open up a floorboard just as a guard walks past, spots you, and captures you!");
        }
    }

    travel(availablePlaces, "alleys", "tower", player);
}

void castle(const char* intro, Player& player) {
    std::vector<std::string> choices{ "walls", "alleys" };
    std::string input;

    print(intro);
    print("You spring out of the king's chambers and find yourself outside of the castle, where do you try your luck exscaping? {walls alleys}:");
    std::getline(std::cin, input);

    while (!std::count(choices.begin(), choices.end(), input)) {
        castle("pick a valid option:", player);
    }

    if (input == choices[0]) {
        walls("You escape up to the castle walls. But patrolling the wall, you see two more guards on top of the castle walls.How will you get past them? {hide, run, cutladder}:", player);
    }
    else {
        alleys("You duck down into a dark alleys just as you see the guards following you round the corner and run past.", player);
    }
}