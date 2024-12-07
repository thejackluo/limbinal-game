using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "Location.cpp"
#include "Event.cpp"
#include "People.cpp"
#include "Item.cpp"

int main(){
    /*
        ========================
        Section 1: Initialize Game
        ========================
    */

    // Create a map
    Map map;

    // Create locations
    Location* home = map.addLocation("Home", "Your house. You can rest here.");

    // Create connections

    // Add connections to locations

    // Add items to locations

    // Create player with no memory, all energy all health and no money and no inventory
    Player player("Hero", 100, 50, 30, 100);
    NPC npc("Merchant");

    // Display the map
    map.displayMap();

    /*
        ========================
        Section 2: Game Loop
        ========================
    */
   // initialize the game (welcome the player with a fancy start screen, then ask the player for the name, then give the player instructoins on playing the game)
    cout << "Welcome to Limbinal!" << endl;
    cout << "What is your name?" << endl;
    string name;
    try {
        cin >> name;
        if (cin.fail()) {
            throw runtime_error("Invalid input for name.");
        }
        player.setName(name);
        cout << "Hello " << player.getName() << "!" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    cout << "Instructions: " << endl;
    cout << "You are in a house. You can rest here." << endl;
    cout << "You can move to different locations by typing the direction you want to go." << endl;
    cout << "You can check your status by typing 'status'." << endl;
    cout << "You can check the map by typing 'map'." << endl;
    cout << "You can quit the game by typing 'quit'." << endl;

    // game loop
    string command;
    while (true) {
        
    }

    
    return 0;
}