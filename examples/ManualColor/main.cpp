#define F_CPU 8000000 //Set the clockspeed
#include <avr/io.h>
#include <util/delay.h>

#define RGB_OutputPort PORTB
#define RGB_OutputPin PINB0

#include "WS2812.h"

int main(void)
{
	DDRB = 0b00000001; //Define the output
	
	Strip strip = Strip(12);
	strip.InitialiseStrip(); //Turn all leds off

	strip.SetPixelColor(11, 255, 0, 0); //Set color of pixel 11 to red
	strip.SetPixelColor(3, 5 255, 255, 0); //Set color of pixel 3 to 8 green
	strip.SetPixelColor(5, 65025); //Set color as 32bit value: for example 65025 for green
	strip.ShowPixel(); //Call to actually display the changes
}
