#define MY_DELAY 5000
#define F_CPU 8000000UL
#include <avr/io.h>


int flag = 0;
int e, a, i, b;

int main(void)
{
	DDRD=0b00100000;  //port D configuration
	PORTD=0b00011000;

	//Timer 1 initialization
	TCCR1A=0x81; //(1<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (1<<WGM10);
	TCCR1B=0x03; //(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10);
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;

	TIMSK=0x00;

	while (1)
	{
		if(!(PIND &(1<<PD3)) && (flag == 0) && (OCR1A != 0xFF))
		{
			i = MY_DELAY;      //
			while (i--);
			if(!(PIND &(1<<PD3)))  //checking if the button is really pushed
			{
				OCR1A=OCR1A+0x01;    // increase LED brightness
				i = MY_DELAY;
				while (i--);
				if(OCR1A == 0xFF)
				{
					flag = 1;
				}
			}
			
		}
		if(!(PIND &(1<<PD4)) && (flag == 0) && (OCR1A != 0x00))
		{
			i = MY_DELAY;
			while (i--);
			if(!(PIND &(1<<PD4))) //checking if the button is really pushed
			{
				OCR1A=OCR1A-0x01; //dimming the LED
				i = MY_DELAY;
				while (i--);
				if(OCR1A==0x00)
				{
					flag = 1;
				}
			}
		}
		if((PIND & (1<<PD3)) && (PIND & (1<<PD4)))
		{
			flag = 0;
		}

	}
}