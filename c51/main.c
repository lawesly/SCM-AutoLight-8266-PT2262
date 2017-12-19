#ifndef _light_h
#include<light.h>
#define _light_h
#endif
unsigned int lightState;
unsigned char serialNumber;
unsigned char openTime[12][2];
bit wifiDownload;
void main(void)
{
unsigned char i;
unsigned char keyValue;
unsigned int lightFlag;
unsigned char lightCheck;


P0=P1=P2=0;
delayMs(DELAYNUM);
//��ʼ�����е�״̬Ϊ0����ʼ��1302, ��ʼ������9600-8-n-1��ʼ��wifiDownloadΪ0��wifi�����������Ϊ0
lightState=0;
serialNumber=0;
ds1302Init();
wifiInit();
wifiDownload=0;
//�ƿ���
for(i=0;i<12;i++)
M433ControlLight(i);
wifiUpload();
while(1)
{
//��ѯwifi�Ƿ���download������У���ִ��
if(wifiDownload)
{
wifiDownload=0;
		for(i=0;i<12;i++)
			M433ControlLight(i);
		wifiUpload();
}		
//��ѯ����
	keyValue=keyScan();
	//������0���ر����еƣ���������0��ȡ����Ӧ�ĵƣ�����ǿ��ƣ���¼���Ƶ�day
	if (keyValue<12)
		{
		if(keyValue==0)
		{
		lightState=0;
		for(i=0;i<12;i++)
			M433ControlLight(i);
		wifiUpload();
		}
		else
		{
		lightFlag=1;
		lightFlag=lightFlag<<keyValue;
		if(lightState%2)
		{
		lightState=lightFlag;
		}
		else
		{
		lightState=lightState^lightFlag;
		}
		M433ControlLight(keyValue);
		wifiUpload();
		if(lightFlag&lightState)
			{
			openTime[keyValue][0]=ds1302Read(Day_R);
			openTime[keyValue][1]=ds1302Read(Hour_R);
			}	
		}
		}				  
		
	//��ʱ���ѯ�Ƿ�����Ҫ�رյĵ�
	if((ds1302Read(Hour_R)==0x08)&&(ds1302Read(Min_R)==0x00))
		{
		lightCheck=lightState;
		for(i=1;i<12;i++)
			{
			 lightCheck/=2;
			 if(lightCheck%2)
			 	{
			 	if(!((openTime[i][0]==ds1302Read(Day_R))&&( openTime[keyValue][1]>0x05)))
			 		{
			 		M433ControlLight(i);
					wifiUpload();
			 		}
			 	}
			}
		}
}

}							  