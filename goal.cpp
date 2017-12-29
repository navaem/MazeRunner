#include "globals.h"
#include "physics.h"
#include "game.h"
#include "math_extra.h"

#include <math.h>


/**
 * Allocate and initialize a new Goal object.
 *
 * 
 * @param[in] x         The x location of the goal
 * @param[in] y         The y location of the goal
 * @return              The newly initialized goal.
 */
Goal* create_goal(int x, int y) {
    Goal* goal = (Goal*) malloc(sizeof(Goal));
    goal->type = GOAL;
    goal->x = x;
    goal->y = y;
    goal->radius = 6;
    return goal;
}

/**
 * Computes the physics update for a goal.
 *
 * @param[out] phys The result physics update. Assumed valid at function start.
 * @param[in]  ball The ball to update
 * @param[in]  goal The goal to that is interacting
 */
int do_goal(Physics* next, const Physics* curr, Goal* goal)
{
    double xdist = (double)(curr->px)-(goal->x);
    double ydist = (double)(curr->py)-(goal->y);
    double dist = pow(pow(ydist,2.0)+pow(xdist,2.0),0.5);
    if (dist < 5.0) {
        return 1;
    }
    return 0;
}

/**
 * Draws a given goal to the screen.
 * 
 * @param[in] goal  The goal to draw
 */
void draw_goal(Goal* goal)
{
    
    uLCD.filled_circle(goal->x,goal->y,goal->radius,WHITE);  
    
}
