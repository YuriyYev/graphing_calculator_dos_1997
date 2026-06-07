extern unsigned _stklen=40000U;
#include"..\express\18blank.cpp"
extern "C" GetcurrentCPU(void);
extern "C" void ctrlchandler(void);
extern "C" void criticalerror(void);

struct _find_data
{
char reserved[15];
char attributes;
unsigned time,date;
unsigned long size;
char name[13];
};


int _findfirst(char *mask,_find_data *dat)
{
asm {
	mov ah,1ah
	push ds
	mov ds,word ptr [dat+2]
	mov dx,word ptr [dat]
	int 21h
	mov ah,4eh
	mov cx,100111b
	mov ds,word ptr [mask+2]
	mov dx,word ptr [mask]
	int 21h
	pop ds
	mov ax,1
	jnc noerror
	mov ax,0
	}
noerror:
return _AX;
}

int _findnext(_find_data *dat)
{
asm {
	mov ah,1ah
	push ds
	mov ds,word ptr [dat+2]
	mov dx,word ptr [dat]
	int 21h
	mov ah,4fh
	int 21h
	pop ds
	mov ax,1
	jnc noerror
	mov ax,0
	}
noerror:
return _AX;
}

int _open(char*adr)
{
asm {
	mov ah,3dh
	mov al,0
	push ds
	mov ds,word ptr [adr+2]
	mov dx,word ptr [adr]
	int 21h
	pop ds
	jnc noerror
	mov ax,-1
	}
noerror:
return _AX;
}

int _creat(char*adr)
{
asm {
	mov ah,3ch
	mov cx,0
	push ds
	mov ds,word ptr [adr+2]
	mov dx,word ptr [adr]
	int 21h
	pop ds
	jnc noerror
	mov ax,-1
	}
noerror:
return _AX;
}

int _delete(char*adr)
{
asm {
	mov ah,41h
	push ds
	mov ds,word ptr [adr+2]
	mov dx,word ptr [adr]
	int 21h
	pop ds
	mov ax,0
	jnc noerror
	mov ax,-1
	}
noerror:
return _AX;
}


int _close(int hand)
{
asm {
	mov ah,3eh
	mov bx,[hand]
	int 21h
	mov ax,0
	jnc noerror
	mov ax,-1
	}
noerror:
return _AX;
}

long filelength(int hand)
{
asm {
	mov ax,4202h
	mov bx,[hand]
	xor cx,cx
	xor dx,dx
	int 21h
	mov di,dx
	mov si,ax
	mov ax,4200h
	mov bx,[hand]
	xor cx,cx
	xor dx,dx
	int 21h
	mov ax,si
	mov dx,di
	jnc noerror
	}
noerror:
}

int _read(int hand,void*buf,int len)
{
asm {
	mov ah,3fh
	mov bx,[hand]
	mov cx,[len]
	push ds
	mov ds,word ptr [buf+2]
	mov dx,word ptr [buf]
	int 21h
	pop ds
	jnc noerror
//	mov ax,-1
	}
throw (int)(-1);
noerror:
return _AX;
}

int _write(int hand,void*buf,int len)
{
asm {
	push bx
	push cx
	push dx
	mov ah,40h
	mov bx,[hand]
	mov cx,[len]
	push ds
	mov ds,word ptr [buf+2]
	mov dx,word ptr [buf]
	int 21h
	pop ds
	pop dx
	pop cx
	pop bx
	jnc noerror
//	mov ax,-1
	}
throw (int)(-1);
noerror:
return _AX;
}




#include "..\express\calc.hpp"
#include "..\express\calckeys.cpp"
extern long double leftborder,rightborder,upborder,downborder;
extern long double xscale,yscale,xgridstep,ygridstep;
extern long firstiter,seconditer;
extern int deactive,isredraw,joinpoints,isauto;

void savestate(void);
int loadstate(void);

