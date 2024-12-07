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

## Topics Covered
1. **Standard Library Containers (map, vector, etc.)**
   - **Implementation**: Used `vector` to store items in inventory and `map` for location connections.
   - **Code Reference**: `Location.cpp` (lines 13-15), `People.cpp` (lines 64-65).

2. **Custom Template Class**
   - **Implementation**: `EventContainer` template class to manage events.
   - **Code Reference**: `Event.cpp` (lines 11-33).

3. **Custom Namespace**
   - **Implementation**: Not implemented.

4. **Classes with a Constructor, Destructor, Assignment Operator**
   - **Implementation**: `People` class with constructor, destructor, and assignment operator.
   - **Code Reference**: `People.cpp` (lines 19-33).

5. **Lambda Functions**
   - **Implementation**: Used in event resolutions to define actions.
   - **Code Reference**: `metadata.cpp` (lines 13-17, 29-34).

6. **Exception Handling**
   - **Implementation**: Used for handling invalid input during player name entry.
   - **Code Reference**: `game.cpp` (lines 47-57).

7. **Inheritance**
   - **Implementation**: `Player` and `NPC` classes inherit from `People`.
   - **Code Reference**: `People.cpp` (lines 62-145).

8. **Virtual functions or Abstract Classes**
   - **Implementation**: `displayStats` is a virtual function in `People`.
   - **Code Reference**: `People.cpp` (lines 53-59, 94-105, 141-144).

9. **Hashing**
   - **Implementation**: Used for event retrieval in `EventManager`.
   - **Code Reference**: `Event.cpp` (lines 104-121).

10. **Sorting Algorithms**
    - **Implementation**: Sorting inventory by item ID and name.
    - **Code Reference**: `People.cpp` (lines 107-117).

## Code Organization
- **game.cpp**: Main game loop and initialization.
- **Event.cpp**: Event management and execution.
- **People.cpp**: Player and NPC classes with inventory management.
- **Item.cpp**: Item class definition.
- **Location.cpp**: Location and map management.
- **metadata.cpp**: Event creation functions.

