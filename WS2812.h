/*
 * WS2812.h
 *
 * Created: 02.01.2022 21:35:01
 *  Author: Julius
 */ 
#ifndef WS2812_H_
#define WS2812_H_

#include <stdbool.h>
#include <stdlib.h>

#define ArraySize(type) sizeof(type)/sizeof(type[0])

uint8_t MaxBrightness = 255;

typedef struct leditem
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} LedItem;

class Strip{
	
//All private methodes:
private:
	LedItem leditems[NumberOfPixels];
	void TimeLed (uint8_t z) {
		switch (z){
			
			case 0:{
				PORTB |= (1<<OutputPin);
				_delay_us(0.12);
				PORTB &= ~(1<<OutputPin);
				_delay_us(0.52); //0.12 + 0.52
				break;
			}
			case 1:{
				PORTB |= (1<<OutputPin);
				_delay_us(0.7);
				PORTB &= ~(1<<OutputPin);
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
		if(red>MaxBrightness)
			red=MaxBrightness;
		if(green>MaxBrightness)
			green=MaxBrightness;		
		if(blue>MaxBrightness)
			blue=MaxBrightness;
			
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
		leditems[index].red = red;
		leditems[index].green = green;
		leditems[index].blue = blue;
	}
	
//All public methodes:
public:
	bool LedIsOff(uint16_t index){
		if(index > ArraySize(leditems))
		return true;

		return leditems[index].red == 0 && leditems[index].green == 0 && leditems[index].blue == 0;
	}
	void ShowPixel()
	{
		for(uint16_t led = 0; led < ArraySize(leditems); led++)
		{
			//If led doesn't have any value, send zero without converting:
			if(LedIsOff_Intern(led))
			{
				for(uint8_t i = 0; i<24;i++)
				{
					TimeLed(0);
				}
			}
			//If led has a color, calculate and send it:
			else
			{
				DoTimeLed(led);
			}
			_delay_us(20);
		}
		_delay_us(30);
	}
	void SetPixelColor(uint16_t index, uint16_t count, uint32_t color)
	{
		if(index + count > ArraySize(leditems))
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
		if(index > ArraySize(leditems))
			return;
			
		SetColor(index, (color & 0xff0000) >> 16, (color & 0x00ff00) >> 8, (color & 0x0000ff));
	}
	void SetPixelColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
	{
		if(index > ArraySize(leditems))
			return;
			
		SetColor(index, red, green, blue);
	}
	void SetPixelColor(uint16_t index, uint16_t count, uint8_t red, uint8_t green, uint8_t blue)
	{
		if(index + count > ArraySize(leditems))
			return;
		
		for(uint16_t i = index; i<index + count; i++){
			SetColor(i, red, green, blue);
		}
	}

	void SetMaxBrightness(uint8_t maxbright){
		MaxBrightness = maxbright;
	}
	void LedsOff()
	{
		for(uint16_t i= 0; i<ArraySize(leditems); i++)
		{
			SetColor(i,0,0,0);
		}
		ShowPixel();
	}
	void InitialiseStrip()
	{
		for (uint8_t i = 0; i < ArraySize(leditems); i++) {
			leditems[i].red = leditems[i].green = leditems[i].blue =0;
			for(uint8_t i = 0; i<24;i++){
				TimeLed(0);
			}
			_delay_us(50);
		}
	}
	uint16_t GetLedCount()
	{
		return ArraySize(leditems);
	}
};
