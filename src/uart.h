#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(unsigned int ubrr);
void uart_flush(void);
unsigned char uart_receive(void);
void uart_transmit(char data);
void uart_send_string(char * data);


#endif