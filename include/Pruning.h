#ifndef AGROSENTINEL_PRUNING_H
#define AGROSENTINEL_PRUNING_H

#include "DefenseAction.h"

// ============================================================================
// Pruning
// ----------------------------------------------------------------------------
// Cutting away damaged branches/leaves. This is a general-purpose defense
// that improves overall orchard condition, and is particularly good at
// controlling Aphids because removing infested branches removes the
// insects along with them.
// ============================================================================
class Pruning : public DefenseAction {
public:
    Pruning() = default;

    void apply(Orchard& orchard) override;
    std::string getName() const override;
    std::string getDescription() const override;
};

#endif // AGROSENTINEL_PRUNING_H
