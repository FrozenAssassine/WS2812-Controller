#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

//!!!Important: define Number of Pixels and OutputPin before including "WS2812.h"!!!
#define NumberOfPixels 12
#define OutputPin PINB0
#include "WS2812.h"

int main(void)
{
	DDRB = 0b00000001;
	Strip strip; //Create an instance of the Strip class
	strip.InitialiseStrip();
	uint8_t red = 255,green = 0, blue = 0;
	
	while (true){
		for(uint16_t i = 0; i<strip.GetLedCount(); i++){
			strip.SetPixelColor(i,red,green,blue);
			strip.ShowPixel();
			_delay_ms(100);
		}
		if(red>254 && blue == 0){
			red=0;
			green = 255;
		}
		else if(green>254){
			blue=255;
			green = 0;
		}
		else if(blue>254 && red==0){
			blue=0;
			red = 255;
		}
	}
}