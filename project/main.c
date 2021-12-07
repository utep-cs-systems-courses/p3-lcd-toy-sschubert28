#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

void main()
{
  
  P1DIR |= LED;		/**< Led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);                 /**< GIE (enable interrupts) */

  /* Setting up playing field and score board */
  clearScreen(COLOR_BLACK);     // Draw black background
  drawString5x7(3, 152, "Player1:", COLOR_WHITE, COLOR_BLACK);  // Draw player 1 score board
  drawString5x7(72, 152, "Player2:", COLOR_WHITE, COLOR_BLACK);  // Draw player 2 score board
  drawRectOutline(2, 2, screenWidth-5, screenHeight-13, COLOR_WHITE);   // Draw field outline
  drawRectOutline(2, (screenHeight-15)/2, screenWidth-5, .5, COLOR_WHITE);  // Draw half line
  fillRectangle((screenWidth / 2)-15, 5, 30, 3, COLOR_WHITE);   // Draw top paddle
  fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_WHITE);   // Draw bottom paddle
  
  
  while (1) {			// forever
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;	// led off 
    or_sr(0x10);	// CPU OFF
    P1OUT |= LED;	// led on 
  }
}
