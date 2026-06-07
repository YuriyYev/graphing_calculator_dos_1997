#include"..\express\common.hpp"

#pragma inline

int Strlen(const char *ptr)
{
for(int len=0;*ptr;ptr++) len++;
return len;
}

void Wait(long t)
	{
	asm{
		mov ah,86h
		mov dx,word ptr t
		mov cx,word ptr t+2
		int 15h
		}
	while(Kbhit()) Getkey();
	}


long Gettimerticks(void)
{
long ticks;
asm mov ah,0
asm int 1ah
asm mov word ptr ticks,dx
asm mov word ptr ticks+2,cx
return ticks;
}

unsigned long int common_seek1=2834761234ul,common_seek2=163502389ul;
int common_isfirst=0;
//int Getkey(void);

long double Getrandom(void)
{
long double work;
unsigned char hund;
asm mov ah,2ch
asm int 21h
hund=_DL;
if(!common_isfirst)
	{
	common_seek1+=((unsigned long)hund)<<8;
	common_seek2+=((unsigned long)hund)<<27;
	common_isfirst=1;
	}
if(!(common_seek1|common_seek2))
	{
	common_seek1=(_FLAGS<<4)+((unsigned long)hund)<<10;
	common_seek2=(_FLAGS<<13)+common_seek1;
	}
	else
	{
	common_seek1+=(((unsigned long)hund)<<10)+hund;
	common_seek2+=(((unsigned long)hund)<<20)+(((int)hund)<<6);
	}
for(int count=0;count<10;count++)
	{
	asm mov ax,seg common_seek1
	asm mov es,ax
	asm mov eax,dword ptr es:[common_seek1]
	asm mov ebx,dword ptr es:[common_seek2]
	asm rol eax,2
	asm ror ebx,2
	asm add eax,ebx
	asm mov dword ptr es:[common_seek1],eax
	asm ror eax,5
	asm rol ebx,5
	asm add ebx,eax
	asm mov dword ptr es:[common_seek2],ebx
	}
work=long(common_seek1+common_seek2);
work/=4294967296.0;
return work;
}

void Printstring(char *ptr)
{
for(;*ptr;ptr++)
	{
	_DL=*ptr;
	asm mov ah,2
	asm int 21h
	}
}

volatile int ctrl_breakpressed;

int Kbhit(void)
{
if(ctrl_breakpressed)
	{
	asm mov ah,0bh
	asm int 21h
	ctrl_breakpressed=0;
	}
asm mov ah,11h
asm int 16h
asm jnz Kbhit_label
asm xor ax,ax
Kbhit_label:
asm mov cx,ax
return _CX;
}

int Pushkey(char keychar,char keycode)
{
if(ctrl_breakpressed)
	{
	asm mov ah,0bh
	asm int 21h
	ctrl_breakpressed=0;
	}
_CH=keycode;
_CL=keychar;
asm mov ah,5
asm int 16h
asm mov cl,al
return !_CL;
} //0 - нет ошибки, не 0 - буфер переполнен

int Getkey(void)
{
if(ctrl_breakpressed)
	{
	asm mov ah,0bh
	asm int 21h
	ctrl_breakpressed=0;
	}
asm mov ah,16
asm int 16h
asm mov cx,ax
return _CX;
}


int Getkeychar(void)
{
if(ctrl_breakpressed)
	{
	asm mov ah,0bh
	asm int 21h
	ctrl_breakpressed=0;
	}
asm mov ah,10h
asm int 16h
asm mov cl,al
return (int)_CL;
}

int Getkeycode(void)
{
if(ctrl_breakpressed)
	{
	asm mov ah,0bh
	asm int 21h
	ctrl_breakpressed=0;
	}
asm mov ah,10h
asm int 16h
asm mov cl,ah
return (int)_CL;
}

int Getkeyboardflags(void)
{
if(ctrl_breakpressed)
	{
	asm mov ah,0bh
	asm int 21h
	ctrl_breakpressed=0;
	}
asm mov ah,18
asm int 16h
asm mov cx,ax
return _CX;
}

#define KBS_RSHIFTDOWN 1
#define KBS_LSHIFTDOWN 2
#define KBS_CTRLDOWN 4
#define KBS_ALTDOWN 8
#define KBS_SCRLOCKON 16
#define KBS_NUMLOCKON 32
#define KBS_CAPSLOCKON 64
#define KBS_INSON 128
#define KBS_LCTRLDOWN 256
#define KBS_LALTDOWN 512
#define KBS_RCTRLDOWN 1024
#define KBS_RALTDOWN 2048
#define KBS_SCRLOCKDOWN 4096
#define KBS_NUMLOCKDOWN 8192
#define KBS_CAPSLOCKDOWN 16384
#define KBS_SYSREQDOWN 32768

char* Strcpy(char *dest,const char *src,int len)
{
if(!len) return dest;
char far*d,far*s;
d=(char far*)dest;
s=(char far*)src;
_CX=len;
asm push ds
asm pushf
asm les di,[d]
asm lds si,[s]
asm cld
asm rep movsb
asm popf
asm pop ds
return dest;
}

