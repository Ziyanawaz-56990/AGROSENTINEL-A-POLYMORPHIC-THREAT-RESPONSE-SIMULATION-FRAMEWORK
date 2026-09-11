#include "Aphids.h"
#include "Orchard.h"
#include <iostream>

Aphids::Aphids() : infestationLevel(0) {}

void Aphids::attackOrchard(Orchard& orchard) {
    infestationLevel++; // the colony grows every round it is left alone

    int healthDamage = 3 + infestationLevel;
    int yieldDamage = 5 + (infestationLevel * 2);

    std::cout << "  [Aphids] A colony of aphids swarms the branches...\n";
    orchard.takeDamage(healthDamage);
    orchard.reduceYield(yieldDamage);
    orchard.setLastThreatName(getName());

    std::cout << "  [Aphids] Health -" << healthDamage
              << ", Yield -" << yieldDamage << "% (infestation level " << infestationLevel << ")\n";
}

std::string Aphids::getName() const {
    return "Aphids";
}

int Aphids::getSeverity() const {
    int severity = 1 + infestationLevel;
    return severity > 10 ? 10 : severity;
}

std::string Aphids::getDescription() const {
    return "Insects that multiply quickly and mainly damage crop yield.";
}
