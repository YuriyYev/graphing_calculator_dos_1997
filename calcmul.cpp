#include "..\express\mymouse.hpp"
#include "..\express\graph18.hpp"
#include "..\express\common.hpp"
#include "..\express\calcbut.hpp"
#include "..\express\calcedl.hpp"

extern Calc_indicator indic;

#ifndef __symbol__
struct symbol
{
int xsize,ysize;//Размер символа
unsigned char *buf;//Изображение символа
};
#define __symbol__
#endif

enum systems {DECSYS=10,HEXSYS=16,OCTSYS=8,BINSYS=2};
enum trig_systems {RAD=32,DEG=64,GRD=96};

extern systems cur_str_system,cur_ans_system;
extern trig_systems cur_trig_str_system;


extern symbol S_KEY_MUL_get;
extern symbol S_KEY_MUL_clear;
extern symbol S_KEY_MUL_del;
extern symbol S_KEY_MUL_copy;
extern symbol S_KEY_MUL_ins;
extern symbol S_KEY_MUL_quit;
extern char *mousearrowquest,*mousearrow;
extern symbol SYM_QUESTION;
void helpon(int);


extern int MULTITUDE_SIZE;
extern int STRING_LEN;

#define KEY_no              0
#define KEY_exit            0x123
#define KEY_mulinsert     	0x160
#define KEY_mulclear      	0x161
#define KEY_mulleftcur    	0x162
#define KEY_mulrightcur   	0x163
#define KEY_mulupcur   		0x164
#define KEY_muldowncur  	0x165
#define KEY_mulleftend    	0x166
#define KEY_mulrightend   	0x167
#define KEY_mulquit         0x168
#define KEY_muldel          0x169
#define KEY_mulcopy         0x16a
#define KEY_get             0x16b
#define KEY_mulhelplock     0x16c

struct mul_element
{
int isvar;
int var;
long double number;
};

struct memory_element
{
int isstring;
int ison,iserror;
long double number,newnumber;
char *string,*flags;
};

void drawconsol(int);
void drawvariables(void);
int convert_number2string(long double,int,int=0);
void drawallkeys(void);
void hidemouse(void);
void showmouse(void);
void Putsymbol(symbol *,int,int,int,int,int=0);
int Putstring(int,int,char *,int,int);
void showcurrentstring(CursorState,int);
void shownumonindic(long double,int,int);

extern CursorState mainstate,graphstate[];
extern	_MouseEvent mev;
extern	Graph18 mygr;
extern	int what_button,nomouse;
extern	char *num2str_buffer,*Error_messages[];
extern	mul_element *multitude;
extern	memory_element *variable;
extern	unsigned char *current_string,*current_flags,*main_string,*main_flags;
extern	int current_len,input_pointer,graph_mode;
extern	long double main_number,*current_number;
extern	int current_mode,last_input_pointer,Counterror,last_mode,real_multitude_len;
extern  symbol *asciisymboltable[];
extern unsigned long multitude_len;


Calc_2button BUT_clearmul(0,360,457,43,18,KEY_mulclear,0,&S_KEY_MUL_clear,0,15,0);
Calc_2button BUT_copy(0,403,457,54,18,KEY_mulcopy,0,&S_KEY_MUL_copy,0,15,0);
Calc_2button BUT_insertelem(0,457,457,43,18,KEY_mulinsert,0,&S_KEY_MUL_ins,0,15,0);
Calc_2button BUT_delelem(0,500,457,41,18,KEY_muldel,0,&S_KEY_MUL_del,0,15,0);
Calc_2button BUT_getelem(0,541,457,29,18,KEY_get,0,&S_KEY_MUL_get,0,15,0);
Calc_2button BUT_quitmul(0,570,457,33,18,KEY_mulquit,0,&S_KEY_MUL_quit,0,15,0);
Calc_2button BUT_mulhelplock(0,603,457,18,18,KEY_mulhelplock,0,&SYM_QUESTION,0,15,15,7,1);


int cur_elem,copy_type,copy_var,ismulhelp,wasinsert;
long double copy_num;
//void changecolor(int left,int up,int right,int down,int scol,int dcol)
//{
//for(int y=up;y<=down;y++)
//	for(int x=left;x<=right;x++)
//		if(mygr.getpixel(x,y)==scol) mygr.putpixel(x,y,dcol);
//}

void get_coord(int el,int& x,int& y,int& endx,int& endy)
{
x=(el/(MULTITUDE_SIZE/3))*208+12;
y=(el%(MULTITUDE_SIZE/3))*12+4;
endx=(el/(MULTITUDE_SIZE/3)+1)*208-1;
endy=y+12-1;
}

