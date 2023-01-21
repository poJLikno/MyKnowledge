#include "main.h"

ISR(USART_RX_vect)
{
	//OCR1A = (int)UDR0;
}

int main(void)
{
	step_motor_init((1<<2), (1<<3), (1<<4), (1<<5));
	//usart_init(207);
	/*pwm_init();
	adc_init();
	pwm_change(0);
	_delay_ms(1000);
	pwm_change(180);
	_delay_ms(1000);*/
	
    while (1) 
    {
		/*char per[5];
		snprintf(per, 5, "%d", adc_read());
		usart_println(per);
		pwm_change(round((float)adc_read() / 5.683333333333333));
		_delay_ms(50);*/
		
		step_motor_rotate(90);
		_delay_ms(1000);
		step_motor_rotate(-90);
		_delay_ms(1000);
		step_motor_rotate(180);
		_delay_ms(1000);
    }
}

