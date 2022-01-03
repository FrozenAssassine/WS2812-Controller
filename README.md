# WS2812-Controller
A library to control the Ws2812 with an AVR-device

### How to use in Microchip Studio:
- Create a new C++ Executable project
- Select the device you wanna use
- Add the library to your project:
  ###### Option 1:
  Import the library to your project by rightclicking on your project in Solutionexplorer (Ctrl + Alt + L) -> there you click on Add -> Existing Item. Now locate the WS2812.h file on your pc.
  ###### Option 2:
  You can also put the file to the other inbuild header librarys by navigating to "C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\avr\include\" there you can paste the WS2812.h file.
   
- Now In your project you can try following samplecode:

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
	DDRB = 0b00000001;
	Strip strip; //Create an instance of the Strip class
	strip.InitialiseStrip();
	
	strip.SetPixelColor(0, 255,0,0);
	strip.SetPixelColor(1, 0,255,0);
	strip.SetPixelColor(2, 0,0,255);
	strip.ShowPixel();
}
```

## Functions:
```cpp
LedIsOff(uint16_t index) //returns whether led is on or off
ShowPixel() //Shows all previously set led's
SetPixelColor(uint16_t index, uint32_t color) //Set the color of the pixel which is indicated by index to a 32bit integer
SetPixelColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) //Set the color of the pixel which is indicated by index to tree 8bit values
SetPixelColor(uint16_t index, uint16_t count, uint8_t red, uint8_t green, uint8_t blue) //Set the color of pixels, indicated by count, starting by index to a rgb value.
SetPixelColor(uint16_t index, uint16_t count, uint32_t color) // //Set the color of pixels, indicated by count, starting by index to a 32bit integer
HSVtoRGB(uint16_t H, uint8_t S,uint8_t V) //Convert HSV to RGB color
InitialiseStrip() //Initialise the strip => Set all leds to off
GetLedCount() //Returns the number of leds
``` 
