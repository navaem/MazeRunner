#include "token.h"

#include "physics.h"
#include "game.h"
#include "globals.h"




/**
 * Allocate and initialize a new Token object.
 *
 * 
 * @param[in] x         The x location of the token
 * @param[in] y         The y location of the token
 * @return              The newly initialized token.
 */
Token* create_token(int x, int y){
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = TOKEN;
    token->x = x;
    token->y = y;
    token->should_erase = 0;
    return token;
}

/**
 * Computes the physics update for a token.
 *
 * @param[out] phys The result physics update. Assumed valid at function start.
 * @param[in]  ball The ball to update
 * @param[in]  token The token to that is interacting
 * @return     if the token was eaten or not
*/
int do_token(Physics* next, const Physics* curr, Token* token){
    double xdist = (double)(curr->px)-(token->x);
    double ydist = (double)(curr->py)-(token->y);
    double dist = pow(pow(ydist,2.0)+pow(xdist,2.0),0.5);
    if (dist < 6) {
        if (token->should_erase == 0) {
            token->should_erase = 1;
            return 1;
        }
    }
    return 0;
}

/**
 * Draws a given token to the screen.
 * 
 * @param[in] token  The token to draw
 */
void draw_token(Token* token){
    if(token->should_erase){
        uLCD.triangle(token->x-1,token->y-1,token->x,token->y+1,token->x+1,token->y-1,BLACK);
    }else {
        uLCD.triangle(token->x-1,token->y-1,token->x,token->y+1,token->x+1,token->y-1,0x00FFFF);
    }
}







