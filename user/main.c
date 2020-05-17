#include "main.h"

unsigned char* temp_p;   //用来处理字符
sbit LED = P2^3;


void main() {
	unsigned char key_flag;
	P_SW1 &= ~0xc0;                		//串口设置在p3.3  p3.2
	//P_SW1 = (P_SW1 & ~0xc0) | 0x40	;		//p3.6  p3.7
	
	Delay_us(1);	
	init_uart(); 					//串口初始化
	Timer0Init();					//定时器0初始化做不定长帧的接收
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(16,0,"OLED_TEST_OK",16);
	OLED_DrawBMP(0,2,64,6,BMP2);
	Delay_ms(1000);
	OLED_Clear();			//清屏
				
	
	while(NRF24L01_Check()); // 等待检测到NRF24L01，程序才会向下执行
	NRF24L01_RT_Init();
  

	strcpy(rece_buf,"_2.4ghz_tx_ok");
	rece_buf[0]=strlen(rece_buf)-1;
	SEND_BUF(rece_buf);	       									// 2.4g发送测试
	
	uart_send_str("uart ok");										//串口发送测试						
	

	while(1) {

		//key_flag=Get_key_value(1);
	
		//uart_send_byte(key[0].falling_edge_flag);
		//uart_send_byte(key[0].rising_edge_flag);
		//uart_send_byte(key[0].high_time);
		//uart_send_byte(key[0].low_time);
		
		//uart_send_byte(key_flag);
		
		
	if(frame[uart_frame_id].status==1){    //接收到数据后status=1;

		frame[uart_frame_id].buffer[frame[uart_frame_id].length]='\0';   //这个蓝牙模块发的数据最后一位 不带\0 手动添加\0方便处理
		
		uart_send_str(frame[uart_frame_id].buffer);     					//发送接收到数据
		uart_send_str("\r\n");																		//换行
		
		OLED_Clear();																							//清屏
		
		OLED_ShowString(0,4,"UATR_RX",16);
		OLED_ShowString(0,6,frame[uart_frame_id].buffer,16);			//显示接收到的数据
		
		if(strcmp(frame[uart_frame_id].buffer,"open")==0){				//strcmp函数为c自带的字符串比较函数 相同返回为0 不同根据大小返回-1或0
			LED=0;
		}
		 else if(strcmp(frame[uart_frame_id].buffer,"close")==0){
			LED=1;
		}
		//uart_send_str_len(frame[uart_frame_id].buffer,frame[uart_frame_id].length);	
		
	frame[uart_frame_id].status=0;				//处理完数据后status 清0;
}
	



		if(NRF_IRQ==0)	 											//如果无线模块接收到数据IRQ会清零 				要求高的把这个放中断里去
		{		
			if(NRF24L01_RxPacket(rece_buf)==0)  //将接收到的数据放在
			{																		//第1位以后是收到的命令数据，rece_buf[0]是数据位数长度 硬件设计好的 详细查数据手册
				 
					temp_p=&rece_buf;      											//这里解释一下temp_p是一个指针 指针地址=接收到的值的地址
					temp_p=temp_p+1;														//地址加1
					uart_send_str_len(temp_p,rece_buf[0]),			//这个值就把第一位的   长度数据 给去掉了

					OLED_Clear();																//清屏
					OLED_ShowString(0,0,"2.4GHz_RX:",16);
					OLED_ShowString(0,2,temp_p,16);							//oled显示接收到的数据
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
		
		
		
		
		
//			key_flag=scan_key();  //获取按键值 无按下返回值为0
		

		//如果一共要发送3个字节，rece_buf[0]必须是3！！！！！！
		//rece_buf[0]为本次要发送的字节数
//			switch (key_flag){
//				case 1:
//				strcpy(rece_buf,"_key1_down");
//				rece_buf[0]=strlen(rece_buf)-1;
//				SEND_BUF(rece_buf);	       		// 2.4g发送测试
//				uart_send_str(rece_buf);   //    uart输出
//				break;
//				
//				case 2:
//				strcpy(rece_buf,"_key2_down");
//				rece_buf[0]=strlen(rece_buf)-1;
//				SEND_BUF(rece_buf);	      	 // 2.4g发送测试
//				uart_send_str(rece_buf);   //    uart输出
//				break;
//				
//				case 3:	
//				strcpy(rece_buf,"_key3_down");
//				rece_buf[0]=strlen(rece_buf)-1;
//				SEND_BUF(rece_buf);	       // 2.4g发送测试
//				uart_send_str(rece_buf);   //    uart输出				
//				break;
//				
//				case 4:
//				strcpy(rece_buf,"_key4_down");
//				rece_buf[0]=strlen(rece_buf)-1;
//				SEND_BUF(rece_buf);	       // 2.4g发送测试	
//				uart_send_str(rece_buf);   //    uart输出				
//				break;
//			}
    }
}

