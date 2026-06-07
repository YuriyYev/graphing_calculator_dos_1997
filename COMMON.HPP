#ifndef _COMMON_HPP

int Strlen(const char *);

void Wait(long);

//extern unsigned long int common_seek1,common_seek2;
int Getkey(void);

long Gettimerticks(void);

long double Getrandom(void);

void Printstring(char *);

int Kbhit(void);

int Pushkey(char,char);

int Getkeychar(void);

int Getkeycode(void);

int Getkeyboardflags(void);

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

char* Strcpy(char *,const char *,int);

char* Strcpyr(char *,const char *,int);

char *Insstr(char *,const char *,int,int);

int Strcmp(char *,const char *,int);

int Strcmpr(char *,const char *,int);

int Abs(int);

int int2string_dec(int,char far*);

int ulong2string_dec(unsigned long,char far*);

int int2string_bin(int,char*);

int int2string_oct(int,char*);

int int2string_hex(int,char*);

#define _COMMON_HPP
#else
#endif
