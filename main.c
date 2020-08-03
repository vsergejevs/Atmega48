#define F_CPU 2000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SW3 0b00000001 // left to right
#define SW4 0b00000010 // right to left
#define SW5 0b00000100 // stop

ISR(INT0_vect)
{
  PORTB = 0b00000000; // SW5 LEDs off
}

int main(void)
{
  unsigned char i, j;
  DDRB = 0xFF;        // Set PORTB for output
  PORTB = 0b00000000; // All LEDs are off

  DDRD = 0x00;        // set PORTD for input
  PORTD = 0b00000001; // left to right
  PORTD = 0b00000010; // right to left
  PORTD = 0b00000100; // stop

  EIMSK = 0b00000011; // External Interrupt Mask Register
  EICRA = 0b00001010; // External Interrupt Control Register
  sei();

  while (1)
  {
    if (!(PIND & SW3))
    {
      for (i = 0; i <= 7; i++)
      {
        PORTB = (1 << i); // LEDs blinking left to right
        _delay_ms(200);
      }
    }
    else
    {
      PORTB = 0b00000000; // LEDs off
    }

    if (!(PIND & SW4))
    {
      for (j = 7; j >= 0; j--)
      {
        PORTB = (1 << j); // LEDs blinking right to left
        _delay_ms(200);
      }
    }
    else
    {
      PORTB = 0b00000000; // LEDs off
    }
  }
}
