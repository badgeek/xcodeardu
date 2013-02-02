#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
 _________.   .__  __          .__          __                        
/  __  \_ |__ |__|/  |_  _____ |__|__  ____/  |______  ______   ____  
>      <| __ \|  \   __\/     \|  \  \/  /\   __\__  \ \____ \_/ __ \ 
/   --   \ \_\ \  ||  | |  Y Y  \  |>    <  |  |  / __ \|  |_> >  ___/ 
\______  /___  /__||__| |__|_|  /__/__/\_ \ |__| (____  /   __/ \___  >
       \/    \/               \/         \/           \/|__|        \/

*/


volatile uint16_t t; //unsigned interger 0 - 65535

void timer_init()
{
    //PWM SOUND OUTPUT
    TCCR0A |= (1<<WGM00)|(1<<COM0A1)|(1<<WGM01); //Fast pwm
	TCCR0B |= (1<<CS00);//no prescale
	
        
    //TIMER1 SOUND GENERATOR @ 44100hz
    //babygnusb attiny85 clock frequency = 16.5 Mhz
    TCCR1 |= _BV(CTC1); //clear timer on compare
    TCCR1 |= _BV(CS11); // prescale 2
    TIMSK |= _BV(OCIE1A); //activate compare interruppt
    OCR1A = 187; // (16500000/2)/187 = 44100Hz
    TCNT1 = 0; //init count
    
	sei(); //enable global interrupt
    
    // babygnusb led pin
    DDRB |= (1<<PB0);
}

int main(void)
{
    // initialize timer & Pwm
    timer_init();	
    // run forever
    while(1)
    {
		
    }
    return 0;
}

ISR(TIMER1_COMPA_vect)
{
    t++;
    OCR0A = ((t>>2|t>>4)&90&t>>5&t>>9&t>>3&t>>5);
    
}