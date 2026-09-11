#include "FungicideSpray.h"
#include "Orchard.h"
#include <iostream>

void FungicideSpray::apply(Orchard& orchard) {
    int healthGain = 15;
    int yieldGain = 5;

    std::cout << "  [FungicideSpray] Spraying fungicide across the orchard...\n";

    if (orchard.getLastThreatName() == "Scab") {
        healthGain += 10;
        yieldGain += 5;
        std::cout << "  [FungicideSpray] Highly effective against Scab!\n";
    }

    orchard.restoreHealth(healthGain);
    orchard.increaseYield(yieldGain);

    std::cout << "  [FungicideSpray] Health +" << healthGain
              << ", Yield +" << yieldGain << "%\n";
}

std::string FungicideSpray::getName() const {
    return "Fungicide Spray";
}

std::string FungicideSpray::getDescription() const {
    return "A chemical treatment, especially effective against Scab.";
}
