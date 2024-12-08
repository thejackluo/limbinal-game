#include "metadata.h"
#include "Item.h"
#include "Event.h"
#include "EventManager.h"
#include "Location.h"
#include "People.h"
#include "Player.h"
#include "NPC.h"
#include "InventoryContainer.h"

#include <vector>
#include <map>
#include <iostream>
#include <cstdlib> // for rand()

std::vector<Character> characters;
std::map<std::string, Location> locations; // Use map for locations
InventoryContainer<Item> globalInventory;  // Use InventoryContainer for items
EventManager eventManager;

// Initialize Player and NPCs
Player ryohashi("Ryohashi", 100, 50, 30, 100);
NPC yumi("Yumi");
NPC kakkeda("Kakkeda");
NPC hiroto("Hiroto");
NPC suzumi("Suzumi");

// Helper: Special memory item IDs
// We'll have multiple memory items: memory fragments
// Collecting all fragments leads to a special memory ending
static const int MEMORY_ITEMS_COUNT = 5;
static std::vector<Item> memoryFragments = {
    Item(101, "Memory Fragment (Childhood)", ItemType::MEM, 10),
    Item(102, "Memory Fragment (Yumi's Note)", ItemType::MEM, 10),
    Item(103, "Memory Fragment (College Days)", ItemType::MEM, 10),
    Item(104, "Memory Fragment (Happy World)", ItemType::MEM, 10),
    Item(105, "Memory Fragment (Lost Purpose)", ItemType::MEM, 10)
};

