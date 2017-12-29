#include "pothole.h"

#include "globals.h"
#include "physics.h"
#include "game.h"
#include "math_extra.h"

#include <math.h>


/**
 * Allocate and initialize a new Pothole object.
 *
 * 
 * @param[in] x         The x location of the pothole
 * @param[in] y         The y location of the pothole
 * @return              The newly initialized pothole.
 */
Pothole* create_pothole(int x, int y, int radius) {
    Pothole* pothole = (Pothole*) malloc(sizeof(Pothole));
    pothole->type = POTHOLE;
    pothole->x = x;
    pothole->y = y;
    pothole->radius = radius;
    pothole->should_draw = 1;
    return pothole;
}

/**
 * Computes the physics update for a pothole.
 *
 * @param[out] phys The result physics update. Assumed valid at function start.
 * @param[in]  ball The ball to update
 * @param[in]  pothole The pothole to that is interacting
 */
void do_pothole(Physics* next, const Physics* curr, Pothole* pothole)
{
	double xdist = (double)(curr->px)-(pothole->x);
	double ydist = (double)(curr->py)-(pothole->y);
	double dist = pow(pow(ydist,2.0)+pow(xdist,2.0),0.5);
    if (dist < pothole->radius) {
    	next->px = 20;
    	next->py = 20;
    	pothole->should_draw = 1;
    } else if(dist < 14){
    	pothole->should_draw = 1;
    }
}

/**
 * Draws a given pothole to the screen.
 * 
 * @param[in] pothole  The pothole to draw
 */
void draw_pothole(Pothole* pothole)
{
    if(pothole->should_draw) {
    	uLCD.filled_circle(pothole->x,pothole->y,pothole->radius,DGREY);

    	//don't draw again unless the ball falls in again
    	pothole->should_draw = 0;
    }
}
