#include "draw_shapes.h"    
#include "switches.h"

// Global Variables
// axis zero for col, axis 1 for row
short drawPosP[2] = {(screenWidth / 2)-15, screenHeight-16};
short drawPosC[2] = {(screenWidth / 2)-15, 5};
short drawPosF[3] = {screenWidth-5, screenHeight-13, (screenHeight-15)/2};  // Coordanites for the field
short drawPosB[2] = {(screenWidth/2)-6, ((screenHeight-15)/2)-5};  // vertical, horizontal
short redrawScreen = 1;
int playerScore = 0, computerScore = 0;
char playerScoreP = 48, computerScoreP = 48;

// Local Variables
short velocity[3] = {3,8,5};
short limits[4] = {3, screenWidth-4, 8, screenHeight-17};  // {left, right, top, bottom}
int directionC = 0;  // 0 for left and 1 for right
int directionB[2] = {0, 0};  // {up/down, left/right} 0 for left and down and 1 for right and up
short drawPosBN[2] = {(screenWidth/2)-6, ((screenHeight-15)/2)-5};  // vertical, horizontal

void
update_shape(void)
{
  drawDiamond(drawPosB[0], drawPosB[1], 5, COLOR_BLACK);   // Draw ball/diamond
  drawPosB[1] = drawPosB[1] + velocity[2];
  drawDiamond(drawPosB[0], drawPosB[1], 5, COLOR_WHITE);   // Draw ball/diamond
  drawRectOutline(2, drawPosF[2], drawPosF[0], .5, COLOR_WHITE);  // Draw half line

  if (directionB[0] = 0) {
    drawPosBN[1] = drawPosB[1] + velocity[2];
    if (drawPosBN[1] >= drawPosP[0] && drawPosBN[1] <= drawPosP[0] + 30) {
      directionB[0] = 1;
      drawDiamond(drawPosB[0], drawPosB[1], 5, COLOR_BLACK);   // Draw ball/diamond
      drawPosB[1] = drawPosB[1] - velocity[2];
      // Make sound
      drawDiamond(drawPosB[0], drawPosB[1], 5, COLOR_WHITE);   // Draw ball/diamond
    } else {
      // It didn't hit the paddle so score
    }
  }

  
  
  if (directionC == 0) {  // Check if Computer paddle is going Left
    if (drawPosC[0] - velocity[1] <= limits[0]) {  // If its gone print over the screen change direction
      directionC = 1;
    } else {
      fillRectangle(drawPosC[0], drawPosC[1], 30, 3, COLOR_BLACK);
      drawPosC[0] = drawPosC[0] - velocity[1]; 
      fillRectangle(drawPosC[0], drawPosC[1], 30, 3, COLOR_WHITE);
    }
  } else if (directionC == 1) {  // Check if Computer paddle is going Right
    if (drawPosC[0] + velocity[1] + 30 >= limits[1]) {  // If its gone print over the screen change direction
      directionC = 0;
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

  if(switch1_down) {  // Used for testing
    playerScore++;
    playerScoreP++;
    drawChar5x7(50, 152, playerScoreP, COLOR_WHITE, COLOR_BLACK);
  }
}

