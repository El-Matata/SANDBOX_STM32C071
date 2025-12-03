/*
 * display.c
 *
 *  Created on: Jun 28, 2024
 *      Author: mahdi
 */


#include "display.h"

typedef struct {
	SSD1306_Font_t* font_Size;
	SSD1306_COLOR background_Color;

	uint8_t temperature_x_Cursor;
	uint8_t temperature_y_Cursor;

	uint8_t humidity_x_Cursor;
	uint8_t humidity_y_Cursor;

	uint8_t day_x_Cursor;
	uint8_t day_y_Cursor;

	uint8_t time_x_Cursor;
	uint8_t time_y_Cursor;

} display_t;

display_t display_Info;

void display_Init(void){
	display_Info.font_Size = &Font_6x8;
	display_Info.background_Color = Black;

	display_Info.temperature_x_Cursor = display_Info.font_Size->width*(sizeof("TEMPERATURE"));
	display_Info.temperature_y_Cursor = display_Info.font_Size->height*TEMPERATURE;

	display_Info.humidity_x_Cursor = display_Info.font_Size->width*(sizeof("HUMIDITY"));
	display_Info.humidity_y_Cursor = display_Info.font_Size->height*HUMIDITY;

	display_Info.day_x_Cursor = display_Info.font_Size->width*(sizeof("DAY"));
	display_Info.day_y_Cursor = display_Info.font_Size->height*DAY;

	display_Info.time_x_Cursor = display_Info.font_Size->width*(sizeof("TIME"));
	display_Info.time_y_Cursor = display_Info.font_Size->height*TIME;

	ssd1306_Init();
	ssd1306_Fill(display_Info.background_Color);

	ssd1306_SetCursor(0, display_Info.temperature_y_Cursor);
	ssd1306_WriteString("TEMPERATURE ", *display_Info.font_Size, White);

	ssd1306_SetCursor(0, display_Info.humidity_y_Cursor);
	ssd1306_WriteString("HUMIDITY ", *display_Info.font_Size, White);

	ssd1306_SetCursor(0, display_Info.day_y_Cursor);
	ssd1306_WriteString("DAY ", *display_Info.font_Size, White);

	ssd1306_SetCursor(0, display_Info.time_y_Cursor);
	ssd1306_WriteString("TIME ", *display_Info.font_Size, White);

	ssd1306_UpdateScreen();
}


void display_Data_OLED(uint8_t DATA_TYPE, double data){

	char buffer[32];

	sprintf(buffer, "%.2f  ", data);
	switch (DATA_TYPE) {
	case TEMPERATURE:
		ssd1306_SetCursor(display_Info.temperature_x_Cursor, display_Info.temperature_y_Cursor);
		ssd1306_WriteString(buffer, *display_Info.font_Size, White);
		break;
	case HUMIDITY:
		ssd1306_SetCursor(display_Info.humidity_x_Cursor, display_Info.humidity_y_Cursor);
		ssd1306_WriteString(buffer, *display_Info.font_Size, White);
		break;
	case DAY:
		ssd1306_SetCursor(display_Info.day_x_Cursor, display_Info.day_y_Cursor);
		ssd1306_WriteString(buffer, *display_Info.font_Size, White);
		break;
	case TIME:
		ssd1306_SetCursor(display_Info.time_x_Cursor, display_Info.time_y_Cursor);
		ssd1306_WriteString(buffer, *display_Info.font_Size, White);
		break;
	default:
		break;
	}
	ssd1306_UpdateScreen();
}



