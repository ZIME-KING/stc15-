#ifndef __key_final_version_h
#define __key_final_version_h




typedef struct {
	unsigned char status;    //0���� 1�̰� 2����
	
	unsigned int  high_time;
	unsigned int  low_time;
	
	unsigned int  falling_edge_flag;
	unsigned int  rising_edge_flag;

	unsigned char count;   						//�ߵ͵�ƽ�ж�
}Key_Typedef;

extern Key_Typedef key[4];

void Edge_detection();
void Get_key_status();

unsigned char Get_key_value(unsigned char n);


#endif