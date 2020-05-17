#include "main.h"

unsigned char scan_key()
{
    unsigned char i;
    if(key_1 == 0)
    {
        delay_ms(10);
        if(key_1==0)    //
        {
            for(i=0; i<100; i++)   //此处消抖程序
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
            for(i=0; i<100; i++)   //此处消抖程序非常经典，怎么按都绝对不会产生抖动。
            {
                if(key_2==0)
                    i=0;
            }    							//在这儿添加按键按下后要执行的功能
            return 2;
        }
    }


    else if(key_3 == 0)
    {
        delay_ms(10);
        if(key_3==0)    //
        {
            for(i=0; i<100; i++)   //此处消抖程序非常经典，怎么按都绝对不会产生抖动。
            {
                if(key_3 == 0)
                    i=0;
            }
            return 3;
            //在这儿添加按键按下后要执行的功能。
        }
    }

    else if(key_4 == 0)
    {
        delay_ms(10);
        if(key_4==0)    //
        {
            for(i=0; i<100; i++)   //此处消抖程序非常经典，怎么按都绝对不会产生抖动。
            {
                if(key_4 == 0)
                    i=0;
            }
            return 4;
            //在这儿添加按键按下后要执行的功能。
        }
    }
//
//		else if(key_5 == 0)
//    {
//        delay_ms(10);
//        if(key_5==0)    //
//        {
//            for(i=0; i<100; i++)   //此处消抖程序
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
//            for(i=0; i<100; i++)   //此处消抖程序
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