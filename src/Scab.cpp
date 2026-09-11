#include "Scab.h"
#include "Orchard.h"
#include <iostream>

Scab::Scab() : spreadLevel(0) {}

void Scab::attackOrchard(Orchard& orchard) {
    spreadLevel++; // Scab gets worse the more it is left unchecked

    int healthDamage = 5 + (spreadLevel * 2);
    int yieldDamage = 3 + spreadLevel;

    std::cout << "  [Scab] Fungal spores spread across the leaves...\n";
    orchard.takeDamage(healthDamage);
    orchard.reduceYield(yieldDamage);
    orchard.setLastThreatName(getName());

    std::cout << "  [Scab] Health -" << healthDamage
              << ", Yield -" << yieldDamage << "% (spread level " << spreadLevel << ")\n";
}

std::string Scab::getName() const {
    return "Scab";
}

int Scab::getSeverity() const {
    // Severity grows with how many times Scab has already attacked,
    // capped at 10 so it fits a simple 1-10 scale.
    int severity = 2 + spreadLevel;
    return severity > 10 ? 10 : severity;
}

std::string Scab::getDescription() const {
    return "A fungal disease that spreads gradually and worsens over time.";
}
