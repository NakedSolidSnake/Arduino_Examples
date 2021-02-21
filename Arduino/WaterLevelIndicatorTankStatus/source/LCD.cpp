/*
 * LCD.c
 *
 *  Created on: 12 de set de 2019
 *      Author: solid
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "../include/LCD.h"
#include <string.h>

#define BLANK   "                "

typedef struct LCD_Context{
	int column;
	int line;
}LCD_Context;

static LCD_Context lcd_ctx = {
		.column = 0,
		.line = 0x80
};

#define LCD_RS_PIN	8
#define LCD_EN_PIN	9
#define LCD_D4_PIN	10
#define LCD_D5_PIN	11
#define LCD_D6_PIN	12
#define LCD_D7_PIN	13

#define LCD_SIZE	16

static LiquidCrystal lcd(LCD_RS_PIN,
						 LCD_EN_PIN,
						 LCD_D4_PIN,
						 LCD_D5_PIN,
						 LCD_D6_PIN,
						 LCD_D7_PIN);

int LCD_init(void)
{
	lcd.begin(LCD_SIZE, 2);
	return 0;
}

int LCD_clear(void)
{
	lcd.clear();
	return 0;
}

int LCD_setColumn(unsigned char column)
{

	if(column > LCD_SIZE)
		return -1;
	lcd_ctx.column = column;
	return 0;
}

int LCD_setLine(unsigned char line)
{
	switch(line)
	{
	case LCD_LINE_1:
		lcd_ctx.line = 0;
		break;

	case LCD_LINE_2:
		lcd_ctx.line = 1;
			break;

	default:
		return -1;
	}

	return 0;
}

int LCD_print(const char *text, unsigned int size)
{
	if(size > LCD_SIZE)
		return -1;
	lcd.setCursor(lcd_ctx.column, lcd_ctx.line);
	lcd.print(text);
	return 0;
}

int LCD_printLines(const char *textLine1, unsigned int sizeText1, const char *textLine2, unsigned int sizeText2)
{
	if(sizeText1 > LCD_SIZE || sizeText2 > LCD_SIZE)
		return -1;

	lcd.setCursor(0,0);
	lcd.print(textLine1);
	lcd.setCursor(0,1);
	lcd.print(textLine2);

	return 0;
}

int LCD_printCenter(const char *text, unsigned char line)
{

	int len = strlen(text);
	LCD_setLine(line);
	LCD_setColumn(0);
	LCD_print(BLANK, strlen(BLANK));
	int offset = (16 - len) / 2;
	LCD_setColumn(offset);
	LCD_setLine(line);
	LCD_print(text, strlen(text));
	return 0;
}
