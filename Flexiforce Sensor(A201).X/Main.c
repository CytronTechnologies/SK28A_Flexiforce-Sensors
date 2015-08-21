/* 
 * File:   Main.c
 * Author: Hatake_Chin
 *
 * Created on August 9, 2012, 6:01 PM
 */

//Include the header file
#include <htc.h>
#include "adc.h"
#include "system.h"
#include "lcd.h"

/*******************************************************************************
* DEVICE CONFIGURATION WORDS                                                   *
*******************************************************************************/
__CONFIG(0x3F32);

/*******************************************************************************
* PRIVATE FUNCTION PROTOTYPES                                                  *
*******************************************************************************/
void initialize(void);
void LED_Blinking(unsigned int k);

void main(void)
{
    unsigned int total;
    unsigned int i;
    unsigned int voltage;

    TRISA0 = 1;
    TRISB = 0b00000001;
    TRISC =  0x00;
    initialize();

    LCD_putstr(" Voltage:");
    adc_on();
    __delay_ms(1);

    while(1)
    {
	total = 0;	                           //clear the ADC result
	for (i = 0; i<10; i++)
	{
            total = (total + ui_adc_read());	   // accumulate the adc reading
	}
            total = total/10;                      // obtain average value(10x)
            voltage =(float)(total *(5.0/1024)*1000); // value in decimal
            LED_Blinking(voltage);

            unsigned char value_[4] = {0};
            unsigned char remainder = 0;
            for(unsigned int j = 0; j < 4; j++)    // A loop where to store each
            {                                      // digit in separate array
                remainder = voltage%10;
                voltage =  voltage/10;
                value_[j] = remainder + 0x30;      // ASCII value
            }

            LCD_goto(0,0x40);	                   //goto 2nd line
            LCD_putchar(value_[3]);
            LCD_putchar('.');
            LCD_putchar(value_[2]);
            LCD_putchar(value_[1]);

    }
	adc_off();
 }

void initialize(void)
{
    adc_initialize();
    __delay_ms(10);
    LCD_initialize();
    LCD_clear();
}

void LED_Blinking(unsigned int k)
{
    if(k >= 1000 && k < 2000)
    {
        LED1 = 1;
    }
    else if (k >= 2000 && k < 3000)
    {
        LED1 = 1;
        LED2 = 1;
    }
    else if(k >= 3000 && k< 4000)
    {
        LED1 = 1;
        LED2 = 1;
        LED3 = 1;
    }
    else if(k >= 4000 && k < 4800)
    {
        LED1 = 1;
        LED2 = 1;
        LED3 = 1;
        LED4 = 1;
    }
    else if (k >= 4800)
    {
        LED1 ^= 1;
        __delay_ms(70);
        LED2 ^= 1;
        __delay_ms(70);
        LED3 ^= 1;
        __delay_ms(70);
        LED4 ^= 1;
        __delay_ms(70);
    }
    else
    {
        LED1 = 0;
        LED2 = 0;
        LED3 = 0;
        LED4 = 0;
    }
}