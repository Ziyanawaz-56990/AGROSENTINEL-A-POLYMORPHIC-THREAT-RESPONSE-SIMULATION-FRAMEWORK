#ifndef AGROSENTINEL_SCAB_H
#define AGROSENTINEL_SCAB_H

#include "Threat.h"

// ============================================================================
// Scab (a fungal disease of apple/pear trees)
// ----------------------------------------------------------------------------
// INHERITANCE:
// "class Scab : public Threat" means "Scab IS-A Threat". Scab automatically
// gets the public interface declared in Threat (attackOrchard, getName,
// getSeverity, getDescription) and is REQUIRED to implement all of the pure
// virtual ones, or it would remain abstract too.
//
// BEHAVIOUR MODELLED HERE:
// Scab spreads gradually. Each time it attacks, it becomes slightly worse
// than the previous attack (spreadLevel increases), causing steadily
// growing damage to health and yield. This models how fungal disease
// worsens the longer it goes untreated.
// ============================================================================
class Scab : public Threat {
private:
    int spreadLevel; // increases every time Scab attacks; models disease spread

public:
    Scab();

    // "override" tells the compiler: "I am intentionally providing my own
    // version of a virtual function declared in the base class." If we
    // misspell the function name or get the signature wrong, the compiler
    // will now give us an error instead of silently creating an unrelated
    // new function. It is good practice to always write "override".
    void attackOrchard(Orchard& orchard) override;
    std::string getName() const override;
    int getSeverity() const override;
    std::string getDescription() const override;
};

#endif // AGROSENTINEL_SCAB_H
