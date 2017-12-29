#include "menu.h"
#include "doublely_linked_list.h"
#include "wall.h"
#include "arena.h"
#include "game.h"


DLinkedList* runLevelSelectMenu()
{
	uLCD.cls();
	uLCD.textbackground_color(BLACK);
	uLCD.color(GREEN);
	uLCD.locate(39,2);
    uLCD.printf("LEVEL SELECT");
	uLCD.textbackground_color(GREEN);

	
    //level1 button
    uLCD.filled_rectangle(13,42,113,60,GREEN);
    uLCD.rectangle(12,41,114,61,WHITE);
    uLCD.textbackground_color(GREEN);
    uLCD.text_string("LEVEL 1", 3, 6, FONT_7X8, BLACK);
    wait(0.1);

    //Level 2 button
    uLCD.filled_rectangle(13,60+5,113,78+5,GREEN);
    uLCD.rectangle(12,59+5,114,79+5,LGREY);
    uLCD.text_string("LEVEL 2",3,9,FONT_7X8,BLACK);
    wait(0.1);
    
    //back button
    uLCD.filled_rectangle(13,88,113,106,GREEN);
    uLCD.rectangle(12,87,114,87+20,LGREY);
    uLCD.text_string("BACK",3,12,FONT_7X8,BLACK);

    

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
            switch (*currSel) {// see which option was chosen
                case 0:
                    //load and return level 1
                	free(selPress);
                	free(upPress);
                	free(downPress);
                	free(currSel);
                	free(changeSel);
                    DLinkedList* level1a = createLevel1();
                    DLinkedList* level2a = createLevel2();
                    DLinkedList* level3a = createLevel3();
                    DLinkedList* levels0 = create_dlinkedlist();
                    insertTail(levels0,(void*)level1a);
                    insertTail(levels0,(void*)level2a);
                    insertTail(levels0,(void*)level3a);
                    return levels0;
                case 1: 
                    //load and return level2
                	free(selPress);
                	free(upPress);
                	free(downPress);
                	free(currSel);
                	free(changeSel);
                    DLinkedList* level2b = createLevel2();
                    DLinkedList* level3b = createLevel3();
                    DLinkedList* levels1 = create_dlinkedlist();
                    insertTail(levels1,(void*)level2b);
                    insertTail(levels1,(void*)level3b);
                    return levels1;
                case 2:
                    //go back to the main menu
                	free(selPress);
                	free(upPress);
                	free(downPress);
                	free(currSel);
                	free(changeSel);
                	uLCD.textbackground_color(BLACK);
   					uLCD.cls();
    				uLCD.locate(39,2);
    				uLCD.color(GREEN);
    				uLCD.printf("MAZERUNNER");
    				//classic button
    				uLCD.filled_rectangle(13,42,113,60,GREEN);
    				uLCD.rectangle(12,41,114,61,WHITE);
    				uLCD.textbackground_color(GREEN);
    				uLCD.text_string("CLASSIC", 3, 6, FONT_7X8, BLACK);
    				wait(0.1);
    				//Level Select button
    				uLCD.filled_rectangle(13,60+5,113,78+5,GREEN);
    				uLCD.rectangle(12,59+5,114,79+5,LGREY);
    				uLCD.text_string("LEVEL SELECT",3,9,FONT_7X8,BLACK);
    				wait(0.1); 
    				//options button
    				uLCD.filled_rectangle(13,88,113,106,GREEN);
    				uLCD.rectangle(12,87,114,87+20,LGREY);
    				uLCD.text_string("DIFFICULTY",3,12,FONT_7X8,BLACK);
                	return NULL;
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


int runDifficultySelectMenu() 
{
	uLCD.cls();
	uLCD.textbackground_color(BLACK);
	uLCD.color(GREEN);
	uLCD.locate(39,2);
    uLCD.printf("DIFFICULTY");
    uLCD.textbackground_color(GREEN);

    //easy button
    uLCD.filled_rectangle(13,42,113,60,GREEN);
    uLCD.rectangle(12,41,114,61,WHITE);
    uLCD.textbackground_color(GREEN);
    uLCD.text_string("EASY", 3, 6, FONT_7X8, BLACK);
    wait(0.1);

    //normal button
    uLCD.filled_rectangle(13,60+5,113,78+5,GREEN);
    uLCD.rectangle(12,59+5,114,79+5,LGREY);
    uLCD.text_string("NORMAL",3,9,FONT_7X8,BLACK);
    wait(0.1);
    
    //hard button
    uLCD.filled_rectangle(13,88,113,106,GREEN);
    uLCD.rectangle(12,87,114,87+20,LGREY);
    uLCD.text_string("HARD",3,12,FONT_7X8,BLACK);

    

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
            uLCD.textbackground_color(BLACK);
            uLCD.cls();
            uLCD.locate(39,2);
            uLCD.color(GREEN);
            uLCD.printf("MAZERUNNER");
            //classic button
            uLCD.filled_rectangle(13,42,113,60,GREEN);
            uLCD.rectangle(12,41,114,61,WHITE);
            uLCD.textbackground_color(GREEN);
            uLCD.text_string("CLASSIC", 3, 6, FONT_7X8, BLACK);
            wait(0.1);
            //Level Select button
            uLCD.filled_rectangle(13,60+5,113,78+5,GREEN);
            uLCD.rectangle(12,59+5,114,79+5,LGREY);
            uLCD.text_string("LEVEL SELECT",3,9,FONT_7X8,BLACK);
            wait(0.1); 
            //options button
            uLCD.filled_rectangle(13,88,113,106,GREEN);
            uLCD.rectangle(12,87,114,87+20,LGREY);
            uLCD.text_string("DIFFICULTY",3,12,FONT_7X8,BLACK);
            switch (*currSel) {// see which option was chosen
                case 0:
                    //change to easy
                	free(selPress);
                	free(upPress);
                	free(downPress);
                	free(currSel);
                	free(changeSel);
                    
                    return 0;
                case 1: 
                    //change to normal
                	free(selPress);
                	free(upPress);
                	free(downPress);
                	free(currSel);
                	free(changeSel);
                    
                    return 1;
                case 2:
                    //change to hard
                    free(selPress);
                    free(upPress);
                    free(downPress);
                    free(currSel);
                    free(changeSel);
                	return 2;
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