#include "game.h"
#include <stdio.h>
#include <stdlib.h>

extern State cs, ps;
extern int gameCount;

void initialize(void) {

  cs.ping.ballColor = BALLCOLOR;
  cs.ping.radius = 2;
  cs.ping.xPos = (rand() % (100) + 50);
  cs.ping.yPos = (rand() % (100) + 15);
  if (rand() % 2 == 0) {
    cs.ping.rowC = 2;
  } else {
    cs.ping.rowC = -2;
  }

  if (rand() % 2 == 0) {
    cs.ping.colC = 2;
  } else {
    cs.ping.colC = -2;
  }
  cs.p1.paddleColor = P1COLOR;
  cs.p1.width = 5;
  cs.p1.height = 40;
  cs.p1.xPos = 5;
  cs.p1.yPos = (rand() % 120);

  cs.p2.paddleColor = P2COLOR;
  cs.p2.width = 5;
  cs.p2.height = 40;
  cs.p2.xPos = 230;
  cs.p2.yPos = (rand() % 120);
}

void playLogic(void) {
  
  if (gameCount == 0) {
    clearScreen();
    initialize();
  } else {
    updateButtons();
    updateObjects();
  }
  if (gameCount == 0) {
    drawPlayScreen();
    delay();
    gameCount++;
  }
  if (gameCount > 0) {
    gameCount++;
    drawPlayScreen();
  } 
}

int hitP1(void) {
  return ((cs.ping.xPos == cs.p1.xPos + cs.p1.width + 1 || cs.ping.xPos == cs.p1.xPos + cs.p1.width) 
  && (cs.ping.yPos >= cs.p1.yPos) && (cs.ping.yPos <= cs.p1.yPos + cs.p1.height - (2 * cs.ping.radius)));
}


int hitP2(void) {
  return ((cs.ping.xPos == cs.p2.xPos - 2 * cs.ping.radius || cs.ping.xPos == cs.p2.xPos - 2 * cs.ping.radius + 1) 
  && (cs.ping.yPos >= cs.p2.yPos) && (cs.ping.yPos <= cs.p2.yPos + cs.p2.height - (2 * cs.ping.radius)));
}

void updateButtons(void) {
  u32 currentButtons = BUTTONS;
  if (KEY_DOWN(BUTTON_B, currentButtons)) {
      if (cs.p2.yPos >= 120) {
        cs.p2.xPos = 230;
        cs.p2.yPos = 120;
      } else {
        cs.p2.yPos += PADDLEINCR;
      }
    }
    if (KEY_DOWN(BUTTON_A, currentButtons)) {
      if (cs.p2.yPos <= 0) {
        cs.p2.xPos = 230;
        cs.p2.yPos = 0;
      } else {
        cs.p2.yPos -= PADDLEINCR;
      }
    }
    if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
      if (cs.p1.yPos >= 120) {
        cs.p1.xPos = 5;
        cs.p1.yPos = 120;
      } else {
        cs.p1.yPos += PADDLEINCR;
      }
    }
    if (KEY_DOWN(BUTTON_UP, currentButtons)) {
      if (cs.p1.yPos <= 0) {
        cs.p1.xPos = 5;
        cs.p1.yPos = 0;
      } else {
        cs.p1.yPos -= PADDLEINCR;
      }
    }
  }
  
  void updateObjects(void) {
    
    cs.ping.xPos += cs.ping.colC;
    cs.ping.yPos += cs.ping.rowC;

    //paddle deflection && (cs.ping.yPos <= cs.p1.yPos - (2 * cs.ping.radius)
    //paddle doesn't deflect, goes through left and right sides
    if (hitP1()) {
      cs.ping.colC = -cs.ping.colC;
    } else if(cs.ping.xPos <= 0) {
      // cs.ping.xPos = 0;
      // cs.ping.colC = -cs.ping.colC;
      cs.score2++;
      if (cs.score2 == 10) {
        gameCount = -1;
      }
      initialize();
    }
    if (hitP2()) {
      cs.ping.colC = -cs.ping.colC;
    } else if(cs.ping.xPos >= 240 - 2 * cs.ping.radius) {
      // cs.ping.xPos = 240 - 2 * cs.ping.radius;
      // cs.ping.colC = -cs.ping.colC;
      cs.score1++;
      if (cs.score1 == 10) {
        gameCount = -1;
      }
      initialize();
    }
    //goes off top and bottom
    if (cs.ping.yPos < 0) {
      cs.ping.yPos = 0;
      cs.ping.rowC = -cs.ping.rowC;
    }
    if (cs.ping.yPos > 160 - 2 * cs.ping.radius) {
      cs.ping.yPos = 160 - 2 * cs.ping.radius;
      cs.ping.rowC = -cs.ping.rowC;
    }
}

void delay(void) {
  volatile u32 increment = 0;
  while (increment < 400000) {
    ++increment;
  }
} 