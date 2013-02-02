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


//unsigned int delay_efek[200];

volatile unsigned long t; // long
volatile uint8_t snd; // 0...255
volatile uint8_t sfx; // 0...255
volatile int j = 50;


void timer_init()
{
    //PWM SOUND OUTPUT
    TCCR0A |= (1<<WGM00)|(1<<WGM01); //Fast pwm
    //TCCR0A |= (1<<WGM00) ; //Phase correct pwm
    TCCR0A |= (1<<COM0A1); //Clear OC0A/OC0B on Compare Match when up-counting.
    TCCR0B |= (1<<CS00);//no prescale
        
    //TIMER1 SOUND GENERATOR @ 44100hz
    //babygnusb attiny85 clock frequency = 16.5 Mhz
    
    //TIMER SETUP
    TCCR1 |= _BV(CTC1); //clear timer on compare
    TIMSK |= _BV(OCIE1A); //activate compare interruppt
    TCNT1 = 0; //init count

    //TIMER FREQUENCY
    //TCCR1 |= _BV(CS10); // prescale 1
    //TCCR1 |= _BV(CS11); // prescale 2
    TCCR1 |= _BV(CS10)|_BV(CS12); // prescale 16    
    //TCCR1 |= _BV(CS11)|_BV(CS12); // prescale 32
    //TCCR1 |= _BV(CS10)|_BV(CS11)|_BV(CS12); // prescale 64
    //TCCR1 |= _BV(CS13); // prescale 128
    //TCCR1 |= _BV(CS10) | _BV(CS13); // prescale 256    
    
    //SAMPLE RATE
    OCR1C = 128; // (16500000/16)/8000 = 128
    //OCR1C = 93; // (16500000/16)/11025 = 93
    //OCR1C = 46; // (16500000/16)/22050 = 46
    //OCR1C = 23; // (16500000/16)/44100 = 23

    //ENABLE INTERRUPT
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
    //delay_efek[t%99] = ((t * ((t>>12|t>>8)&63&t>>4))/2);
 
    int value50 = 30;

    snd = (t * (t>>5|t>>8))>>(t>>16); //viznut
    //snd = (t * ((t>>12|t>>8)&63&t>>4));//floor((delay_efek[t%99]);
    sfx = (snd >> 4 << 7);
    //sfx = (snd >> 2 << 3);
    //sfx = sfx | j;
    OCR0A = sfx;

    j = j - 1;
    if (j <= 0) {
        j = value50;
    }
    
    
    t++;
}