/*
 * LCD.h
 *
 *  Created on: 12 de set de 2019
 *      Author: solid
 */

#ifndef INCLUDE_LCD_H_
#define INCLUDE_LCD_H_

#define LCD_LINE_1	0x80
#define LCD_LINE_2	0xC0

int LCD_init(void);
int LCD_clear(void);
int LCD_setColumn(unsigned char column);
int LCD_setLine(unsigned char line);
int LCD_print(const char *text, unsigned int size);
int LCD_printLines(const char *textLine1, unsigned int sizeText1, const char *textLine2, unsigned int sizeText2);
int LCD_printCenter(const char *text, unsigned char line);


#endif /* INCLUDE_LCD_H_ */

