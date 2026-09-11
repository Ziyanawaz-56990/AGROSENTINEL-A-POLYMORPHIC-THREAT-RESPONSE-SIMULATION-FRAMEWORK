#ifndef AGROSENTINEL_APHIDS_H
#define AGROSENTINEL_APHIDS_H

#include "Threat.h"

// ============================================================================
// Aphids (small insects that feed on tree sap)
// ----------------------------------------------------------------------------
// BEHAVIOUR MODELLED HERE:
// Aphid colonies multiply quickly. Each attack represents a growing
// infestation: health damage grows modestly, but yield damage grows faster,
// because aphids mainly harm fruit/crop production rather than killing
// the tree outright.
// ============================================================================
class Aphids : public Threat {
private:
    int infestationLevel; // grows with each attack, models colony growth

public:
    Aphids();

    void attackOrchard(Orchard& orchard) override;
    std::string getName() const override;
    int getSeverity() const override;
    std::string getDescription() const override;
};

#endif // AGROSENTINEL_APHIDS_H