System_field F_RAD(30+6,226+16,12,12,KEY_RAD,12,7);
System_field F_DEG(70+6,226+16,12,12,KEY_DEG,12,7);
System_field F_GRD(110+6,226+16,12,12,KEY_GRD,12,7);
System_field F_BIN(460+6,226+16,12,12,KEY_BIN,12,7);
System_field F_OCT(500+6,226+16,12,12,KEY_OCT,12,7);
System_field F_DEC(540+6,226+16,12,12,KEY_DEC,12,7);
System_field F_HEX(580+6,226+16,12,12,KEY_HEX,12,7);


#include "..\express\calcwork.cpp"

extern Editline X_scale;
extern Editline Y_scale;
extern Editline VW_iter;
extern Editline XY_iter;

void drawconsol(int fl)
{
hidemouse();
mygr.drawfilledbox(0,0,639,479,7);
if(!fl)
	{
	indic.settext(main_string);
	if(isinsert ^ indic.insertmode) indic.changeinputtype(0);
	}
indic.draw();
	{
	int xc=30,yc=210+16;
	Putsymbol(asciisymboltable['ê'],xc,yc,15,7);
//	if(!fl)
//		{
//		F_RAD.init_System_field(xc+6,yc+16,12,12,KEY_RAD,12,7);
//		F_RAD.turn_on();
//		hidemouse();
//		}
	xc+=8;
	Putsymbol(asciisymboltable['Ä'],xc,yc,15,7);
	xc+=8;
	Putsymbol(asciisymboltable['Ñ'],xc,yc,15,7);
	xc+=8;
	xc+=16;
	Putsymbol(asciisymboltable['É'],xc,yc,15,7);
//	if(!fl)
//		{
//		F_DEG.init_System_field(xc+6,yc+16,12,12,KEY_DEG,12,7);
//		F_DEG.turn_off();
//		hidemouse();
//		}
	xc+=8;
	Putsymbol(asciisymboltable['ê'],xc,yc,15,7);
	xc+=8;
	Putsymbol(asciisymboltable['Ä'],xc,yc,15,7);
	xc+=8;
	xc+=16;
	Putsymbol(asciisymboltable['É'],xc,yc,15,7);
//	if(!fl)
//		{
//		F_GRD.init_System_field(xc+6,yc+16,12,12,KEY_GRD,12,7);
//		F_GRD.turn_off();
//		hidemouse();
//		}
	xc+=8;
	Putsymbol(asciisymboltable['ê'],xc,yc,15,7);
	xc+=8;
	Putsymbol(asciisymboltable['Ñ'],xc,yc,15,7);
	xc=460;
	Putsymbol(asciisymboltable['B'],xc,yc,15,7);
//	if(!fl)
//		{
//		F_BIN.init_System_field(xc+6,yc+16,12,12,KEY_BIN,12,7);
//		F_BIN.turn_off();
//		hidemouse();
//		}
	xc+=8;
	Putsymbol(asciisymboltable['I'],xc,yc,15,7);
	xc+=8;
	Putsymbol(asciisymboltable['N'],xc,yc,15,7);
	xc+=8;
	xc+=16;
	Putsymbol(asciisymboltable['O'],xc,yc,15,7);
//	if(!fl)
//		{
//		F_OCT.init_System_field(xc+6,yc+16,12,12,KEY_OCT,12,7);
//		F_OCT.turn_off();
//		hidemouse();
//		}
	xc+=8;
	Putsymbol(asciisymboltable['C'],xc,yc,15,7);
	xc+=8;
	Putsymbol(asciisymboltable['T'],xc,yc,15,7);
	xc+=8;
	xc+=16;
	Putsymbol(asciisymboltable['D'],xc,yc,15,7);
//	if(!fl)
//		{
//		F_DEC.init_System_field(xc+6,yc+16,12,12,KEY_DEC,12,7);
//		F_DEC.turn_on();
//		hidemouse();
//		}
	xc+=8;
	Putsymbol(asciisymboltable['E'],xc,yc,15,7);
	xc+=8;
	Putsymbol(asciisymboltable['C'],xc,yc,15,7);
	xc+=8;
	xc+=16;
	Putsymbol(asciisymboltable['H'],xc,yc,15,7);
//	if(!fl)
//		{
//		F_HEX.init_System_field(xc+6,yc+16,12,12,KEY_HEX,12,7);
//		F_HEX.turn_off();
//		hidemouse();
//		}
	xc+=8;
	Putsymbol(asciisymboltable['E'],xc,yc,15,7);
	xc+=8;
	Putsymbol(asciisymboltable['X'],xc,yc,15,7);
	}
Putsymbol(&S_emblem1,205,468,15,7);
Putsymbol(&S_emblem2,255,468,15,7);
Putsymbol(&S_emblem3,305,468,15,7);
Putsymbol(&S_emblem4,355,468,15,7);
Putsymbol(&S_emblem5,405,468,15,7);
F_RAD.draw();
F_DEG.draw();
F_GRD.draw();
F_BIN.draw();
F_OCT.draw();
F_DEC.draw();
F_HEX.draw();
showsystems();
showmouse();
}

