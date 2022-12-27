#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#define RGB_OutputPort PORTB
#define RGB_OutputPin PINB0

#include "WS2812.h"

int main(void)
{
	DDRB = 0b00000001;
	Strip strip; //Create an instance of the Strip class
	strip.InitialiseStrip(12);

	while (true){
		strip.SetPixelColor(0,12,255,0,0);
		strip.ShowPixel();
		_delay_ms(1000);
		strip.LedsOff();
		_delay_ms(1000);
	}
}
