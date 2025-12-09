/*
 * display.h
 *
 *  Created on: Jun 28, 2024
 *      Author: mahdi
 */

#ifndef OLED_DISPLAY_H_
#define OLED_DISPLAY_H_

#include "stdio.h"
#include "ssd1306_tests.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"


typedef enum {
	SMALL,
	MEDIUM,
	LARGE,
} font_size_t ;

void display_init(void);
void display_clear(void);
void display_string(uint8_t cursor_x, uint8_t cursor_y, char* string,font_size_t Font);
void display_distance(uint16_t distance);
void display_Wombat(void);

#endif /* OLED_DISPLAY_H_ */
