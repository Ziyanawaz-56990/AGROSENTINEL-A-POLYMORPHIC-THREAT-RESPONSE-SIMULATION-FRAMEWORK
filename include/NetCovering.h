#ifndef AGROSENTINEL_NETCOVERING_H
#define AGROSENTINEL_NETCOVERING_H

#include "DefenseAction.h"

// ============================================================================
// NetCovering
// ----------------------------------------------------------------------------
// Physical protective netting stretched over the orchard. It gives modest
// general protection, but is by far the best option against sudden
// physical damage like a Hailstorm, since the net directly blocks hail
// from reaching the trees and fruit.
// ============================================================================
class NetCovering : public DefenseAction {
public:
    NetCovering() = default;

    void apply(Orchard& orchard) override;
    std::string getName() const override;
    std::string getDescription() const override;
};

#endif // AGROSENTINEL_NETCOVERING_H
