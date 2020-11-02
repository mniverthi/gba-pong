#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "images.h"


extern State cs, ps;
extern int gameCount;


void drawMenu(void) {
  // drawRectDMA(50, 50, 50, 50, MAGENTA);
  // drawString(40, 112, "PONG", BLACK); 
  drawFullScreenImageDMA(menu);
  drawString(80, 31, "Start to play. Select for rules.", MAGENTA);
  // char buffer[1024];
  // sprintf(buffer, "High score: %05u", highScore);
  // drawString(105, 68, buffer, BLUE);
}
void posCalc(void) {

}

void clearScreen(void) {
  drawRectDMA(0, 0, 240, 160, BLACK);
}

void drawPlayScreen(void) { 
  
  char buffer[50];
  sprintf(buffer, "%d \n %d", cs.score1, cs.score2);
  drawString(SCORE_ROW, SCORE_COLUMN, buffer, YELLOW);
  drawImageDMA(145, 96, 48, 13, ponglogo);
  drawRectDMA(ps.p1.yPos, ps.p1.xPos, ps.p1.width, ps.p1.height, BLACK);
  drawRectDMA(ps.p2.yPos, ps.p2.xPos, ps.p2.width, ps.p2.height, BLACK);
  drawRectDMA(ps.ping.yPos, ps.ping.xPos,  2 * ps.ping.radius, 2 * ps.ping.radius, BLACK);
  
  drawRectDMA(cs.p1.yPos, cs.p1.xPos, cs.p1.width, cs.p1.height, P1COLOR);
  drawRectDMA(cs.p2.yPos, cs.p2.xPos, cs.p2.width, cs.p2.height, P2COLOR);
  drawRectDMA(cs.ping.yPos, cs.ping.xPos, 2 * cs.ping.radius, 2 * cs.ping.radius, BALLCOLOR);
  // char test[50];
  // sprintf(test, "%d", gameCount);
  // drawString(100, 200, test, WHITE);
  if (cs.oldScore1 < cs.score1) {
    cs.oldScore1++;
    delay();
  } else if (cs.oldScore2 < cs.score2) {
    cs.oldScore2++;
    delay();
  }
}

void drawRuleScreen(void) {
  drawFullScreenImageDMA(rulescreen);
  drawString(20, 70, "Welcome to pong!", WHITE);
  drawString(35, 20, "Paddle 1 controls are UP and DOWN.", WHITE);
  drawString(50, 20, "Paddle 2 controls are A and B.", WHITE);
  drawString(65, 32, "The first player to 10 wins!", WHITE);
  drawString(100, 32, "Press start to begin the game", RED);
  drawString(120, 20, "Press select to return to the menu", BLUE);
}

void drawEndScreen(void) {
  drawFullScreenImageDMA(endscreen);  
  if (cs.score1 > cs.score2) {
    drawString(50, 75, "Player 1 wins!", RED);
  } else {
    drawString(50, 75, "Player 2 wins!", BLUE);
  }
  drawString(100, 20, "Press select to return to the menu", RED);
}