#include "windmill.h"

#include "globals.h"
#include "physics.h"
#include "game.h"
#include "math_extra.h"

#include <math.h>

const float M_PI = acos(-1.0);


Windmill* create_windmill(int direction, int x, int y, float angle){
    Windmill* wm = (Windmill*)malloc(sizeof(Windmill));
    wm->type = WINDMILL;
    wm->direction = direction;
    wm->x = x;
    wm->y = y;
    wm->angle = angle;
    return wm;
}

void do_windmill(Physics* next, const Physics* curr, Windmill* windmill, float delta){
    
    //the windmill needs to add a rotation to its angle in the right direction
    if (windmill->direction == COUNTERCW){
        windmill->angle = (windmill->angle + .001);
    }else {
        windmill->angle = (windmill->angle - .001);
    }


    //the vector direction of direction will be called zeroX and zeroY
    float vecX = 10*cos(windmill->angle);
    float vecY = 10*sin(windmill->angle);

    //from the center to the ball is the r vector
    float rx = curr->px - windmill->x;
    float ry = curr->py - windmill->y;
    float r = pow(pow((double)rx,2.0)+pow((double)ry,2.0),.5);

    
    if(r > 14) {
        return;
    }
    else {
        //check if the ball is colliding with the vector direction
        if (fabs(cross(rx,ry,vecX,vecY))/10.0 < 4.0){
            next->px = 20;
            next->py = 20;
            next->vx = 0;
            next->vy = 0;
            return;
        }
        vecX = 10*cos(windmill->angle+(M_PI/2));
        vecY = 10*sin(windmill->angle+(M_PI/2));
        //check if the ball is colliding with the vector direction
        if (fabs(cross(rx,ry,vecX,vecY))/10.0 < 4.0) {
            next->px = 20;
            next->py = 20;
            next->vx = 0;
            next->vy = 0;
            return;
        }
        
    }

}


void draw_windmill(Windmill* windmill) {

    if(windmill->lastAngle == NULL) {
        windmill->lastAngle = windmill->angle;
    }
    if(fabs(windmill->lastAngle-windmill->angle) < .1 ){
        return;
    }
    
    float wx0, wy0, wxpi_2, wypi_2, wxpi, wypi, wx3pi_2, wy3pi_2;
    wx0 = windmill->x + 10*cos(windmill->lastAngle);
    wy0 = windmill->y + 10*sin(windmill->lastAngle);
    wxpi_2 = windmill->x + 10*cos(windmill->lastAngle+(M_PI/2));
    wypi_2 = windmill->y + 10*sin(windmill->lastAngle+(M_PI/2));
    wxpi = windmill->x + 10*cos(windmill->lastAngle+M_PI);
    wypi = windmill->y + 10*sin(windmill->lastAngle+M_PI);
    wx3pi_2 =  windmill->x + 10*cos(windmill->lastAngle+(3*M_PI/2));
    wy3pi_2 = windmill->y + 10*sin(windmill->lastAngle+(3*M_PI/2));

    uLCD.line((int)wx0, (int)wy0, (int)wxpi, (int)wypi, BLACK);
    uLCD.line((int)wxpi_2, (int)wypi_2, (int)wx3pi_2, (int)wy3pi_2, BLACK);

    wx0 = windmill->x + 10*cos(windmill->angle);
    wy0 = windmill->y + 10*sin(windmill->angle);
    wxpi_2 = windmill->x + 10*cos(windmill->angle+(M_PI/2));
    wypi_2 = windmill->y + 10*sin(windmill->angle+(M_PI/2));
    wxpi = windmill->x + 10*cos(windmill->angle+M_PI);
    wypi = windmill->y + 10*sin(windmill->angle+M_PI);
    wx3pi_2 =  windmill->x + 10*cos(windmill->angle+(3*M_PI/2));
    wy3pi_2 = windmill->y + 10*sin(windmill->angle+(3*M_PI/2));

    uLCD.line((int)wx0, (int)wy0, (int)wxpi, (int)wypi, RED);
    uLCD.line((int)wxpi_2, (int)wypi_2, (int)wx3pi_2, (int)wy3pi_2, RED);
    windmill->lastAngle = windmill->angle;

        
}

