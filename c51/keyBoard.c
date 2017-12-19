#ifndef _light_h
#include<light.h>
#define _light_h
#endif

unsigned char keyScan(void)
{
unsigned char keyUper,keyLower,keyValue;
P2=0xf0;
if(P2!=0xf0)
	{
	delayMs(10);
	 if((P2|0x80)!=0xf0)
	 	{
		 keyUper=P2;
  		P2=0x0f;
  		keyLower=P2;
 		 keyValue=keyLower+keyUper;
 		 while((P2&0x7f)!=0x0f);
 		 delayMs(10);
  		switch(keyValue)
  			{
 			 case	0xd7:
 			 return 0;break;
 		 	case 0xee:
	 		 return 1;break;
 			 case 0xde:
 			 return 2;break;
 			 case 0xbe:
 			 return 3;break;
			  case 0xed:
			  return 4;break;
			  case 0xdd:
 			 return 5;break;
 			 case 0xbd:
 			 return 6;break;
 			 case 0xeb:
 			 return 7;break;
 			 case 0xdb:
 			 return 8;break;
			  case 0xbb:
			  return 9;break;
			  case 0xe7:
			  return 10;break;
			  case 0xb7:
 			 return 11;break;
 			 default:
			  return 12;
 			 }

		}
	}
	return 12;
}