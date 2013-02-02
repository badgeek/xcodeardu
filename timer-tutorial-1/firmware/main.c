#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// TIMER0

#define AVR_CTC _BV(WGM01);
#define AVR_PRESCALE_1024 _BV(CS02) | _BV(CS00)
#define AVR_COMPARE_IRQ_A _BV(OCIE0A)
#define PB5_OUT (1<<PB5)
#define PB5_ON (1<<PB5)

int timer;

void register_init()
{

	
	TCCR0A |= AVR_CTC; // enable clear timer on compare match..
	TCCR0B |= AVR_PRESCALE_1024; //prescale 1024
	TIMSK0 |= AVR_COMPARE_IRQ_A;  //enable compare interrupt untuk channel A
	DDRB   |= PB5_OUT; //set PB5 as output
	
	sei();
}

int main()
{
	register_init();
	
	while(1)
	{	
		
		//PORTB = 1 << PB5;

	}
	return 0;
}


ISR(TIMER0_COMPA_vect)
{
	//PORTB = PB5_ON;
	
	if (timer >= 7000) {
		PORTB ^= PB5_ON;
		timer = 0;
	}
	
	timer++;
}