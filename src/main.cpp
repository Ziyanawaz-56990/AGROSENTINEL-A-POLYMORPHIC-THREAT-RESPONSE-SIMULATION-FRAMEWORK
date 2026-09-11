#include "GameEngine.h"

// ============================================================================
// main.cpp
// ----------------------------------------------------------------------------
// The entry point of the whole program. It intentionally does almost
// nothing except create a GameEngine and tell it to run. All real logic
// lives inside GameEngine and the class hierarchies it coordinates - this
// keeps main() simple and readable.
// ============================================================================
int main() {
    const int NUMBER_OF_ROUNDS = 5;

    GameEngine engine(NUMBER_OF_ROUNDS);
    engine.run();

    return 0;
}
