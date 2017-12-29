#include "globals.h"
#include "doublely_linked_list.h"

//add more elements as needed



/*
*This function runs the Load save menu and returns what level to run at the start.
*
*@return       a DoublelyLinkedlist containing the save to load. Will return 
*
*/
DLinkedList* runLoadSaveMenu(DLinkedList* saves);

/*
*This function runs the store save menu and stores the save in memory.
*
*@param        Physics* curr the current state to save
*@param        DLinkedList* arena the arena to save
*/
void runStoreSaveMenu(const Physics* curr, DLinkedList* arena, DLinkedList* saves);