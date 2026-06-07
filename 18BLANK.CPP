#include"common.hpp"
char DAC[16];

struct DACelem
{
char red,green,blue;
DACelem(void){}
DACelem(int r,int g,int b)
	{
	red=r;
	green=g;
	blue=b;
	}
};

DACelem forblank[16];

void initDAC(void)
{
char temp;
for(int i=0;i<16;i++)
	{
	asm mov dx,3dah
	asm in al,dx
	asm mov dx,3c0h
	asm mov al,byte ptr i
	asm out dx,al
	asm inc dx
	asm in al,dx
	temp=_AL;
	DAC[i]=temp;
	}
asm mov dx,3dah
asm in al,dx
asm mov dx,3c0h
asm mov al,32
asm out dx,al
}

DACelem readDAC(int code)
{
DACelem tmp;
_AL=DAC[code];
asm cli
asm mov dx,3c7h
//asm mov al,[code]
asm out dx,al
asm inc dx
asm inc dx
asm in al,dx
tmp.red=_AL;
asm in al,dx
tmp.green=_AL;
asm in al,dx
tmp.blue=_AL;
asm sti
return tmp;
}

void waitvsync(void)
{
asm mov dx,3dah
//lab1:
//asm in al,dx
//asm and al,8d
//asm jne lab1
lab2:
asm in al,dx
asm and al,8d
asm je lab2
}

void writeDAC(int code,DACelem &tmp)
{
asm cli
_AL=DAC[code];
asm mov dx,3c8h
//asm mov al,[code]
asm out dx,al
asm inc dx
_AL=tmp.red;
asm out dx,al
_AL=tmp.green;
asm out dx,al
_AL=tmp.blue;
asm out dx,al
asm sti
}

void readpalette(DACelem *ptr)
{
for(int i=0;i<16;i++)
	ptr[i]=readDAC(i);
}

void writepalette(DACelem *ptr)
{
for(int i=0;i<16;i++)
	writeDAC(i,ptr[i]);
}

void blank(void)
{
for(int o=0;o<16;o++)
	forblank[o]=readDAC(o);
waitvsync();
for(o=0;o<16;o++)
	writeDAC(o,DACelem(0,0,0));
}

void fade(void)
{
waitvsync();
for(int o=0;o<16;o++)
	writeDAC(o,forblank[o]);
}

void fade2blank(void)
{
for(int i=0;i<16;i++)
	forblank[i]=readDAC(i);
DACelem temp;
unsigned long nexttimertick,numticks=0;
nexttimertick=Gettimerticks();
while(nexttimertick-Gettimerticks()==0);
nexttimertick=Gettimerticks();
while(nexttimertick-Gettimerticks()==0) numticks++;
long o;
//long pause;
for(i=63;i>=0;i-=1)
	{
	for(o=(numticks>>2);o>=0;o--)
		if(nexttimertick-Gettimerticks()==0);
//	waitvsync();
//    pause=300000;
//    while(pause>0)pause--;
	for(o=0;o<16;o++)
		{
		temp=forblank[o];
		temp.red=temp.red*i/64;
		temp.green=temp.green*i/64;
		temp.blue=temp.blue*i/64;
		writeDAC(o,temp);
		}
	}
}

void blank2fade(void)
{
DACelem temp;
unsigned long nexttimertick,numticks=0;
nexttimertick=Gettimerticks();
while(nexttimertick-Gettimerticks()==0);
nexttimertick=Gettimerticks();
while(nexttimertick-Gettimerticks()==0) numticks++;
long o;
//long pause;
for(int i=1;i<=64;i+=1)
	{
	for(o=(numticks>>2);o>=0;o--)
		if(nexttimertick-Gettimerticks()==0);
//	waitvsync();
//    pause=300000;
//    while(pause>0)pause--;
	for(o=0;o<16;o++)
		{
		temp=forblank[o];
		temp.red=temp.red*i/64;
		temp.green=temp.green*i/64;
		temp.blue=temp.blue*i/64;
		writeDAC(o,temp);
		}
	}
}