long int1b;

#include<except.h>

int initialization(void)
{
try
	{
	num2str_buffer=new char[90];
	curnumbuf=new char[90];
	variable=new memory_element[34];
	multitude=new mul_element[MULTITUDE_SIZE];
	allnums=(long double*)new char[NUMSTACK_SIZE];
	allopers=new char[OPSTACK_SIZE];
	main_string=new char[STRING_LEN+2];
	main_flags=new char[STRING_LEN+1];
	Indic_buffer=new char[STRING_LEN+2];
	Indic_flags=new char[STRING_LEN+1];
	firstlowlimit_str=new char[STRING_LEN+2];
	secondlowlimit_str=new char[STRING_LEN+2];
	firsthighlimit_str=new char[STRING_LEN+2];
	secondhighlimit_str=new char[STRING_LEN+2];
	firstlowlimit_flag=new char[STRING_LEN+1];
	secondlowlimit_flag=new char[STRING_LEN+1];
	firsthighlimit_flag=new char[STRING_LEN+1];
	secondhighlimit_flag=new char[STRING_LEN+1];
	graphic_buffer=new char[44000u];
	for(int i=0;i<34;i++)
		{
		variable[i].string=new char[STRING_LEN+2];
		variable[i].flags=new char[STRING_LEN+1];
//		if(!variable[i].string || !variable[i].flags)
//			{
//			mygr.~Graph18();
//			Printstring(Error_messages[3]);
//			return 0;
//			}
		}
	}
//if(!num_stk || !oper_stk || !allnums || !allopers || !main_string || !graphic_buffer ||
//	 /*!indic ||*/ !main_flags || !firstlowlimit_str || !secondlowlimit_str || !Indic_buffer ||
//	 !firsthighlimit_str || !secondhighlimit_str || !firstlowlimit_flag || !curnumbuf ||
//	 !secondlowlimit_flag || !firsthighlimit_flag || !secondhighlimit_flag ||
//	 !X_scale || !Y_scale || !VW_iter || !XY_iter || !num2str_buffer || !variable || !multitude)
	catch(xalloc)
	{
	mygr.~Graph18();
	Printstring(Error_messages[3]);
	return 0;
	}
//for(int i=0;i<34;i++)
//	{
//	variable[i].string=new char[STRING_LEN+2];
//	variable[i].flags=new char[STRING_LEN+1];
//	if(!variable[i].string || !variable[i].flags)
//		{
//		mygr.~Graph18();
//		Printstring(Error_messages[3]);
//		return 0;
//		}
//	}
//_ES=_DS;
//_DS=(unsigned)((void _seg*)ctrlchandler);
//_DX=(unsigned)((void near*)ctrlchandler);
//_AH=0x25;
//_AL=0x23;
asm mov ah,35h
asm mov al,1bh
asm int 21h
int1b=(((long)_ES)<<16)+_BX;
asm push ds
asm mov ax,seg ctrlchandler
asm mov ds,ax
asm mov dx,offset ctrlchandler
asm mov ah,25h
asm mov al,23h
asm int 21h
asm mov al,1bh
asm int 21h
asm mov ax,seg criticalerror
asm mov ds,ax
asm mov dx,offset criticalerror
asm mov ah,25h
asm mov al,24h
asm int 21h
asm pop ds

//_DS=_ES;
return 1;
}

