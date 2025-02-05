#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                      // No Watch Dog Timer
#FUSES NOBROWNOUT                 // No brownout reset
#FUSES NOLVP                      // No low voltage programming
#use delay(crystal=4MHz)

// Define LCD Pin Assignments
#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>

// Water Level Sensor Pin Definitions
#define LOW_SENSOR   PIN_A0       // Low water level sensor
#define HIGH_SENSOR  PIN_A1       // High water level sensor
#define RELAY        PIN_C0       // Relay controlling the pump

void main() {
   // Initialize LCD with the defined pins
   lcd_init();
   
   // Display startup message on the LCD
   lcd_putc("\f");              // Clear the screen
   lcd_putc("Water Level Ctrl"); // Initial message
   delay_ms(2000);              // Wait 2 seconds
   
   // Clear the LCD screen for the main loop display
   lcd_putc("\f");
   
   // Configure input/output pins
   set_tris_a(0xFF); // Set PORTA (RA0 and RA1) as input for sensors
   set_tris_c(0xFE); // Set RC0 as output (relay control)
   set_tris_d(0x00); // Set PORTD as output for LCD
   
   output_low(PIN_C0);  // Initially turn OFF the pump (relay off)

   while(TRUE) {
      // Read the status of the water level sensors
      int low_level = input(LOW_SENSOR);   // Read low water level sensor
      int high_level = input(HIGH_SENSOR); // Read high water level sensor
      
      // Water level control logic
      if (!low_level && !high_level) {
         // If both sensors are dry, water is low, pump ON
         lcd_gotoxy(1, 1);
         lcd_putc("Water: High      ");
         output_high(RELAY);  // Turn ON the pump
         lcd_gotoxy(1, 2);
         lcd_putc("Pump: OFF        ");
      } 
      else if (low_level && !high_level) {
         // If low sensor is wet, but high sensor is dry, water is medium, pump ON
         lcd_gotoxy(1, 1);
         lcd_putc("Water: Medium   ");
         output_low(RELAY);  // Keep the pump ON
         lcd_gotoxy(1, 2);
         lcd_putc("Pump: ON        ");
      } 
      else if (high_level) {
         // If the high sensor is wet, water is high, pump OFF
         lcd_gotoxy(1, 1);
         lcd_putc("Water: Low     ");
         output_low(RELAY);  // Turn OFF the pump
         lcd_gotoxy(1, 2);
         lcd_putc("Pump: ON       ");
      }
      
      delay_ms(500);  // Add a delay for sensor stability
   }
}

