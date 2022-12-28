#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

//#ifndef F_CPU
//#define FCPU 16000000
//#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdint.h>

#include "src/uart.h"
//#include "src/printf.h"

#define BAUD 57600
#define MYBAUD (((F_CPU / (BAUD * 16UL))) - 1)


int main(void) {
    uart_init(MYBAUD);

    while(1)
    {
        _delay_ms(1000);
        //printf("PRINTF: %d\n", getal);
        uart_send_string("uartt send string\n");

    }
    return 0;
}
