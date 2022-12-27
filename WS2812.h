/*
 * WS2812.h
 *
 * Created: 02.01.2022 21:35:01
 *  Author: Julius
 */ 
#ifndef WS2812_H_
#define WS2812_H_
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define COLOR_RGB 0
#define COLOR_GRB 1

typedef struct leditem
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} LedItem;

class Strip{

//All private functions:
private:

	uint8_t maxBrightness = 255;
	uint8_t colorMode;
	
	//LedItem * leditems;
	LedItem * leditems;
	
	void TimeLed (uint8_t z) {
		switch (z){
			
			case 0:{
				RGB_OutputPort |= (1<<RGB_OutputPin);
				_delay_us(0.12);
				RGB_OutputPort &=~ (1<<RGB_OutputPin);
				_delay_us(0.52); //0.12 + 0.52
				break;
			}
			case 1:{
				RGB_OutputPort |= (1<<RGB_OutputPin);
				_delay_us(0.7);
				RGB_OutputPort &=~ (1<<RGB_OutputPin);
				_delay_us(0.2); //0.7 + 0.2
				break;
			}
		}
	}
	bool LedIsOff_Intern(uint16_t index){
		return leditems[index].red == 0 && leditems[index].green == 0 && leditems[index].blue == 0;
	}
	void DoTimeLed(uint16_t index) 
	{
		uint8_t red = leditems[index].red;
		uint8_t green = leditems[index].green;
		uint8_t blue = leditems[index].blue;
		if(red>maxBrightness)
			red=maxBrightness;
		if(green>maxBrightness)
			green=maxBrightness;		
		if(blue>maxBrightness)
			blue=maxBrightness;
			
		for (uint8_t bit = 8; bit > 0; --bit)
		{
			TimeLed((green >> (bit-1)) & 1);
		}
		for (uint8_t bit = 8; bit > 0; --bit)
		{
			TimeLed((red >> (bit-1)) & 1);
		}
		for (uint8_t bit = 8; bit > 0; --bit)
		{
			TimeLed((blue >> (bit-1)) & 1);
		}
	}
	void SetColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
	{
		if(colorMode == COLOR_RGB){
			leditems[index].red = red;
			leditems[index].green = green;
		}
		else{ //GRB		
			leditems[index].red = green;
			leditems[index].green = red;
		}
		
		leditems[index].blue = blue;
	}
	
//All public functions:
public:
	uint16_t numberOfPixels;

	Strip(int nbrOfPixels, int colorMode = 0)
	{
		this->colorMode = colorMode;
		numberOfPixels = nbrOfPixels;
		leditems = (LedItem*)malloc(nbrOfPixels);
	}

	bool LedIsOff(uint16_t index){
		if(index > numberOfPixels)
			return true;

		return leditems[index].red == 0 && leditems[index].green == 0 && leditems[index].blue == 0;
	}
	void ShowPixel()
	{
		for(uint16_t led = 0; led < numberOfPixels; led++)
		{
			//If led doesn't have any value, send zero without converting:
			if(LedIsOff_Intern(led)) {
				for(uint8_t i = 0; i<24;i++) { TimeLed(0);}
			}
			//If led has a value, calculate and send it:
			else {
				DoTimeLed(led);
			}
			_delay_us(20);
		}
		_delay_us(30);
	}
	void SetPixelColor(uint16_t index, uint16_t count, uint32_t color)
	{
		if(index + count > numberOfPixels)
			return;
		
		uint8_t red = (color & 0xff0000) >> 16;
		uint8_t green = (color & 0x00ff00) >> 8;
		uint8_t blue = (color & 0x0000ff);
		
		for(uint16_t i = index; i<index + count; i++){
			SetColor(i, red, green, blue);
		}
	}
	void SetPixelColor(uint16_t index, uint32_t color)
	{
		if(index > numberOfPixels)
			return;
			
		SetColor(index, (color & 0xff0000) >> 16, (color & 0x00ff00) >> 8, (color & 0x0000ff));
	}
	void SetPixelColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
	{
		if(index > numberOfPixels)
			return;
			
		SetColor(index, red, green, blue);
	}
	void SetPixelColor(uint16_t index, uint16_t count, uint8_t red, uint8_t green, uint8_t blue)
	{
		if(index + count > numberOfPixels)
			return;
		
		for(uint16_t i = index; i<index + count; i++){
			SetColor(i, red, green, blue);
		}
	}
	void SetMaxBrightness(uint8_t maxbright){
		maxBrightness = maxbright;
	}
	void LedsOff()
	{
		for(uint16_t i= 0; i<numberOfPixels; i++)
		{
			SetColor(i,0,0,0);
		}
		ShowPixel();
	}
	void InitialiseStrip()
	{
		for (uint8_t i = 0; i < numberOfPixels; i++) {
			leditems[i].red = leditems[i].green = leditems[i].blue =0;
			for(uint8_t i = 0; i<24;i++){
				TimeLed(0);
			}
			_delay_us(50);
		}
		ShowPixel();
	}
	uint16_t GetLedCount()
	{
		return numberOfPixels;
	}
	int Map(int value, int in_min, int in_max, int out_min, int out_max) {
		return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
	uint32_t ColorHSV(uint16_t hue, uint8_t sat, uint8_t val)
	{
		if(hue > 360) hue = 360;
		if(sat > 255) sat = 255;
		if(val > 255) val = 255;
		
		hue = hue * 4.25;
		uint8_t r, g, b;
		if (hue < 510) {
			b = 0;
			if (hue < 255){ 
				r = 255;
				g = hue;
			}
			else {
				r = 510 - hue;
				g = 255;
			}
			} else if (hue < 1020) {
			r = 0;
			if (hue < 765) {
				g = 255;
				b = hue - 510;
				} else {
				g = 1020 - hue;
				b = 255;
			}
			} else if (hue < 1530) {
			g = 0;
			if (hue < 1275) {
				r = hue - 1020;
				b = 255;
				} else {
				r = 255;
				b = 1530 - hue;
			}
		}
		else {
			r = 255;
			g = b = 0;
		}
		uint32_t v1 = 1 + val;
		uint16_t s1 = 1 + sat;
		uint8_t s2 = 255 - sat;
		return ((((((r * s1) >> 8) + s2) * v1) & 0xff00) << 8) |
		(((((g * s1) >> 8) + s2) * v1) & 0xff00) |
		(((((b * s1) >> 8) + s2) * v1) >> 8);
	}
	uint32_t GetPixelColor(uint16_t index)
	{
		if(index > numberOfPixels)
			return 0;		
		return ((leditems[index].red << 8) | leditems[index].green) << 8 | leditems[index].blue;
	}
	uint8_t GetPixelRed(uint16_t index)
	{
		if(index > numberOfPixels)
			return 0;
		return leditems[index].red;
	}
	uint8_t GetPixelGreen(uint16_t index)
	{
		if(index > numberOfPixels)
			return 0;
		return leditems[index].green;
	}
	uint8_t GetPixelBlue(uint16_t index)
	{
		if(index > numberOfPixels)
			return 0;
		return leditems[index].blue;
	}
};
