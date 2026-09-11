# Algorithm & Complexity

## Simulation algorithm (high level)

```
1. Create Orchard with starting health=100, yield=100, trees=200
2. Create the threat pool  {Scab, Aphids, Hailstorm}    (built once)
3. Create the defense pool {FungicideSpray, Pruning, NetCovering} (built once)
4. Print initial orchard status
5. For round = 1 .. totalRounds:
     a. Randomly pick ONE threat from the threat pool (uniform distribution)
     b. Call threat.attackOrchard(orchard)          <-- polymorphic call
     c. Print updated orchard status
     d. If orchard.isDestroyed(): record event, stop early
     e. Show defense menu, read user's 1-3 choice
     f. Call chosenDefense.apply(orchard)            <-- polymorphic call
     g. Print updated orchard status
     h. Record an EventRecord (round, threat, before/after values, defense)
     i. Advance to next round
6. Print final report (rounds completed, final stats, verdict, full event log)
7. Export the full history + final state to visualization/data/simulation_log.json
```

## Threat selection

A uniform random index is drawn using `std::mt19937` (a high-quality
pseudo-random number generator) with `std::uniform_int_distribution`
over `[0, threatPool.size() - 1]`. Every threat has an equal (1/3)
chance of appearing in a given round. Threat objects are **not**
recreated each round — the same `Scab`/`Aphids`/`Hailstorm` instances
persist across the whole simulation, which is what allows their
internal "spread level" / "infestation level" to realistically
increase the more they reappear.

## Defense selection

The defense is chosen directly by the human player from a printed
menu (1, 2, or 3). `GameEngine::promptDefenseChoice()` validates the
input in a loop: non-numeric input is rejected and re-prompted (using
`std::cin.clear()` + `std::cin.ignore()` to recover from a failed
read), and out-of-range numbers are also rejected.

## Damage calculation

Each `Threat` subclass computes its own damage using simple integer
arithmetic based on its own internal state:

| Threat     | Health damage formula          | Yield damage formula            | Escalates? |
|------------|---------------------------------|----------------------------------|------------|
| Scab       | `5 + spreadLevel * 2`           | `3 + spreadLevel`                | Yes        |
| Aphids     | `3 + infestationLevel`          | `5 + infestationLevel * 2`       | Yes        |
| Hailstorm  | fixed `25`                       | fixed `15`                       | No         |

`spreadLevel`/`infestationLevel` increase by 1 every time that specific
threat attacks.

## Defense effectiveness

Each `DefenseAction` subclass restores a base amount, plus a bonus if
`orchard.getLastThreatName()` matches the threat it counters:

| Defense          | Base health / yield gain | Bonus condition        | Bonus health / yield |
|------------------|---------------------------|--------------------------|------------------------|
| Fungicide Spray  | +15 / +5                  | last threat was Scab      | +10 / +5               |
| Pruning          | +10 / +8                  | last threat was Aphids    | +5 / +7                |
| Net Covering     | +8 / +3                   | last threat was Hailstorm | +20 / +10              |

## Status updates

All health/yield changes go through `Orchard::takeDamage`,
`restoreHealth`, `reduceYield`, `increaseYield`, each of which clamps
the result into `[0, 100]` using a private `clamp()` helper. This
guarantees the orchard's values are always valid, no matter what
sequence of threats/defenses occurs.

## Event logging & final statistics

Every round appends one `EventRecord` (a plain struct, see
`include/GameEngine.h`) to a `std::vector<EventRecord>`. The final
report and the JSON export both simply iterate over this vector once.

## Time & space complexity

Let `R` = number of rounds (a small constant, default 5), and the
threat/defense pools have fixed sizes (3 each).

- **Picking a random threat:** O(1) — one random number generation and
  one array index.
- **`attackOrchard()` / `apply()`:** O(1) — a fixed number of
  arithmetic operations and clamped assignments; no loops over data
  that grows with input size.
- **One full round:** O(1) (all pieces above are O(1)).
- **Whole simulation:** O(R) — linear in the number of rounds, since
  we do a constant amount of work per round.
- **Printing the final report / exporting JSON:** O(R) — a single pass
  over the `history` vector of size ≤ R.
- **Space:** O(R) — the only data structure that grows with the
  simulation is the `history` vector, storing one small fixed-size
  struct per round. Everything else (`Orchard`, threat pool, defense
  pool) is constant size.

There are no searching, sorting, or graph algorithms in this project —
by design. AgroSentinel is intentionally an OOP-design showcase, not an
algorithms showcase, so the complexity is deliberately simple and easy
to state honestly in a viva.