void terminate_func();
terminate_function oldterm;

int main()
{
if(mygr.getvideomode()!=18)
	{
	Printstring(Error_messages[12]);
	return 1;
	}
if(GetcurrentCPU()<64)
	{
	mygr.~Graph18();
	Printstring(Error_messages[13]);
	Printstring("\r\n");
	num2str_buffer[int2string_dec(GetcurrentCPU(),num2str_buffer)]='\0';
	Printstring(num2str_buffer);
	Getkey();
	if(GetcurrentCPU()&0xf<3) return 1;
	mygr.setvideomode18();
//	return 1;
	}
initDAC();
writeDAC(15,DACelem(63,63,63));
writeDAC(8,DACelem(28,28,28));
writeDAC(12,DACelem(63,0,0));
writeDAC(9,DACelem(0,0,63));
writeDAC(14,DACelem(63,63,0));
writeDAC(6,DACelem(15,15,15));
writeDAC(7,DACelem(40,40,40));
writeDAC(11,DACelem(0,59,63));
writeDAC(2,DACelem(0,30,0));
if(!initialization()) return 1;//{while(!Kbhit());Getkey();return 1;}
oldterm=set_terminate(terminate_func);
if(!RESETMOUSE(numbuttons))
	{indic.settext("åõòú çÖ çÄâÑÖçÄ");indic.draw();while(!Kbhit());Getkey();nomouse=1;}
	else
	SETMOUSEHANDLE(ME_LEFTPRESSED|ME_LEFTRELEASED|ME_RIGHTPRESSED|ME_RIGHTRELEASED|ME_MOVED);
if(!nomouse)
	{
	SETGRAPHICSPOINTER(0,0,mousearrow);
	SETMOUSEXLIMIT(0,635);
	SETMOUSEYLIMIT(0,471);
	SETMOUSEMICKEYSRATIO(5,6);
	blank();
	}
//showmouse();
reset();
if(BUT_stay.isactive1() || BUT_bufcopy.isactive1())
	{
//	hidemouse();
	BUT_stay.deactivate();
	BUT_bufcopy.deactivate();
	BUT_bufcopydel.deactivate();
//	showmouse();
	}
showmouse();
if(!nomouse) blank2fade();
while(1)
	{
	what_button=0;
	if(current_mode==0 || current_mode==3)
		if(indic.isedit)
			{
			if(!BUT_stay.isactive1() || !BUT_bufcopy.isactive1())
				{
				hidemouse();
				BUT_stay.activate();
				BUT_bufcopy.activate();
				BUT_bufcopydel.activate();
				showmouse();
				}
			}
			else
			if(BUT_stay.isactive1() || BUT_bufcopy.isactive1())
				{
				hidemouse();
				BUT_stay.deactivate();
				BUT_bufcopy.deactivate();
				BUT_bufcopydel.deactivate();
				showmouse();
				}
	while(!Kbhit() && (nomouse || !ismouseevent()))
		{
		indic.scroll();
		nexttimertick=Gettimerticks()&4;
		if(lasttimertick!=nexttimertick)
			{
			lasttimertick=nexttimertick;
			indic.cursorflash();
			}
		}
	try
		{
		if(Kbhit())
			convertevent(receivekeyevent());
		if(!nomouse && ismouseevent())
			convertevent(receivemouseevent());
		}
		catch(int)
		{
		break;
		}
	}
fade2blank();
_DX=(unsigned)int1b;
_AX=(unsigned)(int1b>>16);
asm push ds
asm mov ds,ax
asm mov ah,25h
asm mov al,1bh
asm int 21h
asm pop ds
RESETMOUSE(numbuttons);
}

void terminate_func()
{
_DX=(unsigned)int1b;
_AX=(unsigned)(int1b>>16);
asm push ds
asm mov ds,ax
asm mov ah,25h
asm mov al,1bh
asm int 21h
asm pop ds
RESETMOUSE(numbuttons);
(*oldterm)();
}