void showindex(void)
{
int xc=324;
if(real_multitude_len>0)
	{
	num2str_buffer[int2string_dec(cur_elem,num2str_buffer)]='\0';
	xc=Putstring(xc,458,num2str_buffer,15,7);
	}
if(xc<348-1) mygr.drawfilledbox(xc,458,348-1,458+11,7);
}

void showbuffer(void)
{
if(!copy_type) return;
int xc=60;
if(copy_type==1)
	{
	Putsymbol(asciisymboltable['A'+copy_var],xc,458,15,7);
	xc+=8;
	}
	else
	{
	convert_number2string(copy_num,DECSYS,2);
	if(num2str_buffer[0]=='+') xc=Putstring(xc,458,num2str_buffer+1,15,7);
		else xc=Putstring(xc,458,num2str_buffer,15,7);
	}
if(xc<260-1) mygr.drawfilledbox(xc,458,260-1,458+11,7);
}

void drawelement(int el,int col=0,int bcol=7)
{
if(el>=real_multitude_len || el<0) return;
int x,y,endx,endy;
get_coord(el,x,y,endx,endy);
if(multitude[el].isvar)
	{
	Putsymbol(asciisymboltable['A'+multitude[el].var],x,y,col,bcol);
	x+=8;
	}
	else
	{
	convert_number2string(multitude[el].number,DECSYS,2);
	if(num2str_buffer[0]=='+') x=Putstring(x,y,num2str_buffer+1,col,bcol);
		else x=Putstring(x,y,num2str_buffer,col,bcol);
	}
if(endx>x) mygr.drawfilledbox(x,y,endx,endy,bcol);
}

void showcur(void)
{
drawelement(cur_elem,0,15);
}

void hidecur(void)
{
drawelement(cur_elem,0,7);
}

//void changeelem(int el,int dc)
//{
//int xc,yc,exc,eyc;
//get_coord(el,xc,yc,exc,eyc);
//changecolor(xc,yc,exc,eyc,sc,dc);
//drawelement(el,dc,7);
//}

int receivemulkeyevent(void)
{
unsigned int keycode,keychar,keystatus;//,capslockon;
keystatus=Getkeyboardflags();
//if(keychar&KBS_CAPSLOCKON) capslockon=1;
keycode=Getkey();
keychar=keycode&255;
keycode>>=8;

if(keychar==224)
	{
	if(keycode==75) return KEY_mulleftcur;
	if(keycode==77) return KEY_mulrightcur;
	if(keycode==72) return KEY_mulupcur;
	if(keycode==80) return KEY_muldowncur;
	if(keycode==71) return KEY_mulleftend;
	if(keycode==79) return KEY_mulrightend;
	if(keycode==82) return KEY_mulinsert;
	if(keycode==83) return KEY_muldel;
	}
if(keychar==27 && keycode==1) return KEY_mulquit;
if(keychar==13 && (keycode==28 || keycode==224) && !(keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))) return KEY_mulcopy;
if(keychar==10 && (keycode==28 || keycode==224) && !(keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))) return KEY_get;
if(keychar==0 && keycode==14) return KEY_mulclear;
if(keychar==0 && keycode==45) return KEY_exit;
if(keychar==0 && keycode==59) return KEY_mulhelplock;
return KEY_no;
}

int receivemulmouseevent(void)
{
mev=getmouseevent();
int x=mev.xcoord;
int y=mev.ycoord;
what_button=KEY_no;
if(mev.event&ME_LEFTPRESSED)
	if(x<636 && x>=12 && y<(MULTITUDE_SIZE/3)*12+4 && y>=4)
		{
		int el=((x-12)/208)*(MULTITUDE_SIZE/3)+(y-4)/12;
		if(el>=real_multitude_len) el=real_multitude_len-1;
		if(el<0 && real_multitude_len>0) el=0;
		if(el!=cur_elem)
			{
			hidemouse();
			hidecur();
			cur_elem=el;
			showcur();
			showindex();
			showmouse();
			}
		return KEY_no;
		}
if(BUT_mulhelplock.event()) goto endkey;
if(BUT_clearmul.event(ismulhelp)) goto endkey;
if(BUT_delelem.event(ismulhelp)) goto endkey;
if(BUT_copy.event(ismulhelp)) goto endkey;
if(BUT_insertelem.event(ismulhelp)) goto endkey;
if(BUT_quitmul.event(ismulhelp)) goto endkey;
if(BUT_getelem.event(ismulhelp)) goto endkey;
endkey:
if(what_button==KEY_mulhelplock)
	{
	ismulhelp=!ismulhelp;
	if(ismulhelp) BUT_mulhelplock.push();
		else
		BUT_mulhelplock.draw();
	hidemouse();
	if(ismulhelp)
		SETGRAPHICSPOINTER(0,0,mousearrowquest);
		else
		SETGRAPHICSPOINTER(0,0,mousearrow);
	showmouse();
	return 1;
	}
if(what_button>32000)
	{
	if(!ismulhelp)
		helpon(what_button-32000);
	return KEY_no;
	}
if(ismulhelp)
	{helpon(what_button);return 1;}
return what_button;
}

