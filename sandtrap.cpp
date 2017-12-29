#include "sandtrap.h"

#include "globals.h"
#include "physics.h"
#include "game.h"
#include "math_extra.h"

#include <math.h>



Sandtrap* create_sandtrap(int x1, int x2, int y1, int y2){
    Sandtrap* sandtrap = (Sandtrap*) malloc(sizeof(Sandtrap));
    sandtrap->type = SANDTRAP;
    sandtrap->x1 = x1;
    sandtrap->x2 = x2;
    sandtrap->y1 = y1;
    sandtrap->y2 = y2;
    sandtrap->should_draw = 1;
    return sandtrap;
}


void do_sandtrap(Physics* next, const Physics* curr, Sandtrap* sandtrap)
{
	if (curr->px < sandtrap->x2 && curr->px > sandtrap->x1) {
		if (curr->py < sandtrap->y2 && curr->py > sandtrap->y1) {
			if (fabs(curr->vy) > 1) {
				if (curr->vy > 0) {
					next->vy = 1;
				} else {
					next->vy = -1;
				}
		    }
		    if (fabs(curr->vy) > 1) {
				if (curr->vx > 0) {
					next->vx = 1;
				} else {
					next->vx = -1;
				}
			}
		}
	}
	if (curr->px < sandtrap->x2 + 4 && curr->px > sandtrap->x1 - 4) {
		if (curr->py < sandtrap->y2 + 4 && curr->py > sandtrap->y1 - 4) {
			sandtrap->should_draw = 1;
		}
	}
}


void draw_sandtrap(Sandtrap* sandtrap)
{
    if (sandtrap->should_draw) {
    	uLCD.filled_rectangle(sandtrap->x1,sandtrap->y1,sandtrap->x2,sandtrap->y2,0xFFDDDD);

    	//don't draw again unless the ball falls in again
    	sandtrap->should_draw = 0;
    }
}
