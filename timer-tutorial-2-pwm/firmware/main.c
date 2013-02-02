#include <avr/io.h>
#include <util/delay.h>
void pwm_init()
{
    // initialize TCCR0 as per requirement, say as follows
    TCCR0A |= (1<<WGM00)|(1<<COM0A1)|(1<<WGM01);
	TCCR0B |= (1<<CS00);
	
	
    // make sure to make OC0 pin (pin PB3 for atmega32) as output pin
    DDRB |= (1<<PB0);
}

void main()
{
	uint8_t i = 0;
    // initialize timer in PWM mode
    pwm_init();	
    // run forever
    while(1)
    {
		
		for (i =0; i<255; ++i) {
			OCR0A = i;
			_delay_ms(2);
		}
		_delay_ms(10);
		for (i =255; i>0; --i) {
			OCR0A = i;
			_delay_ms(2);
		}
			_delay_ms(100);
    }
}
