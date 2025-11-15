#include <avr/io.h>

typedef enum ButtonState_tag
{
    eBtnUndefined = 0,
    eBtnShortKeyPress,
    eBtnDoubleKeyPress,
    eBtnLongKeyPress
} eButtonState_t;

void delay_10ms(void)
{
  volatile uint16_t counter = 3;
  while(counter--)
    ;
}

void delay_1000ms(void)
{
  volatile uint16_t counter_1000 = 100;
  while(counter_1000--)
  {
    delay_10ms();
  }
}
// ===========================================================
eButtonState_t checkButton(void)
{
  eButtonState_t retorno;
  volatile uint8_t counter_check = 0;
  DDRD |= (1<<PD0);

  while(PINB & (1<<PB2))      // No hará nada hasta no se preciona el botón
  {
    ;
    //PORTD |= (1<<PD0);
  }
  delay_10ms();
  
  //PORTD &= ~(1<<PD0);
  PORTD |= (1<<PD0);
  while(!(PINB & (1<<PB2)))   // El botón está siendo precionado
  {
    delay_10ms();

    // if(PINB & (1<<PB2))
    // {
    //   PORTD &= ~(1<<PD0);
    // }
    counter_check++;
  }
  PORTD &= ~(1<<PD0);
  retorno = eBtnShortKeyPress;
  if(counter_check > 100)
  {
    retorno = eBtnLongKeyPress;
  }
  PORTB |= 1<<PB7;
  return retorno;

}
// ===========================================================
int main(void)
{
  DDRA |= (1<<PA7 ) | (1<<PA5) | (1<<PA3) | (1<<PA1);
  PORTA &= ~(1<<PA7) & ~(1<<PA5) & ~(1<<PA3) & ~(1<<PA1);
  DDRC |= (1<<PC6) | (1<<PC4) | (1<<PC2) | (1<<PC5);
  PORTC &= ~(1<<PC6) & ~(1<<PC4) & ~(1<<PC2) & ~(1<<PC5);

  // Configuración del PIN del botón
  DDRB &= ~(7<<PB2);
  PORTB |= (7<<PB2);
  while(1)
  {
    // PORTA &= ~(1<<PA5) & ~(1<<PA1);
    // PORTC &= ~(1<<PC6) & ~(1<<PC2);
    switch(checkButton())
    {
      case eBtnShortKeyPress:
        PORTA |= (1<<PA1);
        break;
      case eBtnDoubleKeyPress:
        PORTA |= (1<<PA5);
        break;
      case eBtnLongKeyPress:
        PORTC |= (1<<PA6);
        break;
      default:
        PORTC |= (1<<PC2);
        break;
    }
    delay_1000ms();
    PORTA &= ~(1<<PA5) & ~(1<<PA1);
    PORTC &= ~(1<<PC6) & ~(1<<PC2);
  }
}
