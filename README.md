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
#define NumberOfPixels 12 //Set the number of leds
#define OutputPort PINB0 //Define the outputport

#define F_CPU 8000000 //Set the clockspeed

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <WS2812.h> //include the libary

int main(void)
{
	DDRB = 0b00000001; //Define the output
	Strip strip;

	strip.InitialiseStrip();

	strip.SetPixelColor(11, 255, 0, 0); //Set color of pixel 11 to red
	strip.SetPixelColor(3, 5 255, 255, 0); //Set color of pixel 3 to 8 green
	strip.SetPixelColor(5, 65025); //Set color as 32bit value: for example 65025 for green
	strip.ShowPixel(); //Call to actually display the changes
}
```

## Functions:
```cpp
LedIsOff(uint16_t index) //returns whether led is on or off
ShowPixel() //Shows all previously set led's
SetPixelColor(uint16_t index, uint32_t color) //Set the color of the pixel which is indicated by index to a 32bit intager
SetPixelColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) //Set the color of the pixel which is indicated by index to 3 8bit values
SetPixelColor(uint16_t index, uint16_t count, uint8_t red, uint8_t green, uint8_t blue) //Change "count" pixels from index
InitialiseStrip() //Initialise the strip => set all leds to off
GetLedCount() //Returns the number of leds
``` 
