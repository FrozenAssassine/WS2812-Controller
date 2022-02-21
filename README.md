# WS2812-Controller
A library to control the WS2812-RGB led with an AVR-device

### How to use in Microchip Studio:
- Create a new C++ Executable project
- Select the chip you wanna use
- To add the library to your project, rightclicking on your project in Solutionexplorer (Ctrl + Alt + L) -> Add -> Existing Item. Now locate the WS2812.h file on your pc.
   
- To test it you can use following samplecode:
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
LedIsOff(5) //returns whether led number 5 is on or off
ShowPixel() //Shows all previously set led's
SetPixelColor(2, 65280) //Set the color of pixel 2 to green
SetPixelColor(4, 255, 0, 0) //Set the color of the pixel 4 to red
SetPixelColor(3, 7, 0, 0, 255) //Set the color from pixel 3 to pixel 10 to blue.
SetPixelColor(1, 5, 16711680) // //Set the color from pixel 1 to pixel 6 red.
LedsOff() //Turn all leds off
SetMaxBrightness(150) //Sets the maximum Brightness of the strip to 150. From 0-255
InitialiseStrip() //Initialise the strip => Set all leds to off
GetLedCount() //Returns the number of leds
``` 
