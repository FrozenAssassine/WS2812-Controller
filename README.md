# WS2812-Controller
A library to control the Ws2812 with an AVR-device

### How to use in Microchip Studio:
- Create a new C++ Executable project
- Select the device you wanna use
- Add the library to your project:
 
	Import the library to your project by rightclicking on your project in Solutionexplorer (Ctrl + Alt + L) -> there you click on Add -> Existing Item. Now locate the WS2812.h file on your pc.
   
- To test it you can try following samplecode:
```cpp
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
```
#### After uploaded to your AVR the first three leds should light up in red, green and blue.


## Functions:
```cpp
LedIsOff(uint16_t index) //returns whether led is on or off
ShowPixel() //Shows all previously set led's
SetPixelColor(uint16_t index, uint32_t color) //Set the color of the pixel which is indicated by index to a 32bit integer
SetPixelColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) //Set the color of the pixel which is indicated by index to three 8bit values
SetPixelColor(uint16_t index, uint16_t count, uint8_t red, uint8_t green, uint8_t blue) //Set the color of pixels, indicated by count, starting by index to a rgb value.
SetPixelColor(uint16_t index, uint16_t count, uint32_t color) // //Set the color of pixels, indicated by count, starting by index to a 32bit integer
InitialiseStrip() //Initialise the strip => Set all leds to off
GetLedCount() //Returns the number of leds
``` 
