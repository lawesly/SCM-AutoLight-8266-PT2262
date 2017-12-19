#include<reg52.h>
//#include<studio.h>
#define Year_W 0x8c//写年月日时分秒
#define Month_W 0x8a
#define Day_W 0x88
#define Hour_W 0x86
#define Min_W 0x84
#define Sec_W 0x82
#define Day_R 0x87 //读日时分
#define Hour_R 0x85
#define Min_R 0x83
#define Ctr_W 0x8e//写控制寄存器
#define DELAYNUM 40
#define M433DELAYNUM 70
sbit timeRst=P1^3;
sbit timeSclk=P1^5;
sbit timeIO=P1^4;
void ds1302Write(unsigned char addr,unsigned char dat);
unsigned char ds1302Read(unsigned char addr);
void ds1302Init(void);
void lightStateShow(unsigned int lightState);
void M433ControlLight(unsigned char lightNumber);

void delayUs(unsigned int us);
void delayMs(unsigned int ms);
void test();
unsigned char keyScan(void);

void wifiInit(void);
void sendByte(unsigned char dat);
void sendTwoByte(unsigned char a,unsigned char b,unsigned char serNumber);
void wifiUpload(void);

extern unsigned int lightState;
extern unsigned char openTime[12][2];

extern unsigned char recvBuffer[2];
extern unsigned char flagCount;
extern unsigned char dataCount;
extern bit wifiDownload;
extern unsigned char serialNumber;