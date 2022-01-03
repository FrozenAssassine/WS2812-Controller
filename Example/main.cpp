#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

//!Important: define Number of Pixels and OutputPin before including "WS2812.h"
#define NumberOfPixels 12
#define OutputPin PINB0
#include "WS2812.h"

int main(void)
{
	DDRB = 0b00000001; //Set PINB0 as output
	Strip strip; //Create an instance of the Strip class
	strip.InitialiseStrip(); //Turn all leds off
	
	strip.SetPixelColor(0, 255,0,0); //Set the color of led one to red
	strip.SetPixelColor(1, 0,255,0); //Set the color of led two to green
	strip.SetPixelColor(2, 0,0,255); //Set the color of led three to blue
	strip.ShowPixel(); //Send the colors to the strip
}
