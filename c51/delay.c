#ifndef _light_h
#include<light.h>
#define _light_h
#endif
/*
void delayUs(unsigned int us)
{
unsigned int i;
for(i=0;i<us;i++);
}
*/
void delayMs(unsigned int ms)
{
unsigned int i,j;
for(i=0;i<ms;i++)
for(j=0;j<1000;j++);
}