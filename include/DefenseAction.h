#ifndef AGROSENTINEL_DEFENSEACTION_H
#define AGROSENTINEL_DEFENSEACTION_H

#include <string>

class Orchard; // forward declaration, same reasoning as in Threat.h

// ============================================================================
// DefenseAction (ABSTRACT BASE CLASS)
// ----------------------------------------------------------------------------
// This mirrors Threat, but for the player's responses. Every defense
// action must be able to "apply" itself to the orchard, describe itself,
// and report a rough effectiveness rating. Just like Threat, this class
// has pure virtual functions and therefore cannot be instantiated directly.
//
// GameEngine will call:
//     defense->apply(orchard);
// through a DefenseAction pointer, without needing to know whether the
// real object is a FungicideSpray, a Pruning, or a NetCovering. This is the
// same runtime polymorphism idea as Threat, applied to the "response" side
// of the simulation.
// ============================================================================
class DefenseAction {
public:
    virtual ~DefenseAction() = default;

    virtual void apply(Orchard& orchard) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
};

#endif // AGROSENTINEL_DEFENSEACTION_H
