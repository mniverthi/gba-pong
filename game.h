#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //


/*
* For example, for a Snake game, one could be:
*
* typedef struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* } Snake;
*
* 
* 
*
*
* Example of a struct to hold state machine data:
* 
* typedef struct state {
*   int currentState;
*   int nextState;
* } State
*
*/

typedef struct ball {
        int radius;
        int xPos;
        int yPos;
        u16 ballColor;
        int rowC;
        int colC;
} Ball;

typedef struct paddle {
        int xPos;
        int yPos;
        int width;
        int height;
        u16 paddleColor;
} Paddle;

typedef struct game_state {
        Ball ping;
        Paddle p1;
        Paddle p2;
        u16 score1;
        u16 score2;
        u16 oldScore1;
        u16 oldScore2;
} State;

void drawMenu(void);
void drawRuleScreen(void);
void drawEndScreen(void);
void drawPlayScreen(void);
void clearScreen(void);
void playLogic(void);
void initialize(void);
int hitP1(void);
int hitP2(void);
void updateButtons(void);
void updateObjects(void);
void delay(void);

#define P1COLOR RED
#define P2COLOR CYAN
#define BALLCOLOR YELLOW
#define PADDLEINCR 2
#define SCORE_ROW 5
#define SCORE_COLUMN 105

#endif
