#include "main.h"
//初始化串口 （设置串口，开启串口中断）
void init_uart(void)    //9600
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0xE0;		//设定定时初值
	TH1 = 0xFE;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
		
	REN = 1;	//允许接收

	EA  = 1;                  	// 打开总中断
	ES  = 1;	                  // 打开串口中断
}       	
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;			//设置定时初值
	TH0 = 0xD4;			//设置定时初值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时

	ET0  = 1;				//开启定时器中断
}
           
// 发送一个字节数据
void uart_send_byte(unsigned char dat)
{
	SBUF = dat; 			// 将数据送到发送缓冲寄存器SBUF，一位一位的发送
	while(!TI);			 	// 等待发送完毕 (发送完毕TI硬件置1)
	TI = 0;						// 将TI清零，表示可以发送下一字节数据。
}

// 发送字符串
void uart_send_str(unsigned char *s)
{
	while(*s != '\0')					//'\0':字符串结束标志
	{
		uart_send_byte(*s);			//发送1个字节数据，1个字符占8位，1字节
		s++;										//指向下一个字符
	}
}

// 发送字符串指定 长度
void uart_send_str_len(unsigned char *s,unsigned char len)
{
	while(len != 0)	
	{
		uart_send_byte(*s);			//发送1个字节数据，1个字符占8位，1字节
		s++;										//指向下一个字符
		len--;
	}
}

//串口中断接收任意长度字节
Frame_Typedef frame[FRAME_QUANTITY];     		//开3个帧缓存
Uart_Frame_Typedef uart1;										//

unsigned char uart_frame_id;


void Uart_Time_Even(void){             					//串口接收用在定时器上的事件 用来判断超时
	
		if(uart1.status !=FREE){
			uart1.time_out++;
			
				if(uart1.time_out>=FRAME_TIMEOUT){
					uart1.status=FREE;
					
							 
			//					if(frame[uart1.frame_id].status==0)    //该帧以处理 空闲 
			//						{
								frame[uart1.frame_id].status=1;  			//当前帧的状态 0以处理 1未处理
			//					}
				        uart_frame_id=uart1.frame_id;
//								uart_buffer_status_p=&frame[uart1.frame_id].status;    // 传出当前接收到的帧数据 的id
//								uart_buffer_p= &frame[uart1.frame_id].buffer ;				 //	传出当前接收到的帧数据状态
					/*
					此处添加帧处理程序
					*/
								//uart_send_str_len(frame[uart1.frame_id].buffer,frame[uart1.frame_id].length);
							 
					uart1.frame_id++;
					if(uart1.frame_id >= FRAME_QUANTITY){
					uart1.frame_id=0;
					}
				}
		}
	}

	
// 定时器1中断interrupt 1
	void timer_interrupt(void)       
{
	 Uart_Time_Even();
	 //TL0 = 0xCD;		//设置定时初值15系列有自动重装模式不用重装初值
	 //TH0 = 0xD4;		//设置定时初值
}
	
	
// 串口中断处理函数 （串口接收到数据，发送数据完毕都可以引起串口中断）也叫串行中断服务程序
//中断统一放interrupt.c里面interrupt 4 
void uart_interrupt(void)  		
{
	if(RI) 																			//接收数据(1字节)完毕，RI会被硬件置1
	{
		RI = 0;            		                   // 将 接收中断标志位 清零(让串口可以继续接收数据)
     if(uart1.status!=BUSY){
				uart1.status=BUSY; 
				frame[uart1.frame_id].length=0;
		 }
			frame[uart1.frame_id].buffer[frame[uart1.frame_id].length]= SBUF;
			frame[uart1.frame_id].length++;
			if(frame[uart1.frame_id].length>=19){
			frame[uart1.frame_id].length=19;
			}
			uart1.time_out=0;
	}
	
	
	if(TI)// 发送数据(1字节)完毕
	{
		TI = 0;// 将 发送中断标志位 清零(让串口可以继续发送数据)
	}
}



//		uart_send_str_len(frame[0].buffer,frame[0].length);
//		uart_send_str("\r\n");
//		uart_send_str_len(frame[1].buffer,frame[1].length);
//		uart_send_str("\r\n");
//		uart_send_str_len(frame[2].buffer,frame[2].length);
//    uart_send_str("\r\n");