void savestate(void)
{
int handle,i,morekey,old_mode,old_fl;
char name[13];
Strcpy(name,"calcpro?.sta",13);
_find_data buf;

old_mode=last_setstate_mode;
old_fl=last_setstate_fl;
last_mes=currentmessage;
hidemouse();
showmessage(message[28]);
setstate(7);
indic.hidecursor();
for(i=0;i<36;i++)
	{
	name[7]=i<10?i+'0':i+'a'-10;
	if(_findfirst(name,&buf))
		BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(12);
		else
		BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(9);
	Strcpy(name,"calcpro?.sta",13);
	BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->activate();
	}

input_again:
showmouse();
morekey=0;
while(1)
	{
	if(Kbhit())
		morekey=receivekeyevent();
	if(!nomouse && ismouseevent())
		morekey=receivemouseevent();
	if(morekey)
		{
		if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
		if(morekey==KEY_break)
			{
			hidemouse();
			for(i=0;i<36;i++)
				{
				BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(i<10?9:11);
				BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->deactivate();
				}
			showmouse();
			return;
			}
		if(morekey==KEY_esc)
			{
			hidemouse();
			if(last_mes)
				showmessage(message[last_mes]);
				else
				showmessage(num2str_buffer);
			for(i=0;i<36;i++)
				{
				BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(i<10?9:11);
				BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->deactivate();
				}
			setstate(old_mode,old_fl);
			indic.showcursor();
			showmouse();
			return;
			}
		if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_0 && morekey<=KEY_9))
			{
			name[7]=morekey;
			break;
			}
		}
	}
handle=_creat(name);
if(handle==-1)
	{
	hidemouse();
	showmessage(message[30]);
	goto input_again;
	}
//Strcpy(current_string,indic.gettext(),Strlen(indic.gettext())+1);
if(current_mode==0) mainstate=indic.getcursorstate();
try
	{
	_write(handle,&main_number,10);
	_write(handle,&Last_answer,10);
	_write(handle,&input_pointer,2);
	_write(handle,&current_mode,2);
	_write(handle,&current_len,2);
	_write(handle,&isinsert,2);
	_write(handle,&fix_num2,2);
	_write(handle,&fix_num8,2);
	_write(handle,&fix_num10,2);
	_write(handle,&fix_num16,2);
	_write(handle,&sci_num2,2);
	_write(handle,&sci_num8,2);
	_write(handle,&sci_num10,2);
	_write(handle,&sci_num16,2);
	_write(handle,&cur_str_system,2);
	_write(handle,&cur_ans_system,2);
	_write(handle,&cur_trig_str_system,2);
	_write(handle,&cur_trig_ans_system,2);
	_write(handle,&leftborder,10);
	_write(handle,&rightborder,10);
	_write(handle,&upborder,10);
	_write(handle,&downborder,10);
	_write(handle,&xscale,10);
	_write(handle,&yscale,10);
	_write(handle,&firstiter,4);
	_write(handle,&seconditer,4);
	_write(handle,main_string,STRING_LEN+1);
	_write(handle,main_flags,STRING_LEN+1);
	_write(handle,firstlowlimit_str,STRING_LEN+1);
	_write(handle,firstlowlimit_flag,STRING_LEN+1);
	_write(handle,firsthighlimit_str,STRING_LEN+1);
	_write(handle,firsthighlimit_flag,STRING_LEN+1);
	_write(handle,secondlowlimit_str,STRING_LEN+1);
	_write(handle,secondlowlimit_flag,STRING_LEN+1);
	_write(handle,secondhighlimit_str,STRING_LEN+1);
	_write(handle,secondhighlimit_flag,STRING_LEN+1);
	_write(handle,Indic_buffer,STRING_LEN+1);
	_write(handle,Indic_flags,STRING_LEN+1);
	_write(handle,&Indic_buffer_len,2);
	_write(handle,&mainstate,sizeof(CursorState));
	_write(handle,&graphstate[0],sizeof(CursorState));
	_write(handle,&graphstate[1],sizeof(CursorState));
	_write(handle,&graphstate[2],sizeof(CursorState));
	_write(handle,&graphstate[3],sizeof(CursorState));
	for(i=0;i<34;i++)
		{
		_write(handle,&variable[i],sizeof(memory_element));
		_write(handle,variable[i].string,STRING_LEN+1);
		_write(handle,variable[i].flags,STRING_LEN+1);
		}
	_write(handle,&multitude_len,4);
	_write(handle,&real_multitude_len,2);
	_write(handle,&isredraw,2);
	_write(handle,&deactive,2);
	_write(handle,&joinpoints,2);

	for(i=0;i<MULTITUDE_SIZE;i++)
		_write(handle,&multitude[i],sizeof(mul_element));
	}
	catch(int)
	{
	_close(handle);
	_delete(name);
	hidemouse();
	showmessage(message[31]);
	BUTTON_ARRAY[morekey>=KEY_0 && morekey<=KEY_9?morekey-KEY_0+BUT_INDEX_0:morekey-KEY_A+BUT_INDEX_A]->seticonscolors(9);
	BUTTON_ARRAY[morekey>=KEY_0 && morekey<=KEY_9?morekey-KEY_0+BUT_INDEX_0:morekey-KEY_A+BUT_INDEX_A]->draw();
	goto input_again;
	}
