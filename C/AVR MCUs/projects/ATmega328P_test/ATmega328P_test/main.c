#define F_CPU 16000000UL

#define D2 1<<2//D
#define D3 1<<3//D
#define D4 1<<4//D
#define D5 1<<5//D
#define D6 1<<6//D
#define D7 1<<7//D
#define D8 1<<0//B
#define D9 1<<1//B
#define D10 1<<2//B
#define D11 1<<3//B
#define D12 1<<4//B
#define D13 1<<5//B
//#define Button 1<<0//C
//#define Speaker 1<<1//C

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int ports[4] = {D10, D11, D12, D13};
unsigned int scale[4] = {1000, 100, 10, 1};
unsigned int ms_var = 0;
unsigned int s_var = 0;
unsigned int m_var = 0;
unsigned int counter = 0;
	
ISR(TIMER0_COMPB_vect)
{
	ms_var += 16;
	if (ms_var >= 1000)
	{
		ms_var = 0;
		s_var++;
		if (s_var == 60)
		{
			s_var = 0;
			m_var++;
			if (m_var == 60)
			{
				m_var = 0;
			}
		}
	}
	
	counter = m_var * 100 + s_var;
	TCNT0 = 0;
}

void Timer_init()
{
	TIMSK0 = (1<<OCIE0B);
	OCR1B = 250;
	TCCR0B = (1<<CS12) | (1<<CS10) | (1<<WGM02);
	TCCR0B &= ~(1<<CS11);
	TCNT0 = 0;
	sei();
}

void Port_init()
{
	DDRD = (D2) | (D3) | (D4) | (D5) | (D6) | (D7);
	DDRB = (D8) | (D9) | (D10) | (D11) | (D12) | (D13);
	
	PORTB = (D10) | (D11) | (D12) | (D13);
	PORTD = 0x00;
}

void Show_num(unsigned int num)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		PORTB = (D10) | (D11) | (D12) | (D13);
		if (i == 1)
		{
			PORTB |= (D9);
		}
		
		switch (num / scale[i])
		{
			case 0:
			PORTD = (D2) | (D3) | (D4) | (D5) | (D6) | (D7);
			
			PORTB &= ~(ports[i]);
			num -= 0 * scale[i];
			_delay_ms(1);
			break;
			
			case 1:
			PORTD = (D3) | (D4);
			
			PORTB &= ~(ports[i]);
			num -= 1 * scale[i];
			_delay_ms(1);
			break;
			
			case 2:
			PORTD = (D2) | (D3) | (D5) | (D6);
			PORTB |= (D8);
			
			PORTB &= ~(ports[i]);
			num -= 2 * scale[i];
			_delay_ms(1);
			break;
			
			case 3:
			PORTD = (D2) | (D3) | (D4) | (D5);
			PORTB |= (D8);
			
			PORTB &= ~(ports[i]);
			num -= 3 * scale[i];
			_delay_ms(1);
			break;
			
			case 4:
			PORTD = (D3) | (D4) | (D7);
			PORTB |= (D8);
			
			PORTB &= ~(ports[i]);
			num -= 4 * scale[i];
			_delay_ms(1);
			break;
			
			case 5:
			PORTD = (D2) | (D4) | (D5) | (D7);
			PORTB |= (D8);
			
			PORTB &= ~(ports[i]);
			num -= 5 * scale[i];
			_delay_ms(1);
			break;
			
			case 6:
			PORTD = (D2) | (D4) | (D5) | (D6) | (D7);
			PORTB |= (D8);
			
			PORTB &= ~(ports[i]);
			num -= 6 * scale[i];
			_delay_ms(1);
			break;
			
			case 7:
			PORTD = (D2) | (D3) | (D4);
			
			PORTB &= ~(ports[i]);
			num -= 7 * scale[i];
			_delay_ms(1);
			break;
			
			case 8:
			PORTD = (D2) | (D3) | (D4) | (D5) | (D6) | (D7);
			PORTB |= (D8);
			
			PORTB &= ~(ports[i]);
			num -= 8 * scale[i];
			_delay_ms(1);
			break;
			
			case 9:
			PORTD = (D2) | (D3) | (D4) | (D5) | (D7);
			PORTB |= (D8);
			
			PORTB &= ~(ports[i]);
			num -= 9 * scale[i];
			_delay_ms(1);
			break;
			
			default:
			PORTD = (D2) | (D3) | (D4) | (D5) | (D6) | (D7);
			
			PORTB &= ~(ports[i]);
			num -= 0 * scale[i];
			_delay_ms(1);
			break;
		}
	}
}

int main(void)
{
	Timer_init();
	Port_init();
	
    while (1) 
    {	
		Show_num(counter);
    }
}

