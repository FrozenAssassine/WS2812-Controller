#define NumberOfPixels 12 //Set the number of leds
#define F_CPU 8000000 //Set the clockspeed
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <WS2812.h> //include the libary

int main(void)
{
	DDRB = 0b00000001; //Define the output
	
	InitialiseStrip();

	SetPixelColor(11, 255, 0, 0); //Set color of pixel 11 to red
	SetPixelColor(3, 5 255, 255, 0); //Set color of pixel 3 to 8 green
	SetPixelColor(5, 65025); //Set color as 32bit value: for example 65025 for green
	ShowPixel(); //Call to actually display the changes
}
	