_close(handle);
hidemouse();
if(last_mes)
	showmessage(message[last_mes]);
	else
	showmessage(num2str_buffer);
for(i=0;i<36;i++)
	{
	BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(i<10?9:11);
	BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->deactivate();
	}
setstate(old_mode,old_fl);
indic.showcursor();
showmouse();
return;
}

int loadstate(void)
{
int handle,i,morekey,old_mode,old_fl;
char name[13];
Strcpy(name,"calcpro?.sta",13);
_find_data buf;

old_mode=last_setstate_mode;
old_fl=last_setstate_fl;
int last_mes=currentmessage;
hidemouse();
showmessage(message[29]);
setstate(7);
indic.hidecursor();
for(i=0;i<36;i++)
	{
	name[7]=i<10?i+'0':i+'a'-10;
	if(_findfirst(name,&buf))
		{
		BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(9);
		BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->activate();
		}
	Strcpy(name,"calcpro?.sta",13);
	}

input_again:
showmouse();
morekey=0;
while(1)
	{
	if(Kbhit())
		morekey=receivekeyevent();
	if(!nomouse && ismouseevent())
		morekey=receivemouseevent();
	if(morekey)
		{
		if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
		if(morekey==KEY_break)
			{
			hidemouse();
			for(i=0;i<36;i++)
				{
				BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(i<10?9:11);
				BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->deactivate();
				}
			showmouse();
			return 1;
			}
		if(morekey==KEY_esc)
			{
			hidemouse();
			if(last_mes)
				showmessage(message[last_mes]);
				else
				showmessage(num2str_buffer);
			for(i=0;i<36;i++)
				{
				BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(i<10?9:11);
				BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->deactivate();
				}
			setstate(old_mode,old_fl);
			indic.showcursor();
			showmouse();
			return 0;
			}
		if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_0 && morekey<=KEY_9))
			{
			name[7]=morekey;
			break;
			}
		}
	}
handle=_open(name);
if(handle==-1)
	{
	hidemouse();
	showmessage(message[32]);
	BUTTON_ARRAY[morekey>=KEY_0 && morekey<=KEY_9?morekey-KEY_0+BUT_INDEX_0:morekey-KEY_A+BUT_INDEX_A]->deactivate();
	goto input_again;
	}

if(filelength(handle)!=84914l)
	{
	hidemouse();
	showmessage(message[34]);
	BUTTON_ARRAY[morekey>=KEY_0 && morekey<=KEY_9?morekey-KEY_0+BUT_INDEX_0:morekey-KEY_A+BUT_INDEX_A]->deactivate();
	goto input_again;
	}