char* Strcpyr(char *dest,const char *src,int len)
{
if(!len) return dest;
char far*d,far*s;
d=(char far*)dest;
s=(char far*)src;
_CX=len;
//_DX=int((char _seg*)src);
//_ES=int((char _seg*)dest);
//_SI=int((char near*)src);
//_DI=int((char near*)dest);
asm push ds
asm pushf
asm les di,[d]
asm lds si,[s]
asm std
asm rep movsb
asm popf
asm pop ds
return dest;
}

char *Insstr(char *dest,const char *src,int len2move,int len2ins)
{
Strcpyr(dest+len2move-1+len2ins,dest+len2move-1,len2move);
Strcpy(dest,src,len2ins);
return dest+len2ins;
}

int Strcmp(char *dest,const char *src,int len)
{
if(!len) return 0;
char far*d,far*s;
d=(char far*)dest;
s=(char far*)src;
_CX=len;
_SI=*((int*)(&s));
_DI=*((int*)(&d));
_ES=*((int*)(&d)+1);
_DX=*((int*)(&s)+1);
asm push ds
asm pushf
asm mov ds,dx
asm cld
asm repe cmpsb
asm mov al,es:[di-1]
asm sub al,ds:[si-1]
asm popf
asm pop ds
asm cbw
return _AX;
}

int Strcmpr(char *dest,const char *src,int len)
{
if(!len) return 0;
char far*d,far*s;
d=(char far*)dest;
s=(char far*)src;
_CX=len;
_SI=*((int*)(&s));
_DI=*((int*)(&d));
_ES=*((int*)(&d)+1);
_DX=*((int*)(&s)+1);
asm push ds
asm pushf
asm mov ds,dx
asm std
asm repe cmpsb
asm mov al,es:[di+1]
asm sub al,ds:[si+1]
asm popf
asm pop ds
asm cbw
return _AX;
}

int Abs(int num)
{
if(num>=0) return num;
	else return -num;
//return num>=0?num:-num;
}

int int2string_dec(int num,char far*pter)
{
if(!num) {pter[0]='0';return 1;}
//int off=0,sign=0;//,work=10000;
asm xor di,di
asm mov si,di
asm mov cx,10
asm mov ax,[num]
asm or ax,ax
asm jns label1
asm inc si
asm neg ax
label1:
asm cwd
label2:
asm div cx
asm push dx
asm inc di
asm xor dx,dx
asm or ax,ax
asm jnz label2
asm mov cx,di
asm xor di,di
asm mov es,word ptr[pter+2]
asm mov bx,word ptr[pter]
asm or si,si
asm jz label3
asm mov byte ptr es:[bx+di],'-'
asm inc di
label3:
asm pop ax
asm add al,'0'
asm mov es:[bx+di],al
asm inc di
asm loop label3
return _DI;

/*
if(num<0)
	{
	ptr[0]='-';
	off++;
	num=-num;
	}
while (work && !(num/work)) work/=10;
while (work)
	{
	ptr[off++]=num/work+'0';
	num%=work;
	work/=10;
	}
return off;*/
}

int ulong2string_dec(unsigned long num,char far*pter)
{
if(!num) {pter[0]='0';return 1;}
//int off=0,sign=0;//,work=10000;
asm xor di,di
asm mov ecx,10
asm mov eax,[num]
asm xor edx,edx
label2:
asm div ecx
asm push dx
asm inc di
asm xor edx,edx
asm or eax,eax
asm jnz label2
asm mov cx,di
asm xor di,di
asm mov es,word ptr[pter+2]
asm mov bx,word ptr[pter]
label3:
asm pop ax
asm add al,'0'
asm mov es:[bx+di],al
asm inc di
asm loop label3
return _DI;
}

int int2string_bin(int num,char*ptr)
{
if(!num) {ptr[0]='0';return 1;}
int off=0,work=16384;
if(num<0)
	{
	ptr[0]='-';
	off++;
	num=-num;
	}
while (work && !(num/work)) work>>=1;
while (work)
	{
	ptr[off++]=num/work+'0';
	num%=work;
	work>>=1;
	}
return off;
}

int int2string_oct(int num,char*ptr)
{
if(!num) {ptr[0]='0';return 1;}
int off=0,work=4096;
if(num<0)
	{
	ptr[0]='-';
	off++;
	num=-num;
	}
while (work && !(num/work)) work>>=3;
while (work)
	{
	ptr[off++]=num/work+'0';
	num%=work;
	work>>=3;
	}
return off;
}

int int2string_hex(int num,char*ptr)
{
if(!num) {ptr[0]='0';return 1;}
int off=0,work=4096;
if(num<0)
	{
	ptr[0]='-';
	off++;
	num=-num;
	}
while (work && !(num/work)) work>>=4;
while (work)
	{
	ptr[off++]=num/work+'0';
	num%=work;
	if(ptr[off-1]>'9') ptr[off-1]+='\xa0'-58;
	work>>=4;
	}
return off;
}
