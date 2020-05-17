/**********************************************************/
/* ��   �ƣ�NRF24L01+����USBͨ��ģ�����                  */
/* ��   �ܣ����ͽ��ղ��Գ���                              */
/*          ��ʽ����λ�Ǹ����������Ҫ���͵�����          */ 
/*                ���磺����5���ֽ� 11 22 33 44 55(16����)*/
/*                ���Դ��ڷ��ͣ�1122334455                */
/*                ģ��ʵ�ʷ��ͣ�051122334455              */     
/* ���ߣ�BQDZ     ����̳��http://bqdz.taobao.com��        */
/* ��ϵ��ʽ�� QQ :851968194     ������������2864          */
/*           �ֻ���15821472722���Ϻ���                    */
/**********************************************************/

#include  "main.h"


unsigned char rece_buf[32];
const uchar TX_ADDRESS[TX_ADR_WIDTH]=ADDRESS_TX; //���͵�ַ
const uchar RX_ADDRESS[RX_ADR_WIDTH]=ADDRESS_RX; //���յ�ַ


//io��ģ��spiд��ʱ��ͬʱ��
/*******************************************************************/
uchar SPI_RW(uchar byte)
{
	uchar bit_ctr;
	for(bit_ctr=0;bit_ctr<8;bit_ctr++)  // ���8λ
	{
		NRF_MOSI=(byte&0x80); 			// MSB TO MOSI
		byte=(byte<<1);							// shift next bit to MSB
		NRF_SCK=1;
		byte|=NRF_MISO;	        		// capture current MISO bit
		NRF_SCK=0;
	}
	return byte;
}

/*********************************************/
/* �������ܣ���24L01�ļĴ���дֵ��һ���ֽڣ� */
/* ��ڲ�����reg   Ҫд�ļĴ�����ַ          */
/*           value ���Ĵ���д��ֵ            */
/* ���ڲ�����status ״ֵ̬                   */
/*********************************************/
uchar NRF24L01_Write_Reg(uchar reg,uchar value)
{
	uchar status;

	NRF_CSN=0;                  //CSN=0;   
  	status = SPI_RW(reg);		//���ͼĴ�����ַ,����ȡ״ֵ̬
	SPI_RW(value);
	NRF_CSN=1;                  //CSN=1;

	return status;
}
/*************************************************/
/* �������ܣ���24L01�ļĴ���ֵ ��һ���ֽڣ�      */
/* ��ڲ�����reg  Ҫ���ļĴ�����ַ               */
/* ���ڲ�����value �����Ĵ�����ֵ                */
/*************************************************/
uchar NRF24L01_Read_Reg(uchar reg)
{
 	uchar value;

	NRF_CSN=0;              //CSN=0;   
  	SPI_RW(reg);			//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
	value = SPI_RW(NOP);
	NRF_CSN=1;             	//CSN=1;

	return value;
}
/*********************************************/
/* �������ܣ���24L01�ļĴ���ֵ������ֽڣ�   */
/* ��ڲ�����reg   �Ĵ�����ַ                */
/*           *pBuf �����Ĵ���ֵ�Ĵ������    */
/*           len   �����ֽڳ���              */
/* ���ڲ�����status ״ֵ̬                   */
/*********************************************/
uchar NRF24L01_Read_Buf(uchar reg,uchar *pBuf,uchar len)
{
	uchar status,u8_ctr;
	NRF_CSN=0;                   	//CSN=0       
  	status=SPI_RW(reg);				//���ͼĴ�����ַ,����ȡ״ֵ̬   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)
	pBuf[u8_ctr]=SPI_RW(0XFF);		//��������
	NRF_CSN=1;                 		//CSN=1
  	return status;        			//���ض�����״ֵ̬
}
/**********************************************/
/* �������ܣ���24L01�ļĴ���дֵ������ֽڣ�  */
/* ��ڲ�����reg  Ҫд�ļĴ�����ַ            */
/*           *pBuf ֵ�Ĵ������               */
/*           len   �����ֽڳ���               */
/**********************************************/
uchar NRF24L01_Write_Buf(uchar reg, uchar *pBuf, uchar len)
{
	uchar status,u8_ctr;
	NRF_CSN=0;
  	status = SPI_RW(reg);			//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)
	SPI_RW(*pBuf++); 				//д������
	NRF_CSN=1;
  	return status;          		//���ض�����״ֵ̬
}							  					   

/*********************************************/
/* �������ܣ�24L01��������                   */
/* ��ڲ�����rxbuf ������������              */
/* ����ֵ�� 0   �ɹ��յ�����                 */
/*          1   û���յ�����                 */
/*********************************************/
uchar NRF24L01_RxPacket(uchar *rxbuf)
{
	uchar state;
	 
	state=NRF24L01_Read_Reg(STATUS);  					//��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(WRITE_REG+STATUS,state); //���TX_DS��MAX_RT�жϱ�־
	if(state&RX_OK)															//���յ�����
	{
		NRF_CE = 0;
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);					//���RX FIFO�Ĵ���
		NRF_CE = 1;
		Delay_150us(); 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}