try
	{
	_read(handle,&main_number,10);
	_read(handle,&Last_answer,10);
	_read(handle,&input_pointer,2);
	_read(handle,&current_mode,2);
	_read(handle,&current_len,2);
	_read(handle,&isinsert,2);
	_read(handle,&fix_num2,2);
	_read(handle,&fix_num8,2);
	_read(handle,&fix_num10,2);
	_read(handle,&fix_num16,2);
	_read(handle,&sci_num2,2);
	_read(handle,&sci_num8,2);
	_read(handle,&sci_num10,2);
	_read(handle,&sci_num16,2);
	_read(handle,&cur_str_system,2);
	_read(handle,&cur_ans_system,2);
	_read(handle,&cur_trig_str_system,2);
	_read(handle,&cur_trig_ans_system,2);
	_read(handle,&leftborder,10);
	_read(handle,&rightborder,10);
	_read(handle,&upborder,10);
	_read(handle,&downborder,10);
	_read(handle,&xscale,10);
	_read(handle,&yscale,10);
	_read(handle,&firstiter,4);
	_read(handle,&seconditer,4);
	_read(handle,main_string,STRING_LEN+1);
	_read(handle,main_flags,STRING_LEN+1);
	_read(handle,firstlowlimit_str,STRING_LEN+1);
	_read(handle,firstlowlimit_flag,STRING_LEN+1);
	_read(handle,firsthighlimit_str,STRING_LEN+1);
	_read(handle,firsthighlimit_flag,STRING_LEN+1);
	_read(handle,secondlowlimit_str,STRING_LEN+1);
	_read(handle,secondlowlimit_flag,STRING_LEN+1);
	_read(handle,secondhighlimit_str,STRING_LEN+1);
	_read(handle,secondhighlimit_flag,STRING_LEN+1);
	_read(handle,Indic_buffer,STRING_LEN+1);
	_read(handle,Indic_flags,STRING_LEN+1);
	_read(handle,&Indic_buffer_len,2);
	_read(handle,&mainstate,sizeof(CursorState));
	_read(handle,&graphstate[0],sizeof(CursorState));
	_read(handle,&graphstate[1],sizeof(CursorState));
	_read(handle,&graphstate[2],sizeof(CursorState));
	_read(handle,&graphstate[3],sizeof(CursorState));
	char *tempptr1,*tempptr2;
	for(i=0;i<34;i++)
		{
		tempptr1=variable[i].string;
		tempptr2=variable[i].flags;
		_read(handle,&variable[i],sizeof(memory_element));
		variable[i].string=tempptr1;
		variable[i].flags=tempptr2;
		_read(handle,variable[i].string,STRING_LEN+1);
		_read(handle,variable[i].flags,STRING_LEN+1);
		}
	_read(handle,&multitude_len,4);
	_read(handle,&real_multitude_len,2);
	_read(handle,&isredraw,2);
	_read(handle,&deactive,2);
	_read(handle,&joinpoints,2);

	for(i=0;i<MULTITUDE_SIZE;i++)
		_read(handle,&multitude[i],sizeof(mul_element));
	}
	catch(int)
	{
	_close(handle);
	hidemouse();
	showmessage(message[33]);
	BUTTON_ARRAY[morekey>=KEY_0 && morekey<=KEY_9?morekey-KEY_0+BUT_INDEX_0:morekey-KEY_A+BUT_INDEX_A]->deactivate();
	goto input_again;
	}
_close(handle);
hidemouse();
for(i=0;i<36;i++)
	{
	BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->seticonscolors(i<10?9:11);
	BUTTON_ARRAY[i<10?i+BUT_INDEX_0:i+BUT_INDEX_A-10]->deactivate();
	}
current_string=main_string;
current_flags=main_flags;
current_number=&main_number;
Counterror=FPUerror=0;
ishelp=0;
drawvariables();
showsystems();
if(current_mode==0)
	{
	showcurrentstring(mainstate,0);
	showonlymessage(1);
	}
	else
	{
	shownumonindic(main_number,cur_ans_system,1);
	showonlymessage(2);
	}
showmouse();
return 1;
}

