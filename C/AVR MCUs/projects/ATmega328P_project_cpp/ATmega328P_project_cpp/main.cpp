#include "main.h"

unsigned short ms = 0;
short lcon = 0;

ISR(USART_RX_vect)
{
	//char data = UDR0;
	usart_transmit(UDR0);
}

ISR(TIMER0_COMPA_vect)
{
	ms += 8;
	
	encoder_listen();
	
	if (ms == 1000)
	{
		ms = 0;
		char her[16];
		snprintf(her, 16, "%d", con);
		usart_println(her);
	}
}

int main(void)
{
	TCCR0A = (1<<COM0A1) | (1<<WGM01);
	TCCR0B = (1<<CS02) | (1<<CS00);
	TCNT0=0x00;
	OCR0A=0x7C;
	TIMSK0 = (1<<OCIE0A);
	
	sei();
	
	//adc r1;
	usart_init(9600);
	encoder_init(6, 7);
	step_motor_init(2, 3, 4, 5);
	
    //servo s1;
    //step_motor m1((1<<2), (1<<3), (1<<4), (1<<5));
    //_delay_ms(1000);
	
    while (1) 
    {
	    if (con != lcon)
	    {
		    step_motor_rotate(con - lcon);
		    lcon = con;
	    }
		_delay_ms(10);
    }
}