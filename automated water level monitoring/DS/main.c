#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)
#use i2c(Master,Fast,sda=PIN_C4,scl=PIN_C3)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>

int sec=0x00,min=0x15,hr=0x50,hr,am_pm;
byte read(byte add)
{
     int data;
     i2c_start();
     i2c_write(0xD0);
     i2c_write(add);
     i2c_stop();
     i2c_start();
     i2c_write(0xD1);
     data=i2c_read(0);
     i2c_stop();
     return data;
}
void write()
void main()
{

   lcd_init();

   while(TRUE)
   {
      
   }

}
