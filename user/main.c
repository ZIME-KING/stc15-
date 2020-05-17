#include "main.h"

unsigned char* temp_p;   //���������ַ�
sbit LED = P2^3;


void main() {
	unsigned char key_flag;
	P_SW1 &= ~0xc0;                		//����������p3.3  p3.2
	//P_SW1 = (P_SW1 & ~0xc0) | 0x40	;		//p3.6  p3.7
	
	Delay_us(1);	
	init_uart(); 					//���ڳ�ʼ��
	Timer0Init();					//��ʱ��0��ʼ����������֡�Ľ���
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(16,0,"OLED_TEST_OK",16);
	OLED_DrawBMP(0,2,64,6,BMP2);
	Delay_ms(1000);
	OLED_Clear();			//����
				
	
	while(NRF24L01_Check()); // �ȴ���⵽NRF24L01������Ż�����ִ��
	NRF24L01_RT_Init();
  

	strcpy(rece_buf,"_2.4ghz_tx_ok");
	rece_buf[0]=strlen(rece_buf)-1;
	SEND_BUF(rece_buf);	       									// 2.4g���Ͳ���
	
	uart_send_str("uart ok");										//���ڷ��Ͳ���						
	

	while(1) {

		//key_flag=Get_key_value(1);
	
		//uart_send_byte(key[0].falling_edge_flag);
		//uart_send_byte(key[0].rising_edge_flag);
		//uart_send_byte(key[0].high_time);
		//uart_send_byte(key[0].low_time);
		
		//uart_send_byte(key_flag);
		
		
	if(frame[uart_frame_id].status==1){    //���յ����ݺ�status=1;

		frame[uart_frame_id].buffer[frame[uart_frame_id].length]='\0';   //�������ģ�鷢���������һλ ����\0 �ֶ����\0���㴦��
		
		uart_send_str(frame[uart_frame_id].buffer);     					//���ͽ��յ�����
		uart_send_str("\r\n");																		//����
		
		OLED_Clear();																							//����
		
		OLED_ShowString(0,4,"UATR_RX",16);
		OLED_ShowString(0,6,frame[uart_frame_id].buffer,16);			//��ʾ���յ�������
		
		if(strcmp(frame[uart_frame_id].buffer,"open")==0){				//strcmp����Ϊc�Դ����ַ����ȽϺ��� ��ͬ����Ϊ0 ��ͬ���ݴ�С����-1��0
			LED=0;
		}
		 else if(strcmp(frame[uart_frame_id].buffer,"close")==0){
			LED=1;
		}
		//uart_send_str_len(frame[uart_frame_id].buffer,frame[uart_frame_id].length);	
		
	frame[uart_frame_id].status=0;				//���������ݺ�status ��0;
}
	



		if(NRF_IRQ==0)	 											//�������ģ����յ�����IRQ������ 				Ҫ��ߵİ�������ж���ȥ
		{		
			if(NRF24L01_RxPacket(rece_buf)==0)  //�����յ������ݷ���
			{																		//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������ Ӳ����ƺõ� ��ϸ�������ֲ�
				 
					temp_p=&rece_buf;      											//�������һ��temp_p��һ��ָ�� ָ���ַ=���յ���ֵ�ĵ�ַ
					temp_p=temp_p+1;														//��ַ��1
					uart_send_str_len(temp_p,rece_buf[0]),			//���ֵ�Ͱѵ�һλ��   �������� ��ȥ����

					OLED_Clear();																//����
					OLED_ShowString(0,0,"2.4GHz_RX:",16);
					OLED_ShowString(0,2,temp_p,16);							//oled��ʾ���յ�������
			}
		}

		if(key[0].status==1){
			OLED_ShowString(0,0,"key0_s",16);
			key[0].status=0;
		}
		else if(key[0].status==2){
			OLED_ShowString(0,0,"key0_l",16);
			key[0].status=0;
		}
		
		
		if(key[1].status==1){
			OLED_ShowString(0,0,"key1_s",16);
			key[1].status=0;
		}
		else if(key[1].status==2){
			OLED_ShowString(0,0,"key1_l",16);
			key[1].status=0;
		}
		
		if(key[2].status==1){
			OLED_ShowString(0,0,"key2_s",16);
			key[2].status=0;
		}
		else if(key[2].status==2){
			OLED_ShowString(0,0,"key2_l",16);
			key[2].status=0;
		}
		
		
		if(key[3].status==1){
			OLED_ShowString(0,0,"key3_s",16);
			key[3].status=0;
		}
		else if(key[3].status==2){
			OLED_ShowString(0,0,"key3_l",16);
			key[3].status=0;
		}
		
		
		
		
		
//			key_flag=scan_key();  //��ȡ����ֵ �ް��·���ֵΪ0
		

		//���һ��Ҫ����3���ֽڣ�rece_buf[0]������3������������
		//rece_buf[0]Ϊ����Ҫ���͵��ֽ���
//			switch (key_flag){
//				case 1:
//				strcpy(rece_buf,"_key1_down");
//				rece_buf[0]=strlen(rece_buf)-1;
//				SEND_BUF(rece_buf);	       		// 2.4g���Ͳ���
//				uart_send_str(rece_buf);   //    uart���
//				break;
//				
//				case 2:
//				strcpy(rece_buf,"_key2_down");
//				rece_buf[0]=strlen(rece_buf)-1;
//				SEND_BUF(rece_buf);	      	 // 2.4g���Ͳ���
//				uart_send_str(rece_buf);   //    uart���
//				break;
//				
//				case 3:	
//				strcpy(rece_buf,"_key3_down");
//				rece_buf[0]=strlen(rece_buf)-1;
//				SEND_BUF(rece_buf);	       // 2.4g���Ͳ���
//				uart_send_str(rece_buf);   //    uart���				
//				break;
//				
//				case 4:
//				strcpy(rece_buf,"_key4_down");
//				rece_buf[0]=strlen(rece_buf)-1;
//				SEND_BUF(rece_buf);	       // 2.4g���Ͳ���	
//				uart_send_str(rece_buf);   //    uart���				
//				break;
//			}
    }
}

