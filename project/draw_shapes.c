#include "draw_shapes.h"    
#include "switches.h"

// Global Variables
// axis zero for col, axis 1 for row
short drawPosP[2] = {(screenWidth / 2)-15, screenHeight-16};
short drawPosC[2] = {(screenWidth / 2)-15, 5};
short redrawScreen = 1;
int playerScore = 0, computerScore = 0;
char playerScoreP = 48, computerScoreP = 48;

// Local Variables
short velocity[2] = {3,8};
short limits[4] = {3, screenWidth-4, 8, screenHeight-17};  // {left, right, top, bottom}
int direction = 0;  // 0 for left and 1 for right

void
update_shape(void)
{  
  if (direction == 0) {  // Check if Computer paddle is going Left
    if ( drawPosC[0] - velocity[1] <= limits[0]) {  // If its gone print over the screen change direction
      direction = 1;
    } else {
      fillRectangle(drawPosC[0], drawPosC[1], 30, 3, COLOR_BLACK);
      drawPosC[0] = drawPosC[0] - velocity[1]; 
      fillRectangle(drawPosC[0], drawPosC[1], 30, 3, COLOR_WHITE);
    }
  } else if (direction == 1) {  // Check if Computer paddle is going Right
    if ( drawPosC[0] + velocity[1] + 30 >= limits[1]) {  // If its gone print over the screen change direction
      direction = 0;
    } else {
      fillRectangle(drawPosC[0], drawPosC[1], 30, 3, COLOR_BLACK);
      drawPosC[0] = drawPosC[0] + velocity[1]; 
      fillRectangle(drawPosC[0], drawPosC[1], 30, 3, COLOR_WHITE);
    }
  }
  
  if (switch4_down && (drawPosP[0] + velocity[0] + 30) <= limits[1]) {  // Check if player paddle can still go right.
    fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_BLACK);
    drawPosP[0] = drawPosP[0] + velocity[0]; 
    fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_WHITE);
  }
  
  if (switch3_down && (drawPosP[0] - velocity[0]) >= limits[0]) {  // Check if player paddle can still go left
    fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_BLACK);
    drawPosP[0] = drawPosP[0] - velocity[0]; 
    fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_WHITE);
  }

  if(switch1_down) {
    playerScore++;
    playerScoreP++;
    drawChar5x7(50, 152, playerScoreP, COLOR_WHITE, COLOR_BLACK);
  }
}

