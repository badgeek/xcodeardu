/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */


//receiver

#include <avr/io.h>
#include <avr/interrupt.h>

int timer_count;

int main(void)
{
	
	//output pin
	DDRB |= (1 << PB5);
	PORTB &= (1 << PB5);
	
	//uart
	int UBBR_value = 25; //2400 baud
	UBRR0H =  (unsigned char) (UBBR_value >> 8);
	UBRR0L =  (unsigned char) UBBR_value;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); //ENABLE TX RX
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	
	
	unsigned char receiveData;
	
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
		
		
		//transmit data
		
		while ( !(UCSR0A & (1<<RXC0)) );
		receiveData = UDR0;
		
		if (receiveData = 0b11110000) {
			PORTB ^= (1 << PB5);
		}
		
		
    }
    return 0;   /* never reached */
}