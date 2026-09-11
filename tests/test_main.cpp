// ============================================================================
// AgroSentinel test suite
// ----------------------------------------------------------------------------
// This does NOT use an external testing framework (like GoogleTest), on
// purpose - it keeps things beginner-friendly and dependency-free. It uses
// a tiny hand-written "CHECK" macro instead.
//
// CHECK(condition, description):
//   - If "condition" is true, the test passes and we print "[PASS]".
//   - If "condition" is false, we print "[FAIL]" with the description and
//     remember that at least one test failed, so main() can return a
//     non-zero exit code (the standard way of telling CI systems /
//     "ctest" that something went wrong).
// ============================================================================

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Orchard.h"
#include "Threat.h"
#include "Scab.h"
#include "Aphids.h"
#include "Hailstorm.h"
#include "DefenseAction.h"
#include "FungicideSpray.h"
#include "Pruning.h"
#include "NetCovering.h"

static int failures = 0;

#define CHECK(condition, description)                                       \
    do {                                                                     \
        if (condition) {                                                    \
            std::cout << "[PASS] " << description << "\n";                  \
        } else {                                                            \
            std::cout << "[FAIL] " << description << "\n";                  \
            failures++;                                                     \
        }                                                                    \
    } while (0)

void test_orchard_damage_and_clamping() {
    std::cout << "\n-- Orchard: damage & clamping --\n";
    Orchard orchard(100, 100, 50);

    orchard.takeDamage(30);
    CHECK(orchard.getHealth() == 70, "takeDamage(30) reduces health from 100 to 70");

    orchard.takeDamage(1000);
    CHECK(orchard.getHealth() == 0, "takeDamage(1000) clamps health at 0, never negative");

    Orchard orchard2(50, 50, 10);
    orchard2.restoreHealth(1000);
    CHECK(orchard2.getHealth() == 100, "restoreHealth(1000) clamps health at 100, never above max");
}

void test_orchard_yield_changes() {
    std::cout << "\n-- Orchard: yield changes --\n";
    Orchard orchard(100, 100, 50);

    orchard.reduceYield(40);
    CHECK(orchard.getYield() == 60, "reduceYield(40) reduces yield from 100 to 60");

    orchard.increaseYield(20);
    CHECK(orchard.getYield() == 80, "increaseYield(20) raises yield from 60 to 80");

    orchard.reduceYield(1000);
    CHECK(orchard.getYield() == 0, "reduceYield(1000) clamps yield at 0");
}

void test_orchard_encapsulation_via_negative_inputs() {
    std::cout << "\n-- Orchard: encapsulation guards against bad input --\n";
    Orchard orchard(100, 100, 50);

    // Negative amounts passed to "damage" methods should not accidentally
    // heal the orchard - the class defends its own invariants.
    orchard.takeDamage(-50);
    CHECK(orchard.getHealth() == 100, "takeDamage(-50) is treated as zero damage, not healing");

    orchard.reduceYield(-50);
    CHECK(orchard.getYield() == 100, "reduceYield(-50) is treated as zero, not a yield boost");
}

void test_scab_attack_behavior() {
    std::cout << "\n-- Scab: polymorphic attack behaviour --\n";
    Orchard orchard(100, 100, 50);
    Scab scab;

    scab.attackOrchard(orchard);
    int healthAfterFirst = orchard.getHealth();
    CHECK(healthAfterFirst < 100, "Scab's first attack reduces orchard health");
    CHECK(orchard.getLastThreatName() == "Scab", "Scab attack records itself as the last threat");

    int damageFirst = 100 - healthAfterFirst;
    scab.attackOrchard(orchard);
    int damageSecond = healthAfterFirst - orchard.getHealth();

    CHECK(damageSecond > damageFirst, "Scab's second attack deals MORE damage than the first (it spreads)");
}

void test_aphids_attack_behavior() {
    std::cout << "\n-- Aphids: polymorphic attack behaviour --\n";
    Orchard orchard(100, 100, 50);
    Aphids aphids;

    aphids.attackOrchard(orchard);
    int yieldAfterFirst = orchard.getYield();
    CHECK(yieldAfterFirst < 100, "Aphids' first attack reduces yield");

    int yieldLossFirst = 100 - yieldAfterFirst;
    aphids.attackOrchard(orchard);
    int yieldLossSecond = yieldAfterFirst - orchard.getYield();

    CHECK(yieldLossSecond > yieldLossFirst, "Aphids' second attack costs MORE yield than the first (infestation grows)");
}

