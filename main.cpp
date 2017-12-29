/* Gatech ECE2035 2017 FALL MAZE RUNNER
* Copyright (c) 2017 Gatech ECE2035
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

// Include header files for platform
#include "mbed.h"

// Include header files for pacman project
#include "globals.h"
#include "math_extra.h"
#include "physics.h"
#include "game.h"
#include "wall.h"
#include "doublely_linked_list.h"
#include "menu.h"
#include "arena.h"

#include<stdio.h>

// Hardware initialization
DigitalIn left_pb(p21);  // push button
DigitalIn right_pb(p22); // push button
DigitalIn up_pb(p23);    // push button
DigitalIn down_pb(p24);  // push button
uLCD_4DGL uLCD(p9,p10,p11); // LCD (serial tx, serial rx, reset pin;)
Serial pc(USBTX,USBRX);     // used by Accelerometer
MMA8452 acc(p28, p27, 100000); // Accelerometer
SDFileSystem sd(p5, p6, p7, p8, "sd"); // SD card and filesystem (mosi, miso, sck, cs)

//speaker initialization
AnalogOut DACout(p18);

// Level creation method declaration
DLinkedList* create_blank_level();

// Parameters. Declared in globals.h
const float mass = 0.001;
const int radius = 4;
const float bounce = 0.5;
int gameDiff = 1;
const double pi = 3.141592653589793238462;


/** Main() is where you start your implementation */
int main()
{
    ////////////////////////////
    // Power-on initialization
    ////////////////////////////
    // Turn up the serial data rate so we don't lag
    uLCD.baudrate(3000000);
    pc.baud(115200);

    // Initialize the buttons
    // Each *_pb variable is 0 when pressed
    left_pb.mode(PullUp);
    right_pb.mode(PullUp);
    up_pb.mode(PullUp);
    down_pb.mode(PullUp);

    // Other hardware initialization here (SD card, speaker, etc.)

    ///////////////
    // Reset loop
    ///////////////
    // This is where control between major phases of the game happens
    // This is a good place to add choose levels, add the game menu, etc.

    ////////////
    // Menu   
    ////////////
    //this is where I will draw the menu and implement a loop to select choices.
    uLCD.background_color(BLACK);
    uLCD.cls();

    
    uLCD.locate(39,2);
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
    
    int *currSel = (int*)malloc(sizeof(int));
    int *changeSel = (int*)malloc(sizeof(int));
    int exitmenu = 1;
    *currSel = 0;
    *changeSel = 0;
    int *selPress = (int*)malloc(sizeof(int));
    int *upPress = (int*)malloc(sizeof(int));
    int *downPress = (int*)malloc(sizeof(int));


    DLinkedList* saves = create_dlinkedlist();

    for(int i = 0; i < 6; i++) {
        insertHead(saves, NULL);
    }
    
    DigitalOut myled(p30);

    
        myled = 1;
        wait(0.2);
        

    
    
    while(exitmenu)
    {
        *selPress = right_pb;
        *upPress = up_pb;
        *downPress = down_pb;
        
        if (!*selPress){ //if selection button is pressed
            
            switch (*currSel) {// see which option was chosen
                case 0:
                    uLCD.cls();
                    free(selPress);
                    free(upPress);
                    free(downPress);
                        // Initialze game state
                        DLinkedList* levelOne = createLevel1();
                        DLinkedList* levelTwo = createLevel2();
                        DLinkedList* levelThree = createLevel3();
                        DLinkedList* arena = create_dlinkedlist();
                        insertTail(arena,(void*)levelOne);
                        insertTail(arena,(void*)levelTwo);
                        insertTail(arena,(void*)levelThree);
                        Physics state = {0};
                        state.px = 20.0;        // Position in the center of the screen
                        state.py = 20.0;
                        state.vx = 0.0;         // Initially unmoving
                        state.vy = 0.0;

                        // Delegate to the game loop to execute the level
                        // run_game() is in game.cpp
                        run_game((DLinkedList*)getHead(arena), &state, saves);
                        run_game((DLinkedList*)getNext(arena), &state, saves);
                        run_game((DLinkedList*)getNext(arena), &state, saves);

                        // Destory the arena and entities once we're done with the level
                        destroyList(arena);
                        
                        exitmenu = 0;

                    
                    break;
                case 1:
                    //load level select menu
                    //once the levels to play have been returned, initialize them
                    //and run them
                    DLinkedList* levels = runLevelSelectMenu();
                    if (levels != NULL) {
                        free(selPress);
                        free(upPress);
                        free(downPress);
                        Physics state = {0};
                        state.px = 20.0;        // Position in the center of the screen
                        state.py = 20.0;
                        state.vx = 0.0;         // Initially unmoving
                        state.vy = 0.0;
                        
                        run_game((DLinkedList*)getHead(levels),&state, saves);
                        run_game((DLinkedList*)getNext(levels),&state, saves);
                        if (getNext(levels)!= NULL)
                        {
                            run_game((DLinkedList*)getCurrent(levels),&state, saves);
                        }

                        // Destory the arena and entities once we're done with the game
                        destroyList(levels);
                        exitmenu = 0;
                        
                    }
                    *currSel = 0;
                    *selPress = 1;
                    break;
                case 2:
                    //load difficulty menu
                    //will return a 0,1, or 2 for changing the mass
                    //more "massive" balls will accelerate slower
                    int newDiff = runDifficultySelectMenu();
                    if (newDiff == 0) {
                        gameDiff = .1;
                    } else if (newDiff == 2) {
                        gameDiff = 2;
                    } else {
                        gameDiff = 1;
                    }
                    *currSel = 0;
                    *selPress = 1;
                    break;
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
    uLCD.cls();
    uLCD.textbackground_color(BLACK);
    uLCD.text_string("GAME OVER",4,2,FONT_7X8,GREEN);
    for (int i = 0; i < 8000; i++){
        DACout.write_u16((uint16_t)2*65535*cos(2.0*pi*150.0*((double)i/8000.0)));
    }
    for (int i = 0; i < 2000; i++){
        DACout.write_u16((uint16_t)2*65535*cos(2.0*pi*183.0*((double)i/8000.0)));
    }
    for (int i = 0; i < 3000; i++){
        DACout.write_u16((uint16_t)2*65535*cos(2.0*pi*250.0*((double)i/8000.0)));
    }
    


    
}

/** Creates a level with only bounding walls and a ball. */
DLinkedList* create_blank_level()
{
    DLinkedList* arena = create_dlinkedlist();

    // Initialize the walls
    Wall* walls[4];
    walls[0] = create_wall(HORIZONTAL, 0, 0, 127, bounce);  // top
    walls[1] = create_wall(HORIZONTAL, 0, 127, 127, bounce);// bottom
    walls[2] = create_wall(VERTICAL, 0, 0, 127, bounce);    // left
    walls[3] = create_wall(VERTICAL, 127, 0, 127, bounce);  // right
    
    // Add the walls to the arena
    for (int i = 0; i < 4; i++)
        insertTail(arena, (void*)walls[i]);

    // Initialize the ball
    Ball* ball = (Ball*) malloc(sizeof(Ball));
    ball->type = BALL;
    ball->x = 20;
    ball->y = 20;
    
    // Add ball to the arena 
    // NOTE: The ball should always be last in the arena list, so that the other 
    // ArenaElements have a chance to compute the Physics updates before the 
    // ball applies forward euler method.
    insertTail(arena, (void*)ball);
    
    return arena;
}