#include "draw_shapes.h"    
#include "switches.h"

// axis zero for col, axis 1 for row
short drawPosP[2] = {(screenWidth / 2)-15, screenHeight-16};
short drawPosC[2] = {(screenWidth / 2)-15, 5};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;


void
update_shape(void)
{
  if(switch4_down) {
    fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_BLACK);
    drawPosP[0] = drawPosP[0] + velocity[0]; 
    fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_WHITE);
  }
  if(switch3_down) {
    fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_BLACK);
    drawPosP[0] = drawPosP[0] - velocity[0]; 
    fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_WHITE);
  }
}

