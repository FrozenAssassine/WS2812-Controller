#define F_CPU 8000000 //For Attiny 85
#include <avr/io.h>
#include <util/delay.h>
#include "WS2812.h"

int main(void)
{
	DDRB = 0b00000001; //Set PINB0 as output
	
	//Create an instance of the Strip class:
	//Set the pixelcount to 12
	//Set the Output to PORTB->PINB0
	Strip strip = Strip(12, PORTB, PINB0);
	
	strip.InitialiseStrip(); //Turn all leds off
	strip.SetMaxBrightness(255);
		
	int color = 0;
	for(uint16_t i= 0; i<strip.numberOfPixels; i++)
	{
		strip.SetPixelColor(i, strip.ColorHSV(color, 255,255));
		color += 360 / strip.numberOfPixels;
		_delay_ms(200);
		strip.ShowPixel(); //Send the colors to the strip
	}
}
