#include "physics.h"
#include "math_extra.h"
#include "globals.h"


#include<stdio.h>


void forward_euler(Physics* state, float delta)
{ 
    // TODO: Implement proper forward euler updates for position and velocity
    
    
    state->px = state->px + state->vx*delta;
    state->py = state->py + state->vy*delta;

    state->vx = state->vx + state->ax*delta*200;
    state->vy = state->vy + state->ay*delta*200;

    // Compute random motion
    // float damp = 0.5;
    // float dx = damp*coin_flip();
    // float dy = damp*coin_flip();

    // Update position and velocity
    // state->px = state->px + dx;
    // state->py = state->py + dy;
    // state->vx = dx;
    // state->vy = dy;

    if(state->px < radius + 1)
    {
        state->px = 5;
        state->vx = 0;
    }
    if(state->px > SIZE_X - (radius + 1))
    {
        state->px = SIZE_X - (radius);
        state->vx = 0;
    }

    if(state->py < radius + 1)
    {
        state->py = 5;
        state->vy = 0;
    }
    if(state->py > SIZE_Y - (radius + 1))
    {
        state->py = SIZE_Y-(radius);
        state->vy = 0;
    }

    if(state->vx > 8)
        state->vx = 8.0;
    if(state->vy > 8)
        state->vy = 8.0;
}

Physics* copy_physics(Physics* curr){
    Physics* newPhys = (Physics*)malloc(sizeof(Physics));
    newPhys->px = curr->px;
    newPhys->py = curr->py;
    newPhys->vx = curr->vx;
    newPhys->vy = curr->vy;
    return newPhys;
}


