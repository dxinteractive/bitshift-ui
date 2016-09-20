/*
 * display_SSD1306
 * Rendering specifics for Adafruit SSD1306 128x64 OLED screen
 * Copyright (c) 2016 Damien Clarke
 * damienclarke.me | github.com/dxinteractive/bitshift
 *
 * .-.    _  .-.      .-.    _  .--. .-. 
 * : :   :_;.' `.     : :   :_;: .-'.' `.
 * : `-. .-.`. .'.--. : `-. .-.: `; `. .'
 * ' .; :: : : :`._-.': .. :: :: :   : : 
 * `.__.':_; :_;`.__.':_;:_;:_;:_;   :_; 
 */


#ifndef BITSHIFT_DISPLAY_SSD1306_H
#define BITSHIFT_DISPLAY_SSD1306_H

#include "../display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class BitshiftDisplaySSD1306 : public BitshiftDisplay
{
    public:
        BitshiftDisplaySSD1306(int pin_sid, int pin_sclk, int pin_dc, int pin_rst, int pin_cs):
			BitshiftDisplay(),
			screen(pin_sid, pin_sclk, pin_dc, pin_rst, pin_cs) {}
		~BitshiftDisplaySSD1306() {}

		virtual void render() {}

	private:
		Adafruit_SSD1306 screen;
};

#endif