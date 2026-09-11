#ifndef AGROSENTINEL_THREAT_H
#define AGROSENTINEL_THREAT_H

#include <string>

class Orchard; // forward declaration: we only need to know Orchard EXISTS
                // here, not what is inside it. The real definition is
                // included in the .cpp files of the derived threat classes.

// ============================================================================
// Threat (ABSTRACT BASE CLASS)
// ----------------------------------------------------------------------------
// ABSTRACTION:
// "Threat" describes WHAT every threat must be able to do (attack an orchard,
// report its name, report its severity) without saying HOW each threat does
// it. The "how" is left to the derived classes (Scab, Aphids, Hailstorm).
//
// This class can never be created directly ("new Threat(...)" will not
// compile) because it contains a PURE VIRTUAL FUNCTION:
//
//     virtual void attackOrchard(Orchard& orchard) = 0;
//
// The "= 0" is what makes it "pure virtual". It means: "This class does not
// provide an implementation for this function. Any class that inherits from
// Threat MUST provide its own implementation, or it will also be abstract."
//
// A class that contains at least one pure virtual function is called an
// ABSTRACT CLASS.
//
// POLYMORPHISM (the key idea of this whole project):
// Because every threat "IS-A" Threat, we can store a Scab, an Aphids, or a
// Hailstorm object behind a single Threat pointer/reference, for example:
//
//     Threat* someThreat = ...;
//     someThreat->attackOrchard(orchard);
//
// At compile time, the compiler does not know which concrete threat this is.
// At RUNTIME, the program looks at the ACTUAL object being pointed to and
// calls the correct overridden version of attackOrchard(). This is called
// RUNTIME POLYMORPHISM or DYNAMIC DISPATCH, and it only works because the
// function is declared "virtual".
// ============================================================================
class Threat {
public:
    // A "virtual destructor" is required whenever a class is meant to be
    // used polymorphically (through base-class pointers). Without it,
    // deleting a derived object through a Threat* could skip the derived
    // class's cleanup code. "= default" tells the compiler to generate the
    // normal, do-nothing destructor body for us.
    virtual ~Threat() = default;

    // Pure virtual function: every derived threat MUST implement this.
    // This is the single entry point GameEngine uses to make a threat act,
    // WITHOUT knowing which concrete threat it is.
    virtual void attackOrchard(Orchard& orchard) = 0;

    // Every threat can describe itself. Also pure virtual.
    virtual std::string getName() const = 0;

    // A rough 1-10 "how dangerous is this threat right now" indicator.
    // Some threats (like Scab) get more severe the longer they are ignored,
    // so this is not a fixed constant - it is computed by each subclass.
    virtual int getSeverity() const = 0;

    // A short, one-line description used in menus and reports.
    virtual std::string getDescription() const = 0;
};

#endif // AGROSENTINEL_THREAT_H
