#ifndef AGROSENTINEL_ORCHARD_H
#define AGROSENTINEL_ORCHARD_H

#include <string>

// ============================================================================
// Orchard
// ----------------------------------------------------------------------------
// This class represents the orchard being simulated: its health, its crop
// yield, how many trees it has, and which round of the simulation we are in.
//
// ENCAPSULATION:
// All of the important data (health, yield, treeCount, round, lastThreatName)
// is declared "private". That means code outside this class CANNOT touch
// these variables directly (e.g. orchard.health = -999; will not compile).
//
// Instead, outside code must go through the public methods below
// (takeDamage, restoreHealth, reduceYield, increaseYield, getHealth, ...).
// Those methods make sure the data always stays valid - for example, health
// can never go below 0 or above 100, because the methods clamp the values.
//
// This is the essence of encapsulation: hiding internal state and only
// allowing controlled, safe modification through a public interface.
// ============================================================================
class Orchard {
private:
    int health;              // 0-100, orchard's overall health
    int yieldPercent;         // 0-100, percentage of a full crop yield
    int treeCount;            // number of trees in the orchard
    int currentRound;         // which round of simulation we are on
    std::string lastThreatName; // name of the most recent threat that attacked

    // A small private helper that keeps a value inside the 0-100 range.
    // "static" here just means this helper does not need an Orchard object
    // to be called; it is a utility function that belongs to the class.
    static int clamp(int value, int minValue, int maxValue);

public:
    // Constructor: runs automatically when an Orchard object is created.
    // It sets up the starting values of the simulation.
    explicit Orchard(int initialHealth = 100, int initialYield = 100, int trees = 200);

    // ---- Controlled mutators (the ONLY way to change orchard state) ----
    void takeDamage(int amount);      // used by threats to hurt the orchard
    void restoreHealth(int amount);   // used by defenses to heal the orchard
    void reduceYield(int amount);     // used by threats to hurt crop yield
    void increaseYield(int amount);   // used by defenses to help crop yield

    void setLastThreatName(const std::string& name);
    void advanceRound();

    // ---- Read-only accessors (safe, cannot modify state) ----
    int getHealth() const;
    int getYield() const;
    int getTreeCount() const;
    int getRound() const;
    std::string getLastThreatName() const;

    bool isDestroyed() const; // true once health has dropped to 0

    // Prints a clean status block to the console.
    void printStatus() const;
};

#endif // AGROSENTINEL_ORCHARD_H
