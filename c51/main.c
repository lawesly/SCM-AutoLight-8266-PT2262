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
//初始化所有灯状态为0，初始化1302, 初始波特率9600-8-n-1初始化wifiDownload为0，wifi传送数据序号为0
lightState=0;
serialNumber=0;
ds1302Init();
wifiInit();
wifiDownload=0;
//灯控制
for(i=0;i<12;i++)
M433ControlLight(i);
wifiUpload();
while(1)
{
//查询wifi是否有download，如果有，就执行
if(wifiDownload)
{
wifiDownload=0;
		for(i=0;i<12;i++)
			M433ControlLight(i);
		wifiUpload();
}		
//查询按键
	keyValue=keyScan();
	//按键是0，关闭所有灯，按键不是0，取反相应的灯，如果是开灯，记录开灯的day
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
		
	//按时间查询是否有需要关闭的灯
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