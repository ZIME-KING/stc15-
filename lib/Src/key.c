#include "main.h"

unsigned char scan_key()
{
    unsigned char i;
    if(key_1 == 0)
    {
        delay_ms(10);
        if(key_1==0)    //
        {
            for(i=0; i<100; i++)   //�˴���������
            {
                if(key_1==0)
                    i=0;
            }
            return 1;
        }

    }
    else if(key_2 == 0)
    {
        delay_ms(10);
        if(key_2==0)    //
        {
            for(i=0; i<100; i++)   //�˴���������ǳ����䣬��ô�������Բ������������
            {
                if(key_2==0)
                    i=0;
            }    							//�������Ӱ������º�Ҫִ�еĹ���
            return 2;
        }
    }


    else if(key_3 == 0)
    {
        delay_ms(10);
        if(key_3==0)    //
        {
            for(i=0; i<100; i++)   //�˴���������ǳ����䣬��ô�������Բ������������
            {
                if(key_3 == 0)
                    i=0;
            }
            return 3;
            //�������Ӱ������º�Ҫִ�еĹ��ܡ�
        }
    }

    else if(key_4 == 0)
    {
        delay_ms(10);
        if(key_4==0)    //
        {
            for(i=0; i<100; i++)   //�˴���������ǳ����䣬��ô�������Բ������������
            {
                if(key_4 == 0)
                    i=0;
            }
            return 4;
            //�������Ӱ������º�Ҫִ�еĹ��ܡ�
        }
    }
//
//		else if(key_5 == 0)
//    {
//        delay_ms(10);
//        if(key_5==0)    //
//        {
//            for(i=0; i<100; i++)   //�˴���������
//            {
//                if(key_5==0)
//                    i=0;
//            }
//            return 5;
//        }

//    }
//
//		else if(key_6 == 0)
//    {
//        delay_ms(10);
//        if(key_6==0)    //
//        {
//            for(i=0; i<100; i++)   //�˴���������
//            {
//                if(key_6==0)
//                    i=0;
//            }
//            return 6;
//        }
//    }
    else
        return 0;
}