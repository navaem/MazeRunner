#pragma once

#include "globals.h"
#include "doublely_linked_list.h"
#include "goal.h"
#include "wall.h"
#include "pothole.h"
#include "windmill.h"
#include "token.h"

//add more elements later








/*
*This function creates level1
*
* @return a DoublelyLinkedList pointer that contains all of the elements of
* level1.
*/
DLinkedList* createLevel1();


/*
*This function creates level2
*
* @return a DoublelyLinkedList pointer that contains all of the elements of
* level2.
*/
DLinkedList* createLevel2();


/*
*This function creates level3
*
* @return a DoublelyLinkedList pointer that contains all of the elements of
* level3.
*/
DLinkedList* createLevel3();

/*
*This function returns a copy of the arena in a different memory location
*
*@param     DLinkedList* arena the arena to be copied
*@return    DLinkedList* the copy of the arena
*/
DLinkedList* copy_arena(DLinkedList* arena1);