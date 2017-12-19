#ifndef _light_h
#include<light.h>
#define _light_h
#endif
//只要调用这个函数，灯状态都已经改变过，所以需要上传数据
void M433ControlLight(unsigned char lightNumber)
{
unsigned int i=lightState;
//判断第0位是1或者所有位都是0时，灯状态改为000000000001
if (lightState==0||(lightState%2))
lightState=1;

//灯显示
i>>=lightNumber;
i=i%2;
i=i<<4;
   P0=(unsigned char)((lightState%256)|i);
   P1=0X02;
   delayMs(DELAYNUM);
   P1=0;
   delayMs(DELAYNUM);
   P0=lightNumber;
   P1=0x04;
   delayMs(M433DELAYNUM);
   P1=0;
   delayMs(DELAYNUM);
   lightStateShow(lightState);
}
