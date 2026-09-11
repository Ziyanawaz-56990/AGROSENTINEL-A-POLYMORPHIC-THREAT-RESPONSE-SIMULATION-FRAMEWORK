#include "GameEngine.h"
#include "Scab.h"
#include "Aphids.h"
#include "Hailstorm.h"
#include "FungicideSpray.h"
#include "Pruning.h"
#include "NetCovering.h"

#include <iostream>
#include <fstream>
#include <limits>

GameEngine::GameEngine(int rounds, unsigned int seed)
    : orchard(100, 100, 200),
      totalRounds(rounds),
      rng(seed) {

    // Build the arsenal of threats ONCE. Each unique_ptr<Threat> owns one
    // concrete object. Because Scab/Aphids track internal state (spread
    // level / infestation level) between attacks, we deliberately keep the
    // SAME objects across rounds instead of creating a new one every time -
    // this is what allows Scab and Aphids to realistically escalate.
    threatPool.push_back(std::make_unique<Scab>());
    threatPool.push_back(std::make_unique<Aphids>());
    threatPool.push_back(std::make_unique<Hailstorm>());

    // Build the arsenal of defenses ONCE, the same way.
    defensePool.push_back(std::make_unique<FungicideSpray>());
    defensePool.push_back(std::make_unique<Pruning>());
    defensePool.push_back(std::make_unique<NetCovering>());
}

Threat& GameEngine::pickRandomThreat() {
    std::uniform_int_distribution<size_t> dist(0, threatPool.size() - 1);
    size_t index = dist(rng);

    // -------------------------------------------------------------------
    // THIS is where runtime polymorphism happens for threats.
    // "threatPool[index]" has the STATIC (compile-time) type
    // std::unique_ptr<Threat>. The compiler has no idea, while compiling
    // this file, whether it holds a Scab, Aphids, or Hailstorm.
    //
    // Later, when GameEngine::run() calls chosenThreat.attackOrchard(...),
    // the program looks at the object's ACTUAL (runtime) type through the
    // virtual function table and calls the matching override. That lookup
    // happens every single time, based on what is really stored there -
    // that is dynamic dispatch.
    // -------------------------------------------------------------------
    return *threatPool[index];
}

DefenseAction& GameEngine::pickDefenseByChoice(int choiceNumber) {
    // choiceNumber is 1-based (matches the printed menu)
    size_t index = static_cast<size_t>(choiceNumber - 1);
    return *defensePool[index];
}

void GameEngine::printDefenseMenu() const {
    std::cout << "\nSelect a defense action:\n";
    for (size_t i = 0; i < defensePool.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << defensePool[i]->getName()
                  << " - " << defensePool[i]->getDescription() << "\n";
    }
    std::cout << "Enter choice (1-" << defensePool.size() << "): ";
}

int GameEngine::promptDefenseChoice() const {
    int choice = 0;
    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // reset the error state on the input stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid number: ";
            continue;
        }

        if (choice < 1 || choice > static_cast<int>(defensePool.size())) {
            std::cout << "Please choose a number between 1 and "
                      << defensePool.size() << ": ";
            continue;
        }

        return choice;
    }
}

void GameEngine::run() {
    std::cout << "========================================\n";
    std::cout << "            AGROSENTINEL\n";
    std::cout << "Polymorphic Threat Response Simulation\n";
    std::cout << "========================================\n\n";

    std::cout << "Initial Orchard Status\n";
    orchard.printStatus();

    for (int round = 1; round <= totalRounds; ++round) {
        std::cout << "\n========== Round " << round << " / " << totalRounds << " ==========\n";

        // 1. A threat is chosen and attacks. GameEngine only sees a Threat&.
        Threat& activeThreat = pickRandomThreat();

        int displayedSeverity = activeThreat.getSeverity();
        std::cout << "\nThreat detected: " << activeThreat.getName()
                  << " (severity " << displayedSeverity << "/10)\n";
        std::cout << activeThreat.getDescription() << "\n\n";

        int healthBefore = orchard.getHealth();
        int yieldBefore = orchard.getYield();

        // ---- POLYMORPHIC CALL #1 ----
        // GameEngine does not know or care whether this is Scab, Aphids,
        // or Hailstorm. It just calls the shared interface.
        activeThreat.attackOrchard(orchard);

        int healthAfterThreat = orchard.getHealth();
        int yieldAfterThreat = orchard.getYield();

        std::cout << "\n";
        orchard.printStatus();

        if (orchard.isDestroyed()) {
            std::cout << "\nThe orchard has been destroyed! Simulation ending early.\n";
            history.push_back({round, activeThreat.getName(), displayedSeverity,
                                healthBefore, healthAfterThreat, yieldBefore, yieldAfterThreat,
                                "None", healthAfterThreat, yieldAfterThreat});
            break;
        }

        // 2. The user selects a defense action.
        printDefenseMenu();
        int choice = promptDefenseChoice();
        DefenseAction& chosenDefense = pickDefenseByChoice(choice);

        std::cout << "\n";
        // ---- POLYMORPHIC CALL #2 ----
        // Same idea, on the defense side: GameEngine does not know if this
        // is FungicideSpray, Pruning, or NetCovering.
        chosenDefense.apply(orchard);

        int healthAfterDefense = orchard.getHealth();
        int yieldAfterDefense = orchard.getYield();

        std::cout << "\n";
        orchard.printStatus();

        history.push_back({round, activeThreat.getName(), displayedSeverity,
                            healthBefore, healthAfterThreat, yieldBefore, yieldAfterThreat,
                            chosenDefense.getName(), healthAfterDefense, yieldAfterDefense});

        orchard.advanceRound();
    }

    printFinalReport();
    exportJSON("visualization/data/simulation_log.json");
}