void initializeMetadata() {
    /*
        =================================================================================
        Section 1: People (Player and NPCs)
        =================================================================================
    */
    // Already initialized globally.

    /*
        =================================================================================
        Section 2: Map Locations
        =================================================================================
    */
    locations["Main House"] = Location("Main House", "Your old home in a suburban limbo. The air is stale, the sky clouded, and everything feels nostalgic but hollow.");
    locations["Suburbs"] = Location("Suburbs", "A quiet stretch of houses with peeling paint and silent streets, Yumi is rumored to appear here.");
    locations["Childhood"] = Location("Childhood", "A neighborhood that triggers old memories. Kakkeda lurks around these parts.");
    locations["Main Town 1"] = Location("Main Town 1", "A transitional area leading north. Hiroto seems to frequent here.");
    locations["Main Town 2"] = Location("Main Town 2", "Further into the world, Suzumi resides here, lost in thought.");
    locations["City 1"] = Location("City 1", "A segment of the futuristic city, reaching here might lead to a conclusion.");
    locations["City 2"] = Location("City 2", "Another segment of the city, adorned with neon lights and silent drones.");
    locations["City 3"] = Location("City 3", "A junction connecting to City 1, City 2, and City 4.");
    locations["City 4"] = Location("City 4", "A northern extension of the city, with towering structures and hidden secrets.");

    // Connect physical world locations
    locations["Main House"].addConnection("south", &locations["Suburbs"]);
    locations["Main House"].addConnection("right", &locations["Childhood"]);
    locations["Main House"].addConnection("north", &locations["Main Town 1"]);
    locations["Main Town 1"].addConnection("east", &locations["Main Town 2"]);
    locations["Main Town 1"].addConnection("north", &locations["City 3"]);
    locations["City 3"].addConnection("west", &locations["City 1"]);
    locations["City 3"].addConnection("east", &locations["City 2"]);
    locations["City 3"].addConnection("north", &locations["City 4"]);

    // Add NPCs to locations
    locations["Suburbs"].addNPC(yumi);
    locations["Childhood"].addNPC(kakkeda);
    locations["Main Town 1"].addNPC(hiroto);
    locations["Main Town 2"].addNPC(suzumi);

    /*
        =================================================================================
        Section 3: Items
        =================================================================================
    */
    // Add some basic items globally
    globalInventory.addItem(Item(1, "Bandage", ItemType::HEALTH, 10));
    globalInventory.addItem(Item(2, "Energy Drink", ItemType::ENERGY, 15));
    globalInventory.addItem(Item(4, "Cash", ItemType::MONEY, 10));

    // Place items in locations
    // Maybe scatter memory fragments around:
    locations["Childhood"].addItem(memoryFragments[0]);    // Childhood memory
    locations["Suburbs"].addItem(memoryFragments[1]);      // Yumi's Note memory
    locations["Main Town 1"].addItem(memoryFragments[2]);  // College memory
    locations["Main Town 2"].addItem(memoryFragments[3]);  // Happy world memory
    locations["City 4"].addItem(memoryFragments[4]);       // Lost Purpose memory

    // Add a few healing items in random spots
    locations["Suburbs"].addItem(Item(10, "Health Kit", ItemType::HEALTH, 20));
    locations["City 2"].addItem(Item(11, "Stimulant", ItemType::ENERGY, 25));

    /*
        =================================================================================
        Section 4: Events
        =================================================================================
        We'll create story events for each location and random events involving NPCs.
    */

    // MAIN HOUSE STORY EVENT:
    // Introduce the world and hint at memory fragments.
    eventManager.addEvent(Event(
        "Main House Introduction",
        Event::EventType::STORY,
        "You awaken in your old Main House. The silence is almost overwhelming. A faint nostalgia tugs at your mind, but memories remain fragmented.",
        {"Search the house", "Step outside"},
        {
            {"You find a faded photograph inside a drawer, it stirs old emotions but no clarity.", [=]() {
                std::cout << "You feel a slight increase in your memory capacity.\n";
                ryohashi.modifyStats(0,0,5,0);
            }},
            {"You decide to step outside, ignoring the scattered hints of your past.", [=]() {
                std::cout << "The world awaits beyond these walls.\n";
            }}
        },
        {},
        100 // Arbitrary event number
    ));
    locations["Main House"].addEvent(*eventManager.getEvent("Main House Introduction"));

    // SUBURBS STORY EVENT:
    // Meeting Yumi - a subtle story event that triggers a memory hint.
    eventManager.addEvent(Event(
        "Suburbs Encounter",
        Event::EventType::STORY,
        "As you wander through the Suburbs, you spot Yumi leaning against a faded fence. She smiles faintly.",
        {"Approach Yumi", "Ignore and keep walking"},
        {
            {"You approach her. Yumi whispers: 'Do you remember the starry nights?' A flash of memory passes through your mind.", [=]() {
                std::cout << "Your mem increases slightly from this encounter.\n";
                ryohashi.modifyStats(0,0,5,0);
            }},
            {"You walk past silently. Yumi disappears into the grey backdrop, leaving you with questions unanswered.\n", [=]() {}}
        },
        {},
        101
    ));
    locations["Suburbs"].addEvent(*eventManager.getEvent("Suburbs Encounter"));

    // CHILDHOOD STORY EVENT:
    // Encounter Kakkeda and old conflicts.
    eventManager.addEvent(Event(
        "Childhood Flashback",
        Event::EventType::STORY,
        "You stand in the Childhood neighborhood. A memory of Kakkeda pushing you in high school emerges.",
        {"Recall the argument", "Try to forget"},
        {
            {"The memory hurts, but you learn something: it was about Limbo and VR ethics. You gain insight.", [=]() {
                std::cout << "You recall Kakkeda's betrayal, understanding your current predicament better.\n";
                ryohashi.modifyStats(0,0,5,0);
            }},
            {"You try to block it out. Ignorance doesn't help you grow.\n", [=]() {}}
        },
        {},
        102
    ));
    locations["Childhood"].addEvent(*eventManager.getEvent("Childhood Flashback"));

    // MAIN TOWN 1 STORY EVENT:
    // Hiroto's message about the past and Limbo.
    eventManager.addEvent(Event(
        "Main Town 1 Reflection",
        Event::EventType::STORY,
        "In Main Town 1, you recall college days at Waseda with Hiroto. He warned you about Kakkeda's ambition.",
        {"Reflect deeply", "Shrug it off"},
        {
            {"You reflect deeply, remembering Hiroto's caution. You gain a clearer picture of the world.", [=]() {
                std::cout << "Your understanding of Limbo improves. Memory +5.\n";
                ryohashi.modifyStats(0,0,5,0);
            }},
            {"You ignore it, remaining uncertain.\n", [=]() {}}
        },
        {},
        103
    ));
    locations["Main Town 1"].addEvent(*eventManager.getEvent("Main Town 1 Reflection"));

    // MAIN TOWN 2 STORY EVENT:
    // Suzumi’s presence and a hint of the Happy World.
    eventManager.addEvent(Event(
        "Main Town 2 Whispers",
        Event::EventType::STORY,
        "In Main Town 2, Suzumi greets you. She speaks of a 'Happy World' that you once knew.",
        {"Ask about Happy World", "Dismiss her words"},
        {
            {"Suzumi says: 'To restore your memory, find all fragments scattered across this limbo. Only then you'll see the truth.'", [=]() {
                std::cout << "You now know collecting all memory fragments may unlock a special ending.\n";
            }},
            {"You dismiss her. Without guidance, finding the truth may be harder.\n", [=]() {}}
        },
        {},
        104
    ));
    locations["Main Town 2"].addEvent(*eventManager.getEvent("Main Town 2 Whispers"));

    // CITY 3 STORY EVENT:
    // Approaching the metropolis and its complexities.
    eventManager.addEvent(Event(
        "City 3 Transition",
        Event::EventType::STORY,
        "You stand in City 3, a crossroads in the futuristic metropolis. The neon lights and polished concrete reflect a twisted society.",
        {"Contemplate going further", "Turn back"},
        {
            {"You prepare yourself: beyond here lies City 1, where an ending might await.", [=]() {
                std::cout << "You feel both anticipation and dread.\n";
            }},
            {"You turn back, hesitant to face the unknown.\n", [=]() {}}
        },
        {},
        105
    ));
    locations["City 3"].addEvent(*eventManager.getEvent("City 3 Transition"));

    // CITY 1 ENDING EVENT:
    // If the player reaches City 1, trigger a final event.
    // Two endings: 
    // - If the player hasn't collected all memory fragments, a "default" ending.
    // - If the player has all memory fragments, a special "memory" ending.
    eventManager.addEvent(Event(
        "City 1 Finale",
        Event::EventType::STORY,
        "At City 1, the world shifts. You feel the VR boundaries thinning. Kakkeda’s voice echoes in digital whispers.",
        {"Accept the truth", "Resist"},
        {
            {"You attempt to break free from Limbo. If you have all memory fragments, you recall everything, forging a new reality. Otherwise, you simply escape to an uncertain freedom.",
             [=]() {
                 // Check if player has all memory fragments (pseudo-check)
                 // In real code, you'd check player's inventory for all memory items.
                 std::cout << "This would trigger one of the final endings.\n";
                 std::cout << "If all memory fragments are present: Memory Ending (a fully restored memory and a new destiny).\n";
                 std::cout << "If not: A bittersweet escape ending.\n";
             }},
            {"You resist, remaining trapped. Nothing changes.\n", [=]() {}}
        },
        {},
        106
    ));
    locations["City 1"].addEvent(*eventManager.getEvent("City 1 Finale"));

    // You might also add events to City 2 and City 4 if needed,
    // but let's leave them as transitions or item pick-up spots for now.
    eventManager.addEvent(Event(
        "City 4 Memory Clue",
        Event::EventType::STORY,
        "City 4 is eerily quiet. You sense a final memory fragment hidden here.",
        {"Search thoroughly", "Give up"},
        {
            {"You find the last Memory Fragment. With all fragments, return to the Main House for a special revelation.", [=]() {
                std::cout << "Now that you have the last fragment, something might happen back home.\n";
            }},
            {"You give up searching, missing a crucial piece.\n", [=]() {}}
        },
        {},
        107
    ));
    locations["City 4"].addEvent(*eventManager.getEvent("City 4 Memory Clue"));

    // Special event at Main House if all memory fragments found (Memory Ending trigger)
    eventManager.addEvent(Event(
        "Main House Memory Ending",
        Event::EventType::STORY,
        "Back at the Main House, all fragments resonate. Your true past emerges, merging Limbo with your happiest memories.",
        {"Embrace your restored memory", "Reject it"},
        {
            {"You embrace the restored memory. You transcend Limbo, rewriting the VR system. A perfect, free world emerges from your mind. (Memory Ending)", [=]() {
                std::cout << "This triggers the Memory Ending.\n";
            }},
            {"You reject it, too afraid to face the truth. The world remains stagnant.\n", [=]() {}}
        },
        {},
        108
    ));
    // The player would only see this event if code checks conditions (inventory items)
    // and decides to trigger it once all memory fragments are collected.

    /*
        =================================================================================
        Random Events 
        =================================================================================
        Triggered when staying in a location. Based on whether NPCs are present.
    */

    // A random event in Suburbs with Yumi
    eventManager.addEvent(Event(
        "Yumi Gift",
        Event::EventType::RANDOM,
        "Yumi approaches quietly. She offers you a small token of comfort.",
        {"Accept"},
        {
            {"You accept a small charm, +5 MEM.", [=]() {
                std::cout << "Yumi gives you a small charm that helps recall faint memories.\n";
                ryohashi.modifyStats(0,0,5,0);
            }}
        },
        {},
        -1
    ));

    // A random event in Childhood with Kakkeda - could be dangerous
    eventManager.addEvent(Event(
        "Kakkeda Attack",
        Event::EventType::RANDOM,
        "Kakkeda appears from the shadows, his eyes cold.",
        {"Defend", "Run"},
        {
            {"Defend yourself!", [=]() {
                int damage = rand() % 15 + 5;
                std::cout << "Kakkeda attacks you for " << damage << " damage!\n";
                ryohashi.modifyStats(-damage,0,0,0);
            }},
            {"You run away, losing some energy.", [=]() {
                ryohashi.modifyStats(0,-10,0,0);
            }}
        },
        {},
        -1
    ));

    // A random event in Main Town 1 with Hiroto - friendly advice
    eventManager.addEvent(Event(
        "Hiroto Advice",
        Event::EventType::RANDOM,
        "Hiroto stops you: 'Don't forget to keep your energy up in this world.'",
        {"Nod"},
        {
            {"You nod. Hiroto hands you an Energy Drink.", [=]() {
                std::cout << "You receive an Energy Drink.\n";
                // In actual code, you'd add this to player's inventory.
            }}
        },
        {},
        -1
    ));

    // A random event in Main Town 2 with Suzumi - cryptic hint
    eventManager.addEvent(Event(
        "Suzumi Hint",
        Event::EventType::RANDOM,
        "Suzumi speaks: 'The fragments you seek are scattered. Only by collecting them can you escape with full clarity.'",
        {"Thank her"},
        {
            {"You thank Suzumi and feel more determined.", [=]() {
                ryohashi.modifyStats(0,0,5,0);
            }}
        },
        {},
        -1
    ));

    // A random event in a location with no NPCs (like City 2)
    eventManager.addEvent(Event(
        "Empty Streets",
        Event::EventType::RANDOM,
        "You linger in empty streets. Nothing but silence and distant neon flicker.",
        {"Wait"},
        {
            {"Nothing changes, but you grow more uneasy.", [=]() {
                std::cout << "No immediate effect.\n";
            }}
        },
        {},
        -1
    ));

    // You can add these random events logic in the main loop where if the player chooses to "stay" and there's an NPC or not, you pick from the eventManager's getRandomEvent().

    // For demonstration, we won't add these random events directly to a location because random events are chosen by eventManager.getRandomEvent().
    // However, you might want a system that picks random events based on current location or NPC presence. One approach could be:
    // - eventManager can store a vector of RANDOM events associated with certain keywords or by checking NPC presence.
    // - For now, we trust that getRandomEvent() might filter by location in the future.

    // Already from the original code, we have some random events (Attack, Give, Message).
    // We can rely on eventManager.getRandomEvent() to occasionally pick from these.

    // The logic for endings (City 1 ending, Memory ending, Death ending) will be handled by the main loop checks:
    // - City 1 event triggers the final storyline.
    // - If player collects all memory items and returns to Main House, trigger the Memory Ending event.
    // - Death ending if player's health <= 0 at any point.

    std::cout << "Metadata initialized with story events, random events, items, and NPC placements.\n";
}