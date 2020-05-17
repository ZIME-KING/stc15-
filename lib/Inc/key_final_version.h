#ifndef __key_final_version_h
#define __key_final_version_h




typedef struct {
	unsigned char status;    //0空闲 1短按 2长按
	
	unsigned int  high_time;
	unsigned int  low_time;
	
	unsigned int  falling_edge_flag;
	unsigned int  rising_edge_flag;

	unsigned char count;   						//高低电平判断
}Key_Typedef;

extern Key_Typedef key[4];

void Edge_detection();
void Get_key_status();

unsigned char Get_key_value(unsigned char n);


#endif