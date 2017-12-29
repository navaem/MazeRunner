#include "game.h"

#include "globals.h"
#include "physics.h"
#include "wall.h"
#include "pothole.h"
#include "goal.h"
#include "windmill.h"
#include "token.h"
#include "sandtrap.h"
#include "arena.h"
#include "rewind.h"

#include "saves.h"


int tokenUse = 0;
int score = 0;

/** Erases the ball from the screen by drawing over it with the background color. */
void erase_ball(Ball* ball)
{
    uLCD.filled_circle(ball->x,ball->y,radius,0x000000);
    // TODO: Draw background color over curriously drawn ball location
}

/** Draws the ball on the screen at the updated location (according to the state) */
void draw_ball(Ball* ball, Physics* state)
{
    // TODO: Save that updated ball position for later erasing
    ball->x = state->px;
    ball->y = state->py;
    uLCD.filled_circle(ball->x,ball->y,radius,GREEN);
    // TODO: Draw ball in its updated location
}

//sets all should draw in the arena to should draw
void set_all_draw(DLinkedList* arena)
{
    ArenaElement* elem = (ArenaElement*)getHead(arena);
    do {
        switch(elem->type) {
            case WALL:
                ((Wall*)elem)->should_draw = 1;
                break;
            case POTHOLE:
                ((Pothole*)elem)->should_draw = 1;
                break;
            case SANDTRAP:
                ((Sandtrap*)elem)->should_draw = 1;
            default:
                break;
        }
    } while(elem = (ArenaElement*)getNext(arena));
}


/** Reads inputs to the game, such as accelerometer and buttons */
GameInputs read_inputs()
{
    GameInputs inputs;
    double x, y, z;
    
    //pretty sure this is making an infinite loop
    acc.readXYZGravity(&x, &y, &z);
    
    // TODO: Get acceleration vector from accelerometer
    inputs.ax = -1*x*1e-3/mass;
    inputs.ay = y*1e-3/mass;
    inputs.az = z;
    // TODO: Read buttons
    left_pb.read();
    right_pb.read();
    up_pb.read();
    down_pb.read();

    return inputs;
}

int update_game(DLinkedList* arena, Physics* curr, int* tokens, GameInputs inputs, float delta)
{   
    int done = 0;
    int hit = 0;
    ///////////////////////////////
    // Prepare for physics update
    ///////////////////////////////
    // Make a copy of the current state for modification
    Physics next = *curr;
    // No acceleration unless the ArenaElements apply them. (Newton's 1st law)
    next.ax = (float)inputs.ax;
    next.ay = (float)inputs.ay;



    // Loop over all arena elements
    ArenaElement* elem = (ArenaElement*)getHead(arena);
    do {
        switch(elem->type) {
            case WALL:
                hit = do_wall(&next, curr, (Wall*) elem, delta);
                if (hit) {// if the wall is hit, do the wall hit animation which flashes 
                    //the screen white.
                    uLCD.background_color(WHITE);
                    uLCD.cls();
                    uLCD.background_color(BLACK);
                    uLCD.cls();
                    set_all_draw(arena);
                }
                break;
            case POTHOLE:
                do_pothole(&next, curr, (Pothole*) elem);
                break;
            case WINDMILL:
                do_windmill(&next, curr, (Windmill*) elem, delta);
                break;
            case TOKEN:
                *tokens = *tokens + do_token(&next, curr, (Token*) elem);
                break;
            case SANDTRAP:
                do_sandtrap(&next, curr, (Sandtrap*)elem);
                break;
            case GOAL:
                if (*tokens > 4)
                    done = do_goal(&next, curr, (Goal*) elem);
                break;
            case BALL:
                forward_euler(&next, delta);
            default:
                break;
        }
    } while(elem = (ArenaElement*)getNext(arena));

    // Last thing! Update state, so it will be saved for the next iteration.
    *curr = next;
    
    // Zero means we aren't done yet
    if(*tokens < 5){
        done = 0;
    }
    return done;
}

