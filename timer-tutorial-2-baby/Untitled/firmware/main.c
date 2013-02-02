/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint16_t count;
volatile uint16_t count2;

int main(void)
{
    
    TCCR1 |= _BV(CTC1); //clear timer on compare
    //TCCR1 &= ~(_BV(COM1A1)|_BV(COM1A0)); // disconnect from OC1A
    //TCCR1 |= _BV(CS10); // no prescale
    TCCR1 |= _BV(CS11); // prescale 2
    //TIMSK |= _BV(TOIE1); //timer overflow
    TIMSK |= _BV(OCIE1A); //activate compare interruppt
    OCR1A = 187;
    TCNT1 = 0;
    
	DDRB |= 1<<PB0;
    PORTB &= ~(1 << PB0);

    sei();
    
    /* endless loop */
    for(;;){

    }
    return 0;   /* never reached */
}


ISR(TIMER1_COMPA_vect)
{
    count++;
    
    if (count >= 44110) {
        PORTB ^= (1 << PB0);
        //count2++;
        count = 0;
    }
    
    //if (count2 >= 2) {
    //    PORTB ^= (1 << PB0);
    //    count2 = 0;
    //}
    
}