int convertmulevent(int key)
{
if(key==KEY_no) return 1;
//if(key==KEY_exit)
//	{
//	Pushkey(0,45);
//	return 0;
//	}
if(key==KEY_get && cur_elem>=0)
	{
	int i=0,len;
	if(multitude[cur_elem].isvar)
		len=convert_number2string(variable[multitude[cur_elem].var].number,cur_str_system,2);
		else
		len=convert_number2string(multitude[cur_elem].number,cur_str_system,2);
	if(num2str_buffer[0]=='+') i++;
	len-=i;
	if(current_len+len>STRING_LEN) return 1;
	Insstr(current_string+input_pointer,num2str_buffer+i,current_len-input_pointer+1,len);
	for(i=0;i<len;i++)
		{
		current_flags[input_pointer+i+len]=current_flags[input_pointer+i];
		current_flags[input_pointer+i]=cur_trig_str_system|cur_str_system;
		}
	current_len+=len;
	input_pointer+=len;
	if(current_mode!=1)
		{
		indic.settext(current_string);
		indic.setcursorposition(input_pointer);
		}
//	if(current_mode==0)
//		mainstate=indic.getcursorstate();
//		else
//		graphstate[graph_mode]=indic.getcursorstate();
	}
if(key==KEY_mulclear)
	{
	multitude_len=0;
	real_multitude_len=0;
	cur_elem=-1;
	hidemouse();
	mygr.drawfilledbox(12,4,208-8+12-1,(MULTITUDE_SIZE/3)*12+4-1,7);
	mygr.drawfilledbox(12+208,4,416-8+12-1,(MULTITUDE_SIZE/3)*12+4-1,7);
	mygr.drawfilledbox(12+416,4,624-8+12-1,(MULTITUDE_SIZE/3)*12+4-1,7);
	showindex();
//	showcur();
//	copy_type=0;
//	BUT_insertelem.deactivate(1);
	showmouse();
	return 1;
	}
if(key==KEY_mulcopy && real_multitude_len>=0)
	{
	if(multitude[cur_elem].isvar)
		{
		copy_type=1;
		copy_var=multitude[cur_elem].var;
		}
		else
		{
		copy_type=2;
		copy_num=multitude[cur_elem].number;
		}
	hidemouse();
	showbuffer();
	BUT_insertelem.activate();
	showmouse();
	return 1;
	}
if(key==KEY_muldel && real_multitude_len>0)
	{
	int col=15;
	for(int i=cur_elem;i<real_multitude_len-1;i++)
		{
		multitude[i].isvar=multitude[i+1].isvar;
		multitude[i].var=multitude[i+1].var;
		multitude[i].number=multitude[i+1].number;
		drawelement(i,0,col);
		col=7;
		}
	real_multitude_len--;
	multitude_len--;
	int x,y,ex,ey;
	get_coord(real_multitude_len,x,y,ex,ey);
	hidemouse();
	mygr.drawfilledbox(x,y,ex,ey,7);
	if(cur_elem==real_multitude_len)
		{
		cur_elem--;
		showcur();
		showindex();
		if(cur_elem==-1)
			{
			BUT_clearmul.deactivate();
			BUT_delelem.deactivate();
			BUT_copy.deactivate();
			BUT_getelem.deactivate();
			}
		}
	showmouse();
	return 1;
	}
if(key==KEY_mulinsert && copy_type && real_multitude_len<MULTITUDE_SIZE)
	{
	real_multitude_len++;
	multitude_len++;
	if(cur_elem<0)
		{
		cur_elem=0;
		BUT_delelem.activate();
		BUT_copy.activate();
		BUT_getelem.activate();
		}
	for(int i=real_multitude_len-1;i>cur_elem;i--)
		{
		multitude[i].isvar=multitude[i-1].isvar;
		multitude[i].var=multitude[i-1].var;
		multitude[i].number=multitude[i-1].number;
		drawelement(i);
		}
	if(copy_type==1)
		{
		multitude[cur_elem].isvar=1;
		multitude[cur_elem].var=copy_var;
		}
		else
		{
		multitude[cur_elem].isvar=0;
		multitude[cur_elem].number=copy_num;
		}
	hidemouse();
	showcur();
	if(!cur_elem) showindex();
	showmouse();
	return 1;
	}
if(key==KEY_mulleftcur)
	if(cur_elem>0)
		{
		hidemouse();
		hidecur();
		cur_elem-=MULTITUDE_SIZE/3;
		if(cur_elem<0) cur_elem=0;
		showcur();
		showindex();
		showmouse();
		return 1;
		}
if(key==KEY_mulleftend)
	if(cur_elem>0)
		{
		hidemouse();
		hidecur();
		cur_elem=0;
		showcur();
		showindex();
		showmouse();
		return 1;
		}
if(key==KEY_mulrightcur)
	if(cur_elem<real_multitude_len-1)
		{
		hidemouse();
		hidecur();
		cur_elem+=MULTITUDE_SIZE/3;
		if(cur_elem>=real_multitude_len) cur_elem=real_multitude_len-1;
		showcur();
		showindex();
		showmouse();
		return 1;
		}
if(key==KEY_mulrightend)
	if(cur_elem<real_multitude_len-1)
		{
		hidemouse();
		hidecur();
		cur_elem=real_multitude_len-1;
		showcur();
		showindex();
		showmouse();
		return 1;
		}
if(key==KEY_mulupcur)
	if(cur_elem>0)
		{
		hidemouse();
		hidecur();
		cur_elem--;
		showcur();
		showindex();
		showmouse();
		return 1;
		}
if(key==KEY_muldowncur)
	if(cur_elem<real_multitude_len-1)
		{
		hidemouse();
		hidecur();
		cur_elem++;
		showcur();
		showindex();
		showmouse();
		return 1;
		}
if(key==KEY_mulquit) return 0;
if(key==KEY_exit)
	throw int(0);
//	{
//	Pushkey(0,45);
//	return 0;
//	}
return 1;
}

