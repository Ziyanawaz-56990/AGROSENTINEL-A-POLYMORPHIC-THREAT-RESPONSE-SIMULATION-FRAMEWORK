#include "NetCovering.h"
#include "Orchard.h"
#include <iostream>

void NetCovering::apply(Orchard& orchard) {
    int healthGain = 8;
    int yieldGain = 3;

    std::cout << "  [NetCovering] Stretching protective netting over the trees...\n";

    if (orchard.getLastThreatName() == "Hailstorm") {
        healthGain += 20;
        yieldGain += 10;
        std::cout << "  [NetCovering] Blocks hail directly - excellent vs Hailstorm!\n";
    }

    orchard.restoreHealth(healthGain);
    orchard.increaseYield(yieldGain);

    std::cout << "  [NetCovering] Health +" << healthGain
              << ", Yield +" << yieldGain << "%\n";
}

std::string NetCovering::getName() const {
    return "Net Covering";
}

std::string NetCovering::getDescription() const {
    return "Physical netting; a general shield, excellent against Hailstorm.";
}
