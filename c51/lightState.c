#ifndef _light_h
#include<light.h>
#define _light_h
#endif

void lightStateShow(unsigned int lightState)
{
//灯指示的显示

P0=(unsigned char)(lightState&0xff);
P1=0x01;
delayMs(DELAYNUM);
P1=0;
delayMs(DELAYNUM);
P0=(unsigned char)(lightState>>8);
P1=0x02;
delayMs(DELAYNUM);
P1=0;
delayMs(DELAYNUM);


}