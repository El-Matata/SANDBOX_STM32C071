/*
 * display.c
 *
 *  Created on: Jun 28, 2024
 *      Author: mahdi
 */


#include "display.h"
#include "Graphics/Images.h"

void display_init(void){
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetContrast(127);
	ssd1306_UpdateScreen();
}

void display_clear(void){
	ssd1306_Fill(Black);
	ssd1306_UpdateScreen();
}

void display_string(uint8_t cursor_x, uint8_t cursor_y, char* string, font_size_t Font){
	ssd1306_SetCursor(cursor_x, cursor_y);
	if(Font == SMALL){
		ssd1306_WriteString(string, Font_6x8, White);
	}
	else if(Font == MEDIUM){
		ssd1306_WriteString(string, Font_11x18, White);
	}
	else if(Font == LARGE){
		ssd1306_WriteString(string, Font_16x24, White);
	}
	ssd1306_UpdateScreen();
}

void display_Wombat(void){
	ssd1306_DrawBitmap(0, 0, WombatBitMap, 128, 64, White);
	ssd1306_UpdateScreen();
}
