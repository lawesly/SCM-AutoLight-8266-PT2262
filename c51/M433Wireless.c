#ifndef _light_h
#include<light.h>
#define _light_h
#endif
//ֻҪ���������������״̬���Ѿ��ı����������Ҫ�ϴ�����
void M433ControlLight(unsigned char lightNumber)
{
unsigned int i=lightState;
//�жϵ�0λ��1��������λ����0ʱ����״̬��Ϊ000000000001
if (lightState==0||(lightState%2))
lightState=1;

//����ʾ
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
