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

typedef struct leditem
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	
} LedItem;

class Strip{
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
	bool LedIsOff(uint16_t index){
		if(index > ArraySize(leditems))
		return true;

		return leditems[index].blue == 0 &&
		leditems[index].green == 0 &&
		leditems[index].red== 0;
	}
	void DoTimeLed(uint16_t index){
		for (uint8_t bit = 8; bit > 0; --bit)
		{
			TimeLed((leditems[index].green >> (bit-1)) & 1);
		}
		for (uint8_t bit = 8; bit > 0; --bit)
		{
			TimeLed((leditems[index].red >> (bit-1)) & 1);
		}
		for (uint8_t bit = 8; bit > 0; --bit)
		{
			TimeLed((leditems[index].blue >> (bit-1)) & 1);
		}
	}
public:
	void ShowPixel(){
		for(uint16_t led = 0; led<ArraySize(leditems); led++)
		{
			//If led doesn't have any value send zero without converting:
			if(LedIsOff(led)){
				for(uint8_t i = 0; i<24;i++){
					TimeLed(0);
				}
			}
			//If led has a set color, calculate and send it:
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
	
		for(uint16_t i = index; i<index + count; i++){
			leditems[i].red = (color & 0xff0000) >> 16;
			leditems[i].green = (color & 0x00ff00) >> 8;
			leditems[i].blue = (color & 0x0000ff);
		}
	}
	void SetPixelColor(uint16_t index, uint32_t color)
	{
		if(index > ArraySize(leditems))
		return;

		leditems[index].red = (color & 0xff0000) >> 16;
		leditems[index].green = (color & 0x00ff00) >> 8;
		leditems[index].blue = (color & 0x0000ff);
	}
	void SetPixelColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
	{
		if(index > ArraySize(leditems))
		return;

		leditems[index].red = red;
		leditems[index].green = green;
		leditems[index].blue = blue;
	}
	void SetPixelColor(uint16_t index, uint16_t count, uint8_t red, uint8_t green, uint8_t blue)
	{
		if(index + count > ArraySize(leditems))
		return;

		for(uint16_t i = index; i<index + count; i++){
			leditems[i].red = red;
			leditems[i].green = green;
			leditems[i].blue = blue;
		}
	}
	uint32_t HSVtoRGB(uint16_t H, uint8_t S,uint8_t V){
		if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
			//Invalid input
			return 0;
		}
	
		float s = S/100;
		float v = V/100;
		float C = s*v;
		float X = C*(1-abs(fmod(H/60.0, 2)-1));
		float m = v-C;
		float r,g,b;
		if(H >= 0 && H < 60){
			r = C,g = X,b = 0;
		}
		else if(H >= 60 && H < 120){
			r = X,g = C,b = 0;
		}
		else if(H >= 120 && H < 180){
			r = 0,g = C,b = X;
		}
		else if(H >= 180 && H < 240){
			r = 0,g = X,b = C;
		}
		else if(H >= 240 && H < 300){
			r = X,g = 0,b = C;
		}
		else{
			r = C,g = 0,b = X;
		}
		uint32_t rgb = (r+m)*255;
		rgb = (rgb << 8) + (g+m)*255;
		rgb = (rgb << 8) + (b+m)*255;
		return rgb;
	}
	void InitialiseStrip()
	{
		for (uint8_t i = 0; i < ArraySize(leditems); i++) {
			leditems[i].red = leditems[i].green = leditems[i].blue =0;
		}
		ShowPixel();
	}
	uint16_t GetLedCount()
	{
		return ArraySize(leditems);
	}
};
#endif /* WS2812_H_ */
