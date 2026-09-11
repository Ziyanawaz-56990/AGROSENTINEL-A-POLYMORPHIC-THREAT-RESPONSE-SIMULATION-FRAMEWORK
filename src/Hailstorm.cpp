#include "Hailstorm.h"
#include "Orchard.h"
#include <iostream>

void Hailstorm::attackOrchard(Orchard& orchard) {
    const int healthDamage = 25;
    const int yieldDamage = 15;

    std::cout << "  [Hailstorm] Heavy hail crashes down on the orchard...\n";
    orchard.takeDamage(healthDamage);
    orchard.reduceYield(yieldDamage);
    orchard.setLastThreatName(getName());

    std::cout << "  [Hailstorm] Health -" << healthDamage
              << ", Yield -" << yieldDamage << "% (sudden impact)\n";
}

std::string Hailstorm::getName() const {
    return "Hailstorm";
}

int Hailstorm::getSeverity() const {
    return 8; // always dangerous, does not build up like a disease/infestation
}

std::string Hailstorm::getDescription() const {
    return "A sudden, heavy weather event that deals immediate damage.";
}
