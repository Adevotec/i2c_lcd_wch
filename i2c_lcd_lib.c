/*
 * i2c_lcd_lib.c
 *
 *  Created on: Jul 3, 2023
 *      Author: Delta
 */
#include "i2c_lcd_lib.h"
#include "ch32v00x_i2c.h"

void Write_PCF(uint8_t dat)
{
    I2C_GenerateSTART( I2C1, ENABLE );
    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT ) );
    I2C_SendData(I2C1, Address_PCF << 1);
    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );
    I2C_SendData( I2C1, dat);
    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) );
    I2C_GenerateSTOP( I2C1, ENABLE );
}

void Data_LCD(uint8_t ctrl, uint8_t cmd)
{
    uint8_t datos = 0;
    if((cmd & 0X01)== 1 ) datos = datos|LCD_D4; else datos = datos & ~LCD_D4;
    if((cmd & 0X02)== 2 ) datos = datos|LCD_D5; else datos = datos & ~LCD_D5;
    if((cmd & 0X04)== 4 ) datos = datos|LCD_D6; else datos = datos & ~LCD_D6;
    if((cmd & 0X08)== 8 ) datos = datos|LCD_D7; else datos = datos & ~LCD_D7;

    Delay_Us(100);

    if(ctrl == 1)
        datos = datos | LCD_RS;
    else
        datos = datos & ~LCD_RS;

    Write_PCF((datos | LCD_E) | LED_LCD);
    Delay_Ms(2);
    Write_PCF((datos & ~LCD_E) | LED_LCD);
}

void Plot_LCD(uint8_t ctrl, uint8_t cmd)
{
    Data_LCD(ctrl,cmd >> 4);
    Data_LCD(ctrl,cmd & 0x0F);
}


void I2C_LCD_Init(void)
{
    const uint8_t lcd_FuntionSet[5] = {0x28,0x08,0x01,0x06,0x0C};
    Write_PCF(0x00);
    Delay_Ms(15);
    for(uint8_t i = 0; i < 3; i++){
        Data_LCD(0,0x03);
        Delay_Ms(5);
    }
    Data_LCD(0,0x02);
    for(uint8_t i = 0; i < 5; i++)
    {
        Plot_LCD(0, lcd_FuntionSet[i]);
        Delay_Ms(5);
    }
}

void I2C_LCD_Chr_Cp(uint8_t letra)
{
    Plot_LCD(1,letra);
    Delay_Us(10);
}

void I2C_LCD_Cmd(uint8_t cmd)
{
    Plot_LCD(0,cmd);
    Delay_Us(10);
}

void I2C_LCD_XY(uint8_t y, uint8_t x)
{
    switch(y)
    {
        case 1: I2C_LCD_Cmd(0x80 + (x-1));  break;
        case 2: I2C_LCD_Cmd(0xC0 + (x-1)); break;
        case 3: I2C_LCD_Cmd(0x94 + (x-1)); break;
        case 4: I2C_LCD_Cmd(0xD4 + (x-1)); break;
    }
    Delay_Us(100);
    return;
}

void I2C_LCD_Chr(uint8_t y, uint8_t x, uint8_t letra)
{
    I2C_LCD_XY(y,x);
    Plot_LCD(1,letra);
}

void I2C_LCD_Out_Cp(uint8_t *text)
{
    while(*text)
    {
        I2C_LCD_Chr_Cp(*text);
        text++;
    }
    return;
}

void I2C_LCD_Out(uint8_t y, uint8_t x, uint8_t *text)
{
    I2C_LCD_XY(y,x);
    while(*text)
    {
        I2C_LCD_Chr_Cp(*text);
        text++;
    }
}


