#include "globals.h"
#include "doublely_linked_list.h"

//add more elements as needed


/*
*This function runs the level select menu and returns what level to run at the start.
*
*@return       a DoublelyLinkedlist containing the level to load. Will return 
*NULL if no level was chosen
*
*/
DLinkedList* runLevelSelectMenu();

/*
*This function runs the Difficulty select menu and returns what mass to set the ball to.
*
*@return an int that distinguishes what mass to set the ball to.
*/
int runDifficultySelectMenu();