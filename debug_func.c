#include "debug_func.h"

void show_clock()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	// GPIOA BUS enable
 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			// Alternative function MODE
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// SPEED - High
  GPIO_InitStructure.GPIO_Pin = MCO_pin;				// PIN 9

  GPIO_Init(MCO_port, &GPIO_InitStructure);				// Struct initialization
 
  RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1);	// Clock from PLL to the A9 pin without dividing
}