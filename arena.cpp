#include "arena.h"
#include "globals.h"
#include "doublely_linked_list.h"
#include "goal.h"
#include "wall.h"
#include "pothole.h"
#include "windmill.h"
#include "token.h"
#include "game.h"
#include "sandtrap.h"


//add more elements later



//the order of an arena is walls,potholes,element1,element2,element3,goal,ball

DLinkedList* createLevel1()
{
    //394 bytes
    DLinkedList* arena = create_dlinkedlist();
    

    //make walls
    Wall* walls[6];//186 bytes
    walls[0] = create_wall(HORIZONTAL, 0, 0, 127, bounce);  // top
    walls[1] = create_wall(HORIZONTAL, 0, 127, 127, bounce);// bottom
    walls[2] = create_wall(VERTICAL, 0, 0, 127, bounce);    // left
    walls[3] = create_wall(VERTICAL, 127, 0, 127, bounce);  // right
    walls[4] = create_wall(VERTICAL, 32,0, 80,bounce);
    walls[5] = create_wall(VERTICAL, 80, 32, 95,bounce);

    //add walls
    for (int i = 0; i < 6; i++)
        insertTail(arena, (void*)walls[i]);

    //make windmills
    Windmill* windmills[3];//84 bytes
    windmills[0] = create_windmill(COUNTERCW,57,40,3.14*.13);
    windmills[1] = create_windmill(COUNTERCW,13,80,3.14*.06);
    windmills[2] = create_windmill(CLOCKWISE,100,15,3.14*.7);
    
    //add windmills
    for (int i = 0; i < 3; i++){
        insertTail(arena, (void*)windmills[i]);
    }
    
    //add 5 tokens
    Token* tokens[5];//80 bytes
    tokens[0] = create_token(100,114);
    tokens[1] = create_token(10,104);
    tokens[2] = create_token(64,85);
    tokens[3] = create_token(78,29);
    tokens[4] = create_token(50,10);
    for (int i = 0; i < 5; i++){
        insertTail(arena, (void*)tokens[i]);
    }

    //make potholes
    Pothole* potholes[1];//20 bytes
    potholes[0] = create_pothole(20,118,8);

    //add potholes
    insertTail(arena, (void*)potholes[0]);

    //make/add goal
    insertTail(arena, (void*)create_goal(110,40)); //16 bytes

    // Initialize the ball
    Ball* ball = (Ball*) malloc(sizeof(Ball)); // 12 bytes
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

DLinkedList* createLevel2()
{
    //384 bytes
    DLinkedList* arena = create_dlinkedlist();

    //make walls
    Wall* walls[5];// 140 bytes
    walls[0] = create_wall(HORIZONTAL, 0, 0, 127, bounce);  // top
    walls[1] = create_wall(HORIZONTAL, 0, 127, 127, bounce);// bottom
    walls[2] = create_wall(VERTICAL, 0, 0, 127, bounce);    // left
    walls[3] = create_wall(VERTICAL, 127, 0, 127, bounce);  // right
    walls[4] = create_wall(HORIZONTAL,0,96,112,bounce);

    //add walls
    for (int i = 0; i < 5; i++)
        insertTail(arena, (void*)walls[i]);

    //add windmills
    Windmill* windmills[4]; //112 bytes
    windmills[0] = create_windmill(COUNTERCW,17,40,3.14*.13);
    windmills[1] = create_windmill(COUNTERCW,17,80,3.14*.06);
    windmills[2] = create_windmill(COUNTERCW,47,64,3.14*.7);
    windmills[3] = create_windmill(CLOCKWISE,89,72,3.14*.32);

    //add windmills
    for (int i = 0; i < 4; i++)
        insertTail(arena, (void*)windmills[i]);




    //add 5 tokens
    Token* tokens[5]; //80 bytes
    tokens[0] = create_token(10,114);
    tokens[1] = create_token(120,104);
    tokens[2] = create_token(68,71);
    tokens[3] = create_token(78,77);
    tokens[4] = create_token(50,120);
    for (int i = 0; i < 5; i++)
        insertTail(arena, (void*)tokens[i]);


    insertTail(arena, (void*)create_sandtrap(64,104,10,30));//24 bytes


    //make/add goal
    insertTail(arena, (void*)create_goal(10,110));//16 bytes

    // Initialize the ball
    Ball* ball = (Ball*) malloc(sizeof(Ball));//12 bytes
    ball->type = BALL;
    ball->x = 20;
    ball->y = 20;

    insertTail(arena, (void*)ball);

    return arena;
}

DLinkedList* createLevel3()
{
    //572 bytes
    DLinkedList* arena = create_dlinkedlist();

    //make walls
    Wall* walls[9];//364 bytes
    walls[0] = create_wall(HORIZONTAL, 0, 0, 127, bounce);  // top
    walls[1] = create_wall(HORIZONTAL, 0, 127, 127, bounce);// bottom
    walls[2] = create_wall(VERTICAL, 0, 0, 127, bounce);    // left
    walls[3] = create_wall(VERTICAL, 127, 0, 127, bounce);  // right
    walls[4] = create_wall(VERTICAL, 32, 0, 64, bounce);
    walls[5] = create_wall(VERTICAL, 64, 16, 64,bounce);
    walls[6] = create_wall(VERTICAL, 80, 16, 16, bounce);
    walls[7] = create_wall(HORIZONTAL, 64,16, 16,bounce);
    walls[8] = create_wall(HORIZONTAL,0,96,112,bounce);

    //add walls
    for (int i = 0; i < 9; i++)
        insertTail(arena, (void*)walls[i]);

    //add windmills
    Windmill* windmills[2];//112 bytes
    windmills[0] = create_windmill(COUNTERCW,45,16,3.14*.06);
    windmills[1] = create_windmill(COUNTERCW,47,64,3.14*.7);
    

    //add windmills
    for (int i = 0; i < 3; i++)
        insertTail(arena, (void*)windmills[i]);

    //add 5 tokens
    Token* tokens[5];//80 bytes
    tokens[0] = create_token(10,114);
    tokens[1] = create_token(10,104);
    tokens[2] = create_token(64,85);
    tokens[3] = create_token(78,29);
    tokens[4] = create_token(50,10);
    for (int i = 0; i < 5; i++)
        insertTail(arena, (void*)tokens[i]);

    //make potholes
    Pothole* potholes[2];//40 bytes
    potholes[0] = create_pothole(89,110,4);
    potholes[1] = create_pothole(30,110,2);

    //add potholes
    insertTail(arena, (void*)potholes[0]);
    insertTail(arena, (void*)potholes[1]);


    //make/add goal
    insertTail(arena, (void*)create_goal(110,40));//16 bytes


    // Initialize the ball
    Ball* ball = (Ball*) malloc(sizeof(Ball));
    ball->type = BALL;
    ball->x = 20;
    ball->y = 20;

    insertTail(arena, (void*)ball);

    return arena;
}

DLinkedList* copy_arena(DLinkedList* arena1)
{
    DLinkedList* newArena = create_dlinkedlist();

    ArenaElement* elem = (ArenaElement*)getHead(arena1);
    do {
        switch(elem->type) {
            case WALL:
                Wall* wall = create_wall(((Wall*)elem)->direction,((Wall*)elem)->x,((Wall*)elem)->y,
                    ((Wall*)elem)->length,((Wall*)elem)->bounce);
                insertTail(newArena,(void*)wall);
                break;
            case POTHOLE:
                Pothole* pothole = create_pothole(((Pothole*)elem)->x,((Pothole*)elem)->y,
                    ((Pothole*)elem)->radius);
                insertTail(newArena,(void*)pothole);
                break;
            case WINDMILL:
                Windmill* wm = create_windmill(((Windmill*)elem)->direction,((Windmill*)elem)->x,
                    ((Windmill*)elem)->y, ((Windmill*)elem)->angle);
                insertTail(newArena,(void*)wm);
                break;
            case TOKEN:
                Token* token = create_token(((Token*)elem)->x,((Token*)elem)->y);
                token->should_erase = ((Token*)elem)->should_erase;
                insertTail(newArena,(void*)token);
                break;
            case SANDTRAP:
                Sandtrap* st = create_sandtrap(((Sandtrap*)elem)->x1,((Sandtrap*)elem)->x2,
                    ((Sandtrap*)elem)->y1,((Sandtrap*)elem)->y2);
                insertTail(newArena,(void*)st);
                break;
            case GOAL:
                Goal* goal = create_goal(((Goal*)elem)->x,((Goal*)elem)->y);
                insertTail(newArena,(void*)goal);
                break;
            case BALL:
                Ball* ball = (Ball*)malloc(sizeof(Ball));
                ball->type = BALL;
                ball->x = ((Ball*)elem)->x;
                ball->y = ((Ball*)elem)->y;
                insertTail(newArena,(void*)ball);
                break;
            default:
                break;
        }
    } while(elem = (ArenaElement*)getNext(arena1));
    return newArena;

}



