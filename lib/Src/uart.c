#include "main.h"
//��ʼ������ �����ô��ڣ����������жϣ�
void init_uart(void)    //9600
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xE0;		//�趨��ʱ��ֵ
	TH1 = 0xFE;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
		
	REN = 1;	//�������

	EA  = 1;                  	// �����ж�
	ES  = 1;	                  // �򿪴����ж�
}       	
void Timer0Init(void)		//1����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xCD;			//���ö�ʱ��ֵ
	TH0 = 0xD4;			//���ö�ʱ��ֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ

	ET0  = 1;				//������ʱ���ж�
}
           
// ����һ���ֽ�����
void uart_send_byte(unsigned char dat)
{
	SBUF = dat; 			// �������͵����ͻ���Ĵ���SBUF��һλһλ�ķ���
	while(!TI);			 	// �ȴ�������� (�������TIӲ����1)
	TI = 0;						// ��TI���㣬��ʾ���Է�����һ�ֽ����ݡ�
}

// �����ַ���
void uart_send_str(unsigned char *s)
{
	while(*s != '\0')					//'\0':�ַ���������־
	{
		uart_send_byte(*s);			//����1���ֽ����ݣ�1���ַ�ռ8λ��1�ֽ�
		s++;										//ָ����һ���ַ�
	}
}

// �����ַ���ָ�� ����
void uart_send_str_len(unsigned char *s,unsigned char len)
{
	while(len != 0)	
	{
		uart_send_byte(*s);			//����1���ֽ����ݣ�1���ַ�ռ8λ��1�ֽ�
		s++;										//ָ����һ���ַ�
		len--;
	}
}

//�����жϽ������ⳤ���ֽ�
Frame_Typedef frame[FRAME_QUANTITY];     		//��3��֡����
Uart_Frame_Typedef uart1;										//

unsigned char uart_frame_id;


void Uart_Time_Even(void){             					//���ڽ������ڶ�ʱ���ϵ��¼� �����жϳ�ʱ
	
		if(uart1.status !=FREE){
			uart1.time_out++;
			
				if(uart1.time_out>=FRAME_TIMEOUT){
					uart1.status=FREE;
					
							 
			//					if(frame[uart1.frame_id].status==0)    //��֡�Դ��� ���� 
			//						{
								frame[uart1.frame_id].status=1;  			//��ǰ֡��״̬ 0�Դ��� 1δ����
			//					}
				        uart_frame_id=uart1.frame_id;
//								uart_buffer_status_p=&frame[uart1.frame_id].status;    // ������ǰ���յ���֡���� ��id
//								uart_buffer_p= &frame[uart1.frame_id].buffer ;				 //	������ǰ���յ���֡����״̬
					/*
					�˴����֡�������
					*/
								//uart_send_str_len(frame[uart1.frame_id].buffer,frame[uart1.frame_id].length);
							 
					uart1.frame_id++;
					if(uart1.frame_id >= FRAME_QUANTITY){
					uart1.frame_id=0;
					}
				}
		}
	}

	
// ��ʱ��1�ж�interrupt 1
	void timer_interrupt(void)       
{
	 Uart_Time_Even();
	 //TL0 = 0xCD;		//���ö�ʱ��ֵ15ϵ�����Զ���װģʽ������װ��ֵ
	 //TH0 = 0xD4;		//���ö�ʱ��ֵ
}
	
	
// �����жϴ����� �����ڽ��յ����ݣ�����������϶��������𴮿��жϣ�Ҳ�д����жϷ������
//�ж�ͳһ��interrupt.c����interrupt 4 
void uart_interrupt(void)  		
{
	if(RI) 																			//��������(1�ֽ�)��ϣ�RI�ᱻӲ����1
	{
		RI = 0;            		                   // �� �����жϱ�־λ ����(�ô��ڿ��Լ�����������)
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
	
	
	if(TI)// ��������(1�ֽ�)���
	{
		TI = 0;// �� �����жϱ�־λ ����(�ô��ڿ��Լ�����������)
	}
}



//		uart_send_str_len(frame[0].buffer,frame[0].length);
//		uart_send_str("\r\n");
//		uart_send_str_len(frame[1].buffer,frame[1].length);
//		uart_send_str("\r\n");
//		uart_send_str_len(frame[2].buffer,frame[2].length);
//    uart_send_str("\r\n");
