# OOP Concepts in AgroSentinel

This document explains the four pillars of Object-Oriented Programming
(OOP) using the **actual classes** in this project. If you only read one
document before your viva, read this one.

## 1. Abstraction

**Abstract class:** a class that defines *what* something must do, without
saying *how*. It cannot be instantiated directly.

**Pure virtual function:** a virtual function written with `= 0` at the
end, e.g. `virtual void attackOrchard(Orchard& orchard) = 0;`. It has no
body in the base class — every derived class is *forced* to provide one.

In this project:

- `Threat` (`include/Threat.h`) is abstract. It declares
  `attackOrchard()`, `getName()`, `getSeverity()`, and `getDescription()`
  as pure virtual. You cannot write `Threat t;` anywhere in the code —
  it will not compile, because the compiler knows the class is
  incomplete on purpose.
- `DefenseAction` (`include/DefenseAction.h`) is abstract for the same
  reason, with `apply()`, `getName()`, and `getDescription()`.

**Why does GameEngine not need implementation details?**
`GameEngine` only ever holds `Threat*`/`std::unique_ptr<Threat>` and
`DefenseAction*`/`std::unique_ptr<DefenseAction>` variables. It calls
`attackOrchard()` and `apply()` on them. It never needs to know whether
the real object is a `Scab` or a `Hailstorm` — the abstraction hides
that detail completely. This is what makes it trivial to add a fourth
threat later without touching `GameEngine` at all.

## 2. Inheritance

```
Threat
├── Scab
├── Aphids
└── Hailstorm

DefenseAction
├── FungicideSpray
├── Pruning
└── NetCovering
```

Every derived class writes `class Scab : public Threat`. This means
"Scab **is a** Threat". Scab automatically has the same public interface
as Threat (so it can be stored and called the same way), but it
**specializes** the behaviour: it adds a private `spreadLevel` member
and provides its own version of `attackOrchard()` that makes the disease
worsen over time. `Aphids` and `Hailstorm` specialize the interface in
their own, very different ways (see `docs/simulation.md`).

The same pattern repeats for `DefenseAction` → `FungicideSpray`,
`Pruning`, `NetCovering`.

## 3. Polymorphism (the most important section)

**Runtime polymorphism:** when the program decides, *while it is
running*, which overridden function to call — based on the real object
behind a base-class pointer/reference, not on the type written in the
source code.

Here is the exact mechanism, taken from `GameEngine::pickRandomThreat()`
and `GameEngine::run()`:

```cpp
std::vector<std::unique_ptr<Threat>> threatPool; // holds Scab, Aphids, Hailstorm

Threat& activeThreat = pickRandomThreat(); // returns a Threat&, real type unknown here
activeThreat.attackOrchard(orchard);       // <-- polymorphic call
```

At compile time, `activeThreat` has type `Threat&`. The compiler cannot
know in advance whether this will be a `Scab`, `Aphids`, or `Hailstorm`
— that is decided by a random number at runtime. Because
`attackOrchard()` is declared `virtual` in `Threat`, the compiler
generates code that looks up the *actual* object's version of the
function through a **virtual table (vtable)** every time the call
happens. This lookup is what "dynamic dispatch" means.

**What if `virtual` were removed?**
If `attackOrchard()` were not virtual, the compiler would use **static
binding**: it would always call `Threat::attackOrchard()` based on the
*declared* type of the reference (`Threat&`), completely ignoring the
real object. Since `Threat::attackOrchard()` doesn't even have a body
(it's pure virtual), this would not compile at all in our case — but
even in a version where the base class *did* have a body, removing
`virtual` would silently call the wrong (base class) behaviour every
time, breaking the whole simulation. This is exactly why `virtual` is
essential here, not decorative.

**Why this proves genuine runtime polymorphism (and not fake
polymorphism through `if`/`switch` on a type string):**
Nowhere in `GameEngine` does the code say
`if (activeThreat.getName() == "Scab") { ... }` to decide *how to
attack*. The attacking behaviour is entirely decided by which override
runs — there is exactly one call site (`activeThreat.attackOrchard(orchard)`)
for three completely different behaviours.

(Note: `FungicideSpray`/`Pruning`/`NetCovering` do read
`orchard.getLastThreatName()` to decide on a *bonus* — but that is
reading plain data the `Orchard` already stores, not switching on a
`Threat` object's type or casting it. The polymorphic dispatch for
"which threat attacked" already happened earlier, through
`attackOrchard()`.)

## 4. Encapsulation

In `include/Orchard.h`, all state (`health`, `yieldPercent`, `treeCount`,
`currentRound`, `lastThreatName`) is `private`. Code outside the class —
including `GameEngine`, `Scab`, `FungicideSpray`, everything — **cannot**
write `orchard.health = 9999;`. It simply will not compile.

Instead, external code must go through public methods:

```cpp
orchard.takeDamage(25);     // internally clamps health to [0, 100]
orchard.restoreHealth(15);  // internally clamps health to [0, 100]
orchard.getHealth();        // read-only, cannot be used to set anything
```

Because these methods are the *only* way in, `Orchard` can guarantee
its own rules ("health never goes below 0 or above 100", "damage
amounts are never negative") no matter what any other class does. The
tests in `tests/test_main.cpp` (`test_orchard_encapsulation_via_negative_inputs`)
specifically check this.
