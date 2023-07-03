#include "F_CPU.h"
#include <math.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "LedStrip/LedStrip.h"

// Led strip settings
const uint8_t led_count = 34;

const RGB white_color = { 255, 255, 255 };// White

const RGB rainbow_colors[7] = {
	{ 255, 0, 0 },  // Red
	{ 255, 128, 0 },// Orange
	{ 255, 255, 0 },// Yellow
	{ 0, 255, 0 },  // Green
	{ 0, 255, 255 },// Cyan
	{ 0, 0, 255 },  // Blue
	{ 128, 0, 255 } // Purple
};
// ------------------

// Flags & system variables
uint8_t led_strip_mode;

uint8_t array_animation_index, animation_ticks;

const uint8_t led_width_mask[3][8] = {
	{ 3, 3, 3, 3, 3, 3, 3, 0 },
	{ 1, 3, 3, 3, 3, 3, 3, 2 },
	{ 2, 3, 3, 3, 3, 3, 3, 1 },
};
// ------------------------

void static_color_modes(void);
void halh_dynamic_color_modes(void);
void dynamic_color_modes(void);

int main(void)
{
	// Flags & system variables
	uint8_t avoid_flag = 0;
	uint8_t modes_count = 13;
	// ------------------------
		
	// Pins configuration
		// Avoid module       PB0 INPUT
	DDRB &= ~(1<<0);
	PORTB &= ~(1<<0);
		// Led strip          PB1 OUTPUT
	DDRB |= (1<<1);
	PORTB &= ~(1<<1);
		// Button             PB2 INPUT PULL-UP
	DDRB &= ~(1<<2);
	PORTB |= (1<<2);
	_delay_ms(100);
	// ----------------
	
	// Start program
		// Set start-up rainbow color during 5 sec.
	setLedStripArray((RGB *)rainbow_colors, sizeof(rainbow_colors), led_count);
	_delay_ms(5000);
	
		// Clean led strip
	ledStripOFF(led_count);
	_delay_ms(250);
	
    while (1) 
    {	
		uint8_t pins = PINB;
		// Avoid module
		if (~pins & (1<<0))
		{
			switch (avoid_flag)
			{
				case 0:
					avoid_flag = !avoid_flag;
					static_color_modes();
					halh_dynamic_color_modes();
					break;
				
				case 1:
					avoid_flag = !avoid_flag;
					ledStripOFF(led_count);
					_delay_ms(50);
					break;
				
				default:
					break;
			}
			_delay_ms(500);
			while (~PINB & (1<<0));
			_delay_ms(500);
		}
		// Button
		else if (~pins & (1<<2))
		{
			if (led_strip_mode >= modes_count - 1)
			{
				led_strip_mode = 0;
			}
			else
			{
				led_strip_mode++;
			}
			_delay_ms(250);
			while (~PINB & (1<<2));
			_delay_ms(250);
		}
		// Led strip modes
		else if (avoid_flag)
		{
			dynamic_color_modes();
		}
    }
}

void static_color_modes(void)
{
	// White
	if (led_strip_mode == 0)
	{
		setLedStripColor(white_color, led_count);
	}
	// Red, Orange, Yellow, Green, Cyan, Blue, Purple
	else if (led_strip_mode < 8)
	{
		setLedStripColor(rainbow_colors[led_strip_mode - 1], led_count);
	}
	// Rainbow (1 led per color)
	else if (led_strip_mode == 8)
	{
		setLedStripArray((RGB *)rainbow_colors, sizeof(rainbow_colors), led_count);
	}
	// Rainbow (3 leds per color)
	else if (led_strip_mode == 9)
	{
		setLedStripColorsArray((RGB *)rainbow_colors, (uint8_t *)led_width_mask[0], 8, 21, led_count);
	}
}

void halh_dynamic_color_modes(void)
{
	// Rainbow run (1 led per color)
	if (led_strip_mode == 10)
	{
		array_animation_index = 0;
		animation_ticks = 0;
	}
	// Rainbow run (3 leds per color)
	else if (led_strip_mode == 11)
	{
		array_animation_index = 0;
		animation_ticks = 0;
	}
	// Rainbow breath
	else if (led_strip_mode == 12)
	{
		array_animation_index = 0;
		animation_ticks = 0;
	}
}

void dynamic_color_modes(void)
{
	// Rainbow run (1 led per color)
	if (led_strip_mode == 10)
	{
		if (array_animation_index >= 7) array_animation_index = 0;
		RGB save_rainbow_colors[7] = { 0 };
		memcpy(save_rainbow_colors, rainbow_colors, sizeof(rainbow_colors));
		uint8_t i = 0;
		for (i = 0; i < array_animation_index; i++)
		{
			RGB mem[7] = { 0 };
			mem[0] = save_rainbow_colors[sizeof(rainbow_colors) / sizeof(RGB) - 1];
			memcpy(&mem[1], save_rainbow_colors, sizeof(rainbow_colors) - sizeof(RGB));
			memcpy(save_rainbow_colors, mem, sizeof(rainbow_colors));
		}
		setLedStripArray((RGB *)save_rainbow_colors, sizeof(rainbow_colors), led_count);
		array_animation_index++;
		_delay_ms(150);
	}
	
	// Rainbow run (3 leds per color)
	else if (led_strip_mode == 11)// 20 tics
	{
		if (array_animation_index >= 3) array_animation_index = 0;
		if (animation_ticks >= 21) animation_ticks = 0;
		RGB save_rainbow_colors[8] = { 0 };
		memcpy(save_rainbow_colors, rainbow_colors, sizeof(rainbow_colors));
		uint8_t i = 0;
		for (i = 0; i < animation_ticks; i += 3)
		{
			RGB mem[8] = { 0 };
			memcpy(&mem[1], save_rainbow_colors, sizeof(rainbow_colors));
			mem[0] = mem[7];
			memcpy(save_rainbow_colors, mem, sizeof(save_rainbow_colors));
		}
		setLedStripColorsArray(
			save_rainbow_colors,
			(uint8_t *)led_width_mask[array_animation_index],
			sizeof(save_rainbow_colors) / sizeof(RGB),// Elements count
			3 * sizeof(rainbow_colors) / sizeof(RGB),// Leds per tick
			led_count);
		array_animation_index++;
		animation_ticks++;
		_delay_ms(150);
	}
	
	// Rainbow breath
	else if (led_strip_mode == 12)
	{
		if (array_animation_index >= 7) array_animation_index = 0;
		float cof = (float)sin(animation_ticks * 3.1415f / 180.f);
		RGB color = {
			(uint8_t)((float)rainbow_colors[array_animation_index].r * cof),
			(uint8_t)((float)rainbow_colors[array_animation_index].g * cof),
			(uint8_t)((float)rainbow_colors[array_animation_index].b * cof)
		};
		setLedStripColor(color, led_count);
		if (animation_ticks == 180)
		{
			animation_ticks = 0;
			array_animation_index++;
		}
		animation_ticks += 1;
		_delay_ms(40);
	}
}