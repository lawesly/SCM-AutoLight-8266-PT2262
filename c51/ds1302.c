#ifndef _light_h
#include<light.h>
#define _light_h
#endif
unsigned char writeRtcAddr[]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
unsigned char initTime[]={0x00,0x41,0x15,0x24,0x12,0x04,0x15};//2013-01-01 12:00:00

void ds1302Write(unsigned char addr,unsigned char dat)
{
unsigned char n;
timeRst=0;;
timeSclk=0;;
timeRst=1;;
for(n=0;n<8;n++)
{
timeIO=addr&0x01;
addr>>=1;
timeSclk=1;;
timeSclk=0;;
}
for(n=0;n<8;n++)
{
timeIO=dat&0x01;
dat>>=1;
timeSclk=1;;
timeSclk=0;
}
timeRst=0;;
}
unsigned char ds1302Read(unsigned char addr)
{
unsigned char n,dat,dat1;
timeRst=0;;
timeSclk=0;;
timeRst=1;;
for(n=0;n<8;n++)
{
timeIO=addr&0x01;
addr>>=1;
timeSclk=1;;
timeSclk=0;;
}
;
for(n=0;n<8;n++)
{
dat1=timeIO;
dat=(dat>>1)|(dat1<<7);
timeSclk=1;;
timeSclk=0;;
}
timeRst=0;;
timeSclk=1;;
timeIO=0;;
timeIO=1;;
return dat;
}
void ds1302Init(void)
{
unsigned char n;
ds1302Write(0x8e,0x00);
for(n=0;n<7;n++)
{
ds1302Write(writeRtcAddr[n],initTime[n]);
}
ds1302Write(0x8e,0x80);
}