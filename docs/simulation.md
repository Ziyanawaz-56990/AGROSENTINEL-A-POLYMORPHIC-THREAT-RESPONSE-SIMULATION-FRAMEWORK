# Simulation Walkthrough

This document walks through what actually happens, step by step, so you
can narrate it confidently in a demo.

## Setup

`main.cpp` creates one `GameEngine` configured for 5 rounds. The
`GameEngine` constructor builds:

- A `threatPool` containing one `Scab`, one `Aphids`, one `Hailstorm`
  (each wrapped in `std::unique_ptr<Threat>`).
- A `defensePool` containing one `FungicideSpray`, one `Pruning`, one
  `NetCovering` (each wrapped in `std::unique_ptr<DefenseAction>`).
- An `Orchard` starting at health 100, yield 100%, 200 trees.

## A single round, in detail

1. **A threat is chosen.** `pickRandomThreat()` rolls a random index
   0-2 and returns a reference to that pool entry — for example,
   entry 0, the `Scab` object.
2. **The threat attacks.** `activeThreat.attackOrchard(orchard)` is
   called. Because `activeThreat` is a `Threat&` but really refers to
   the `Scab` object, C++'s virtual dispatch mechanism runs
   `Scab::attackOrchard()`. Scab increases its own `spreadLevel`,
   computes damage from it, and calls `orchard.takeDamage(...)` and
   `orchard.reduceYield(...)`. It also calls
   `orchard.setLastThreatName("Scab")`.
3. **Status is printed.** `orchard.printStatus()` shows the new
   health/yield.
4. **Destruction check.** If health has hit 0, the round (and the
   whole simulation) ends early.
5. **Defense menu.** The three defenses are listed with their names
   and descriptions (read polymorphically through
   `DefenseAction::getName()` / `getDescription()`).
6. **The player chooses.** Say they type `1` for Fungicide Spray.
7. **The defense applies.** `chosenDefense.apply(orchard)` runs
   `FungicideSpray::apply()`, which checks
   `orchard.getLastThreatName() == "Scab"` — true in this example — so
   it applies its bonus healing.
8. **Status is printed again**, and an `EventRecord` capturing the
   whole round (before/after values, names) is appended to `history`.
9. **Round counter advances**, and the loop repeats for the next round.

## End of simulation

After all rounds finish (or the orchard is destroyed early),
`printFinalReport()` prints a summary: rounds completed, final
health/yield, a plain-language verdict, and the full event log.
`exportJSON()` then writes the same information as structured JSON to
`visualization/data/simulation_log.json` for the dashboard.

## Demonstration scenario (matches the project brief)

```
Initial state (Health 100, Yield 100%)
   ↓
Scab detected → Scab::attackOrchard() runs (polymorphic call #1)
   ↓
Orchard health/yield decrease, lastThreatName = "Scab"
   ↓
Player selects Fungicide Spray
   ↓
FungicideSpray::apply() runs (polymorphic call #2), sees lastThreatName
== "Scab", applies bonus healing
   ↓
Health/yield increase
   ↓
Next round: Hailstorm detected → Hailstorm::attackOrchard() runs
   ↓
Sudden heavy damage
   ↓
Player selects Net Covering → big bonus vs Hailstorm
   ↓
... continues for remaining rounds ...
   ↓
Final report printed + simulation_log.json written
```
