# AgroSentinel — Complete Project Blueprint & Documentation

**A Polymorphic Threat Response Simulation Framework**

This document is a deep, beginner-friendly explanation of AgroSentinel —
not just *what* it is, but *why* every decision was made, *how* it
works internally, and *how* you would build it again from zero. Treat
it as a second, more exhaustive companion to the project's main
`README.md`.

---

# WHY THIS PROJECT IS AN OOP PROJECT

Before anything else: AgroSentinel isn't a generic program that had
classes bolted onto it to satisfy an assignment requirement. Its
subject matter — an orchard, under attack from real agricultural
threats, being defended with real countermeasures — maps onto Object-
Oriented Programming (OOP) *naturally*, because the real world it
models is already made of "things that have state and behavior,"
which is exactly what a class is.

```text
Real-world Entity          →  Class
An orchard                 →  Orchard
"A threat" in general      →  Threat (abstract)
A specific fungal disease  →  Scab (a concrete Threat)
A specific insect problem  →  Aphids (a concrete Threat)
A specific weather event   →  Hailstorm (a concrete Threat)
"A defense" in general     →  DefenseAction (abstract)
A specific chemical spray  →  FungicideSpray (a concrete DefenseAction)
A specific pruning action  →  Pruning (a concrete DefenseAction)
A specific netting action  →  NetCovering (a concrete DefenseAction)
The simulation itself      →  GameEngine

Characteristics of an orchard (health, yield, tree count) → Attributes
Actions an orchard can undergo (take damage, heal, lose yield) → Methods
```

Here's why each pillar shows up *because the domain demands it*, not
because we forced it in:

- **Encapsulation** is necessary because an orchard's health and yield
  are real quantities that must stay within valid bounds (0-100). If
  any code anywhere could freely set `health = -9999`, the simulation
  would be meaningless. So `Orchard` hides its data and only exposes
  safe, validated methods.
- **Abstraction** is necessary because, conceptually, "a threat" is a
  category, not a concrete thing you can point to — you can point to
  a *specific* threat (Scab, say), but "the idea of a threat" only
  exists as a shared contract of behavior. That's exactly what an
  abstract class represents.
- **Inheritance** is necessary because Scab, Aphids, and Hailstorm are
  all fundamentally "a type of threat" — they share an interface
  (attack an orchard, report a name/severity) while differing
  completely in the details.
- **Polymorphism** is necessary because the simulation engine has to
  process *whichever* threat shows up in a given round without
  knowing in advance which one it will be — this is precisely the
  situation polymorphism exists to solve.

If AgroSentinel had been "print the numbers 1 to 10," OOP would have
been forced and unnecessary. Because it's "different kinds of things
that all act on a shared target through a shared interface," OOP is
the *natural* fit, not a decoration.

---

## 1. Project Title and Introduction

- **Project name:** AgroSentinel
- **Tagline:** A Polymorphic Threat Response Simulation Framework
- **Project type:** A C++17 console simulation with an optional
  companion web-based visualization dashboard.
- **Main purpose:** To simulate an orchard defending itself against a
  sequence of agricultural threats, while cleanly demonstrating every
  core principle of Object-Oriented Programming through genuinely
  necessary, load-bearing design (not decorative classes).
- **Target users:** Primarily, a computer science / software
  engineering student (you) building this as a college OOP project,
  and secondarily, an instructor evaluating that project.
- **One-paragraph overview:** AgroSentinel puts you in charge of an
  orchard for several rounds. Each round, a randomly chosen threat —
  a fungal disease, an insect infestation, or a sudden hailstorm —
  attacks your orchard, reducing its health and crop yield. You choose
  a defense in response, and the orchard's condition updates
  accordingly. Every threat and every defense is implemented as its
  own class, but the simulation engine driving all of this interacts
  with them only through two shared, abstract interfaces — which is
  what allows the same few lines of engine code to correctly handle
  six completely different behaviors.

### What problem does the project solve?

At face value, this is a simulation game, so it doesn't solve a
real agricultural problem. Its actual "problem" is educational: many
beginner OOP projects (bank accounts, shape calculators) technically
use inheritance and virtual functions, but the *simulation itself*
doesn't actually need them — you could rewrite the whole thing with
`if`/`else` chains and lose nothing. AgroSentinel solves *that*
problem: it's designed so removing polymorphism would genuinely break
the program's ability to cleanly handle new threats/defenses, making
the OOP demonstrably real rather than cosmetic.

### Why is this problem important?

For a student, being able to point at working code and say "this
*needs* to be polymorphic, and here's exactly why, and here's what
breaks if you remove `virtual`" is a much stronger, more defensible
position in an oral exam than reciting a textbook definition.

### Who faces this problem?

Any student building a first substantial OOP project, and — more
broadly — any programmer designing a system that must handle an
open-ended, growing set of "kinds of things" (here: threats and
defenses) without rewriting the core logic every time a new kind is
added.

### What currently happens without this project?

Without a deliberately-designed example like this, students often
default to a single class with a `type` field and giant `switch`
statements, which technically "has a class" but does not demonstrate
runtime polymorphism.

### How does AgroSentinel improve the situation?

It provides a working, tested, complete reference implementation where
adding a **fourth** threat class requires touching exactly one new
pair of files (`Drought.h` / `Drought.cpp`) and zero changes to
`GameEngine` — which is the clearest possible proof that the
polymorphic design is real.

### What can the user actually do with it?

Run the simulation from a terminal, watch different threats attack
with genuinely different math behind them, choose from three defenses
each round, see the orchard's health/yield evolve, read a final
report, and (optionally) view the same data as a browser dashboard
with charts.

---

## 2. Why This Project?

### The real-world problem behind it

Orchard/crop management is a real domain with real threats (disease,
pests, weather), which makes for a much more relatable simulation
theme than an abstract "Shape" or "Animal" example, while still being
simple enough to model with basic arithmetic — no biology or
agriculture expertise required.

### Why is it worth solving (as a learning exercise)?

Because a convincing demonstration of polymorphism is one of the
hardest things for a beginner to build *correctly* — it's easy to
accidentally write "fake" polymorphism. Solving this well is a
genuinely useful skill upgrade.

### Why is software a suitable solution?

A simulation is inherently a software problem — it requires modeling
state that changes over time in response to different kinds of
events, which is exactly what programs (and specifically, object-
oriented programs) are good at.

### Why is an OOP approach suitable?

Because the domain has natural "kinds" (kinds of threats, kinds of
defenses) that share behavior but differ in specifics — the textbook
definition of when inheritance and polymorphism apply.

### What can be learned by building it?

Abstract classes, pure virtual functions, dynamic dispatch, RAII and
smart pointers, encapsulation/invariant protection, CMake project
structuring, writing tests without a framework, and connecting a
compiled program to a simple visualization layer.

### What makes it a good beginner/intermediate C++ project?

It's scoped tightly: three threats, three defenses, one central
engine, one data class. It compiles cleanly with warnings enabled, has
no external dependencies, and every concept (smart pointers, virtual
functions, `std::vector`) is introduced with a real, working use —
never an artificial example.

### How does it demonstrate practical software-development skills?

Beyond OOP: it demonstrates test-writing, build configuration (CMake),
clean separation of concerns (engine vs. presentation), version
control practices, and technical documentation writing — the full
lifecycle of a small but real piece of software.

---

## 3. Project Objectives

### Functional objectives

- Simulate multiple rounds of threats attacking, and defenses
  responding to, an orchard. *(Why: this is the core behavior of the
  program — everything else supports it.)* *(How: `GameEngine::run()`
  loops for a configured number of rounds.)*
- Track and report a full history of events and final statistics.
  *(Why: needed for the final report and for the visualization.)*
  *(How: `std::vector<EventRecord>` inside `GameEngine`.)*

### Technical objectives

- Genuinely require virtual dispatch — no type-checking branches
  deciding *how* a threat attacks or a defense heals. *(Why: this is
  the entire pedagogical point of the project.)* *(How: `Threat` and
  `DefenseAction` are abstract classes with pure virtual functions.)*
- Compile cleanly under `-Wall -Wextra` with C++17. *(Why: clean,
  warning-free code is a baseline professional standard.)* *(How:
  careful, deliberate code — verified by actually compiling it.)*
