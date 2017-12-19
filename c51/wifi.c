#ifndef _light_h
#include<light.h>
#define _light_h
#endif

unsigned char recvBuffer[2]={0,0};
unsigned char flagCount=0;
unsigned char dataCount=0;
void wifiInit(void)
{
SCON=0x50;
TMOD=0x20;
TH1=0xFd;
TL1=0xFd;
TR1=1;
EA=1;
ES=1;
}
void sendByte(unsigned char dat)
{
SBUF=dat;
while(!TI);
TI=0;
}
void sendTwoByte(unsigned char a,unsigned char b,unsigned char serNumber)
{
unsigned char i;

unsigned char sendSer[10]={0,0,0,0,0,0,0,0,0,0};

sendSer[0]=0x48;
sendSer[1]=0x0a;
sendSer[2]=0x01;
sendSer[3]=0x01;
sendSer[4]=serNumber;
sendSer[5]=0;
sendSer[6]=0;
sendSer[7]=a;
sendSer[8]=b;
sendSer[9]=0;
for(i=0;i<9;i++)
{
sendSer[9]+=sendSer[i];
}
for(i=0;i<10;i++)
{
sendByte(sendSer[i]);
}

}

void serIn(void) interrupt 4
{
if(RI)
{
RI=0;

if(flagCount==3||dataCount==1)
{
	recvBuffer[dataCount++]=SBUF;
	if(dataCount==2)
	{
		wifiDownload=1;
		flagCount=0;
		dataCount=0;
		lightState=(unsigned int)recvBuffer[0]*256+recvBuffer[1];
		if(lightState==0||(lightState%2))
			lightState=1;	
	}
}
if(0x61==SBUF)
flagCount++;
else flagCount=0;
}
}

//上传数据
void wifiUpload()
{
unsigned char a,b;
a=lightState>>8;
b=lightState;
sendTwoByte(a,b,serialNumber);
sendTwoByte(a,b,serialNumber);
sendTwoByte(a,b,serialNumber++);
 delayMs(DELAYNUM);
 }