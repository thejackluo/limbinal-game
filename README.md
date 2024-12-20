# Limbinal Game
By Jack Luo

## Notes about the game
1. No Starting Class: Everyone has the same baseline stats and abilities.
2. Game Loop: Each decision runs through its loop (present choices → make decision → apply results → check state).
   Random events are integrated into this loop for variety.
3. Objects in the Game:
   - Player: Tracks stats (health, inventory, etc.).
   - NPCs: Can interact with the player.
   - Locations: Rooms, hallways, and areas where events happen.
   - Items: Usable objects in the game.
   - Events: Define interactions, branching storylines, and random occurrences.
4. Endings:
   - Determined by choices, stats, inventory, and random elements.

## Development Status
**Limbinal** is a work in progress.

## Topics Covered
1. **Standard Library Containers (map, vector, etc.)**
   - **Implementation**: Used `vector` to store items in inventory and `map` for location connections.
   - **Code Reference**: `Location.cpp` (startLine: 13, endLine: 15), `People.cpp` (startLine: 64, endLine: 65).

2. **Custom Template Class**
   - **Implementation**: `EventContainer` template class to manage events.
   - **Code Reference**: `Event.cpp` (startLine: 11, endLine: 33).

3. **Custom Namespace**
   - **Implementation**: Not implemented.

4. **Classes with a Constructor, Destructor, Assignment Operator**
   - **Implementation**: `People` class with constructor, destructor, and assignment operator.
   - **Code Reference**: `People.cpp` (startLine: 19, endLine: 33).

5. **Lambda Functions**
   - **Implementation**: Used in event resolutions to define actions.
   - **Code Reference**: `metadata.cpp` (startLine: 13, endLine: 17), `metadata.cpp` (startLine: 29, endLine: 34).

6. **Exception Handling**
   - **Implementation**: Used for handling invalid input during player name entry.
   - **Code Reference**: `game.cpp` (startLine: 47, endLine: 57).

7. **Inheritance**
   - **Implementation**: `Player` and `NPC` classes inherit from `People`.
   - **Code Reference**: `People.cpp` (startLine: 62, endLine: 145).

8. **Virtual functions or Abstract Classes**
   - **Implementation**: `displayStats` is a virtual function in `People`.
   - **Code Reference**: `People.cpp` (startLine: 53, endLine: 59), `People.cpp` (startLine: 94, endLine: 105), `People.cpp` (startLine: 141, endLine: 144).

9. **Hashing**
   - **Implementation**: Used for event retrieval in `EventManager`.
   - **Code Reference**: `Event.cpp` (startLine: 104, endLine: 121).

10. **Sorting Algorithms**
    - **Implementation**: Sorting inventory by item ID and name.
    - **Code Reference**: `People.cpp` (startLine: 107, endLine: 117).

## Code Organization
- **game.cpp**: Main game loop and initialization.
- **Event.cpp**: Event management and execution.
- **People.cpp**: Player and NPC classes with inventory management.
- **Item.cpp**: Item class definition.
- **Location.cpp**: Location and map management.
- **metadata.cpp**: Event creation functions.

## Story Synopsis

### Limbinal: A Journey Through the Virtual and Real

In the year 2030, the world has become a place where virtual reality and the real world intertwine in unexpected ways. The protagonist, Ryohashi, finds himself trapped in a virtual world known as Limbo, a place that reflects the deepest desires and fears of its participants. This world is eerily familiar yet unsettling, with endless streets and static trees, devoid of life and sound.

#### Characters
- **Ryohashi**: The main protagonist, a socially reserved individual with a passion for technology and philosophy. Trapped in Limbo by his former friend Kakkeda, Ryohashi seeks to uncover the truth and save his friends, especially Yumi, who is his beacon of light.
- **Yumi**: The deuteragonist, a carefree girl fascinated by astrology. She mysteriously disappeared from Ryohashi's life and is now trapped in Limbo, sending distress messages to the real world.
- **Kakkeda**: The antagonist, a perfectionist with a love for VR technology. He co-founded the VR system with Ryohashi but trapped him in Limbo due to ideological differences.
- **Hiroto**: A friend of Yumi, realistic and paranoid, who supports Yumi's stance on Limbo and navigates a world under surveillance.
- **Suzumi**: A mysterious girl with a golden ponytail, part of Ryohashi's journey.

## Sources
- https://patorjk.com/software/taag/#p=display&f=Big&t=Limbinal
- Code Org GPT: https://chatgpt.com/share/6755494d-2d18-800f-b916-9732e534a59d
- GUI GPT: https://chatgpt.com/share/67554964-0d20-800f-aaf9-d91f98b1f0e7