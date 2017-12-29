#include "globals.h"
#include "doublely_linked_list.h"
#include "physics.h"
#include "game.h"
#include "arena.h"

//add more elements as needed



/*
*This function runs the rewind function and returns a doublely linked list
* containing the new physics state and arena
*
*@param        the rewind arenas to display
*@param        the rewind states to display
*@return       a DoublelyLinkedlist containing the rewinded state
*
*/
DLinkedList* runRewind(DLinkedList* rewindArenas){
    if (getHead(rewindArenas) == NULL) {
        return NULL;
    }
    int limit = getSize(rewindArenas);
    DLinkedList* currArena = (DLinkedList*)getHead(rewindArenas);
    Ball* ball = (Ball*)getTail(currArena);
    uLCD.filled_circle(ball->x,ball->y,2,0xAA4444);
    (rewindArenas->current)->data = NULL;
    
    destroyList(currArena);
    deleteForward(rewindArenas);
    wait(.25);

    for (int i = 1; i < limit - 1; i++) {
        currArena = (DLinkedList*)getCurrent(rewindArenas);
        ball = (Ball*)getTail(currArena);
        uLCD.filled_circle(ball->x,ball->y,2,0xAA4444);
        (rewindArenas->current)->data = NULL;
        destroyList(currArena);
        removeForward(rewindArenas);
        wait(.25);
    }
    currArena = (DLinkedList*)getCurrent(rewindArenas);
    (rewindArenas->current)->data = NULL;
    removeForward(rewindArenas);
    return currArena;


}