int run_game(DLinkedList* arena, Physics* state, DLinkedList* saves)
{
    // Initialize game loop timers
    int tick, phys_tick, draw_tick, rewind_tick;
    Timer timer;
    timer.start();
    tick = timer.read_ms();
    phys_tick = tick;
    draw_tick = tick;
    rewind_tick = tick;

    // Initialize debug counters
    int count = 0;
    int count2 = 0;

    // Initial draw of the game
    uLCD.background_color(BLACK);
    uLCD.cls();

    int* tokens = (int*)malloc(sizeof(int));
    *tokens = 0;

    state->px = 20.0;        // Position in the center of the screen
    state->py = 20.0;
    state->vx = 0.0;         // Initially unmoving
    state->vy = 0.0;

    int rightPress;          //button reader values
    int leftPress;
    int upPress;
    int downPress;

    DLinkedList* oldTail1;


    DLinkedList* rewoundLoad;

    
    DLinkedList* rewindArenas = create_dlinkedlist();
    

    

    wait(1);
    ///////////////////
    // Main game loop
    ///////////////////
    while(1) {
        // Read timer to determine how long the last loop took
        
        ////////
        //check push buttons
        //////////

        rightPress = !right_pb;
        leftPress = !left_pb;
        upPress = !up_pb;
        downPress = !down_pb;
        //need to check if the skip level feature, rewind, jump back, or 
        //get all tokens has been selected.


        if (upPress&&downPress){
            //skip level
            return 1;
        } else if(rightPress) {
            //get all tokens mode
            if (tokenUse < 1){
                tokenUse++;
                *tokens = 5;
                myled = 0;
                ArenaElement* elem = (ArenaElement*)getHead(arena);
                do {
                    switch (elem->type) {
                        case TOKEN:
                            ((Token*)elem)->should_erase = 1;
                            draw_token((Token*)elem);
                            break;
                        default:
                            break;
                    }
                } while(elem = (ArenaElement*)getNext(arena));
            }
        } else if(leftPress){
            //Jump back
            //opens the saves menu
            DLinkedList* newLoad;
            newLoad = runLoadSaveMenu(saves);
            if (newLoad == NULL){
                continue;
            }
            DLinkedList* newArena = (DLinkedList*)getTail(newLoad);
            free(arena);
            arena = copy_arena(newArena);
            Physics* newState = (Physics*)getHead(newLoad);
            free(state);
            state = copy_physics(newState);
            destroyList(newLoad);
            tick = timer.read_ms();
            phys_tick = tick;
        } else if (upPress){
            //Rewind
            rewoundLoad = runRewind(rewindArenas);
            if (rewoundLoad == NULL) {
                continue;
            }
            free(arena);
            arena = rewoundLoad;
            Ball* newBall = (Ball*)getTail(arena);
            state->px = newBall->x;
            state->py = newBall->y;
            tick = timer.read_ms();
            phys_tick = tick;
        } else if (downPress){
            //save state
            //need to open a saves menu
            runStoreSaveMenu(state, arena, saves);
            tick = timer.read_ms();
            phys_tick = tick;
        }



        
        tick = timer.read_ms();
        
        //score keeping
        
        score++;

        ///////////////////
        // Physics Update
        ///////////////////
        // Rate limit: 1 ms
        int diff = tick - phys_tick;
        if (diff < 1) continue;
        phys_tick = tick;

        // Compute elapsed time in milliseconds
        float delta = (diff)*1e-3*(float)gameDiff;
        

        // Read inputs
        GameInputs inputs = read_inputs();

        // Update game state
        int done = update_game(arena, state, tokens, inputs, delta);
        if (done) {
            *tokens = 0;
            int limit = getSize(rewindArenas);
            getHead(rewindArenas);
            DLinkedList* currArena;
            for (int i = 0; i < limit; i++) {
                currArena = (DLinkedList*)getCurrent(rewindArenas);
                (rewindArenas->current)->data = NULL;
                destroyList(currArena);
                removeForward(rewindArenas);
            }
            return done;
        }

        // Debug: Count physics updates
        count2++;

        //////////////////
        // Render update
        //////////////////
        // Rate limit: 40ms
        if(tick - draw_tick < 40) continue;
        draw_tick = tick;



        /////////////////
        // Save States for REwind
        //////////////////
        if (tick - rewind_tick > 350) {
            rewind_tick = tick;
            if (getSize(rewindArenas) > 9) {//only store max of 10 arenas
                //the tail will be deleted from the stack
                getTail(rewindArenas);
                oldTail1 = (DLinkedList*)removeForward(rewindArenas);
                destroyList(oldTail1);
            }
            DLinkedList* arenaCopy = copy_arena(arena);
            insertHead(rewindArenas,(void*)arenaCopy);
        }

            


        // Erase moving stuff
        ArenaElement* elem = (ArenaElement*)getHead(arena);
        do {
            switch(elem->type) {
                case BALL:
                    erase_ball((Ball*) elem);
                    break;
                default: break;
            }
        } while(elem = (ArenaElement*)getNext(arena));

        // Draw everything
        elem = (ArenaElement*)getHead(arena);
        do {
            switch(elem->type) {
                case WALL:
                    draw_wall((Wall*) elem);
                    break;
                case POTHOLE:
                    draw_pothole((Pothole*)elem);
                    break;
                case WINDMILL:
                    draw_windmill((Windmill*)elem);
                    break;
                case TOKEN:
                    draw_token((Token*)elem);
                    break;
                case SANDTRAP:
                    draw_sandtrap((Sandtrap*)elem);
                    break;
                case GOAL:
                    draw_goal((Goal*)elem);
                    break;
                case BALL:
                    draw_ball((Ball*) elem, state);
                    break;
                default:
                    break;
            }
        } while(elem = (ArenaElement*)getNext(arena));

        ///////////////
        // Display score
        ///////////////
        // Displays rate info in the top corner
        //  First number is total time to update and render this frame
        //  Second number is how many physics iterations between drawing frames
        //  Only displayed every 10th render update (roughly 2.5 Hz)
        // TODO: Take this out before you turn your code in!
        if ((count = (count+1)%10) == 0) {
            uLCD.locate(0, 0);
            uLCD.printf("%d \r\n", score);
        }
        
        // Reset physics iteration counter after every render update
        count2 = 0;
    }
}



void draw_everything(DLinkedList* arena) {
    ArenaElement* elem = (ArenaElement*)getHead(arena);
    do {
        switch(elem->type) {
            case BALL:
                erase_ball((Ball*) elem);
                break;
            default: break;
        }
    } while(elem = (ArenaElement*)getNext(arena));

    // Draw everything
    elem = (ArenaElement*)getHead(arena);
    do {
        switch(elem->type) {
            case WALL:
                draw_wall((Wall*) elem);
                break;
            case POTHOLE:
                draw_pothole((Pothole*)elem);
                break;
            case WINDMILL:
                draw_windmill((Windmill*)elem);
                break;
            case TOKEN:
                draw_token((Token*)elem);
                break;
            case SANDTRAP:
                draw_sandtrap((Sandtrap*)elem);
                break;
            case GOAL:
                draw_goal((Goal*)elem);
                break;
            case BALL:
                Ball* ball = (Ball*)elem;
                uLCD.filled_circle(ball->x,ball->y,radius,GREEN);
                break;
            default:
                break;
        }
    } while(elem = (ArenaElement*)getNext(arena));
}