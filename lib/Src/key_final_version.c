
#include "main.h"

sbit key_0 = P1^0;
sbit key_1 = P1^1;
sbit key_2 = P1^2;
sbit key_3 = P1^3;



Key_Typedef key[4];
//static
unsigned char Get_key_value(unsigned char n){
	
unsigned char x;
	
	switch (n) {
	case 0:
		x=key_0;
		//return x;
		break;

	case 1:
		x=key_1;
		//return key_2;
		break;

	case 2:
		x=key_2;
		//return key_3;
		break;

	case 3:
		x=key_3;
		//return key_4;
		break;

	default:
		x=0;
	//	return 0;
		break;
	}
	return x;
}


//边沿检测  放到定时器1ms跑一次
void Edge_detection(){
	unsigned char i;	
	
	
	

	for(i=0;i<4;i++){
		
		key[i].count <<= 1;
			if(Get_key_value(i)==1)
				key[i].count++;
		
		if(key[i].count==0xf0){
		key[i].falling_edge_flag=1;
		key[i].rising_edge_flag=0;
		}
		else if (key[i].count==0x0f){
		key[i].falling_edge_flag=0;
		key[i].rising_edge_flag=1;
		}
		
		if(key[i].falling_edge_flag!=0){
		key[i].low_time++;
		}
		if(key[i].rising_edge_flag!=0){
		key[i].high_time++;
		}
	}
}

void Get_key_status(){
	unsigned char i;
	
	for(i=0;i<4;i++){
		if(key[i].high_time>=5){      
			
			if(key[i].low_time<=10){ 					//干扰
			   //if(key[i].status=0;
			}
			
		  else if(key[i].low_time<=300){    //短按
				key[i].status=1;
			}
			
			else if(key[i].low_time>=300){    //长按
				key[i].status=2;
			}
			
			
						key[i].low_time=0;     						 //按键处理 计数清0
			key[i].high_time=0;
		}
	}
}