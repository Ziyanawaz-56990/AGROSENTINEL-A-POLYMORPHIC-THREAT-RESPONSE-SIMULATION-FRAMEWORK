# AgroSentinel

**A Polymorphic Threat Response Simulation Framework**

A C++ object-oriented simulation of an orchard defending itself against
different agricultural threats, built to demonstrate the four pillars
of OOP — abstraction, inheritance, polymorphism, and encapsulation —
through a genuinely working, runnable project rather than toy examples.

---

## Table of Contents

- [Overview](#overview)
- [Problem Statement & Motivation](#problem-statement--motivation)
- [Objectives](#objectives)
- [Features](#features)
- [Architecture](#architecture)
- [OOP Concepts Used](#oop-concepts-used)
- [Class Hierarchy](#class-hierarchy)
- [How Polymorphism Works Here](#how-polymorphism-works-here)
- [Simulation Workflow](#simulation-workflow)
- [Technology Stack](#technology-stack)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation & Compilation](#installation--compilation)
- [Execution](#execution)
- [Visualization](#visualization)
- [Testing](#testing)
- [Sample Output](#sample-output)
- [Screenshots](#screenshots)
- [Algorithm & Complexity](#algorithm--complexity)
- [Design Decisions](#design-decisions)
- [Limitations](#limitations)
- [Future Improvements](#future-improvements)
- [Learning Outcomes](#learning-outcomes)
- [Author](#author)

---

## Overview

AgroSentinel simulates a small orchard facing a sequence of threats —
a fungal disease, an insect infestation, and a hailstorm — while the
player chooses defenses to respond with each round. Under the hood,
every threat and every defense is a separate class, all accessed
through two shared, abstract interfaces (`Threat` and `DefenseAction`).
The `GameEngine` never needs to know which concrete threat or defense
it is dealing with — it always calls through the base class, and C++
figures out the correct behaviour at runtime. That is the entire point
of the project.

## Problem Statement & Motivation

Most beginner OOP projects (bank accounts, shape calculators, employee
hierarchies) are correct but forgettable, and it's easy to fake
polymorphism with `if (type == "X")` chains that defeat the whole
purpose of virtual functions. AgroSentinel was built to give a more
memorable, visual, and *game-like* domain (an orchard defending itself)
while being strict about actually requiring virtual dispatch to work —
there is no type-checking branch anywhere that decides *how* a threat
attacks or *how* a defense heals.

## Objectives

- Demonstrate all four OOP pillars with genuine, load-bearing use —
  not decoration.
- Build clean, compiling, tested, modern (C++17) code that a beginner
  can still read and follow.
- Keep the C++ simulation as the graded core, with a lightweight
  visualization layer on top that never replaces it.
- Produce a GitHub-ready repository: documentation, tests, `.gitignore`,
  license, and a clear commit history.

## Features

- Abstract `Threat` and `DefenseAction` base classes with pure virtual
  functions.
- Three distinct threats (`Scab`, `Aphids`, `Hailstorm`) with genuinely
  different, stateful behaviour.
- Three distinct defenses (`FungicideSpray`, `Pruning`, `NetCovering`),
  each with a bonus against a specific threat.
- An `Orchard` class with fully encapsulated state (private data,
  controlled public methods).
- A `GameEngine` that runs multiple rounds, validates user input,
  tracks a full event history, and prints a final report with a
  plain-language verdict.
- Randomized threat selection using `<random>` (`std::mt19937`).
- A dependency-free test suite covering damage, healing, yield,
  boundary conditions, and — most importantly — genuine runtime
  polymorphism.
- A JSON export of the full simulation history.
- An HTML/CSS/JavaScript dashboard (Chart.js) that visualizes health,
  yield, threat severity, and the full event log.

## Architecture

See [`docs/architecture.md`](docs/architecture.md) for the full
breakdown and a Mermaid class diagram. In short:

```
C++ simulation engine (src/, include/)   →  writes  →  visualization/data/simulation_log.json
                                                                    ↓ read by
                                          HTML/CSS/JS dashboard (visualization/)
```

**C++ = simulation engine and OOP core. Visualization = presentation
layer only.** All simulation rules live in C++; the dashboard just
displays what already happened.

## OOP Concepts Used

Full explanations with code excerpts live in
[`docs/oop-concepts.md`](docs/oop-concepts.md). Summary:

| Pillar         | Where it lives                                                        |
|----------------|-------------------------------------------------------------------------|
| Abstraction    | `Threat`, `DefenseAction` — abstract classes with pure virtual methods |
| Inheritance    | `Scab`/`Aphids`/`Hailstorm` extend `Threat`; `FungicideSpray`/`Pruning`/`NetCovering` extend `DefenseAction` |
| Polymorphism   | `GameEngine` calls `attackOrchard()`/`apply()` through base references; the real override runs at runtime |
| Encapsulation  | `Orchard`'s `health`/`yieldPercent`/etc. are private, only reachable through controlled public methods |

## Class Hierarchy

```
Threat (abstract)                 DefenseAction (abstract)
   ├── Scab                          ├── FungicideSpray
   ├── Aphids                        ├── Pruning
   └── Hailstorm                     └── NetCovering

Orchard  ◄── used by ── Threat & DefenseAction implementations
Orchard, Threat, DefenseAction  ◄── owned/used by ── GameEngine
```

A ready-to-render Mermaid diagram is in
[`docs/architecture.md`](docs/architecture.md#mermaid-class-diagram).

## How Polymorphism Works Here

```cpp
Threat& activeThreat = pickRandomThreat(); // static type: Threat&, real type decided at runtime
activeThreat.attackOrchard(orchard);       // dynamic dispatch: runs Scab/Aphids/Hailstorm's own version

DefenseAction& chosenDefense = pickDefenseByChoice(choice);
chosenDefense.apply(orchard);              // same idea, for defenses
```

`attackOrchard()` and `apply()` are declared `virtual` in their base
classes. The compiler cannot know in advance which override will run —
it generates a lookup through each object's virtual table that happens
**at runtime**, based on the object that is *actually* there. See
[`docs/oop-concepts.md`](docs/oop-concepts.md#3-polymorphism-the-most-important-section)
for a detailed breakdown, including what would break if `virtual` were
removed.

## Simulation Workflow

1. View initial orchard status.
2. A threat is randomly selected and attacks (polymorphic call).
3. Orchard health/yield change; status is printed.
4. Player selects a defense from a menu.
5. Defense responds (polymorphic call); status is printed again.
6. Repeat for several rounds (default: 5).
7. Print a final report with a verdict and the full event log.
8. Export the same data as JSON for the dashboard.

Full walkthrough: [`docs/simulation.md`](docs/simulation.md).

## Technology Stack

- **C++17** — the simulation engine (core of the project).
- **CMake 3.10+** — build configuration.
- **HTML / CSS / vanilla JavaScript** — visualization dashboard.
- **Chart.js** (via CDN) — charts in the dashboard.
- No external C++ dependencies, no package managers, no frameworks.

## Project Structure

```
AgroSentinel/
├── README.md
├── LICENSE
├── .gitignore
├── CMakeLists.txt
├── include/            # class declarations (.h)
├── src/                # class implementations + main.cpp
├── tests/              # dependency-free test suite
├── visualization/      # HTML/CSS/JS dashboard + exported JSON data
├── docs/               # architecture, OOP concepts, algorithm, simulation
├── examples/           # a saved sample console run
└── assets/             # (reserved for screenshots/images used in docs)
```

## Requirements

- A C++17-compatible compiler (GCC 7+, Clang 6+, or MSVC 2017+).
- CMake 3.10 or newer (or just a direct `g++`/`clang++` command — both
  are shown below).
- Any modern web browser, for the optional visualization.
- Python 3 (or any other tool that can serve static files), only if you
  want to view the visualization — used purely to work around browsers
  blocking local file access via `fetch()`.

## Installation & Compilation

Clone or download the project, then from the project's root folder:

### Option 1 — CMake (recommended)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

This produces two executables inside `build/`:
`agrosentinel` (the simulation) and `agrosentinel_tests` (the test suite).

### Option 2 — Direct compiler command (no CMake needed)

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o agrosentinel
```

## Execution

```bash
./agrosentinel          # on Windows: agrosentinel.exe
```

Follow the on-screen prompts: read the threat, read the orchard status,
type `1`, `2`, or `3` to pick a defense, and repeat for 5 rounds.

## Visualization

After running `./agrosentinel` at least once from the project root, a
file `visualization/data/simulation_log.json` will exist. To view the
dashboard:

```bash
cd visualization
python3 -m http.server 8000
```

Then open `http://localhost:8000` in your browser. (A plain
`file://.../index.html` double-click will usually **not** work, because
browsers block `fetch()` requests to local files for security reasons —
running a tiny local server avoids that entirely and needs no
installation beyond Python, which ships with most systems.)

## Testing

```bash
# with CMake
cd build
ctest --output-on-failure

# or directly
g++ -std=c++17 -Iinclude src/Orchard.cpp src/Scab.cpp src/Aphids.cpp \
    src/Hailstorm.cpp src/FungicideSpray.cpp src/Pruning.cpp \
    src/NetCovering.cpp tests/test_main.cpp -o agrosentinel_tests
./agrosentinel_tests
```

The suite checks: orchard damage/healing/clamping, encapsulation
guarantees, each threat's escalating (or fixed) behaviour, each
defense's bonus effect, boundary conditions (overkill damage, full
health), and — the most important test — that a `std::vector<Threat*>`
containing three different concrete objects really does call three
different implementations when the exact same line of code
(`threat->attackOrchard(orchard)`) runs for each one.

## Sample Output

See [`examples/sample-output.txt`](examples/sample-output.txt) for a
full saved run. Excerpt:

```
========================================
            AGROSENTINEL
Polymorphic Threat Response Simulation
========================================

Initial Orchard Status
----------------------------------------
 Orchard Status (Round 1)
----------------------------------------
  Health : 100 / 100
  Yield  : 100%
  Trees  : 200
----------------------------------------

========== Round 1 / 5 ==========

Threat detected: Aphids (severity 1/10)
Insects that multiply quickly and mainly damage crop yield.

  [Aphids] A colony of aphids swarms the branches...
  [Aphids] Health -4, Yield -7% (infestation level 1)

Select a defense action:
  1. Fungicide Spray - A chemical treatment, especially effective against Scab.
  2. Pruning - Removes damaged growth; a general-purpose defense, strong vs Aphids.
  3. Net Covering - Physical netting; a general shield, excellent against Hailstorm.
Enter choice (1-3):
```

## Screenshots

Suggested screenshots (see `docs/screenshots/` — add your own image
files there once captured):

1. Program running in the terminal, initial status.
2. A threat attack in progress.
3. A defense action being applied.
4. The final report / event log.
5. The visualization dashboard (cards + charts).
6. The project structure open in an editor/IDE.
7. The repository page on GitHub.

## Algorithm & Complexity

Full detail in [`docs/algorithm.md`](docs/algorithm.md). Summary: every
threat/defense action is O(1); the whole simulation is O(R) time and
O(R) space, where R is the number of rounds (default 5) — dominated
entirely by the event history, not by any searching/sorting algorithm.

## Design Decisions

- **`std::unique_ptr` over raw `new`/`delete`:** threats and defenses
  are stored as `std::unique_ptr<Threat>` / `std::unique_ptr<DefenseAction>`.
  This gives dynamic polymorphism (storing different derived types
  behind one base pointer) with automatic, guaranteed cleanup (RAII) —
  no manual `delete`, no risk of memory leaks or double-frees.
- **Persistent threat instances, not recreated per round:** this lets
  `Scab` and `Aphids` realistically escalate the more they reappear,
  which was a specific requirement of the brief.
- **Defense bonuses read `Orchard::getLastThreatName()`, not a `Threat`
  object:** this keeps the "which threat was countered" logic entirely
  as plain data on `Orchard`, so `DefenseAction` subclasses never need
  to inspect or downcast a `Threat` — preserving genuine polymorphism.
- **JSON export instead of a live server:** avoids introducing
  networking, HTTP, or JSON-parsing libraries into the C++ code, which
  would add complexity unrelated to the OOP learning goals.

## Limitations

- The simulation is turn-based and console-driven; there is no
  save/load between separate runs.
- Threat/defense numbers are fixed formulas, not configurable from the
  command line (yet).
- The visualization only reads the *most recent* exported run; it does
  not compare multiple past runs.
- No persistence/database — this is intentional for a project of this
  scope.

## Future Improvements

- Add more threats/defenses (e.g. `Drought`, `Irrigation`) — trivial,
  since `GameEngine` needs zero changes thanks to polymorphism.
- Add a difficulty setting affecting threat frequency/severity.
- Let the visualization compare multiple saved runs over time.
- Add a scoring system across multiple full playthroughs.

## Learning Outcomes

Building AgroSentinel demonstrates practical, working understanding of:
abstract classes and pure virtual functions, inheritance hierarchies,
runtime polymorphism via virtual dispatch, encapsulation and invariant
protection, RAII and smart pointers, modern C++17 idioms, CMake project
structuring, writing a dependency-free test suite, and connecting a
compiled C++ program to a simple web-based visualization through a
file-based data hand-off.

## Author

Built as a college-level C++ OOP project.Owned by Ziya Nawaz bearing ID B125080 from CSE-B.
