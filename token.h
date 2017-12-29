#pragma once

// Forward declarations
struct Physics;
struct Entity;


//NOTE each level has 5 tokens

/**
 * Structure to represent a token in the arena.
 * 
 * This structure is a ArenaElement; its first data element is an integer (type)
 * whose value is always TOKEN.
 */
struct Token {
    int type;
    int x, y;
    int should_erase;
};



/**
 * Allocate and initialize a new Token object.
 *
 * 
 * @param[in] x         The x location of the token
 * @param[in] y         The y location of the token
 * @return              The newly initialized token.
 */
Token* create_token(int x, int y);

/**
 * Computes the physics update for a token.
 *
 * @param[out] phys The result physics update. Assumed valid at function start.
 * @param[in]  ball The ball to update
 * @param[in]  token The token to that is interacting
 * @return     if the token was eaten or not
*/
int do_token(Physics* next, const Physics* curr, Token* token);

/**
 * Draws a given token to the screen.
 * 
 * @param[in] token  The token to draw
 */
void draw_token(Token* token);
