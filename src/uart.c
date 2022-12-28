
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "uart.h"
//#include "printf.h"


#include <avr/io.h>


void uart_init(unsigned int ubrr)
{
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    //Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data */
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
}


void uart_flush(void)
{
    unsigned char dummy;
    while (UCSR0A & (1<<RXC0)) dummy = UDR0;
    dummy = dummy;
}

unsigned char uart_receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)));
    /* Get and return received data from buffer */
    return UDR0;
}



void uart_transmit(char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)));
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

void uart_send_string(char * data)
{
    while (*data)
    {
        //_putchar(*data++);
        uart_transmit(*data++);

    }
}