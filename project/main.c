#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!

short drawPosF[3] = {screenWidth-5, screenHeight-13, (screenHeight-15)/2};  // Coordanites for the field
int loop = 1;

void gameSetup()
{
  clearScreen(COLOR_BLACK);     // Draw black background
  drawString5x7(3, 152, "Player1:", COLOR_WHITE, COLOR_BLACK);  // Draw player 1 score board
  drawChar5x7(50, 152, playerScoreP, COLOR_WHITE, COLOR_BLACK);  // Draw player 2 score
  drawString5x7(65, 152, "Computer:", COLOR_WHITE, COLOR_BLACK);  // Draw Computer score board
  drawChar5x7(118, 152, computerScoreP, COLOR_WHITE, COLOR_BLACK);  // Draw Computer score
  drawRectOutline(2, 2, drawPosF[0], drawPosF[1], COLOR_WHITE);   // Draw field outline
  drawRectOutline(2, drawPosF[2], drawPosF[0], .5, COLOR_WHITE);  // Draw half line
  fillRectangle(drawPosC[0], drawPosC[1], 30, 3, COLOR_WHITE);   // Draw top paddle
  fillRectangle(drawPosP[0], drawPosP[1], 30, 3, COLOR_WHITE);   // Draw bottom paddle
  drawDiamond((screenWidth/2)-6, drawPosF[2]-5, 5, COLOR_WHITE);   // Draw ball/diamond
  
}

void endGameMessage()
{
  clearScreen(COLOR_BLACK);     // Draw black background
  if (playerScore == 5) {
    drawString5x7(3, screenWidth/2, "PLAYER 1 WINS!!!", COLOR_WHITE, COLOR_BLACK);  // Player win message
  } else if (computerScore == 5) {
    drawString5x7(3, screenWidth/2, "COMPUTER WINS!!!", COLOR_WHITE, COLOR_BLACK);  // Computer win message
  }
}

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
  gameSetup();
  
  while (loop) {  // Until somebody wins 
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    
    if (playerScore == 5 || computerScore == 5) {
      loop = 0;
    }
    
    P1OUT &= ~LED;	// led off 
    or_sr(0x10);	// CPU OFF
    P1OUT |= LED;	// led on 
  }
  endGameMessage();
}
