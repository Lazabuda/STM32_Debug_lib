// DEFINES
#define MCO_pin GPIO_Pin_8
#define MCO_port GPIOA

#define Rx_USART GPIO_Pin_10
#define Tx_USART GPIO_Pin_9
#define USART_PORT GPIOA

// Func declarations
void show_clock();
void UART_init();
void USART1_send (uint32_t data);