- Manage all dynamic objects with smart pointers, not raw
  `new`/`delete`. *(Why: eliminates a whole class of memory bugs.)*
  *(How: `std::unique_ptr<Threat>` / `std::unique_ptr<DefenseAction>`
  in `GameEngine`'s pools.)*

### Learning objectives

- Understand, from a working example, exactly how and why virtual
  dispatch works at runtime, not just what the keyword `virtual` does
  on paper.
- Practice separating "engine" logic from "presentation" logic.

### User-experience objectives

- Give clear, readable console output at every step (status blocks,
  labeled damage/healing numbers). *(Why: a simulation that's hard to
  follow undermines the demonstration.)* *(How: `Orchard::printStatus()`
  and labeled `std::cout` lines in every threat/defense.)*
- Provide an optional visual dashboard for a more polished
  presentation. *(Why: useful for a demo, without being required for
  the grading of the OOP itself.)* *(How: the HTML/CSS/JS dashboard in
  `visualization/`.)*

---

## 4. What Exactly Will the Project Do?

### When the user runs the program, what happens first?

The terminal prints a banner ("AGROSENTINEL — Polymorphic Threat
Response Simulation") and the orchard's starting status: Health
100/100, Yield 100%, 200 trees.

### Complete user journey, step by step

1. **What the user sees:** the initial orchard status block.
2. **What they do:** nothing yet — round 1 begins automatically.
3. **What information they enter:** nothing, until the defense prompt.
4. **What the system does internally:** `GameEngine::pickRandomThreat()`
   rolls a random index (0, 1, or 2) using `std::mt19937` and returns a
   reference into `threatPool`. Say index 0 is chosen — that's the
   `Scab` object.
5. **What happens internally, in detail:** `GameEngine` calls
   `activeThreat.attackOrchard(orchard)`. Because `activeThreat` has
   static type `Threat&` but its real, runtime type is `Scab`, C++'s
   virtual dispatch mechanism finds and runs `Scab::attackOrchard()`.
   Inside that function, `Scab` increments its private `spreadLevel`,
   computes `healthDamage = 5 + spreadLevel * 2` and
   `yieldDamage = 3 + spreadLevel`, and calls
   `orchard.takeDamage(healthDamage)` and
   `orchard.reduceYield(yieldDamage)` — both of which are `Orchard`'s
   own private-data-guarding methods, which clamp the results into
   `[0, 100]`.
6. **What result is shown:** the console prints exactly what damage
   was dealt and the orchard's updated status.
7. **What the user clicks/types:** a defense menu appears
   (`1. Fungicide Spray`, `2. Pruning`, `3. Net Covering`); the user
   types a number.
8. **What happens if the user makes a mistake:** if they type a
   non-numeric value, `promptDefenseChoice()` catches the failed
   read, clears the error state on `std::cin`, discards the bad
   input, and re-prompts. If they type an out-of-range number (e.g.
   `9`), it's rejected with a message and re-prompted, without
   crashing.
9. **What happens when they complete a round:** the chosen
   `DefenseAction` is applied polymorphically the same way (via
   `chosenDefense.apply(orchard)`), the status is printed again, an
   `EventRecord` is appended to `history`, and the loop moves to the
   next round.
10. **What happens at the very end:** after all rounds (default 5),
    `printFinalReport()` prints total stats and a plain-language
    verdict, and `exportJSON()` writes
    `visualization/data/simulation_log.json` for the dashboard.

### Realistic example, traced through the code

Say round 2 rolls `Hailstorm`. `Hailstorm::attackOrchard()` runs — it
has *no* internal escalating state (unlike Scab/Aphids), so it always
subtracts a fixed 25 health and 15% yield, and calls
`orchard.setLastThreatName("Hailstorm")`. The user picks `3` (Net
Covering). `NetCovering::apply()` reads
`orchard.getLastThreatName()`, sees it's `"Hailstorm"`, and applies a
large bonus (+20 health, +10% yield instead of the base +8/+3) because
netting is specifically effective against hail.

---

## 5. Visual / Frontend Outcome

AgroSentinel has two "screens": the terminal (primary, and what's
actually graded) and the optional browser dashboard (secondary,
presentation-only).

### Terminal — wireframe (text-based)

```text
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
  1. Fungicide Spray - ...
  2. Pruning - ...
  3. Net Covering - ...
Enter choice (1-3): _
```

**What the user sees:** clean, labeled status blocks and numbered
menus. **What they can do:** read information and type a single
number. **What happens internally:** described in Section 4.

### Browser dashboard — wireframe (text-based)

```text
------------------------------------------------------------
 🌿 AgroSentinel                      [ Orchard survived ]
    Polymorphic Threat Response Simulation — Dashboard
------------------------------------------------------------

 | Final Health | Final Yield | Rounds Completed | Trees |
 |     85/100   |     81%     |      5 of 5       |  200  |
 |  [======  ]  |  [=====  ]  |                    |       |

------------------------------------------------------------
 Health & Yield Over Time
   (line chart across rounds)
------------------------------------------------------------

 Threat Severity By Round
   (bar chart across rounds)
------------------------------------------------------------

 Event Log
 | Round | Threat | Severity | Health (b→a→a) | Yield | Defense |
 |   1   | Aphids |   1/10   |  100→96→100     | ...   | Fung.   |
 | ...   |        |          |                 |       |         |
------------------------------------------------------------
```

**What the user sees:** four summary cards, two charts, and a table.
**What they can do:** read/scroll — it's a read-only report, not an
interactive control panel. **What happens internally:** `script.js`
fetches `data/simulation_log.json` and renders it with Chart.js; no
computation happens in the browser.

There is no login page, navigation bar, forms, or multi-page
structure in this project — a single-page report is all the domain
requires. Adding those would be scope creep unrelated to the OOP
learning goals.

---

## 6. Expected Final Outcome

At the end, you will have: a compiling, warning-free C++17 console
program; a passing test suite; a browser dashboard that visualizes a
completed run; full documentation (this file, the main README, and
four supporting docs); and a GitHub repository with a clean commit
history.

### What I can demonstrate to my teacher

A live run of the simulation from the terminal, a live view of the
dashboard populated from that run, the test suite passing, and a
guided tour of the source code showing exactly where each OOP pillar
lives (see the Professor Demo Script in `README.md`).

### Realistic demonstration flow

```text
1. Open terminal, run the compiled program
2. Show initial orchard status
3. Play through 2-3 rounds live, narrating each threat/defense
4. Show the final report and event log
5. Open the browser dashboard, point out the charts came from
   the same run
6. Open the source code, show Threat.h / DefenseAction.h and their
   pure virtual functions
7. Show GameEngine.cpp's attackOrchard()/apply() calls and explain
   the virtual dispatch
8. (Optional) run the test suite and show it passing
```

---

## 7. Technology Stack

### Programming Language

**C++ (C++17 standard)**
1. **What it is:** a compiled, statically-typed, general-purpose
   programming language with strong OOP support.
2. **Why we need it:** the entire simulation logic and all class
   design lives here — it's the graded core of the project.
3. **Why chosen for this project:** C++'s explicit `virtual`,
   `override`, and abstract-class mechanics make polymorphism visible
   and teachable in a way higher-level languages often hide.
4. **What part it handles:** everything in `include/` and `src/` —
   100% of the simulation.
5. **How it communicates with other technologies:** it writes a plain
   JSON text file to disk; it does not call or link to anything else
   directly.
6. **Beginner difficulty:** Medium — pointers and manual memory
   concepts exist, but this project uses smart pointers specifically
   to soften that curve.
7. **Essential or optional:** Essential — it *is* the project.

### Frontend (optional visualization only)

**HTML**
1. Markup language describing page structure.
2. Needed to have any web page at all.
3. Chosen because it requires no build tools or frameworks — open a
   text file, done.
4. Handles: the dashboard's layout (`visualization/index.html`).
5. Communicates with CSS (via `<link>`) and JS (via `<script>`).
6. Beginner difficulty: Easy.
7. Optional — the C++ program runs and is fully gradable without it.

**CSS**
1. Styling language controlling appearance.
2. Needed to make the dashboard readable and presentable.
3. Chosen (plain CSS, no framework) to avoid adding a dependency
   unrelated to the OOP learning goals.
4. Handles: colors, layout, spacing (`visualization/style.css`).
5. Communicates with HTML via class/id selectors.
6. Beginner difficulty: Easy.
7. Optional.

**JavaScript (vanilla, no framework)**
1. A scripting language that runs in the browser.
2. Needed to fetch the JSON file and draw the charts dynamically.
3. Chosen over React/Vue/etc. because the dashboard is a single,
   simple, read-only page — a framework would add complexity with no
   benefit here.
4. Handles: `fetch()`-ing the data and building the charts/table
   (`visualization/script.js`).
5. Communicates with the C++ side *indirectly*, by reading the file
   the C++ program already wrote.
6. Beginner difficulty: Medium.
7. Optional.

**Chart.js (via CDN)**
1. A small, free charting library.
2. Needed so we don't hand-draw charts with raw `<canvas>` math.
3. Chosen for its simplicity and because it requires zero
   installation (just a `<script>` tag pointing at a CDN).
4. Handles: the two charts in the dashboard.
5. Loaded by, and used from, `script.js`.
6. Beginner difficulty: Easy (for basic usage like ours).
7. Optional, and only used within the optional visualization layer.

### Backend

**There is no traditional "backend" (no server, no HTTP routes, no
authentication).** The C++ program itself plays the backend's role —
it holds the business logic and produces output — but it runs as a
one-shot console program, not a long-running server. This is a
deliberate simplification: a real backend framework would introduce
networking and request-handling concepts that are unrelated to the
OOP grading criteria.

### Database

**No database is used — and this is intentional, not an oversight.**

- What data needs to be stored? Only the results of the *most recent*
  run, temporarily, so the dashboard can display it.
- Why not a database (MySQL/SQLite/MongoDB)? A database is designed
  for persistent, queryable, multi-record storage — AgroSentinel has
  exactly one "record" (the latest simulation) that only needs to
  survive from the end of the C++ program to the opening of the
  dashboard. Introducing a database would add setup complexity
  (installing a DB engine, writing SQL or a driver library) with zero
  benefit to a project graded on OOP design.
- What we use instead: a single **JSON text file**
  (`visualization/data/simulation_log.json`), written using
  `std::ofstream` (plain file output, a concept every beginner C++
  course already covers) and read using the browser's built-in
  `fetch()`.

---

## 8. Why Each Technology Is Used

| Technology  | Purpose                                | Why We Use It                                             | Beginner Difficulty |
|-------------|-----------------------------------------|-------------------------------------------------------------|----------------------|
| C++17       | Core simulation logic, all OOP design   | Explicit, teachable OOP mechanics; project's graded core    | Medium               |
| CMake       | Build configuration                     | Standard, portable way to compile multi-file C++ projects   | Easy–Medium          |
| HTML        | Dashboard structure                     | Simplest way to lay out a web page, no tooling required     | Easy                 |
| CSS         | Dashboard styling                       | Makes the dashboard presentable for a demo                  | Easy                 |
| JavaScript  | Reads JSON, builds charts/table         | Only language browsers run natively; no framework needed    | Medium               |
| Chart.js    | Draws line/bar charts                   | Avoids hand-writing chart-drawing math                      | Easy                 |
| JSON file   | Data hand-off from C++ to dashboard     | Simplest possible "storage" for a single, temporary record  | Easy                 |

---

## 9. Complete Project Architecture

```text
USER (types choices in the terminal)
  ↓
C++ SIMULATION ENGINE  (GameEngine, using Threat/DefenseAction/Orchard)
  ↓
JSON FILE  (visualization/data/simulation_log.json — written once, at the end)
  ↓
HTML / CSS / JS DASHBOARD  (reads the file, no computation of its own)
  ↓
USER (views the dashboard in a browser)
```

### Layer-by-layer

**C++ Simulation Engine (`include/`, `src/`)**
- *Enters:* keyboard input (defense choices) via `std::cin`.
- *Leaves:* console output (`std::cout`) and one JSON file.
- *Why it exists:* this is the entire graded artifact — all OOP
  design and business logic lives here.
- *Files/classes:* `Orchard`, `Threat` + subclasses, `DefenseAction` +
  subclasses, `GameEngine`, `main.cpp`.
- *Communicates with:* the next layer only via the file it writes;
  it has zero awareness of HTML/CSS/JS.

**JSON File (`visualization/data/simulation_log.json`)**
- *Enters:* structured data written by `GameEngine::exportJSON()`.
- *Leaves:* the same data, read by `fetch()` in the browser.
- *Why it exists:* the simplest possible hand-off point between two
  otherwise disconnected programs (the C++ executable and the
  browser), with no server or networking required.
- *Files:* just the one `.json` file.
- *Communicates with:* both layers around it, purely by being read
  from / written to disk.

**HTML/CSS/JS Dashboard (`visualization/`)**
- *Enters:* the JSON file's contents.
- *Leaves:* rendered cards, charts, and a table in the browser.
- *Why it exists:* an optional, more polished way to present results
  in a demo.
- *Files:* `index.html`, `style.css`, `script.js`.
- *Communicates with:* the JSON file (reads it); has no path back
  into the C++ program (one-way data flow).

There is no "business logic" layer separate from the OOP classes —
in this project, the classes themselves *are* the business logic,
which is exactly the point.

---

## 10. Project Folder Structure

```text
AgroSentinel/
│
├── README.md                 # Main project overview & instructions
├── LICENSE                   # MIT license
├── .gitignore                # Excludes build artifacts, IDE files, etc.
├── CMakeLists.txt            # Build configuration
│
├── include/                  # Class DECLARATIONS (the "what", in .h files)
│   ├── Orchard.h
│   ├── Threat.h
│   ├── Scab.h
│   ├── Aphids.h
│   ├── Hailstorm.h
│   ├── DefenseAction.h
│   ├── FungicideSpray.h
│   ├── Pruning.h
│   ├── NetCovering.h
│   └── GameEngine.h
│
├── src/                       # Class IMPLEMENTATIONS (the "how", in .cpp files)
│   ├── Orchard.cpp
│   ├── Scab.cpp
│   ├── Aphids.cpp
│   ├── Hailstorm.cpp
│   ├── FungicideSpray.cpp
│   ├── Pruning.cpp
│   ├── NetCovering.cpp
│   ├── GameEngine.cpp
│   └── main.cpp               # Program entry point
│
├── visualization/              # Optional presentation layer
│   ├── index.html
│   ├── style.css
│   ├── script.js
│   └── data/
│       └── simulation_log.json # Written by the C++ program each run
│
├── tests/
│   └── test_main.cpp           # Dependency-free test suite
│
├── docs/
│   ├── PROJECT_BLUEPRINT.md    # This file
│   ├── architecture.md
│   ├── oop-concepts.md
│   ├── algorithm.md
│   ├── simulation.md
│   └── screenshots/             # Your captured screenshots go here
│
├── examples/
│   └── sample-output.txt        # A saved sample console run
│
└── assets/                      # Reserved for any extra images/diagrams
```

**Why this shape specifically:** separating `include/` from `src/` is
a standard C++ convention that keeps a class's *interface* (what
other code needs to know) visually separate from its *implementation*
(details other code shouldn't need to care about) — which is itself a
small, practical expression of encapsulation at the file level.
`visualization/` sits outside `src/`/`include/` entirely, reinforcing
that it's not part of the compiled program.

---

## 11. Most Important Section — OOP Concepts

Already covered at the top of this document
(**WHY THIS PROJECT IS AN OOP PROJECT**). The short version, restated
as a mapping table:

| Real-world entity                  | Becomes...                        |
|-------------------------------------|-------------------------------------|
| The orchard                         | `Orchard` class (object: one instance per run) |
| "A threat", generically             | `Threat` abstract class            |
| Scab / Aphids / Hailstorm           | Concrete `Threat` subclasses (objects) |
| "A defense", generically            | `DefenseAction` abstract class     |
| Spray / Pruning / Netting           | Concrete `DefenseAction` subclasses (objects) |
| The orchard's health, yield, etc.   | `Orchard`'s private attributes     |
| "Take damage", "heal", "attack"     | Methods                             |
| The simulation itself               | `GameEngine`                        |

---

## 12. Four Pillars of OOP

### 1. Encapsulation

**What it means:** bundling data together with the functions that
operate on it, and restricting direct outside access to that data.

**Why we need it:** health and yield are meaningful only within
`[0, 100]`. If any class anywhere could freely assign
`orchard.health = -50;`, the simulation's numbers would become
nonsensical, and bugs like that would be nearly impossible to trace
back to their source.

**Which class uses it:** `Orchard` (`include/Orchard.h`).

**Which data is private:** `health`, `yieldPercent`, `treeCount`,
`currentRound`, `lastThreatName`.

**Which functions are public:** `takeDamage()`, `restoreHealth()`,
`reduceYield()`, `increaseYield()`, `getHealth()`, `getYield()`,
`getTreeCount()`, `getRound()`, `getLastThreatName()`,
`setLastThreatName()`, `advanceRound()`, `isDestroyed()`,
`printStatus()`.

**Why the data isn't directly accessible:** so that *every* change to
health/yield is forced through a method that clamps the result into a
valid range — the class protects its own invariants no matter what
outside code does.

**Example from this project:**
```cpp
void Orchard::takeDamage(int amount) {
    if (amount < 0) amount = 0;                 // guard against bad input
    health = clamp(health - amount, 0, 100);    // never below 0, never above 100
}
```
No threat, defense, or engine code can bypass this — they can only
call `takeDamage()`, never touch `health` directly.

### 2. Abstraction

**What it means:** exposing *what* an object can do, while hiding
*how* it does it.

**What complexity is hidden:** the specific arithmetic each threat
uses (escalating spread level vs. fixed hailstorm damage) is
completely invisible to `GameEngine` — it just calls `attackOrchard()`.

**Which classes provide abstraction:** `Threat` and `DefenseAction`.

**What the user (i.e., `GameEngine`) sees:** a simple contract —
`attackOrchard(Orchard&)`, `getName()`, `getSeverity()`,
`getDescription()` for threats; `apply(Orchard&)`, `getName()`,
`getDescription()` for defenses.

**What happens internally (hidden from GameEngine):** e.g. `Scab`
privately tracks `spreadLevel` and grows its damage formula over time
— `GameEngine` has no idea this internal state even exists.

**Example from this project:**
```cpp
// GameEngine.cpp — this is ALL GameEngine knows or needs to know:
activeThreat.attackOrchard(orchard);
```
Whether that call internally increments a counter, checks the last
threat's name, or does nothing extra at all is completely abstracted
away from the caller.

### 3. Inheritance

**Which classes inherit from which:**

```text
Threat (base/abstract)
    |
    ├── Scab (derived)
    ├── Aphids (derived)
    └── Hailstorm (derived)

DefenseAction (base/abstract)
    |
    ├── FungicideSpray (derived)
    ├── Pruning (derived)
    └── NetCovering (derived)
```

**Why inheritance makes sense here:** every concrete threat genuinely
*is a* threat — they all need the same three or four operations
(attack, name, severity, description) but implement them completely
differently. That "is-a, but different" relationship is exactly what
inheritance models.

**Parent/base class:** `Threat` (and `DefenseAction`).

**Child/derived classes:** `Scab`, `Aphids`, `Hailstorm` (and
`FungicideSpray`, `Pruning`, `NetCovering`).

**Common properties (inherited, shared by all):** the four-function
public interface, and the requirement that they be usable
interchangeably through a `Threat&`/`DefenseAction&`.

**Specialized properties (unique per subclass):** `Scab`'s private
`spreadLevel`; `Aphids`'s private `infestationLevel`; `Hailstorm` has
no extra state at all.

**What code is reused:** the *interface* is reused (every subclass is
guaranteed to be callable the same way), even though the actual
damage/healing *logic* is not shared code — each subclass writes its
own.

### 4. Polymorphism

**What it means:** the same function call, written once, produces
different behavior depending on the actual object involved — decided
while the program is *running*, not when it's compiled.

**Why it's useful:** it lets `GameEngine` handle any current or future
threat/defense without ever being modified.

**Where it appears in this project:**
```cpp
Threat& activeThreat = pickRandomThreat();  // real type unknown here
activeThreat.attackOrchard(orchard);        // <-- polymorphic call
```

**Method overriding:** every concrete threat/defense class overrides
its base class's pure virtual functions, using the `override` keyword
(e.g. `void attackOrchard(Orchard& orchard) override;` in `Scab.h`).

**Function overloading:** not used in this project — there's no
situation here where the same function name with *different
parameter types* is genuinely useful; adding it would be an
artificial addition, not a natural fit.

**Virtual functions:** `Threat::attackOrchard()`, `getName()`,
`getSeverity()`, `getDescription()`, and `DefenseAction::apply()`,
`getName()`, `getDescription()` are all declared `virtual` (and pure
virtual, with `= 0`, in the base classes).

**How the same interface produces different behavior:** the exact
same call site, `activeThreat.attackOrchard(orchard);`, runs
`Scab::attackOrchard()` some rounds and `Hailstorm::attackOrchard()`
other rounds, without a single `if` statement checking which one it
is.

**Concrete example:** see `docs/oop-concepts.md`, section 3, for the
full trace including what would break if `virtual` were removed.

---

## 13. All Other OOP Concepts Used

**Class** — used throughout (`Orchard`, `Threat`, `Scab`, etc.). A
blueprint describing what data and behavior a category of objects has.

**Object** — e.g. the single `Orchard` instance created inside
`GameEngine`, or the `Scab` instance living in `threatPool[0]`. A
concrete instance built from a class.

**Constructor** — every class has one. E.g. `Orchard::Orchard(int
initialHealth, int initialYield, int trees)` sets up starting values.
Used because objects need valid initial state the moment they exist.

**Parameterized constructor** — `Orchard`'s constructor takes
arguments (health, yield, trees) with default values, letting
`GameEngine` create it as `Orchard orchard(100, 100, 200);` or the
tests create smaller custom orchards for boundary testing (e.g.
`Orchard orchard(5, 5, 10);`).

**Default constructor** — `Hailstorm() = default;`,
`NetCovering() = default;`, etc. — these classes need no custom setup,
so we explicitly ask the compiler to generate the normal empty
constructor.

**Destructor** — every polymorphic base class declares
`virtual ~Threat() = default;` (same for `DefenseAction`). This is
required so that, if a derived object is ever deleted through a base
pointer (which `std::unique_ptr<Threat>` effectively does), the
correct cleanup runs. Since none of our classes manage raw resources,
`= default` is sufficient — we don't need custom cleanup code, just
the *virtual*-ness of the destructor.

**Encapsulation, Abstraction, Inheritance, Polymorphism** — covered in
detail in Section 12.

**Function overloading** — *not used.* This concept is not necessary
for this project because no class in AgroSentinel needs the same
operation to accept genuinely different sets of parameter types; every
function has exactly one sensible signature.

**Operator overloading** — *not used.* This concept is not necessary
here because no AgroSentinel class represents a mathematical or
comparable value type (like a vector or a fraction) where operators
such as `+` or `==` would have an obvious, natural meaning.

**Method overriding** — used extensively; see Section 12 (every
concrete threat/defense overrides its base class's virtual functions).

**Virtual functions / Pure virtual functions / Abstract classes** —
covered in Section 12 / `docs/oop-concepts.md`.

**Static members** — *not used.* Nothing in this project needs data
or behavior shared across *all* instances of a class rather than
belonging to one particular object — each `Orchard`, threat, and
defense is independent.

**Friend functions/classes** — *not used, and deliberately avoided.*
`friend` breaks encapsulation by letting an outside function/class
reach into another class's private data. Since one of this project's
explicit goals is to *demonstrate* encapsulation, introducing `friend`
would work against that goal.

**Composition** — `GameEngine` is composed *of* an `Orchard` (it has
a plain `Orchard orchard;` member, not a pointer) — the `Orchard`'s
lifetime is entirely owned by, and tied to, its `GameEngine`. This is
a "strong ownership" (composition) relationship.

**Aggregation** — `GameEngine`'s `threatPool` and `defensePool`
(vectors of `std::unique_ptr<Threat>`/`std::unique_ptr<DefenseAction>`)
are closer to composition too, in this project, since `GameEngine`
fully owns them via smart pointers, not raw shared references. We
don't have a case of true aggregation (where a contained object could
outlive or be shared outside its container) in this project — that's
fine; not every relationship type needs to be forced in artificially.

**Association** — `Threat` and `DefenseAction` subclasses are
*associated with* `Orchard` (they take an `Orchard&` parameter and
modify it) without owning it — a "uses-a" rather than "has-a"
relationship.

**`this` pointer** — used implicitly throughout (every non-static
member function has access to it), though never referenced explicitly
by name in this codebase, since none of our methods needed to
disambiguate a member name from a parameter name or return `*this`
for chaining.

**Access specifiers** — `private` is used for all real internal state
(`Orchard`'s data members, `Scab`'s `spreadLevel`, etc.); `public` is
used for every method meant to be called from outside the class.

**Dynamic memory** — used via `std::unique_ptr<Threat>` and
`std::unique_ptr<DefenseAction>` inside `GameEngine`'s pools
(`std::make_unique<Scab>()`, etc.) — this *is* dynamic (heap)
allocation, just managed automatically instead of with raw
`new`/`delete`.

**Exception handling** — *not used explicitly.* This project handles
its one realistic failure mode — bad console input — with manual
`std::cin` state-checking (`std::cin.fail()`, `std::cin.clear()`)
rather than exceptions, because none of the operations here
(arithmetic on bounded integers, file writing) throw C++ exceptions
in normal use. Adding `try`/`catch` blocks with nothing that can
realistically throw would be artificial.

---

## 14. OOP Class Design

### Orchard
- **Purpose:** hold and protect the orchard's simulation state.
- **Attributes:** `health` (int, private), `yieldPercent` (int,
  private), `treeCount` (int, private), `currentRound` (int, private),
  `lastThreatName` (std::string, private).
- **Methods:** `takeDamage()`, `restoreHealth()`, `reduceYield()`,
  `increaseYield()`, `getHealth()`, `getYield()`, `getTreeCount()`,
  `getRound()`, `getLastThreatName()`, `setLastThreatName()`,
  `advanceRound()`, `isDestroyed()`, `printStatus()`.
- **Constructor:** `Orchard(int initialHealth=100, int
  initialYield=100, int trees=200)`.
- **Destructor:** implicit/default (no dynamic resources to clean up).
- **Access modifiers:** all data private; all listed methods public.
- **Relationships:** used (associated with) by every `Threat` and
  `DefenseAction`; owned (composed) by `GameEngine`.

### Threat (abstract)
- **Purpose:** define the shared contract every threat must follow.
- **Attributes:** none (purely an interface).
- **Methods:** `attackOrchard(Orchard&)`, `getName()`,
  `getSeverity()`, `getDescription()` — all pure virtual.
- **Constructor:** none needed (no data to initialize).
- **Destructor:** `virtual ~Threat() = default;`
- **Access modifiers:** all methods public (an interface has nothing
  to hide).
- **Relationships:** base class for `Scab`, `Aphids`, `Hailstorm`.

### Scab / Aphids / Hailstorm
- **Purpose:** implement one specific threat's behavior.
- **Attributes:** `Scab` — `spreadLevel` (int, private); `Aphids` —
  `infestationLevel` (int, private); `Hailstorm` — none.
- **Methods:** overrides of all of `Threat`'s virtual functions.
- **Constructor:** default (`Scab()`, initializing `spreadLevel(0)`,
  etc.).
- **Destructor:** implicit/default.
- **Access modifiers:** internal state private; interface public.
- **Relationships:** derived from `Threat`; modify `Orchard` via its
  public methods.

### DefenseAction (abstract) / FungicideSpray / Pruning / NetCovering
- Mirrors the `Threat` family exactly, with `apply(Orchard&)`,
  `getName()`, `getDescription()` as the shared interface, and each
  concrete class implementing its own healing formula plus a
  conditional bonus based on `orchard.getLastThreatName()`.

### GameEngine
- **Purpose:** drive the simulation loop; the only class that knows
  about every other class.
- **Attributes:** `orchard` (Orchard, by value — composition),
  `threatPool` (`std::vector<std::unique_ptr<Threat>>`),
  `defensePool` (`std::vector<std::unique_ptr<DefenseAction>>`),
  `history` (`std::vector<EventRecord>`), `totalRounds` (int), `rng`
  (`std::mt19937`).
- **Methods:** `run()`, `printFinalReport()`, `exportJSON()`, plus
  private helpers `pickRandomThreat()`, `pickDefenseByChoice()`,
  `printDefenseMenu()`, `promptDefenseChoice()`.
- **Constructor:** `GameEngine(int rounds=5, unsigned int
  seed=std::random_device{}())` — builds the threat/defense pools once.
- **Destructor:** implicit/default (the `unique_ptr`s clean up their
  owned objects automatically).
- **Access modifiers:** all state private; all listed methods
  appropriately public/private.
- **Relationships:** composes one `Orchard`; owns (via smart pointers)
  all threats and defenses; called by `main()`.

### Summary table

| Class          | Responsibility                              | Important Attributes                          | Important Methods                          |
|-----------------|----------------------------------------------|-------------------------------------------------|-----------------------------------------------|
| `Orchard`       | Protect and expose orchard state             | `health`, `yieldPercent`, `treeCount`            | `takeDamage()`, `restoreHealth()`, `getHealth()` |
| `Threat`        | Define shared threat interface (abstract)    | —                                                 | `attackOrchard()` (pure virtual)              |
| `Scab`/`Aphids`/`Hailstorm` | Implement one threat's behavior | `spreadLevel` / `infestationLevel` / —           | `attackOrchard()`, `getSeverity()`            |
| `DefenseAction` | Define shared defense interface (abstract)   | —                                                 | `apply()` (pure virtual)                      |
| `FungicideSpray`/`Pruning`/`NetCovering` | Implement one defense | —                                     | `apply()`                                     |
| `GameEngine`    | Drive the simulation loop                    | `orchard`, `threatPool`, `defensePool`, `history` | `run()`, `printFinalReport()`, `exportJSON()` |

### How the classes communicate

`main()` creates one `GameEngine`. `GameEngine` owns one `Orchard` and
pools of `Threat`/`DefenseAction` pointers. Each round, `GameEngine`
selects a `Threat&` and calls its interface method, passing in the
`Orchard&` by reference so the threat can modify it directly (through
`Orchard`'s public methods only). The same pattern repeats for the
chosen `DefenseAction&`. No class other than `GameEngine` holds
references to more than one other class at a time.

---

## 15. Class Relationship Diagram

```text
                         GameEngine
                        /    |     \
             (composes)/     |      \(owns via unique_ptr)
                      /      |       \
                Orchard   Threat*   DefenseAction*
                   ^          ^            ^
                   |          |            |
         (used by) |    (inherits)   (inherits)
                   |          |            |
        Scab,Aphids,Hailstorm |   FungicideSpray,Pruning,NetCovering
                   \__________|____________/
                     all modify Orchard (association)
```

**Inheritance:** `Scab`/`Aphids`/`Hailstorm` → `Threat`;
`FungicideSpray`/`Pruning`/`NetCovering` → `DefenseAction`.

**Composition:** `GameEngine` *has-a* `Orchard` as a plain (non-
pointer) member — the `Orchard`'s entire lifetime is bound to its
owning `GameEngine`.

**Ownership via smart pointer (composition-like):** `GameEngine`
*owns* its threats/defenses through `std::unique_ptr`, meaning they
are destroyed automatically when `GameEngine` is destroyed.

**Association:** `Threat`/`DefenseAction` subclasses *use* an
`Orchard&` parameter to modify it, without owning it — the `Orchard`
object continues to exist independently of any particular threat or
defense call.

---

## 16. Complete Data Flow

```text
User types a defense choice (e.g. "1") at the terminal prompt
        ↓
std::cin reads the raw input in GameEngine::promptDefenseChoice()
        ↓
Input is validated (numeric? in range 1-3?) — reprompt if not
        ↓
GameEngine::pickDefenseByChoice(choice) returns a DefenseAction&
        ↓
chosenDefense.apply(orchard) is called — POLYMORPHIC DISPATCH
        ↓
The real object (e.g. FungicideSpray) runs its own apply() logic
        ↓
It reads orchard.getLastThreatName() and calls orchard.restoreHealth()
/ orchard.increaseYield() — Orchard's private clamp() enforces limits
        ↓
Orchard's private state (health, yieldPercent) is updated
        ↓
GameEngine reads the new state via getHealth()/getYield() and appends
an EventRecord to its history vector
        ↓
orchard.printStatus() prints the updated numbers to the console
        ↓
(after all rounds) GameEngine::exportJSON() writes the full history
+ final state to visualization/data/simulation_log.json
        ↓
(separately, later) the browser's script.js fetches that JSON file
        ↓
Chart.js renders it as cards, charts, and a table
```

---

## 17. How the Project Will Actually Be Built

### Phase 1 — Understanding the problem
Understand that the goal is a simulation where the *choice of which
threat/defense object is active* must be resolved at runtime, and that
the engine must never contain logic like "if this is a Scab..."

### Phase 2 — Planning
Decide the classes needed: `Orchard`, `Threat` (+3 subclasses),
`DefenseAction` (+3 subclasses), `GameEngine`. Decide `Orchard`'s
attributes (health, yield, trees) and their valid ranges.

### Phase 3 — Basic C++ implementation
Start with `Orchard` alone — get it compiling and manually testable
before any threats exist. Then create the empty `Threat` abstract
class, and one working subclass (`Scab`) before adding the other two.

### Phase 4 — OOP implementation
Add `override`/`virtual` carefully; verify the base classes cannot be
instantiated (try writing `Threat t;` and confirm it fails to
compile — that's proof abstraction is really in effect). Add the
remaining subclasses only once the first pair (one threat, one
defense) fully works end-to-end.

### Phase 5 — Data handling
Decide the `EventRecord` struct's fields, based on what the final
report and dashboard actually need to show.

### Phase 6 — "Backend" (the engine)
Build `GameEngine`'s constructor (populate the pools), then `run()`
(the round loop), then `printFinalReport()`, then `exportJSON()`.

### Phase 7 — Frontend
Build `index.html`'s static layout first (with placeholder numbers),
then `style.css`, then `script.js` to make it dynamic.

### Phase 8 — Integration
Confirm the JSON keys `script.js` expects exactly match the keys
`GameEngine::exportJSON()` writes.

### Phase 9 — Testing
Write `tests/test_main.cpp` covering damage, healing, boundary
clamping, and — critically — a test that proves polymorphism by
storing mixed threat types in one `std::vector<Threat*>` and calling
the same line of code on each.

### Phase 10 — Final polishing
Add `.gitignore`, `LICENSE`, README, docs, screenshots, and push to
GitHub with a clean commit history.

---

## 18. Build It From Zero

**Step 1 — Create `include/Orchard.h` and `src/Orchard.cpp`.**
*Why first:* every other class depends on `Orchard` existing.
*Concept:* encapsulation (private data + public methods).
*Test it:* write a tiny throwaway `main()` that creates an `Orchard`,
calls `takeDamage(30)`, and prints `getHealth()` — confirm it prints
70.

**Step 2 — Create `include/Threat.h` (abstract, no .cpp needed).**
*Why:* establishes the shared interface before any concrete threat
exists. *Concept:* abstraction, pure virtual functions. *Test it:*
try to compile `Threat t;` somewhere — confirm the compiler refuses.

**Step 3 — Create `Scab.h`/`Scab.cpp`.**
*Why:* the first concrete threat, to prove the abstract interface
works. *Concept:* inheritance, `override`. *Test it:* create a `Scab`
object directly, call `attackOrchard()` on a test `Orchard`, confirm
health/yield drop.

**Step 4 — Create `Aphids.h`/`.cpp` and `Hailstorm.h`/`.cpp`.**
*Why:* now that the pattern is proven once, repeat it twice more with
different formulas. *Test it:* same manual test as Step 3, for each.

**Step 5 — Repeat Steps 2–4 for `DefenseAction` and its three
subclasses.**

**Step 6 — Create `GameEngine.h`/`.cpp`.**
*Why:* now that both hierarchies exist, build the class that ties them
together. *Concept:* polymorphism (calling through base
references), RAII (`std::unique_ptr`). *Test it:* run the full
interactive loop manually and watch the console output.

**Step 7 — Create `main.cpp`.**
*Why:* the entry point, kept intentionally almost empty. *Test it:*
compile the whole program and run it.

**Step 8 — Write `tests/test_main.cpp`.**
*Why:* prove correctness formally instead of only by eyeballing
console output. *Test it:* run the test binary, confirm
"ALL TESTS PASSED."

**Step 9 — Build `visualization/`.**
*Why:* optional, but adds presentation value; done last since it
depends on the JSON export already existing. *Test it:* run the C++
program once, then serve `visualization/` locally and check the
dashboard populates correctly.

**Step 10 — Write documentation, `.gitignore`, `LICENSE`, and push to
GitHub.**

---

## 19. Example of Internal Working (One Feature, Fully Traced)

**Feature: applying Net Covering after a Hailstorm attack.**

```text
USER ACTION
    Types "3" at the defense prompt
        ↓
UI (terminal)
    std::cin >> choice; reads "3"
        ↓
INPUT VALIDATION
    promptDefenseChoice() confirms 3 is between 1 and defensePool.size()
        ↓
OBJECT SELECTION
    pickDefenseByChoice(3) returns *defensePool[2], i.e. the NetCovering object,
    as a DefenseAction&
        ↓
CLASS METHOD (POLYMORPHIC CALL)
    chosenDefense.apply(orchard) resolves, at runtime, to
    NetCovering::apply(Orchard& orchard)
        ↓
INTERNAL LOGIC
    NetCovering::apply() checks orchard.getLastThreatName() == "Hailstorm"
    (true, since Hailstorm attacked this round) → applies bonus: healthGain = 28,
    yieldGain = 13
        ↓
DATA UPDATE (ENCAPSULATED)
    orchard.restoreHealth(28) and orchard.increaseYield(13) run, each
    clamping the result into [0, 100] via Orchard's private clamp() helper
        ↓
RESULT
    orchard.getHealth() / orchard.getYield() now reflect the healed values
        ↓
UI (terminal)
    orchard.printStatus() prints the new Health/Yield/Trees block
        ↓
(Later) EXPORTED
    This round's before/after values are written into simulation_log.json,
    and eventually rendered as a row in the dashboard's Event Log table
    and a data point on both charts.
```

---

## 20. Database / Data Storage

As established in Section 7: **no database is used.** To restate why,
directly against the checklist a database question usually raises:

- **What data needs to be stored?** Just the most recent simulation's
  event history and final stats — one "record," temporarily.
- **Why it needs to be stored (briefly) at all:** so the dashboard,
  which runs in a separate process (the browser) at a separate time,
  can display it.
- **Database choice:** none — a single JSON file instead.
- **Tables/fields:** N/A; the JSON file's structure (see
  `visualization/data/simulation_log.json`) plays this role: a
  top-level object with `finalHealth`, `finalYield`, `treeCount`,
  `totalRounds`, `roundsCompleted`, `destroyed`, and an `events` array
  where each entry has `round`, `threat`, `severity`,
  `healthBeforeThreat`, `healthAfterThreat`, `yieldBeforeThreat`,
  `yieldAfterThreat`, `defense`, `healthAfterDefense`,
  `yieldAfterDefense`.
- **Primary/foreign keys:** N/A — there is only one "table" (the
  events array) and no relationships between multiple tables to
  manage.
- **How C++ interacts with storage:** plain `std::ofstream`, writing
  hand-built JSON text — no database driver or query language needed.
- **Insert/retrieve/update/delete:** the file is fully rewritten
  (overwritten) each time the simulation runs — there's no partial
  update, no query, and no delete operation, because there's only ever
  one current "record."

**Why a simpler storage method is genuinely better here, not just
easier:** a real database's strengths — concurrent access, complex
queries, relationships between many records — are all unused if we
have one temporary snapshot of one simulation run. Using one would add
setup and conceptual overhead without adding any real capability to
this project.

---

## 21. Frontend–Backend Connection

**What "frontend" means:** the part of a program the user directly
sees and interacts with — here, the terminal output/input, and
optionally the browser dashboard.

**What "backend" means:** the part that holds the logic and data
processing, usually not directly visible to the user — here, the C++
`GameEngine` and its class hierarchy.

**What an API is:** "Application Programming Interface" — a defined
set of rules for how one piece of software can request information or
actions from another, usually over a network, using a specific
request/response format (very often JSON over HTTP).

**Why an API is normally needed:** when a frontend and backend run as
two *separate, simultaneously-running* programs (e.g. a web server and
a browser talking live), they need an agreed-upon way to ask for and
receive data in real time.

**Does AgroSentinel use one?** No — and this is a deliberate,
justified choice, not a missing feature. The C++ program and the
dashboard are never running *at the same time*, talking to each
other live; the C++ program finishes completely, writes one file,
and *later*, separately, the dashboard reads that file. There is no
request, no response, no live connection — so there is nothing for an
API to do here. Building one would mean adding an HTTP server and
JSON-parsing library to the C++ code purely to satisfy an
architecture pattern the project doesn't actually need.

**Concrete example of how the data still gets from backend to
frontend, using Net Covering vs. Hailstorm (from Section 19):**
after `GameEngine::exportJSON()` runs, the relevant JSON fragment
looks like:
```json
{ "round": 5, "threat": "Hailstorm", "severity": 8,
  "healthBeforeThreat": 100, "healthAfterThreat": 75,
  "defense": "Net Covering", "healthAfterDefense": 85 }
```
`script.js`'s `fetch("data/simulation_log.json")` reads the whole
file, `JSON.parse`s it automatically (the browser's `fetch().json()`
does this), and `renderLogTable()` turns that one object into one
`<tr>` row in the Event Log table.

---

## 22. UI/UX Design

**Color/theme direction:** an earthy, agricultural green/amber palette
(`--green: #3f7d3a`, `--amber: #c98a2c`, `--red: #b5432e` for
severity/warnings), on a soft off-white background — evokes "orchard"
without relying on photos or icons that would need external assets.

**Typography:** the system's default sans-serif stack (Segoe UI,
Roboto, Helvetica, Arial) — no custom font loading, keeping the page
dependency-free and fast.

**Layout:** a single centered column, max-width ~1000px, with a
summary-cards grid, two stacked chart panels, and a table — a simple,
predictable top-to-bottom reading order appropriate for a one-page
report.

**Navigation:** none — there's only one page, so a navbar would be an
empty gesture.

**Buttons:** none in the dashboard (it's read-only); in the terminal,
"buttons" are the numbered menu choices (1/2/3).

**Cards:** four summary cards (Final Health, Final Yield, Rounds
Completed, Trees) with a big number and, for health/yield, a small
progress bar.

**Forms:** none — the only input in the whole project is the
terminal's numeric defense choice.

**Tables:** one — the Event Log, listing every round's threat,
severity, health/yield progression, and defense used.

**Icons:** a single leaf emoji (🌿) in the header — deliberately
minimal, avoiding an icon-font dependency for one decorative glyph.

**Feedback messages:** the terminal validates bad input with a plain
re-prompt message ("Please enter a valid number:"); the dashboard's
status pill reads "Orchard survived" / "Orchard destroyed" /
"No simulation data yet."

**Loading states:** the dashboard's status pill initially reads
"Loading data…" until the fetch resolves.

**Error states:** if `simulation_log.json` doesn't exist yet (the C++
program hasn't been run), the dashboard shows "No simulation data yet"
instead of a blank/broken page, and logs a helpful console warning.

**Empty states:** not applicable beyond the above — the event table
is always populated once real data loads, since a simulation with
zero rounds isn't a supported configuration.

**Responsive design:** the cards grid uses
`grid-template-columns: repeat(auto-fit, minmax(180px, 1fr))`, so it
naturally reflows to fewer columns on a narrow browser window without
extra media queries.

---

## 23. Features

### Core/MVP Features (required)
- Abstract `Threat`/`DefenseAction` interfaces with pure virtual
  functions. *(Required: this is the project's entire thesis.)*
- Three distinct, genuinely different threats and defenses.
  *(Required: without variety, polymorphism has nothing to
  demonstrate.)*
- Encapsulated `Orchard` state. *(Required: the second pillar being
  graded.)*
- Multi-round simulation loop with user-selected defenses.
  *(Required: this is the actual program.)*
- Final report and event log. *(Required: needed to evaluate outcomes
  and support the demo.)*
- Test suite proving correctness and polymorphism. *(Required: proof,
  not just claims.)*

### Secondary Features (useful, not essential)
- JSON export + HTML/CSS/JS dashboard. *(Useful for a more polished
  demo; the program is fully functional and fully graded on OOP
  without it.)*
- Input-validation loop for defense choice (rejecting bad input
  gracefully instead of crashing). *(Useful robustness; the core
  OOP demonstration doesn't depend on it.)*

### Future Features (not built, could be added later)
- A fourth threat/defense pair (e.g. `Drought`/`Irrigation`) — would
  require zero changes to `GameEngine`, a strong follow-up
  demonstration of the design's extensibility.
- Configurable difficulty (round count, damage multipliers) via
  command-line arguments.
- A "compare multiple past runs" view in the dashboard, requiring the
  JSON export to append rather than overwrite.

---

## 24. Testing

| Test Case                                              | Input                                   | Expected Output                                   | Purpose                                    |
|-----------------------------------------------------------|-------------------------------------------|-------------------------------------------------------|-----------------------------------------------|
| Normal damage                                              | `takeDamage(30)` on a full orchard         | Health drops from 100 to 70                            | Confirms basic damage math                    |
| Overkill (boundary) damage                                 | `takeDamage(1000)` on a full orchard       | Health clamps at 0, never negative                     | Confirms encapsulation's invariant protection |
| Over-healing (boundary)                                    | `restoreHealth(1000)` on a half-health orchard | Health clamps at 100, never above max               | Confirms encapsulation's invariant protection |
| Invalid/negative input                                     | `takeDamage(-50)`                          | Treated as zero damage, health unchanged                | Confirms methods guard against bad input      |
| Escalating threat behavior                                 | Call `Scab::attackOrchard()` twice in a row | Second call deals strictly more damage than the first  | Confirms Scab's stateful, worsening behavior  |
| Fixed threat behavior                                      | Call `Hailstorm::attackOrchard()` twice     | Both calls deal exactly the same damage (25)            | Confirms Hailstorm has no escalation, by design |
| Conditional defense bonus                                  | Apply `FungicideSpray` right after `Scab` attacks | Larger health gain than applying it with no prior Scab attack | Confirms defense/threat "counter" logic works |
| Runtime polymorphism (core requirement)                    | Store `Scab`, `Aphids`, `Hailstorm` in one `std::vector<Threat*>`, call `attackOrchard()` on each via a loop | Each call damages the orchard using genuinely different logic | Directly proves dynamic dispatch is real, not simulated |
| Destroyed orchard (boundary)                                | Deal 25+ damage to an orchard with only 5 health | `getHealth() == 0` and `isDestroyed() == true`         | Confirms boundary handling at the "game over" edge |
| Invalid console input (manual/interactive test, not automated) | Type a letter instead of a number at the defense prompt | Program re-prompts instead of crashing                  | Confirms input-validation robustness           |

Full implementation of all of these lives in `tests/test_main.cpp`.

---

## 25. Possible Errors and How to Handle Them

- **Invalid input (non-numeric or out-of-range defense choice):**
  handled by `promptDefenseChoice()`'s validation loop — reprompt,
  never crash.
- **Missing/empty JSON file (dashboard opened before the C++ program
  ever ran):** `script.js`'s `try/catch` around `fetch()` catches the
  failure and shows "No simulation data yet" instead of a broken page.
- **File write failure (e.g. no write permission for
  `visualization/data/`):** `GameEngine::exportJSON()` checks
  `out.is_open()` and prints a warning to `std::cerr` instead of
  silently failing or crashing.
- **Database failure:** not applicable — no database exists to fail.
- **Network failure:** not applicable for the C++ program (it does no
  networking); the only "network" involved is the CDN link to
  Chart.js, which — if unreachable — would simply mean the charts
  don't render, while the cards and table (which don't depend on
  Chart.js) still would.
- **Orchard reaching 0 health mid-simulation:** explicitly handled —
  `GameEngine::run()` checks `orchard.isDestroyed()` right after each
  attack and ends the simulation early with a clear message, rather
  than continuing to prompt for defenses against a destroyed orchard.
- **Program crashes from unexpected `std::cin` state:** avoided by
  always checking `std::cin.fail()` and calling `std::cin.clear()` +
  `std::cin.ignore(...)` to recover, rather than letting a bad read
  leave the stream in a broken state that would loop forever or crash
  later.

---

## 26. Security Basics

AgroSentinel is a single-user, offline console program with an
optional static local dashboard — most standard "security" concerns
(authentication, authorization, SQL injection) genuinely do not apply,
and forcing them in would be dishonest padding. What *does* apply:

- **Input validation:** the defense-choice prompt validates both that
  the input is numeric and that it's within the valid menu range —
  this is the one place untrusted (user-typed) input enters the
  program, and it's handled.
- **Password protection / Authentication / Authorization:** not
  applicable — there are no user accounts, logins, or permission
  levels in this project; adding them would be unrelated scope creep.
- **SQL injection:** not applicable — there is no database and no SQL
  anywhere in the project.
- **Secure data handling:** the only "data" ever written to disk is
  non-sensitive simulation statistics (health/yield numbers) — there
  is no personal, financial, or otherwise sensitive information
  involved, so no encryption or access-control measures are needed.

---

## 27. Performance

- **Which operations are expensive:** none, by design — every
  operation in this project (damage calculation, healing calculation,
  random threat selection, status printing) works on a small, fixed
  number of integers.
- **Which data structures are used, and why:**
  `std::vector<std::unique_ptr<Threat>>` /
  `std::vector<std::unique_ptr<DefenseAction>>` for the fixed-size
  pools (a vector is the natural default C++ container for "a
  small, ordered collection I need to index into"), and
  `std::vector<EventRecord>` for the history (it needs to grow by one
  element per round, which `std::vector` handles efficiently with
  amortized O(1) `push_back`).
- **Time complexity:** O(1) per round's threat/defense logic; O(R)
  for the whole simulation and for generating the final report/JSON
  (R = number of rounds, a small constant, default 5). Full detail in
  `docs/algorithm.md`.
- **Space complexity:** O(R) — the only structure that grows with the
  simulation is the event history; everything else is fixed-size.
- **Why this is appropriate for a beginner project:** there's no
  large dataset, no repeated searching, and no algorithmic bottleneck
  to optimize — correctness and clean OOP design are the actual
  engineering challenge here, not performance tuning.

---

## 28. GitHub Structure

- **Repository name:** `AgroSentinel`.
- **Branches:** a single `main` branch is sufficient for a project of
  this size; a beginner does not need feature branches unless
  practicing that workflow deliberately.
- **Commits:** see the staged commit plan below — one logical unit of
  work per commit, with a clear, descriptive message.
- **README:** the project root `README.md`, covering overview,
  setup, and usage (already written).
- **Source code:** `include/`, `src/`.
- **Documentation:** `docs/` (this file plus the four supporting docs).
- **Screenshots:** `docs/screenshots/`.
- **Demo:** the `examples/sample-output.txt` file, plus, if desired, a
  short screen recording linked from the README.
- **Future improvements:** documented in the main README's "Future
  Improvements" section.

### Recommended commit milestones

```text
1. Initial project structure, .gitignore, LICENSE, CMakeLists.txt
2. Implement Orchard class (encapsulation)
3. Add abstract Threat and DefenseAction base classes
4. Add concrete threat classes: Scab, Aphids, Hailstorm
5. Add concrete defense classes: FungicideSpray, Pruning, NetCovering
6. Implement GameEngine and the polymorphic simulation loop
7. Add main.cpp entry point
8. Add test suite
9. Add visualization dashboard (HTML/CSS/JS)
10. Add documentation (architecture, OOP concepts, algorithm, simulation, blueprint)
11. Add sample output, screenshots, and finalize README
```

---

## 29. What I Will Learn From This Project

- **Programming / C++:** modern C++17 syntax, header/source
  separation, const-correctness, `override`.
- **OOP:** genuine, load-bearing use of all four pillars, plus
  supporting concepts like RAII and composition vs. association.
- **Data structures:** practical use of `std::vector` for both
  fixed-size pools and a growing event log.
- **Algorithms:** basic randomized selection (`std::mt19937` +
  `std::uniform_int_distribution`), and reasoning honestly about time/
  space complexity even when it's simple.
- **Frontend:** minimal, dependency-light HTML/CSS/JS, and using a
  charting library (Chart.js) correctly.
- **Backend (conceptually):** understanding that "backend" is a role
  (holding logic/data), not necessarily a network server — and when a
  full client-server/API architecture is warranted vs. unnecessary.
- **Database (conceptually):** recognizing when a database is
  actually needed vs. when a simpler file-based approach is the more
  honest engineering choice.
- **Git/GitHub:** repository setup, staged commits, `.gitignore`
  hygiene, and writing a professional README.
- **Software architecture:** separating a graded "engine" from an
  optional "presentation" layer, and documenting *why*, not just
  *what*.
- **Testing:** writing a dependency-free test suite, including a test
  specifically designed to prove a design property (polymorphism)
  rather than just check arithmetic.
- **Problem solving:** working through ambiguous requirements (how
  much should each threat/defense do?) by making, and being able to
  justify, concrete design decisions.

---

## 30. Viva / Presentation Preparation

### Basic questions
**Q: What is AgroSentinel?**
A: A C++ simulation where different threats attack an orchard each
round and I choose defenses to respond, built specifically to
demonstrate genuine OOP design.

**Q: What does the program actually output?**
A: Console status updates each round, a final report with a verdict,
and an exported JSON file that an optional dashboard can display.

### OOP questions
**Q: Where exactly is polymorphism demonstrated?**
A: In `GameEngine`, where `activeThreat.attackOrchard(orchard)` is
called through a `Threat&` — the real override that runs depends on
the actual object, decided at runtime.

**Q: How do you know it's real polymorphism and not `if`-chains in
disguise?**
A: There is no code anywhere checking the threat's *type* to decide
*how* it attacks — I have a dedicated test that puts three different
threat types in one vector and calls the exact same line of code on
each, confirming different behavior runs each time.

### C++ questions
**Q: Why `std::unique_ptr` instead of raw pointers?**
A: It gives automatic, guaranteed cleanup (RAII) — no manual `delete`
calls, no risk of memory leaks, while still allowing polymorphic
storage of different derived types behind one base type.

**Q: Why `override` on every derived function?**
A: It makes the compiler verify I'm actually overriding a real base
class virtual function with a matching signature — protects against
silent typos that would otherwise just create an unrelated new
function.

### Architecture questions
**Q: Why is there no database?**
A: The project only ever needs to hand off one temporary snapshot (the
latest run) from the C++ program to the dashboard — a single JSON
file does that with far less complexity than setting up and querying
an actual database, with no loss of functionality for what's needed.

**Q: Why is there no API/server?**
A: The C++ program and the dashboard never run at the same time
talking live to each other — the C++ program finishes and writes a
file; the dashboard reads it later. An API solves live communication
between two simultaneously-running programs, which isn't the situation
here.

### Technology-stack questions
**Q: Why C++ instead of Python/Java for the OOP core?**
A: C++'s explicit `virtual`/`override`/abstract-class mechanics make
the mechanics of polymorphism directly visible in the code, which
suits a project whose whole purpose is demonstrating that mechanism.

**Q: Why vanilla JS instead of React for the dashboard?**
A: The dashboard is a single, static, read-only report page — a
framework's component/state management would add complexity with no
functional benefit here.

### Database questions
**Q: If you needed to scale this to many saved runs, what would you
add?**
A: I'd move from a single overwritten JSON file to either an
append-only JSON array of runs, or, if querying/filtering many runs
became important, a lightweight embedded database like SQLite.

### Frontend questions
**Q: Why doesn't opening `index.html` directly (double-click) work?**
A: Browsers block `fetch()` requests to local files for security
reasons; running a tiny local web server (e.g.
`python3 -m http.server`) serves the files over `http://`, which
`fetch()` is allowed to read.

### "Why did you use this?" / "Why didn't you use X?" questions
**Q: Why not use exceptions for error handling?**
A: None of this project's operations (bounded integer math, file
writing checked with `is_open()`) realistically throw C++ exceptions
in normal use, so adding `try`/`catch` blocks would be artificial;
console-input validation is handled directly through `std::cin`'s
own state-checking instead.

**Q: Why not add a login/user system?**
A: There's no multi-user concept in this project at all — it's a
single-player, single-session simulation — so authentication would be
unrelated scope creep, not a missing requirement.

---

## 31. Final Project Summary

AgroSentinel is a C++17 console simulation in which an orchard, over
several rounds, is attacked by randomly chosen threats — a fungal
disease, an insect infestation, or a hailstorm — and defended with a
player-chosen response — a chemical spray, pruning, or protective
netting. It was created to give a concrete, working, and genuinely
necessary (not decorative) demonstration of all four pillars of
Object-Oriented Programming: **encapsulation** (Orchard's protected,
clamped state), **abstraction** (the `Threat`/`DefenseAction` abstract
interfaces), **inheritance** (six concrete subclasses sharing two
interfaces), and **polymorphism** (the `GameEngine` calling through
base references and letting C++'s virtual dispatch pick the correct
behavior at runtime). It uses no database and no API by deliberate,
justified design choice — a single JSON file is all the "data
handoff" the project actually needs, since the optional HTML/CSS/JS
dashboard only ever reads a completed run after the fact, never
communicating live with the C++ program. The user can play through
multiple rounds, see a final report and event log, and optionally
view the same results as a browser dashboard with charts. Building it
required practicing modern C++17 idioms (smart pointers, `override`),
CMake project structuring, dependency-free test writing, and clear
technical documentation — the complete, realistic lifecycle of a small
but genuinely well-engineered piece of software. Future improvements
could include additional threat/defense classes (requiring zero
`GameEngine` changes, itself a strong proof of the design's
extensibility), configurable difficulty, and multi-run comparison in
the dashboard.

---

# BEGINNER BUILD CHECKLIST

- [ ] Read through this blueprint fully before writing any code
- [ ] Install a C++17-capable compiler (e.g. `g++`) and confirm it works (`g++ --version`)
- [ ] Install CMake (optional but recommended) and confirm it works (`cmake --version`)
- [ ] Create a GitHub account (if you don't have one) and a new empty repository named `AgroSentinel`
- [ ] Create the local project folder structure (`include/`, `src/`, `tests/`, `visualization/`, `docs/`, `examples/`, `assets/`)
- [ ] Write `.gitignore` and `LICENSE` first, so build artifacts never get accidentally committed
- [ ] Design `Orchard`'s attributes and valid ranges on paper before coding it
- [ ] Implement `Orchard.h` / `Orchard.cpp` (encapsulation) and manually test it with a throwaway `main()`
- [ ] Implement the abstract `Threat.h` (abstraction) — confirm it cannot be instantiated directly
- [ ] Implement `Scab` (first concrete threat) and manually test it against a test `Orchard`
- [ ] Implement `Aphids` and `Hailstorm` (inheritance, specialized behavior)
- [ ] Implement the abstract `DefenseAction.h`
- [ ] Implement `FungicideSpray`, `Pruning`, `NetCovering`
- [ ] Implement `GameEngine.h` / `GameEngine.cpp` (polymorphism — calling through base references; RAII via smart pointers)
- [ ] Implement `main.cpp` and get the full interactive simulation running end-to-end
- [ ] Write `CMakeLists.txt` and confirm the project builds cleanly with `-Wall -Wextra`
- [ ] Write `tests/test_main.cpp`, including a dedicated polymorphism test, and confirm all tests pass
- [ ] Add `GameEngine::exportJSON()` and confirm a valid JSON file is produced after a run
- [ ] Build `visualization/index.html`, `style.css`, and `script.js`, and confirm the dashboard renders real data (served via a local web server, not opened directly)
- [ ] Write the main `README.md` and the supporting `docs/` files (architecture, OOP concepts, algorithm, simulation, this blueprint)
- [ ] Save a sample console run to `examples/sample-output.txt`
- [ ] Take and add screenshots to `docs/screenshots/`
- [ ] `git init`, `git add .`, and make your first commit
- [ ] Connect the local repo to GitHub and push (`git remote add origin ...`, `git push -u origin main`)
- [ ] Make the remaining staged commits (see Section 28) if you want a more granular history
- [ ] Prepare and rehearse the 30-second / 2-minute / 5-minute explanations
- [ ] Prepare and rehearse the professor demo script
- [ ] Review the viva Q&A (Section 30) until you can answer each one without notes
