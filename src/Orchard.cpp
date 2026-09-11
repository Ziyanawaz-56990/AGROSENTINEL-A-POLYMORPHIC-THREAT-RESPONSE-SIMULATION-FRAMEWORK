#include "Orchard.h"
#include <iostream>
#include <iomanip>

int Orchard::clamp(int value, int minValue, int maxValue) {
    if (value < minValue) return minValue;
    if (value > maxValue) return maxValue;
    return value;
}

Orchard::Orchard(int initialHealth, int initialYield, int trees)
    : health(clamp(initialHealth, 0, 100)),
      yieldPercent(clamp(initialYield, 0, 100)),
      treeCount(trees),
      currentRound(1),
      lastThreatName("None") {
}

void Orchard::takeDamage(int amount) {
    if (amount < 0) amount = 0; // damage can never "heal" through this method
    health = clamp(health - amount, 0, 100);
}

void Orchard::restoreHealth(int amount) {
    if (amount < 0) amount = 0; // this method can only heal, never hurt
    health = clamp(health + amount, 0, 100);
}

void Orchard::reduceYield(int amount) {
    if (amount < 0) amount = 0;
    yieldPercent = clamp(yieldPercent - amount, 0, 100);
}

void Orchard::increaseYield(int amount) {
    if (amount < 0) amount = 0;
    yieldPercent = clamp(yieldPercent + amount, 0, 100);
}

void Orchard::setLastThreatName(const std::string& name) {
    lastThreatName = name;
}

void Orchard::advanceRound() {
    currentRound++;
}

int Orchard::getHealth() const { return health; }
int Orchard::getYield() const { return yieldPercent; }
int Orchard::getTreeCount() const { return treeCount; }
int Orchard::getRound() const { return currentRound; }
std::string Orchard::getLastThreatName() const { return lastThreatName; }

bool Orchard::isDestroyed() const {
    return health <= 0;
}

void Orchard::printStatus() const {
    std::cout << "----------------------------------------\n";
    std::cout << " Orchard Status (Round " << currentRound << ")\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  Health : " << std::setw(3) << health << " / 100\n";
    std::cout << "  Yield  : " << std::setw(3) << yieldPercent << "%\n";
    std::cout << "  Trees  : " << treeCount << "\n";
    std::cout << "----------------------------------------\n";
}
