#include "Pruning.h"
#include "Orchard.h"
#include <iostream>

void Pruning::apply(Orchard& orchard) {
    int healthGain = 10;
    int yieldGain = 8;

    std::cout << "  [Pruning] Cutting away damaged branches and leaves...\n";

    if (orchard.getLastThreatName() == "Aphids") {
        healthGain += 5;
        yieldGain += 7;
        std::cout << "  [Pruning] Removes infested branches - strong vs Aphids!\n";
    }

    orchard.restoreHealth(healthGain);
    orchard.increaseYield(yieldGain);

    std::cout << "  [Pruning] Health +" << healthGain
              << ", Yield +" << yieldGain << "%\n";
}

std::string Pruning::getName() const {
    return "Pruning";
}

std::string Pruning::getDescription() const {
    return "Removes damaged growth; a general-purpose defense, strong vs Aphids.";
}
