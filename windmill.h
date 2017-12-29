#pragma once



// Forward declarations
struct Physics;
struct Entity;

/**
 * Structure to represent a Windmill in the arena.
 * 
 * This structure is a ArenaElement; its first data element is an integer (type)
 * whose value is always WM.
 */
struct Windmill {
    int type;
    float direction;
    int x, y;
    float angle, lastAngle;
    float delta;

    //note that the radius has been implemented as 10
};

// Directions
#define COUNTERCW  0
#define CLOCKWISE  1

/**
 * Allocate and initialize a new Windmill object.
 *
 * @param[in] direction The direction of the Windmill's spin (COUNTERCW or CLOCKWISE)
 * @param[in] x         The x location of the origin of the windmill
 * @param[in] y         The y location of the origin of the windmill
 * @param[in] angle     The angle to start the windmill at between 0 and pi
 * @return              The newly initialized windmill.
 */
Windmill* create_windmill(int direction, int x, int y, float angle);

/**
 * Computes the physics update for a windmill.
 *
 * @param[out] phys The result physics update. Assumed valid at function start.
 * @param[in]  ball The ball to update
 * @param[in]  windmill The windmill to bounce off of
 * @param[in]  delta The elapsed time, in seconds, since the previous update
 */
void do_windmill(Physics* next, const Physics* curr, Windmill* windmill, float delta);

/**
 * Draws a given windmill to the screen.
 * 
 * @param[in] windmill  The windmill to draw
 */
void draw_windmill(Windmill* windmill);

