#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "images.h"

/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app.
typedef enum {
  MENU,
  RULES,
  PLAY,
  END
} GBAState;

int gameCount = 0;
State cs, ps;

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

 
  // Load initial game state
  GBAState state = MENU;
  GBAState prevState = END;

  while (1) {
    waitForVBlank();
    currentButtons = BUTTONS;  // Load the current state of the buttons

    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    switch (state) {
      case MENU:
        if (prevState != state) {
          clearScreen();
          prevState = state;
          gameCount = 0;
          drawMenu();
        }
        if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
          state = PLAY;
          prevState = MENU;
          gameCount++;
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
          state = RULES;
          prevState = MENU;
          gameCount++;
        }
        break;
      case RULES:
        if (prevState != state) {
          clearScreen();
          prevState = state;
          gameCount = 0;
          drawRuleScreen();
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
          state = MENU;
          prevState = RULES;
          gameCount++;
        }
        if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
          state = PLAY;
          prevState = RULES;
          gameCount++;
        }
        break;
      case PLAY:
        if (prevState != state) {
            clearScreen();
            prevState = state;
            gameCount = 0;
            cs.score1 = 0;
            cs.score2 = 0;
            cs.oldScore1 = 0;
            cs.oldScore2 = 0;
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
            state = MENU;
            prevState = PLAY;
            gameCount++;
        }
        if (cs.score1 == 10 || cs.score2 == 10) {
          state = END;
          prevState = PLAY;
          gameCount++;
        }
        ps = cs;
        playLogic();
        break;
      case END:
        if (prevState != state) {
          clearScreen();
          prevState = state;
          gameCount = 0;
          drawEndScreen();
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
          state = MENU;
          prevState = END;
          gameCount++;
        }
        break;
    }
    previousButtons = currentButtons;  // Store the current state of the buttons
  }
  return 0;
}
 