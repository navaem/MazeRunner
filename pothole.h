#pragma once

// Forward declarations
struct Physics;
struct Entity;

/**
 * Structure to represent a Pothole in the arena.
 * 
 * This structure is a ArenaElement; its first data element is an integer (type)
 * whose value is always POTHOLE.
 */
struct Pothole {
    int type;
    int x, y;
    int radius;
    int should_draw;
};



/**
 * Allocate and initialize a new Pothole object.
 *
 * 
 * @param[in] x         The x location of the pothole
 * @param[in] y         The y location of the pothole
 * @param[in] radius    The radius of the pothole
 * @return              The newly initialized pothole.
 */
Pothole* create_pothole(int x, int y, int radius);

/**
 * Computes the physics update for a pothole.
 *
 * @param[out] phys The result physics update. Assumed valid at function start.
 * @param[in]  ball The ball to update
 * @param[in]  pothole The pothole to that is interacting
*/
void do_pothole(Physics* next, const Physics* curr, Pothole* pothole);

/**
 * Draws a given pothole to the screen.
 * 
 * @param[in] pothole  The pothole to draw
 */
void draw_pothole(Pothole* pothole);
