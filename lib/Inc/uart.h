#ifndef __uart_h
#define __uart_h

//#define UART_BUFFER_LENTH 20
#define FRAME_QUANTITY  3   //֡��������
#define FRAME_TIMEOUT   5   //��ʱ
#define BUSY            1		
#define FREE						0

typedef struct {
unsigned char buffer[20];   //֡���ݻ�����
unsigned char status;       //֡����״̬  
unsigned char length; 			//֡����	
}Frame_Typedef;

typedef struct {
unsigned char  status;	    		//���ڽ���֡״̬  0�� 1æ 
unsigned char  frame_id;	    	//��ǰ�����֡id
unsigned char  time_out;	    	//��ʱ���� 
}Uart_Frame_Typedef;


extern Frame_Typedef frame[FRAME_QUANTITY];     		//��3��֡����
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