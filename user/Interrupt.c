#include "main.h"

void Uart(void) interrupt 4
{
    uart_interrupt();
}

void Timer_1(void) interrupt 3
{
//uart_rx();
}

void Timer_0 (void) interrupt 1
{
    timer_interrupt();
	
		Edge_detection();
	
		Get_key_status();
		//uart_send_str("uart ok");	
	
	
		
}

void External_1(void) interrupt 2
{
//uart_rx();
}

void External_0(void) interrupt 0
{
//uart_rx();
}