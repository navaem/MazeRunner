#include "globals.h"
#include "doublely_linked_list.h"
#include "physics.h"
#include "game.h"
#include "arena.h"

//add more elements as needed

void create_saves() {
	//create saves that will be initialized with 6 nodes
	//State1, arena 1, state 2, arena 2, state 3, arena 3
	
}


/*
*This function runs the Load save menu and returns what level to run at the start.
*
*@return       a DoublelyLinkedlist containing the save to load. Will return 
*
*/
DLinkedList* runLoadSaveMenu(DLinkedList* saves)
{
    uLCD.cls();
    uLCD.textbackground_color(BLACK);
    uLCD.color(GREEN);
    uLCD.locate(39,2);
    uLCD.printf("SAVES");
    uLCD.textbackground_color(GREEN);

    //SAVE SLOT 1 button
    uLCD.filled_rectangle(13,42,113,60,GREEN);
    uLCD.rectangle(12,41,114,61,WHITE);
    uLCD.textbackground_color(GREEN);
    uLCD.text_string("SAVE SLOT 1", 3, 6, FONT_7X8, BLACK);
    wait(0.1);

    //SAVE SLOT 2 button
    uLCD.filled_rectangle(13,60+5,113,78+5,GREEN);
    uLCD.rectangle(12,59+5,114,79+5,LGREY);
    uLCD.text_string("SAVE SLOT 2",3,9,FONT_7X8,BLACK);
    wait(0.1);
    
    //SAVE SLOT 3 button
    uLCD.filled_rectangle(13,88,113,106,GREEN);
    uLCD.rectangle(12,87,114,87+20,LGREY);
    uLCD.text_string("SAVE SLOT 3",3,12,FONT_7X8,BLACK);

    DLinkedList* load = create_dlinkedlist();

    //A while loop will run to handle selections using the pushbuttons
    
    int * currSel = (int*)malloc(sizeof(int));
    int * changeSel = (int*)malloc(sizeof(int));
    *currSel = 0;
    *changeSel = 0;
    int *selPress = (int*)malloc(sizeof(int));
    int *upPress = (int*)malloc(sizeof(int));
    int *downPress = (int*)malloc(sizeof(int));
    


    
    while (1)
    {

        *selPress = right_pb;
        *upPress = up_pb;
        *downPress = down_pb;

        if (!*selPress){ //if selection button is pressed
        	uLCD.cls();
        	wait(1);
            switch (*currSel) {// see which option was chosen
                case 0:
                    //load save in slot 1
                    if (getHead(saves)== NULL)
                    {
                        continue;
                    }
                    insertTail(load,copy_physics((Physics*)getCurrent(saves)));
                    insertTail(load,copy_arena((DLinkedList*)getNext(saves)));
                    free(currSel);
                    free(changeSel);
                    free(selPress);
                    free(upPress);
                    free(downPress);
                    return (DLinkedList*) load;
                case 1: 
                    //load save in slot 2
                    getHead(saves);
                    getNext(saves);
                    if (getNext(saves) == NULL)
                    {
                        continue;
                    }
                    insertTail(load,copy_physics((Physics*)getCurrent(saves)));
                    insertTail(load,copy_arena((DLinkedList*)getNext(saves)));
                    free(currSel);
                    free(changeSel);
                    free(selPress);
                    free(upPress);
                    free(downPress);
                    return (DLinkedList*)load;
                case 2:
                    //load save in slot 3
                    getHead(saves);
                    getNext(saves);
                    getNext(saves);
                    getNext(saves);
                    if(getNext(saves)==NULL)
                    {
                        continue;
                    }
                    insertTail(load,copy_physics((Physics*)getCurrent(saves)));
                    insertTail(load,copy_arena((DLinkedList*)getNext(saves)));
                    free(currSel);
                    free(changeSel);
                    free(selPress);
                    free(upPress);
                    free(downPress);
                    return (DLinkedList*)load;
                default:
                    break;
            }
        }

        //read the new currSel
        if (!*upPress&&!*downPress){
            continue;
        }else if(!*upPress) {
            if (*currSel!=0){
                (*currSel)--;
                *changeSel = 1;
            }
        }else if(!*downPress){
            if (*currSel!=2){
                (*currSel)++;
                *changeSel = 1;
            }
        }else{
            continue;
        }

        if (*changeSel) {
            switch (*currSel) {
                case 0:
                    uLCD.rectangle(12,41,114,61,WHITE);
                    uLCD.rectangle(12,59+5,114,79+5,LGREY);
                    uLCD.rectangle(12,87,114,87+20,LGREY);
                    break;
                case 1:
                    uLCD.rectangle(12,41,114,61,LGREY);
                    uLCD.rectangle(12,59+5,114,79+5,WHITE);
                    uLCD.rectangle(12,87,114,87+20,LGREY);
                    break;
                case 2:
                    uLCD.rectangle(12,41,114,61,LGREY);
                    uLCD.rectangle(12,59+5,114,79+5,LGREY);
                    uLCD.rectangle(12,87,114,87+20,WHITE);
                    break;
                default:
                    break;
            }
        }
        *changeSel = 0;
        wait(1);
    }
}

