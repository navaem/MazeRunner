#pragma once

// Forward declarations
struct Physics;
struct Entity;

/**
 * Structure to represent a sandtrap in the arena.
 * 
 * This structure is a ArenaElement; its first data element is an integer (type)
 * whose value is always SANDTRAP.
 */
struct Sandtrap {
    int type;
    int x1, x2, y1, y2;
    int should_draw;
};



/**
 * Allocate and initialize a new Sandtrap object.
 *
 * 
 * @param[in] x1         The x1 coordinate of the sandtrap
 * @param[in] x2         The x2 coordinate of the sandtrap
 * @param[in] y1         The y1 coordinate of the sandtrap
 * @param[in] y2         The y2 coordinate of the sandtrap
 * @return              The newly initialized sandtrap.
 */
Sandtrap* create_sandtrap(int x1, int x2, int y1, int y2);

/**
 * Computes the physics update for a sandtrap.
 *
 * @param[out] phys The result physics update. Assumed valid at function start.
 * @param[in]  ball The ball to update
 * @param[in]  sandtrap The sandtrap to that is interacting
*/
void do_sandtrap(Physics* next, const Physics* curr, Sandtrap* sandtrap);

/**
 * Draws a given sandtrap to the screen.
 * 
 * @param[in] sandtrap  The sandtrap to draw
 */
void draw_sandtrap(Sandtrap* sandtrap);
