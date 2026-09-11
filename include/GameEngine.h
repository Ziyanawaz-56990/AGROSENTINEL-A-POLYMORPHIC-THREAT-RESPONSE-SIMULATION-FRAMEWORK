#ifndef AGROSENTINEL_GAMEENGINE_H
#define AGROSENTINEL_GAMEENGINE_H

#include <vector>
#include <memory>
#include <string>
#include <random>

#include "Orchard.h"
#include "Threat.h"
#include "DefenseAction.h"

// One row of the event log: what happened during a single round.
// This is plain data (no behaviour), used both for the console report
// and for exporting to JSON for the visualization layer.
struct EventRecord {
    int round;
    std::string threatName;
    int threatSeverity;
    int healthBeforeThreat;
    int healthAfterThreat;
    int yieldBeforeThreat;
    int yieldAfterThreat;
    std::string defenseName;
    int healthAfterDefense;
    int yieldAfterDefense;
};

// ============================================================================
// GameEngine
// ----------------------------------------------------------------------------
// This class DRIVES the simulation. It is the piece that ties everything
// else together, but the key design goal is:
//
//     GameEngine does NOT need to know anything about the concrete threat
//     or defense classes. It only ever talks to them through the abstract
//     Threat* / DefenseAction* interfaces.
//
// It stores its threats and defenses using std::unique_ptr, a "smart
// pointer". A std::unique_ptr<Threat> owns exactly one Threat object and
// automatically deletes it when the unique_ptr itself is destroyed (for
// example, when the vector holding it is destroyed). This means we get the
// benefits of dynamic polymorphism (storing different derived types behind
// a common base pointer) WITHOUT manually writing "delete" anywhere and
// WITHOUT risking memory leaks. This pattern is called RAII (Resource
// Acquisition Is Initialization): the object's lifetime is tied to a
// variable's scope, and cleanup happens automatically.
// ============================================================================
class GameEngine {
private:
    Orchard orchard;

    // The "arsenal" of possible threats and defenses. Each is a smart
    // pointer to an abstract base class, but each actually points at a
    // concrete object (Scab, Aphids, Hailstorm, ...). GameEngine only calls
    // the base-class interface on them.
    std::vector<std::unique_ptr<Threat>> threatPool;
    std::vector<std::unique_ptr<DefenseAction>> defensePool;

    std::vector<EventRecord> history;

    int totalRounds;
    std::mt19937 rng; // a random number generator (Mersenne Twister engine)

    // Internal helpers
    Threat& pickRandomThreat();
    DefenseAction& pickDefenseByChoice(int choiceNumber);
    void printDefenseMenu() const;
    int promptDefenseChoice() const;

public:
    GameEngine(int rounds = 5, unsigned int seed = std::random_device{}());

    // Runs the full interactive simulation from start to finish.
    void run();

    // Prints the final statistics/report after all rounds are complete.
    void printFinalReport() const;

    // Writes the full event history + final state to a JSON file so the
    // HTML/JS visualization can read it and draw charts.
    void exportJSON(const std::string& path) const;
};

#endif // AGROSENTINEL_GAMEENGINE_H
