#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
 
 
         ##          ##
           ##      ##        
         ##############
       ####  ######  ####
     ######################
     ##  ##############  ##    
     ##  ##          ##  ##
           ####  ####
 
 
*/


volatile unsigned long t; //unsigned interger 0 - 65535

void timer_init()
{
    //PWM SOUND OUTPUT
    TCCR0A |= (1<<WGM00)|(1<<WGM01); //Fast pwm
    
    //TCCR0A |= (1<<WGM00) ; //Phase correct pwm
    
    TCCR0A |= (1<<COM0A1); //Clear OC0A/OC0B on Compare Match when up-counting.
    TCCR0B |= (1<<CS00);//no prescale
	
        
    //TIMER1 SOUND GENERATOR @ 44100hz
    //babygnusb attiny85 clock frequency = 16.5 Mhz
    TCCR1 |= _BV(CTC1); //clear timer on compare
    //TCCR1 |= _BV(CS10); // prescale 1
    TCCR1 |= _BV(CS11); // prescale 2
    //TCCR1 |= _BV(CS10)|_BV(CS12); // prescale 16    
    //TCCR1 |= _BV(CS11)|_BV(CS12); // prescale 32
    //TCCR1 |= _BV(CS10)|_BV(CS11)|_BV(CS12); // prescale 64
    //TCCR1 |= _BV(CS13); // prescale 128
    //TCCR1 |= _BV(CS10) | _BV(CS13); // prescale 256
    TIMSK |= _BV(OCIE1A); //activate compare interruppt
    //OCR1A = 3; // (16500000/2)/387 = 22050Hz
    OCR1C = 100; // (16500000/2)/187 = 44100Hz
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

    OCR0A = (t * (t>>5|t>>8))>>(t>>16); //viznut
    //OCR0A = t * ((t>>12|t>>8)&63&t>>4);
    
    //if (t>65534) t=0;
    
}