int drawmultitude(void)
{
ismulhelp=0;
wasinsert=0;
hidemouse();
mygr.drawfilledbox(1,1,638,478,7);
mygr.drawtwocoloredbox(0,0,639,479,15,8);
mygr.drawyline(1,451-1,12-8+3,8);
mygr.drawyline(1,452-1,12-8+4,15);
mygr.drawyline(1,451-1,208+12-8+3,8);
mygr.drawyline(1,452-1,208+12-8+4,15);
mygr.drawyline(1,451-1,416+12-8+3,8);
mygr.drawyline(1,452-1,416+12-8+4,15);
mygr.drawyline(1,451-1,624+12-8+3,8);
mygr.drawyline(1,452-1,624+12-8+4,15);
mygr.drawxline(1,638,448+3,8);
mygr.drawxline(1,638,448+4,15);
Putstring(12,458,"Буфер:",15,7);
Putstring(268,458,"Индекс:",15,7);
BUT_clearmul.draw();
BUT_delelem.draw();
BUT_copy.draw();
BUT_insertelem.draw();
BUT_insertelem.deactivate();
BUT_quitmul.draw();
BUT_getelem.draw();
BUT_mulhelplock.draw();
for(int i=0;i<real_multitude_len;i++)
	drawelement(i);
if(real_multitude_len==0)
	{
	cur_elem=-1;
	BUT_clearmul.deactivate();
	BUT_delelem.deactivate();
	BUT_copy.deactivate();
	BUT_getelem.deactivate();
	}
	else
	{
	cur_elem=0;
	BUT_clearmul.activate();
	BUT_delelem.activate();
	BUT_copy.activate();
	BUT_getelem.activate();
	}
copy_type=0;
showindex();
showcur();
showmouse();
while(1)
{
what_button=0;
while(!Kbhit() && (nomouse || !ismouseevent()));
if(Kbhit())
	if(!convertmulevent(receivemulkeyevent())) break;
if(!nomouse && ismouseevent())
	if(!convertmulevent(receivemulmouseevent())) break;
}
//if(Kbhit())
//	if(receivemulkeyevent()==KEY_exit) return 0;
//indic.settext(Error_messages[0]);
hidemouse();
drawconsol(1);
//indic.hidemouse_ind();
indic.activate();
drawallkeys();
drawvariables();
showmouse();
//if(current_mode==0)
//	showcurrentstring(mainstate,0);
//	else if(current_mode==3)
//			showcurrentstring(graphstate[graph_mode],3);
//			else shownumonindic(main_number,cur_ans_system,1);
return 1;
}





