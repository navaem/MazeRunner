#pragma once

// Forward declarations
struct Physics;
struct Entity;

/**
 * Structure to represent a Goal in the arena.
 * 
 * This structure is a ArenaElement; its first data element is an integer (type)
 * whose value is always POTHOLE.
 */
struct Goal {
    int type;
    int x, y;
    int radius;
};



/**
 * Allocate and initialize a new Goal object.
 *
 * 
 * @param[in] x         The x location of the goal
 * @param[in] y         The y location of the goal
 * @return              The newly initialized goal.
 */
Goal* create_goal(int x, int y);

/**
 * Computes the physics update for a goal.
 *
 * @param[out] phys The result physics update. Assumed valid at function start.
 * @param[in]  ball The ball to update
 * @param[in]  goal The goal to that is interacting
 * @return     whether the goal was scored or not
*/
int do_goal(Physics* next, const Physics* curr, Goal* goal);

/**
 * Draws a given goal to the screen.
 * 
 * @param[in] goal  The goal to draw
 */
void draw_goal(Goal* goal);
