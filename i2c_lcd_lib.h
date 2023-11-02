
#ifndef __I2C_LCD_LIB_H
#define __I2C_LCD_LIB_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define Address_PCF    0x27

#define P0  0b00000001  //1
#define P1  0b00000010  //2
#define P2  0b00000100  //4
#define P3  0b00001000  //8
#define P4  0b00010000  //16
#define P5  0b00100000  //32
#define P6  0b01000000  //64
#define P7  0b10000000  //128

// conexiones y utilidades de PCF

#define LED_LCD        P3
#define LCD_RS         P0
#define LCD_RW         P1
#define LCD_E          P2
#define LCD_D4         P4
#define LCD_D5         P5
#define LCD_D6         P6
#define LCD_D7         P7

/********************************************************/
#define      _I2C_FIRST_ROW           128
#define      _I2C_SECOND_ROW          192
#define      _I2C_THIRD_ROW           148
#define      _I2C_FOURTH_ROW          212
#define      _I2C_CLEAR               1
#define      _I2C_RETURN_HOME         2
#define      _I2C_CURSOR_OFF          12
#define      _I2C_UNDERLINE_ON        14
#define      _I2C_BLINK_CURSOR_ON     15
#define      _I2C_MOVE_CURSOR_LEFT    16
#define      _I2C_MOVE_CURSOR_RIGHT   20
#define      _I2C_TURN_OFF            0
#define      _I2C_TURN_ON             8
#define      _I2C_SHIFT_LEFT          24
#define      _I2C_SHIFT_RIGHT         28

void Write_PCF(uint8_t dat);
void Data_LCD(uint8_t ctrl,uint8_t cmd);
void Plot_LCD(uint8_t ctrl,uint8_t cmd);
void I2C_LCD_Init(void);
void I2C_LCD_Chr_Cp(uint8_t letra);
void I2C_LCD_Cmd(uint8_t cmd);
void I2C_LCD_XY(uint8_t y, uint8_t x);
void I2C_LCD_Chr(uint8_t y, uint8_t x, uint8_t letra);
void I2C_LCD_Out_Cp(uint8_t *text);
void I2C_LCD_Out(uint8_t y, uint8_t x, uint8_t *text);

#ifdef __cplusplus
}
#endif

#endif /*__I2C_LCD_LIB*/
