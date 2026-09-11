#ifndef AGROSENTINEL_FUNGICIDESPRAY_H
#define AGROSENTINEL_FUNGICIDESPRAY_H

#include "DefenseAction.h"

// ============================================================================
// FungicideSpray
// ----------------------------------------------------------------------------
// A chemical treatment that is especially good against fungal disease
// (Scab). It checks Orchard::getLastThreatName() - a piece of DATA stored
// in the orchard - to decide whether to give a bonus. This is not the same
// thing as "checking the threat's type"; the DefenseAction never looks at
// a Threat object or casts anything. It only reads a plain string that the
// Orchard already stores. The polymorphic dispatch for "which threat
// attacked" already happened earlier, inside GameEngine, through
// Threat::attackOrchard().
// ============================================================================
class FungicideSpray : public DefenseAction {
public:
    FungicideSpray() = default;

    void apply(Orchard& orchard) override;
    std::string getName() const override;
    std::string getDescription() const override;
};

#endif // AGROSENTINEL_FUNGICIDESPRAY_H
