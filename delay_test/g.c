#include <avr/io.h>

int main(void)
{
	DDRG |= (1 << PG5);
	TCCR0A	= (2 << COM0B0) | (3 << WGM00);
	TCCR0B = (4 << CS00) | (1 << WGM02);
	OCR0A = 142 - 1;
	OCR0B = (OCR0A >> 1);
	
	while(1)
		;
}