void GameEngine::printFinalReport() const {
    std::cout << "\n========================================\n";
    std::cout << "            FINAL REPORT\n";
    std::cout << "========================================\n";
    std::cout << "Rounds completed : " << history.size() << " / " << totalRounds << "\n";
    std::cout << "Final Health     : " << orchard.getHealth() << " / 100\n";
    std::cout << "Final Yield      : " << orchard.getYield() << "%\n";
    std::cout << "Trees remaining  : " << orchard.getTreeCount() << "\n";

    std::string verdict;
    if (orchard.isDestroyed()) {
        verdict = "The orchard was lost. Try different defense choices next time.";
    } else if (orchard.getHealth() >= 70 && orchard.getYield() >= 70) {
        verdict = "Excellent management! The orchard is thriving.";
    } else if (orchard.getHealth() >= 40) {
        verdict = "The orchard survived, but took significant damage.";
    } else {
        verdict = "The orchard barely survived. Consider a more careful strategy.";
    }
    std::cout << "Verdict          : " << verdict << "\n";

    std::cout << "\nEvent Log:\n";
    for (const auto& e : history) {
        std::cout << "  Round " << e.round << ": " << e.threatName
                  << " (sev " << e.threatSeverity << ") -> health "
                  << e.healthBeforeThreat << "->" << e.healthAfterThreat
                  << ", yield " << e.yieldBeforeThreat << "->" << e.yieldAfterThreat;
        if (e.defenseName != "None") {
            std::cout << " | defended with " << e.defenseName
                      << " -> health " << e.healthAfterThreat << "->" << e.healthAfterDefense
                      << ", yield " << e.yieldAfterThreat << "->" << e.yieldAfterDefense;
        }
        std::cout << "\n";
    }
    std::cout << "========================================\n";
}

void GameEngine::exportJSON(const std::string& path) const {
    std::ofstream out(path);
    if (!out.is_open()) {
        std::cerr << "Warning: could not write visualization data to " << path << "\n";
        return;
    }

    out << "{\n";
    out << "  \"finalHealth\": " << orchard.getHealth() << ",\n";
    out << "  \"finalYield\": " << orchard.getYield() << ",\n";
    out << "  \"treeCount\": " << orchard.getTreeCount() << ",\n";
    out << "  \"totalRounds\": " << totalRounds << ",\n";
    out << "  \"roundsCompleted\": " << history.size() << ",\n";
    out << "  \"destroyed\": " << (orchard.isDestroyed() ? "true" : "false") << ",\n";
    out << "  \"events\": [\n";

    for (size_t i = 0; i < history.size(); ++i) {
        const auto& e = history[i];
        out << "    {\n";
        out << "      \"round\": " << e.round << ",\n";
        out << "      \"threat\": \"" << e.threatName << "\",\n";
        out << "      \"severity\": " << e.threatSeverity << ",\n";
        out << "      \"healthBeforeThreat\": " << e.healthBeforeThreat << ",\n";
        out << "      \"healthAfterThreat\": " << e.healthAfterThreat << ",\n";
        out << "      \"yieldBeforeThreat\": " << e.yieldBeforeThreat << ",\n";
        out << "      \"yieldAfterThreat\": " << e.yieldAfterThreat << ",\n";
        out << "      \"defense\": \"" << e.defenseName << "\",\n";
        out << "      \"healthAfterDefense\": " << e.healthAfterDefense << ",\n";
        out << "      \"yieldAfterDefense\": " << e.yieldAfterDefense << "\n";
        out << "    }" << (i + 1 < history.size() ? "," : "") << "\n";
    }

    out << "  ]\n";
    out << "}\n";

    std::cout << "\n(Visualization data written to " << path << ")\n";
}