void test_hailstorm_attack_behavior() {
    std::cout << "\n-- Hailstorm: polymorphic attack behaviour --\n";
    Orchard orchard(100, 100, 50);
    Hailstorm hail;

    hail.attackOrchard(orchard);
    CHECK(orchard.getHealth() == 75, "Hailstorm deals a fixed 25 health damage on first hit");

    int healthAfterFirst = orchard.getHealth();
    hail.attackOrchard(orchard);
    int damageSecond = healthAfterFirst - orchard.getHealth();
    CHECK(damageSecond == 25, "Hailstorm deals the SAME fixed damage every time (no escalation)");
}

void test_defense_actions() {
    std::cout << "\n-- Defense actions: polymorphic apply() --\n";

    Orchard orchard(50, 50, 50);
    FungicideSpray spray;
    spray.apply(orchard);
    CHECK(orchard.getHealth() == 65, "FungicideSpray restores +15 health with no prior Scab attack");

    Orchard orchard2(50, 50, 50);
    Scab scab;
    scab.attackOrchard(orchard2); // sets lastThreatName to "Scab"
    int healthBeforeSpray = orchard2.getHealth();
    FungicideSpray spray2;
    spray2.apply(orchard2);
    CHECK(orchard2.getHealth() == healthBeforeSpray + 25,
          "FungicideSpray gives a +10 health bonus specifically after Scab");

    Orchard orchard3(50, 50, 50);
    Pruning pruning;
    pruning.apply(orchard3);
    CHECK(orchard3.getHealth() == 60, "Pruning restores +10 health by default");

    Orchard orchard4(50, 50, 50);
    Hailstorm hail;
    hail.attackOrchard(orchard4);
    int healthBeforeNet = orchard4.getHealth();
    NetCovering net;
    net.apply(orchard4);
    CHECK(orchard4.getHealth() == healthBeforeNet + 28,
          "NetCovering gives a big (+20) bonus specifically after Hailstorm");
}

void test_runtime_polymorphism_through_base_pointers() {
    std::cout << "\n-- Core requirement: genuine runtime polymorphism --\n";

    // This is the heart of the whole project: a std::vector of BASE CLASS
    // pointers (Threat*), where each pointer secretly refers to a
    // DIFFERENT derived class. We call the exact same function,
    // attackOrchard(), through every single one, and each call runs
    // DIFFERENT code - decided at runtime, not compile time.
    std::vector<std::unique_ptr<Threat>> threats;
    threats.push_back(std::make_unique<Scab>());
    threats.push_back(std::make_unique<Aphids>());
    threats.push_back(std::make_unique<Hailstorm>());

    Orchard orchard(100, 100, 50);
    for (auto& threat : threats) {
        int healthBefore = orchard.getHealth();
        threat->attackOrchard(orchard); // <-- dynamic dispatch happens here
        CHECK(orchard.getHealth() < healthBefore,
              threat->getName() + " damaged the orchard when called through a Threat* pointer");
    }

    CHECK(threats[0]->getName() == "Scab", "Index 0 in the polymorphic vector is really a Scab");
    CHECK(threats[1]->getName() == "Aphids", "Index 1 in the polymorphic vector is really an Aphids");
    CHECK(threats[2]->getName() == "Hailstorm", "Index 2 in the polymorphic vector is really a Hailstorm");
}

void test_boundary_conditions() {
    std::cout << "\n-- Boundary conditions --\n";
    Orchard orchard(5, 5, 10);

    Hailstorm hail;
    hail.attackOrchard(orchard); // 25 damage against only 5 health
    CHECK(orchard.getHealth() == 0, "Health never goes below 0, even under heavy overkill damage");
    CHECK(orchard.isDestroyed(), "isDestroyed() correctly reports true once health hits 0");

    Orchard fullOrchard(100, 100, 10);
    FungicideSpray spray;
    spray.apply(fullOrchard);
    CHECK(fullOrchard.getHealth() == 100, "Health never exceeds 100, even when already full and healed again");
}

int main() {
    std::cout << "========================================\n";
    std::cout << "        AGROSENTINEL TEST SUITE\n";
    std::cout << "========================================\n";

    test_orchard_damage_and_clamping();
    test_orchard_yield_changes();
    test_orchard_encapsulation_via_negative_inputs();
    test_scab_attack_behavior();
    test_aphids_attack_behavior();
    test_hailstorm_attack_behavior();
    test_defense_actions();
    test_runtime_polymorphism_through_base_pointers();
    test_boundary_conditions();

    std::cout << "\n========================================\n";
    if (failures == 0) {
        std::cout << "ALL TESTS PASSED\n";
    } else {
        std::cout << failures << " TEST(S) FAILED\n";
    }
    std::cout << "========================================\n";

    return failures == 0 ? 0 : 1;
}
