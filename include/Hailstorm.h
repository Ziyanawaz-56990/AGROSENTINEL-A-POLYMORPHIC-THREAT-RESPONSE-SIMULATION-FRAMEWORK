#ifndef AGROSENTINEL_HAILSTORM_H
#define AGROSENTINEL_HAILSTORM_H

#include "Threat.h"

// ============================================================================
// Hailstorm (a sudden weather event)
// ----------------------------------------------------------------------------
// BEHAVIOUR MODELLED HERE:
// Unlike Scab and Aphids, a hailstorm does not build up over time - it is a
// single sudden, heavy blow. It always deals large, fairly consistent
// damage. It has no "memory" between attacks (no growing internal level),
// which is itself an important demonstration of polymorphism: different
// Threat subclasses can have COMPLETELY different internal designs, yet
// they are all used through the exact same Threat interface.
// ============================================================================
class Hailstorm : public Threat {
public:
    Hailstorm() = default;

    void attackOrchard(Orchard& orchard) override;
    std::string getName() const override;
    int getSeverity() const override;
    std::string getDescription() const override;
};

#endif // AGROSENTINEL_HAILSTORM_H
