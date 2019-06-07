/* ========================================================================== */
/*		Exp15_3.c : 119 Ambulance Sound			              */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2010.  */

#include <avr/io.h>
#include "OK-128LCD.h"

int main(void)
{
  unsigned char i, glitch;

  MCU_initialize();                             // initialize MCU and kit
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module

  LCD_string(0x80,"   * SOUND *    ");          // display title
  LCD_string(0xC0," 119 Ambulance  ");

  TCCR1A = 0x40;                                // CTC mode(12), use OC1A
  TCCR1B = 0x1A;                                // f(OC1A) = 16MHz/8/2/(1+N)
  TCCR1C = 0x00;
  TCNT1 = 0x0000;                               // clear Timer/Counter1

  while(1)
    { for(i = 0; i < 5; i++)
        { TCCR1B = 0x1A;                        // speaker on
          do{ glitch = TCNT1L;                  // protect glitch
              glitch = TCNT1H;
             } while(glitch >= (2082 >> 8));
          ICR1 = 2082;                          // 480 Hz
          Delay_ms(500);                        // delay for 500 ms

          do{ glitch = TCNT1L;                  // protect glitch
              glitch = TCNT1H;
             } while(glitch >= (2777 >> 8));
          ICR1 = 2777;                          // 360 Hz
          Delay_ms(500);                        // delay for 500 ms
        }

      TCCR1B = 0x18;                            // speaker off
      Delay_ms(1000);                           // delay for 1 sec
    }
}