/**********************************************/
/* �������ܣ�����24L01Ϊ����ģʽ              */
/* ��ڲ�����txbuf  ������������              */
/* ����ֵ�� 0x10    �ﵽ����ط�����������ʧ��*/
/*          0x20    �ɹ��������              */
/*          0xff    ����ʧ��                  */
/**********************************************/
uchar NRF24L01_TxPacket(uchar *txbuf)
{
	uchar state;
   
	NRF_CE=0;																								//CE���ͣ�ʹ��24L01����
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);	//д���ݵ�TX BUF  32���ֽ�
 	NRF_CE=1;																								//CE�øߣ�ʹ�ܷ���	   
	while(NRF_IRQ==1);																			//�ȴ��������
	state=NRF24L01_Read_Reg(STATUS);  											//��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(WRITE_REG+STATUS,state); 						//���TX_DS��MAX_RT�жϱ�־
	if(state&MAX_TX)																				//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);										//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(state&TX_OK)											//�������
	{
		return TX_OK;
	}
	return 0xff;											//����ʧ��
}

/********************************************/
/* �������ܣ����24L01�Ƿ����              */
/* ����ֵ��  0  ����                        */
/*           1  ������                      */
/********************************************/ 	  
uchar NRF24L01_Check(void)
{
	uchar check_in_buf[5]={0x11,0x22,0x33,0x44,0x55};
	uchar check_out_buf[5]={0x00};

	NRF_SCK=0;
	NRF_CSN=1;    
	NRF_CE=0;

	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR, check_in_buf, 5);

	NRF24L01_Read_Buf(READ_REG+TX_ADDR, check_out_buf, 5);

	if((check_out_buf[0] == 0x11)&&\
	   (check_out_buf[1] == 0x22)&&\
	   (check_out_buf[2] == 0x33)&&\
	   (check_out_buf[3] == 0x44)&&\
	   (check_out_buf[4] == 0x55))return 0;
	else return 1;
}			


void NRF24L01_RT_Init(void)
{	
		NRF_CE=0;		  
  	NRF24L01_Write_Reg(WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��
		NRF24L01_Write_Reg(FLUSH_RX,0xff);									//���RX FIFO�Ĵ���    
  	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR,(uchar*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
  	NRF24L01_Write_Buf(WRITE_REG+RX_ADDR_P0,(uchar*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  
  	NRF24L01_Write_Reg(WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
  	NRF24L01_Write_Reg(WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
  	NRF24L01_Write_Reg(WRITE_REG+RF_CH,0);        //����RFͨ��Ϊ2.400GHz  Ƶ��=2.4+0GHz
  	NRF24L01_Write_Reg(WRITE_REG+RF_SETUP,0x0F);  //����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(WRITE_REG+CONFIG,0x0f);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
		NRF_CE=1;									  //CE�øߣ�ʹ�ܷ���
}

void SEND_BUF(uchar *buf)
{
	NRF_CE=0;
	NRF24L01_Write_Reg(WRITE_REG+CONFIG,0x0e);
	NRF_CE=1;
	Delay_us(15);
	NRF24L01_TxPacket(buf);
	NRF_CE=0;
	NRF24L01_Write_Reg(WRITE_REG+CONFIG, 0x0f);
	NRF_CE=1;	
}
//void main()
//{
//	buzzer=1;
//	while(NRF24L01_Check()); // �ȴ���⵽NRF24L01������Ż�����ִ��
//	NRF24L01_RT_Init();
//	
//			rece_buf[1]='1';
//			rece_buf[2]='2';
//			rece_buf[3]='3';
//			rece_buf[0]=3;	  					//һ��Ҫ����3���ֽڣ�rece_buf[0]������3������������
//			SEND_BUF(rece_buf);
//	
//	
//	
//	
//	P3=0XFF;
//	
//	while(1)
//	{
//		if(NRF_IRQ==0)	 	// �������ģ����յ�����
//		{		
//			if(NRF24L01_RxPacket(rece_buf)==0)
//			{			   
//				if(	rece_buf[1]=='1')		   	//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
//					LED=0;
//				if(	rece_buf[1]=='2')	 		//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
//					LED=1;		
//			}
//		}
//		if(S1==0)								//����S1����ASCII�� ��123��
//		{
//			rece_buf[1]='1';
//			rece_buf[2]='2';
//			rece_buf[3]='3';
//			rece_buf[0]=3;	  					//һ��Ҫ����3���ֽڣ�rece_buf[0]������3������������
//			SEND_BUF(rece_buf);
//			while(!S1);	
//		}
//		if(S2==0)								//����S1����ASCII�� ��ABCD��
//		{
//			rece_buf[1]='A';
//			rece_buf[2]='B';
//			rece_buf[3]='C';
//			rece_buf[4]='D';
//			rece_buf[0]=4;	   					//һ��Ҫ����4���ֽڣ�rece_buf[0]������4������������
//			SEND_BUF(rece_buf);
//			while(!S2);	
//		}
//		if(0)			  					//���� ���Ϻ���Ƕ���ӡ�
//		{
//			rece_buf[1]=0xc9;					//��
//			rece_buf[2]=0xcf;					//��
//			rece_buf[3]=0xba;					//��
//			rece_buf[4]=0xa3;					//��
//			rece_buf[5]=0xb1;					//��
//			rece_buf[6]=0xa6;					//��
//			rece_buf[7]=0xc7;					//Ƕ
//			rece_buf[8]=0xb6;					//Ƕ
//			rece_buf[9]=0xb5;					//��
//			rece_buf[10]=0xe7;				//��
//			rece_buf[11]=0xd7;				//��
//			rece_buf[12]=0xd3;				//��
//			rece_buf[0]=12;						//һ��Ҫ����12���ֽڣ�rece_buf[0]������12������������
//			SEND_BUF(rece_buf);
//		}
//		delay(100);
//	}
//}