/*
*This function runs the store save menu and stores the save in memory.
*
*@param        Physics* curr the current state to save
*@param        DLinkedList* arena the arena to save
*/
void runStoreSaveMenu(const Physics* curr, DLinkedList* arena, DLinkedList* saves)
{
    uLCD.cls();
    uLCD.textbackground_color(BLACK);
    uLCD.color(GREEN);
    uLCD.locate(39,2);
    uLCD.printf("SAVES");
    uLCD.textbackground_color(GREEN);

    //SAVE SLOT 1 button
    uLCD.filled_rectangle(13,42,113,60,GREEN);
    uLCD.rectangle(12,41,114,61,WHITE);
    uLCD.textbackground_color(GREEN);
    uLCD.text_string("SAVE SLOT 1", 3, 6, FONT_7X8, BLACK);
    wait(0.1);

    //SAVE SLOT 2 button
    uLCD.filled_rectangle(13,60+5,113,78+5,GREEN);
    uLCD.rectangle(12,59+5,114,79+5,LGREY);
    uLCD.text_string("SAVE SLOT 2",3,9,FONT_7X8,BLACK);
    wait(0.1);
    
    //SAVE SLOT 3 button
    uLCD.filled_rectangle(13,88,113,106,GREEN);
    uLCD.rectangle(12,87,114,87+20,LGREY);
    uLCD.text_string("SAVE SLOT 3",3,12,FONT_7X8,BLACK);

    DLinkedList* arenaCopy = copy_arena(arena);
    Physics* stateCopy = copy_physics((Physics*)curr);
    

    //A while loop will run to handle selections using the pushbuttons
    
    int * currSel = (int*)malloc(sizeof(int));
    int * changeSel = (int*)malloc(sizeof(int));
    *currSel = 0;
    *changeSel = 0;
    int *selPress = (int*)malloc(sizeof(int));
    int *upPress = (int*)malloc(sizeof(int));
    int *downPress = (int*)malloc(sizeof(int));
    


    
    while (1)
    {

        *selPress = right_pb;
        *upPress = up_pb;
        *downPress = down_pb;

        if (!*selPress){ //if selection button is pressed
        	uLCD.cls();
        	set_all_draw(arena);
        	set_all_draw(arenaCopy);
        	wait(1);
            switch (*currSel) {// see which option was chosen
                case 0:
                    //save in slot 1
                    getHead(saves);
                    deleteForward(saves);
                    if (getCurrent(saves)!=NULL) {
                    	destroyList((DLinkedList*)getCurrent(saves));
                    	(saves->current)->data = NULL;
                    }
                    deleteForward(saves);
                    insertHead(saves,(void*)arenaCopy);
                    insertHead(saves,(void*)stateCopy);
                    free(currSel);
                    free(changeSel);
                    free(selPress);
                    free(upPress);
                    free(downPress);
                    return;
                case 1: 
                    //save in slot 2
                    getHead(saves);
                    getNext(saves);
                    getNext(saves);
                    deleteForward(saves);
                    if (getCurrent(saves)!=NULL) {
                    	destroyList((DLinkedList*)getCurrent(saves));
                    	(saves->current)->data = NULL;
                    }
                    deleteForward(saves);
                    insertBefore(saves,(void*)stateCopy);
                    insertBefore(saves,(void*)arenaCopy);
                    free(currSel);
                    free(changeSel);
                    free(selPress);
                    free(upPress);
                    free(downPress);
                    return;
                case 2:
                    //save in slot 3
                    getHead(saves);
                    getNext(saves);
                    getNext(saves);
                    getNext(saves);
                    getNext(saves);
                    deleteForward(saves);
                    if (getCurrent(saves)!=NULL) {
                    	destroyList((DLinkedList*)getCurrent(saves));
                    	(saves->current)->data = NULL;
                    }
                    deleteForward(saves);
                    insertTail(saves,(void*)stateCopy);
                    insertTail(saves,(void*)arenaCopy);
                    free(currSel);
                    free(changeSel);
                    free(selPress);
                    free(upPress);
                    free(downPress);
                    return;
                default:
                    break;
            }
        }

        //read the new currSel
        if (!*upPress&&!*downPress){
            continue;
        }else if(!*upPress) {
            if (*currSel!=0){
                (*currSel)--;
                *changeSel = 1;
            }
        }else if(!*downPress){
            if (*currSel!=2){
                (*currSel)++;
                *changeSel = 1;
            }
        }else{
            continue;
        }

        if (*changeSel) {
            switch (*currSel) {
                case 0:
                    uLCD.rectangle(12,41,114,61,WHITE);
                    uLCD.rectangle(12,59+5,114,79+5,LGREY);
                    uLCD.rectangle(12,87,114,87+20,LGREY);
                    break;
                case 1:
                    uLCD.rectangle(12,41,114,61,LGREY);
                    uLCD.rectangle(12,59+5,114,79+5,WHITE);
                    uLCD.rectangle(12,87,114,87+20,LGREY);
                    break;
                case 2:
                    uLCD.rectangle(12,41,114,61,LGREY);
                    uLCD.rectangle(12,59+5,114,79+5,LGREY);
                    uLCD.rectangle(12,87,114,87+20,WHITE);
                    break;
                default:
                    break;
            }
        }
        *changeSel = 0;
        wait(1);
    }





}

