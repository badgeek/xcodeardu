/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <avr/interrupt.h>

int timer_count;

int main(void)
{
	
	//output pin
	DDRB |= (1 << PB5);
	PORTB &= (1 << PB5);
	
	
	//timer0 setup
	
	TCCR0A |= _BV(WGM01);
	TCCR0B |= (1 << CS00) | (1 << CS02); //1024 PRESCALE
	TIMSK0 |= (1 << TOIE0); //TIMER OVERFLOW
	//TCNT0 = 0;

	sei(); // enable interrupt for timer0
	
	//uart
	int UBBR_value = 25; //2400 baud
	UBRR0H =  (unsigned char) (UBBR_value >> 8);
	UBRR0L =  (unsigned char) UBBR_value;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); //ENABLE TX RX
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
		
		
		//transmit data
		

		
    }
    return 0;   /* never reached */
}


ISR(TIMER0_OVF_vect)
{
	timer_count++;
	if (timer_count >= 30) {
		
		while (! (UCSR0A  & (1 << UDRE0))   );
			UDR0 = 0b11110000;
		
		
		PORTB ^= (1 << PB5); 
		timer_count = 0;
	}
	TCNT0 = 0;
}