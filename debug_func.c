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


void UART_init()
{
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;            //Turn on clock on APB1 to UASRT1 ----------------------------тут
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;            //Turn on clock on AHB1 to GPIOA

  //PA9 - TX
  GPIOA->MODER &= ~GPIO_MODER_MODER9_0;            //MODER 10
  GPIOA->MODER |= GPIO_MODER_MODER9_1;            //MODER 10
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;               //PUPDR 00
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;               //OTYPER 0 => PA2 - AF PP
  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9;      //OSPEED 11 -  very high speed
  GPIOA->AFR[1] |= 0x00000070;                        //AF7

  //PA10 - RX
  GPIOA->MODER &= ~GPIO_MODER_MODER10;               //MODER 00
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10;               //PUPDR 0 => PA3 - floating input
  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10;   //OSPEED 11 -  very high speed

  USART1->BRR = 0x00001117;                              // BRR = (f(APB1)+ 4800)/9600, f(APB1) == 42 MHz
  USART1->CR1 |= USART_CR1_UE;                        //Enable USART2
  USART1->CR1 |= USART_CR1_TE;                        //Transmitter USART2
  USART1->CR1 |= USART_CR1_RE;                        //Resiver USART2

  USART1->CR1 |= USART_CR1_RXNEIE;                  //RX Interrupt Enable
  NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_send (uint32_t data)
{
  char data_str[20];
  char *new_line = "\r\n\0";
  sprintf(data_str, "%d", data);
  int i = 0;
  while(!USART1->SR & USART_SR_TC);
  while (i < strlen(data_str))
  {
    while(!USART1->SR & USART_SR_TC);
    USART1->DR = data_str[i];
    Delay(500);
    i++;
  }
  USART1->DR = *new_line;
}