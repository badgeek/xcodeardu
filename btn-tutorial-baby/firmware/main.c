/*
 File:       main.c
 Version:    1.0.0
 Date:       May. 12, 2006
 
 AVR Tutorial #3 - Button Debounce (Polling)
 
 Schematic and details available at http://www.micahcarrick.com.
 
 ****************************************************************************
 Copyright (C) 2006 Micah Carrick   <email@micahcarrick.com>
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define F_CPU 8000000UL         /* 8MHz crystal oscillator */

#define BUTTON_PORT PORTB       /* PORTx - register for button output */
#define BUTTON_PIN PINB         /* PINx - register for button input */
#define BUTTON_BIT PB2          /* bit for button input/output */

#define LED_PORT PORTB          /* PORTx - register for LED output */
#define LED_BIT PB0             /* bit for button input/output */
#define LED_DDR DDRB            /* LED data direction register */

#define DEBOUNCE_TIME 25        /* time to wait while "de-bouncing" button */
#define LOCK_INPUT_TIME 250     /* time to wait after a button press */

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

/* function prototypes */

void delay_ms(uint16_t ms);
void init_io();
int button_is_pressed();
void toggle_led();


int 
main (void)
{
    init_io();
    
    while (1)                       
    {
        if (button_is_pressed())
        {
            
            //toggle_led();
            LED_PORT |= _BV(LED_BIT);
            
            delay_ms(LOCK_INPUT_TIME);
        }else{
            LED_PORT &= ~_BV(LED_BIT);
            
            
        }
    }
}

/* 
 * init_io - Initialize I/O and peripherals.
 */ 
void 
init_io() 
{
    /* set LED pin as digital output */
    LED_DDR = _BV (LED_BIT); 
    
    /* led is OFF initially (set pin high) */         
    LED_PORT |= _BV(LED_BIT);
    
    DDRB |= _BV(DDB1);
    /* turn on internal pull-up resistor for the switch */
    BUTTON_PORT |= _BV(BUTTON_BIT);
}

/* 
 * delay_ms - Perform long delays in approximate milliseconds.
 */ 
void 
delay_ms(uint16_t ms) 
{
    while ( ms ) 
    {
        _delay_ms(1);
        ms--;
    }
}

/* 
 * button_is_pressed - Check if the button is being pressed with debounce.
 * Returns 1 if the button was pressed, 0 otherwise.
 */ 
int 
button_is_pressed()
{
    /* the button is pressed when BUTTON_BIT is clear */
    if (!bit_is_clear(BUTTON_PIN, BUTTON_BIT))
    {
        delay_ms(DEBOUNCE_TIME);
        if (!bit_is_clear(BUTTON_PIN, BUTTON_BIT)) return 1;
    }
    
    return 0;
}

/* 
 * toggle_led - Toggles the state of the LED.
 */ 
void
toggle_led()
{
    LED_PORT ^= _BV(LED_BIT);
}

