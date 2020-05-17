#ifndef __uart_h
#define __uart_h

//#define UART_BUFFER_LENTH 20
#define FRAME_QUANTITY  3   //帧缓存数量
#define FRAME_TIMEOUT   5   //超时
#define BUSY            1		
#define FREE						0

typedef struct {
unsigned char buffer[20];   //帧数据缓存区
unsigned char status;       //帧数据状态  
unsigned char length; 			//帧长度	
}Frame_Typedef;

typedef struct {
unsigned char  status;	    		//串口接收帧状态  0闲 1忙 
unsigned char  frame_id;	    	//当前处理的帧id
unsigned char  time_out;	    	//超时计数 
}Uart_Frame_Typedef;


extern Frame_Typedef frame[FRAME_QUANTITY];     		//开3个帧缓存
extern Uart_Frame_Typedef uart1;

extern unsigned char uart_frame_id;


void init_uart(void);
void timer_interrupt(void);
void uart_interrupt(void); 

void uart_send_byte(unsigned char dat);
void uart_send_str(unsigned char *s);
//void uart_send_str_len(unsigned char *s,unsigned char pos,unsigned char len);

void uart_send_str_len(unsigned char *s,unsigned char len);

void Timer0Init(void);

void Uart_Time_Even(void);
//void uart_rx();
#endif