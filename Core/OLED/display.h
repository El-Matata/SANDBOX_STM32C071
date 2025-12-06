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

#include "Graphics/Images.h"

typedef enum {
	TEMPERATURE,
	HUMIDITY,
	DAY,
	TIME
} DATA_DISPLAY_t ;


void display_Init(void);
void display_Data_OLED(uint8_t DATA_TYPE, double data);
void display_Wombat(void);

#endif /* OLED_DISPLAY_H_ */
