#include "..\express\mymouse.hpp"
#include "..\express\graph18.hpp"
#include "..\express\common.hpp"
#include "..\express\calcedl.hpp"
#include "..\express\calcbut.hpp"
#include "..\express\fpu.hpp"

#ifndef __symbol__
struct symbol
{
int xsize,ysize;//Размер символа
unsigned char *buf;//Изображение символа
};
#define __symbol__
#endif

extern symbol S_KEY_GRAPH_movescrleft;
extern symbol S_KEY_GRAPH_movescrright;
extern symbol S_KEY_GRAPH_movescrup;
extern symbol S_KEY_GRAPH_movescrdown;
extern symbol S_KEY_GRAPH_movewallleft;
extern symbol S_KEY_GRAPH_movewallleftright;
extern symbol S_KEY_GRAPH_movewallright;
extern symbol S_KEY_GRAPH_movewallrightleft;
extern symbol S_KEY_GRAPH_movewallup;
extern symbol S_KEY_GRAPH_movewallupdown;
extern symbol S_KEY_GRAPH_movewalldown;
extern symbol S_KEY_GRAPH_movewalldownup;
extern symbol S_KEY_GRAPH_xexpand;
extern symbol S_KEY_GRAPH_xcompress;
extern symbol S_KEY_GRAPH_yexpand;
extern symbol S_KEY_GRAPH_ycompress;
extern symbol S_KEY_GRAPH_expand;
extern symbol S_KEY_GRAPH_compress;
extern symbol S_KEY_GRAPH_eval;
extern symbol S_KEY_GRAPH_evalrev;
extern symbol S_KEY_GRAPH_draw;
extern symbol S_KEY_GRAPH_clear;
extern symbol S_KEY_GRAPH_cont;
extern symbol S_KEY_GRAPH_center;
extern symbol S_KEY_GRAPH_stop;
extern symbol S_KEY_GRAPH_step;
extern symbol S_KEY_GRAPH_quit;
extern symbol S_KEY_GRAPH_save;
extern symbol S_KEY_GRAPH_preview;
extern symbol S_KEY_GRAPH_isrows;
extern symbol S_KEY_GRAPH_isgrid;
extern symbol SYM_QUESTION;

extern symbol *asciisymboltable[];

#define KEY_no				0x00
#define KEY_e 			0xb3
#define KEY_leftcur    	0x11c
#define KEY_rightcur   	0x11d
#define KEY_leftend    	0x120
#define KEY_rightend   	0x121
#define KEY_del      	0x114
#define KEY_bs      	0x115
#define KEY_exit     		0x123
#define KEY_movescrleft     0x134
#define KEY_movescrright    0x135
#define KEY_movescrup       0x136
#define KEY_movescrdown     0x137
#define KEY_movewallleft    0x138
#define KEY_movewallleftright	0x139
#define KEY_movewallright   0x13a
#define KEY_movewallrightleft   0x13b
#define KEY_movewallup      0x13c
#define KEY_movewallupdown      0x13d
#define KEY_movewalldown    0x13e
#define KEY_movewalldownup      0x13f
#define KEY_xexpand         0x140
#define KEY_xcompress           0x141
#define KEY_yexpand         0x142
#define KEY_ycompress           0x143
#define KEY_expand          0x144
#define KEY_compress            0x145
#define KEY_eval            0x146
#define KEY_evalrev         0x147
#define KEY_draw            0x148
#define KEY_stop            0x149
#define KEY_step            0x14a
#define KEY_quit            0x14b

#define KEY_join            0x14d
#define KEY_onlyvw          0x14e
#define KEY_onlyxy          0x14f
#define KEY_move            0x150
#define KEY_cont     		0x158
#define KEY_graphclear     		0x159
#define KEY_center   	  	0x15a
#define KEY_expandcenterscreen 0x15b
#define KEY_centerscreen 0x15c
#define KEY_graphhelplock            0x15d
#define KEY_graphsave            0x15e
#define KEY_graphrowslock        0x15f
#define KEY_redraw				0x17b
#define KEY_graphgridlock		0x17c
#define KEY_auto				0x17d
#define KEY_preview				0x17e
#define KEY_compresscenterscreen 0x17f
#define KEY_scalehelp		0x181
#define KEY_iterhelp		0x182
#define KEY_gridstephelp  	0x183

struct memory_element
{
int isstring;
int ison,iserror;
long double number,newnumber;
char *string,*flags;
};


void drawconsol(int);
long double countstring(char *,char *);
void drawvariables(void);
int convert_number2string(long double,int,int);
void recountvariables(int);
void showerrormessage(void);
void drawallkeys(void);
void hidemouse(void);
void showmouse(void);
void Putsymbol(symbol *,int,int,int,int,int=0);
void showcurrentstring(CursorState,int);
void shownumonindic(long double,int,int);
void helpon(int);
void waitvsync();
void drawmainview(void);

extern CursorState mainstate,graphstate[];
extern	_MouseEvent mev;
extern	Graph18 mygr;
extern	int what_button,nomouse;
extern	Calc_indicator indic;
extern	char *num2str_buffer,*Error_messages[];
extern	memory_element *variable;
extern	unsigned char *current_string,*current_flags,*main_string,*main_flags;
extern	long double firstlowlimit,secondlowlimit,firsthighlimit,secondhighlimit;
extern	int current_len,input_pointer;
extern	long double far main_number,*current_number;
extern	int current_mode,last_input_pointer,Counterror,prev_mode;
extern char *mousearrowquest,*mousearrow;

enum systems {DECSYS=10,HEXSYS=16,OCTSYS=8,BINSYS=2};
enum trig_systems {RAD=32,DEG=64,GRD=96};
extern systems cur_ans_system;


//#include"calc.hpp"

long double leftborder,rightborder,upborder,downborder;
long double xscale,yscale,xgridstep,ygridstep;
unsigned long firstiter,seconditer,firstworkiter,secondworkiter;
char joinpoints,deactive,isredraw,isauto;
long double firstworking,secondworking,firstscale,secondscale;
//long double firststep,secondstep;
int firststate,secondstate,firstsize,secondsize,firstrev,secondrev;
Editline *activeinputline,*visualscale,*visualiter,*visualgridstep;
int forkeepingerror[34],firstlastx,firstlasty,secondlastx,secondlasty,firstislast,secondislast;
long double forkeeping[34];
int leftshow,rightshow,iserrormessage;
char *alltext[]={"X координата=","Текущая итерация для VW=","Текущее V=","Текущее W=",
"Левый предел=","Правый предел=","Верхний предел=","Нижний предел=","Y координата=",
"Текущая итерация для XY=","Текущее X=","Текущее Y="};
char *switchtext[6]={"X шаг сетки=","Y шаг сетки=","X масштаб=","Y масштаб=",
"Количество итераций для XY=","Количество итераций для VW="};
int xgridsteplen=96,ygridsteplen=96;
int alllen[]={104,192,80,80,104,112,120,112,104,192,80,80};
void *allnumbers[]={0,&firstworkiter,&firstworking,&firstworking,&leftborder,
&rightborder,&upborder,&downborder,0,&secondworkiter,&secondworking,&secondworking};

int countrepeat,isgraphhelp,isrows=1,isgrid=0,wasxscalein,wasyscalein;
int wasxyiterin,wasvwiterin,wasxgridstepin,wasygridstepin;

int ispreview,xscrsize,yscrsize;
unsigned long lasttimerticks;

Editline X_scale(87,414,23,"",11,0);
Editline Y_scale(87/*373*/,414,23,"",11,0);
Editline X_Gridstep(381,414,23,"",11,0);
Editline Y_Gridstep(381,414,23,"",11,0);
Editline VW_iter(223,434,10,"",11,0);
Editline XY_iter(223/*349*/,434,10,"",11,0);
System_field Join(625,417,12,12,KEY_join,12,7);
System_field Only_VW(520-8,437,12,12,KEY_onlyvw,12,7);
System_field Only_XY(625,437,12,12,KEY_onlyxy,12,7);
System_field Redraw(625,457,12,12,KEY_redraw,12,7);
System_field Autogrid(402,437,12,12,KEY_auto,12,7);
#define m0 1
#define m1 2
#define mm0 128
#define mm1 512

Calc_2button far BUT_graphhelplock(m0,602,2,18,18,KEY_graphhelplock,0,&SYM_QUESTION,0,15,15,7,1);
Calc_2button far BUT_graphrowslock(m0,620,2,18,18,KEY_graphrowslock,0,&S_KEY_GRAPH_isrows,0,15,15,7,1);
Calc_2button far BUT_graphgridlock(m0,177,457,18,18,KEY_graphgridlock,0,&S_KEY_GRAPH_isgrid,0,15,15,7,1);

Calc_2button far BUT_movescrleft(m0,602,22,36,18,KEY_movescrleft,0,&S_KEY_GRAPH_movescrleft,0,15,0);
Calc_2button far BUT_movescrright(m0,602,40,36,18,KEY_movescrright,0,&S_KEY_GRAPH_movescrright,0,15,0);
Calc_2button far BUT_movescrup(m0,602,60,36,18,KEY_movescrup,0,&S_KEY_GRAPH_movescrup,0,15,0);
Calc_2button far BUT_movescrdown(m0,602,78,36,18,KEY_movescrdown,0,&S_KEY_GRAPH_movescrdown,0,15,0);
Calc_2button far BUT_movewallleft(m0,602,98,36,18,KEY_movewallleft,0,&S_KEY_GRAPH_movewallleft,0,15,0);
Calc_2button far BUT_movewallleftright(m0,602,116,36,18,KEY_movewallleftright,0,&S_KEY_GRAPH_movewallleftright,0,15,0);

Calc_2button far BUT_movewallright(m0,602,136,36,18,KEY_movewallright,0,&S_KEY_GRAPH_movewallright,0,15,0);
Calc_2button far BUT_movewallrightleft(m0,602,154,36,18,KEY_movewallrightleft,0,&S_KEY_GRAPH_movewallrightleft,0,15,0);
Calc_2button far BUT_movewallup(m0,602,174,36,18,KEY_movewallup,0,&S_KEY_GRAPH_movewallup,0,15,0);
Calc_2button far BUT_movewallupdown(m0,602,192,36,18,KEY_movewallupdown,0,&S_KEY_GRAPH_movewallupdown,0,15,0);
Calc_2button far BUT_movewalldown(m0,602,212,36,18,KEY_movewalldown,0,&S_KEY_GRAPH_movewalldown,0,15,0);
Calc_2button far BUT_movewalldownup(m0,602,230,36,18,KEY_movewalldownup,0,&S_KEY_GRAPH_movewalldownup,0,15,0);

Calc_2button far BUT_xexpand(m0,602,250,36,18,KEY_xexpand,0,&S_KEY_GRAPH_xexpand,0,15,0);
Calc_2button far BUT_xcompress(m0,602,268,36,18,KEY_xcompress,0,&S_KEY_GRAPH_xcompress,0,15,0);
Calc_2button far BUT_yexpand(m0,602,288,36,18,KEY_yexpand,0,&S_KEY_GRAPH_yexpand,0,15,0);
Calc_2button far BUT_ycompress(m0,602,306,36,18,KEY_ycompress,0,&S_KEY_GRAPH_ycompress,0,15,0);
Calc_2button far BUT_expand(m0,602,326,36,18,KEY_expand,0,&S_KEY_GRAPH_expand,0,15,0);
Calc_2button far BUT_compress(m0,602,344,36,18,KEY_compress,0,&S_KEY_GRAPH_compress,0,15,0);
Calc_2button far BUT_eval(m0,602,364,36,18,KEY_eval,0,&S_KEY_GRAPH_eval,0,15,0);
Calc_2button far BUT_evalrev(m0,602,382,36,18,KEY_evalrev,0,&S_KEY_GRAPH_evalrev,0,15,0);

Calc_2button far BUT_quit(m0+m1,4,457,45,18,KEY_quit,0,&S_KEY_GRAPH_quit,0,15,0);
Calc_2button far BUT_preview(m0,54,457,47,18,KEY_preview,0,&S_KEY_GRAPH_preview,0,15,0);
Calc_2button far BUT_save(m0,200,457,45,18,KEY_graphsave,0,&S_KEY_GRAPH_save,0,15,0);
Calc_2button far BUT_center(m0,250,457,45,18,KEY_center,0,&S_KEY_GRAPH_center,0,15,0);
Calc_2button far BUT_clear_graph(m0,300,457,45,18,KEY_graphclear,0,&S_KEY_GRAPH_clear,0,15,0);
Calc_2button far BUT_step(m0,350,457,45,18,KEY_step,0,&S_KEY_GRAPH_step,0,15,0);
Calc_2button far BUT_cont(m0,400,457,45,18,KEY_cont,0,&S_KEY_GRAPH_cont,0,15,0);
Calc_2button far BUT_stop(m1,450,457,45,18,KEY_stop,0,&S_KEY_GRAPH_stop,0,15,0);
Calc_2button far BUT_draw(m0,500,457,45,18,KEY_draw,0,&S_KEY_GRAPH_draw,0,15,0);


long double string2double(char *str)
{
long double temper=0,ap=0,wok=10,exp=0;
unsigned char digit,nextchar;
int pointer=0,isin=0,numdigits=0,sign=0;

nextchar=str[pointer++];
if(!nextchar) return 1;
if(nextchar=='-')
	{
	sign=1;
	nextchar=str[pointer++];
	}

do
{
	if(nextchar==',')
		if(!isin) isin++;
	if(nextchar>='0' && nextchar<='9' && isin<2)// && numdigits<=16)
		{
		digit=nextchar-48;
		if(!isin)
			temper=FPU_add(FPU_mul(temper,10.0),digit);
			else
			{
			ap=FPU_add(ap,FPU_div(digit,wok));
			wok*=10;
			}
//		numdigits++;
		}

	if(nextchar=='-' && isin==2)
		isin=3;
	if(nextchar>='0' && nextchar<='9' && isin>1)// && exp<500)
		{
		exp=FPU_add(FPU_mul(exp,10),nextchar-48);
		if(isin==2) isin=4;
		}
	if(FPUerror) break;
	if(nextchar=='E' && isin<2)
		{
		isin=2;
		}
	nextchar=str[pointer++];
} while(nextchar);
temper=FPUadd(temper,ap);
if(isin==3) exp=-exp;
ap=FPU_power(10,exp);
temper=FPUmul(temper,ap);
if(FPUerror)
	{
	if(FPUerror==1)
		{
		FPUerror=0;
		temper=1.0e4900;
		}
		else
			{
			FPUerror=0;
			temper=1;
			}
	}
//if(temper>1e4500) temper=1e4500;
//if(temper<1e-4500) temper=1e-4500;
if(sign) temper=-temper;
return temper;
}

int convert_round(long double &num)
{
int res=convert_number2string(num,DECSYS,3);
for(int i=0;i<res;i++)
	if(num2str_buffer[i]==KEY_e)
		num2str_buffer[i]='E';
num=string2double(num2str_buffer);
return res;
}

int Putstring(int xc,int yc,char *ptr,int fc,int bc)
{
for(;*ptr;ptr++)
	{
	if(*ptr==KEY_e)
		Putsymbol(asciisymboltable['E'],xc,yc,fc,bc);
		else
		Putsymbol(asciisymboltable[*ptr],xc,yc,fc,bc);
	xc+=8;
	}
return xc;
}

void showoptions(void)
{
if(ispreview) return;
if(joinpoints) Join.turn_on();
	else Join.turn_off();
if(isredraw) Redraw.turn_on();
	else Redraw.turn_off();
if(isauto) Autogrid.turn_on();
	else Autogrid.turn_off();
if(deactive)
	if(deactive==1)
		{
		Only_XY.turn_on();
		Only_VW.turn_off();
		}
		else
		{
		Only_XY.turn_off();
		Only_VW.turn_on();
		}
	else
	{
	Only_XY.turn_off();
	Only_VW.turn_off();
	}
}


void showonleft(int textnum,long double &num)
{
if(ispreview) return;
hidemouse();
//SETMOUSEEXLUSIONAREA(3,401,319,412);
if(leftshow!=textnum)
	{
	Putstring(3,401,alltext[textnum],15,7);
	leftshow=textnum;
	}
convert_round(num);
convert_number2string(num,DECSYS,4);
char *ptr=num2str_buffer;
if(*ptr=='+') ptr++;
mygr.drawfilledbox(Putstring(alllen[textnum]+3,401,ptr,15,7),401,319,412,7);
showmouse();
}

void showonright(int textnum,long double &num)
{
if(ispreview) return;
hidemouse();
//SETMOUSEEXLUSIONAREA(323,401,638,412);
if(rightshow!=textnum)
	{
	Putstring(323,401,alltext[textnum],15,7);
	rightshow=textnum;
	}
convert_round(num);
convert_number2string(num,DECSYS,4);
char *ptr=num2str_buffer;
if(*ptr=='+') ptr++;
mygr.drawfilledbox(Putstring(alllen[textnum]+323,401,ptr,15,7),401,638,412,7);
showmouse();
}

long double commonshownext(int &tempshow)
{
if(tempshow>=4 && tempshow<=6) tempshow++;
	else if(tempshow==7 || tempshow==8)
			switch(secondstate)
				{
				case 0:tempshow=0;break;
				case 1:tempshow=11;break;
				case 2:tempshow=10;break;
				case 3:tempshow=9;break;
				}
			else if(tempshow>8) tempshow=0;
if(!tempshow)
	switch(firststate)
		{
		case 0:tempshow=4;break;
        case 1:tempshow=3;break;
		case 2:tempshow=2;break;
		case 3:tempshow=1;break;
		}
	else if(tempshow<4) tempshow=4;
if(tempshow==1 || tempshow==9) return (long double)(*(unsigned long*)(allnumbers[tempshow]));
return *(long double*)(allnumbers[tempshow]);
}

void shownextonleft(void)
{
long double temp;
int tempshow=leftshow;
temp=commonshownext(tempshow);
showonleft(tempshow,temp);
}

void shownextonright(void)
{
long double temp;
int tempshow=rightshow;
temp=commonshownext(tempshow);
showonright(tempshow,temp);
}


long double commonshowprev(int &tempshow)
{
if(tempshow>=5 && tempshow<=8) tempshow--;
	else if(tempshow==4)
		    switch(firststate)
				{
				case 0:tempshow=0;break;
				case 1:tempshow=3;break;
		        case 2:tempshow=2;break;
				case 3:tempshow=1;break;
				}
			else if(tempshow<4) tempshow=0;
if(tempshow==0)
	switch(secondstate)
		{
		case 0:tempshow=7;break;
		case 1:tempshow=11;break;
		case 2:tempshow=10;break;
        case 3:tempshow=9;break;
		}
	else if(tempshow>8) tempshow=7;
if(tempshow==1 || tempshow==9) return (long double)(*(unsigned long*)(allnumbers[tempshow]));
return *(long double*)(allnumbers[tempshow]);
}

void showprevonleft(void)
{
long double temp;
int tempshow=leftshow;
temp=commonshowprev(tempshow);
showonleft(tempshow,temp);
}


void showprevonright(void)
{
long double temp;
int tempshow=rightshow;
temp=commonshowprev(tempshow);
showonright(tempshow,temp);
}


void showxcoord(long double num)
{
showonleft(0,num);
}

void showycoord(long double num)
{
showonright(8,num);
}

void showleftborder(void)
{
if(!ispreview) {showonleft(4,leftborder);return;}
hidemouse();
//SETMOUSEEXLUSIONAREA(3+alllen[4],436,319,447);
//Putstring(3,432,alltext[4],0,15);
convert_round(leftborder);
convert_number2string(leftborder,DECSYS,4);
char *ptr=num2str_buffer;
if(*ptr=='+') ptr++;
int xpos=310-Strlen(ptr)*8;
Putstring(xpos,436,ptr,0,15);
mygr.drawfilledbox(alllen[4]+3,436,xpos-1,447,15);
showmouse();
}

void showrightborder(void)
{
if(!ispreview) {showonright(5,rightborder);return;}
hidemouse();
//SETMOUSEEXLUSIONAREA(323+alllen[5],436,639,447);
//Putstring(3,432,alltext[4],0,15);
convert_round(rightborder);
convert_number2string(rightborder,DECSYS,4);
char *ptr=num2str_buffer;
if(*ptr=='+') ptr++;
int xpos=637-Strlen(ptr)*8;
Putstring(xpos,436,ptr,0,15);
mygr.drawfilledbox(alllen[5]+323,436,xpos-1,447,15);
showmouse();
}

void showupborder(void)
{
if(!ispreview) {showonleft(6,upborder);return;}
hidemouse();
//SETMOUSEEXLUSIONAREA(323+alllen[6],448,639,459);
//Putstring(3,432,alltext[4],0,15);
convert_round(upborder);
convert_number2string(upborder,DECSYS,4);
char *ptr=num2str_buffer;
if(*ptr=='+') ptr++;
int xpos=637-Strlen(ptr)*8;
Putstring(xpos,448,ptr,0,15);
mygr.drawfilledbox(alllen[6]+323,448,xpos-1,459,15);
showmouse();
}

void showdownborder(void)
{
showonright(7,downborder);
if(!ispreview) {showonright(7,downborder);return;}
hidemouse();
//SETMOUSEEXLUSIONAREA(3+alllen[7],448,319,459);
//Putstring(3,432,alltext[4],0,15);
convert_round(downborder);
convert_number2string(downborder,DECSYS,4);
char *ptr=num2str_buffer;
if(*ptr=='+') ptr++;
int xpos=310-Strlen(ptr)*8;
Putstring(xpos,448,ptr,0,15);
mygr.drawfilledbox(alllen[7]+3,448,xpos-1,459,15);
showmouse();
}

void showcurvwiter(void)
{
long double temp=firstworkiter;
showonleft(1,temp);
if(rightshow==1) showonright(1,temp);

}

void showcurv(void)
{
showonleft(2,firstworking);
if(rightshow==2) showonright(2,firstworking);
}

void showcurw(void)
{
showonleft(3,firstworking);
if(rightshow==3) showonright(3,firstworking);
}

void showcurxyiter(void)
{
long double temp=secondworkiter;
showonright(9,temp);
if(leftshow==9) showonleft(9,temp);
}

void showcurx(void)
{
showonright(10,secondworking);
if(leftshow==10) showonleft(10,secondworking);
}

void showcury(void)
{
showonright(11,secondworking);
if(leftshow==11) showonleft(11,secondworking);
}

void showxgridstep()
{
convert_round(xgridstep);
convert_number2string(xgridstep,DECSYS,4);
if(!ispreview)
	{
	X_Gridstep.hidemouse_edl();
	if(activeinputline==&X_Gridstep)
		{
		X_Gridstep.deactivate();
		activeinputline=0;
		}
	if(num2str_buffer[0]=='+') X_Gridstep.settext(num2str_buffer+1);
		else X_Gridstep.settext(num2str_buffer);
	if(visualgridstep==&X_Gridstep) X_Gridstep.redraw();
	}
	else
	{
	hidemouse();
//	SETMOUSEEXLUSIONAREA(3+xgridsteplen,460,319,471);
	char *ptr=num2str_buffer;
	if(*ptr=='+') ptr++;
	int xpos=310-Strlen(ptr)*8;
	Putstring(xpos,460,ptr,0,15);
	mygr.drawfilledbox(xgridsteplen+3,460,xpos-1,471,15);
	}
showmouse();
}

void showygridstep()
{
convert_round(ygridstep);
convert_number2string(ygridstep,DECSYS,4);
if(!ispreview)
	{
	Y_Gridstep.hidemouse_edl();
	if(activeinputline==&Y_Gridstep)
		{
		Y_Gridstep.deactivate();
		activeinputline=0;
		}
	if(num2str_buffer[0]=='+') Y_Gridstep.settext(num2str_buffer+1);
		else Y_Gridstep.settext(num2str_buffer);
	if(visualgridstep==&Y_Gridstep) Y_Gridstep.redraw();
	}
	else
	{
	hidemouse();
//	SETMOUSEEXLUSIONAREA(323+ygridsteplen,460,639,471);
	char *ptr=num2str_buffer;
	if(*ptr=='+') ptr++;
	int xpos=637-Strlen(ptr)*8;
	Putstring(xpos,460,ptr,0,15);
	mygr.drawfilledbox(xgridsteplen+323,460,xpos-1,471,15);
	}
showmouse();
}

void showyscale()
{
if(ispreview) return;
Y_scale.hidemouse_edl();
if(activeinputline==&Y_scale)
	{
	Y_scale.deactivate();
	activeinputline=0;
	}
convert_round(yscale);
convert_number2string(yscale,DECSYS,4);
if(num2str_buffer[0]=='+') Y_scale.settext(num2str_buffer+1);
	else Y_scale.settext(num2str_buffer);
if(visualscale==&Y_scale) Y_scale.redraw();
showmouse();
}

void showxscale()
{
if(ispreview) return;
X_scale.hidemouse_edl();
if(activeinputline==&X_scale)
	{
	X_scale.deactivate();
	activeinputline=0;
	}
convert_round(xscale);
convert_number2string(xscale,DECSYS,4);
if(num2str_buffer[0]=='+') X_scale.settext(num2str_buffer+1);
	else X_scale.settext(num2str_buffer);
if(visualscale==&X_scale) X_scale.redraw();
showmouse();
}

int mainxerror(void)
{
if(FPUerror) FPUerror=0;
if(FPU_abs(FPU_sub(FPU_add(FPU_mul(xscale,xscrsize),leftborder),rightborder))>=FPU_div(xscale,2)
	  || FPUadd(xscale,leftborder)==leftborder || FPUsub(leftborder,xscale)==leftborder
	  || FPUadd(xscale,rightborder)==rightborder || FPUsub(rightborder,xscale)==rightborder
	  || leftborder==rightborder || xscale>1.0e4801 || xscale<1.0e-4801)
	{
	FPUerror=0;
	if(ispreview) return 1;
	hidemouse();
	Putstring(106,460,"ТОЧНОСТЬ",15,12);
	showmouse();
	iserrormessage=1;
	return 1;
	}
	else if(iserrormessage)
		{
		iserrormessage=0;
		if(!ispreview)
			{
			hidemouse();
			mygr.drawfilledbox_rel(106,460,64,12,7);
			showmouse();
			}
		}
return 0;
}

int mainyerror(void)
{
if(FPUerror) FPUerror=0;
if(FPU_abs(FPU_sub(FPU_add(FPU_mul(yscale,yscrsize),downborder),upborder))>FPU_div(yscale,2)
	  || FPUadd(yscale,downborder)==downborder || FPUsub(downborder,yscale)==downborder
	  || FPUadd(upborder,yscale)==upborder || FPUsub(upborder,yscale)==upborder
	  || downborder==upborder || yscale>1.0e4801 || yscale<1.0e-4801)
	{
	FPUerror=0;
	if(ispreview) return 1;
	hidemouse();
	Putstring(106,460,"ТОЧНОСТЬ",15,12);
	showmouse();
	iserrormessage=1;
	return 1;
	}
	else if(iserrormessage)
		{
		iserrormessage=0;
		if(!ispreview)
			{
			hidemouse();
			mygr.drawfilledbox_rel(106,460,64,12,7);
			showmouse();
			}
		}
return 0;
}

void readxgridstep(void)
{
if(ispreview) return;
long double temp;
temp=string2double(X_Gridstep.gettext());
if(temp<=0) return;
convert_round(temp);
xgridstep=temp;
}

void readygridstep(void)
{
if(ispreview) return;
long double temp;
temp=string2double(Y_Gridstep.gettext());
if(temp<=0) return;
convert_round(temp);
ygridstep=temp;
}

void readxscale(void)
{
if(ispreview) return;
long double temp,forxscale,forleftb,forrightb;
temp=string2double(X_scale.gettext());
if(temp<=0) return;
convert_round(temp);
if(temp!=xscale)
	{
	forxscale=xscale;forleftb=leftborder;forrightb=rightborder;
	xscale=temp;
	temp=FPU_mul(xscale,xscrsize>>1);
	rightborder=FPU_div(FPUadd(leftborder,rightborder),2);
	leftborder=FPUsub(rightborder,temp);
	rightborder=FPUadd(rightborder,temp);
	if(FPUerror) FPUerror=0;
	if(mainxerror())
		{
		xscale=forxscale;
		leftborder=forleftb;
		rightborder=forrightb;
		}
	}
}

void readyscale(void)
{
if(ispreview) return;
long double temp,foryscale,fordownb,forupb;
temp=string2double(Y_scale.gettext());
if(temp<=0) return;
convert_round(temp);
if(temp!=yscale)
	{
	foryscale=yscale;fordownb=downborder;forupb=upborder;
	yscale=temp;
	temp=FPU_mul(yscale,yscrsize>>1);
	upborder=FPU_div(FPUadd(downborder,upborder),2);
	downborder=FPUsub(upborder,temp);
	upborder=FPUadd(upborder,temp);
	if(FPUerror) FPUerror=0;
	if(mainyerror())
		{
		yscale=foryscale;
		downborder=fordownb;
		upborder=forupb;
		}
	}
}

void showvwiter()
{
if(ispreview) return;
VW_iter.hidemouse_edl();
if(activeinputline==&VW_iter)
	{
	VW_iter.deactivate();
	activeinputline=0;
	}
num2str_buffer[ulong2string_dec(firstiter,num2str_buffer)]='\0';
VW_iter.settext(num2str_buffer);
if(visualiter==&VW_iter) VW_iter.redraw();
showmouse();
}

void showxyiter()
{
if(ispreview) return;
XY_iter.hidemouse_edl();
if(activeinputline==&XY_iter)
	{
	XY_iter.deactivate();
	activeinputline=0;
	}
num2str_buffer[ulong2string_dec(seconditer,num2str_buffer)]='\0';
XY_iter.settext(num2str_buffer);
if(visualiter==&XY_iter) XY_iter.redraw();
showmouse();
}

void readvwiter(void)
{
if(ispreview) return;
long double temp=string2double(VW_iter.gettext());
if(temp>4294967295.0) temp=4294967295.0;
	else if(temp<0) temp=1;
firstiter=(unsigned long)temp;
}

void readxyiter(void)
{
if(ispreview) return;
long double temp=string2double(XY_iter.gettext());
if(temp>4294967295.0) temp=4294967295.0;
	else if(temp<0) temp=1;
seconditer=(unsigned long)temp;
}

void madexgridstepvisual(int isstart=0)
{
if(visualgridstep!=&X_Gridstep || isstart)
	{
	hidemouse();
	if(activeinputline==&Y_Gridstep) Y_Gridstep.deactivate();
	mygr.drawtwocoloredbox(281,415,378,430,8,15);
	Putstring(282,417,switchtext[0],15,7);
	X_Gridstep.redraw();
	if(activeinputline==&Y_Gridstep) {X_Gridstep.activate();activeinputline=&X_Gridstep;}
	visualgridstep=&X_Gridstep;
	showmouse();
	}
}

void madeygridstepvisual(int isstart=0)
{
if(visualgridstep!=&Y_Gridstep || isstart)
	{
	hidemouse();
	if(activeinputline==&X_Gridstep) X_Gridstep.deactivate();
	mygr.drawtwocoloredbox(281,415,378,430,15,8);
	Putstring(282,417,switchtext[1],15,7);
	Y_Gridstep.redraw();
	if(activeinputline==&X_Gridstep) {Y_Gridstep.activate();activeinputline=&Y_Gridstep;}
	visualgridstep=&Y_Gridstep;
	showmouse();
	}
}

void madexscalevisual(int isstart=0)
{
if(visualscale!=&X_scale || isstart)
	{
	hidemouse();
	if(activeinputline==&Y_scale) Y_scale.deactivate();
	mygr.drawtwocoloredbox(2,415,85,430,8,15);
	Putstring(4,417,switchtext[2],15,7);
	X_scale.redraw();
	if(activeinputline==&Y_scale) {X_scale.activate();activeinputline=&X_scale;}
	visualscale=&X_scale;
	showmouse();
	}
}

void madeyscalevisual(int isstart=0)
{
if(visualscale!=&Y_scale || isstart)
	{
	hidemouse();
	if(activeinputline==&X_scale) X_scale.deactivate();
	mygr.drawtwocoloredbox(2,415,85,430,15,8);
	Putstring(4,417,switchtext[3],15,7);
	Y_scale.redraw();
	if(activeinputline==&X_scale) {Y_scale.activate();activeinputline=&Y_scale;}
	visualscale=&Y_scale;
	showmouse();
	}
}

void madexyitervisual(int isstart=0)
{
if(visualiter!=&XY_iter || isstart)
	{
	hidemouse();
	if(activeinputline==&VW_iter) VW_iter.deactivate();
	mygr.drawtwocoloredbox(2,436,221,450,15,8);
	Putstring(4,437,switchtext[4],15,7);
	XY_iter.redraw();
	if(activeinputline==&VW_iter) {XY_iter.activate();activeinputline=&XY_iter;}
	visualiter=&XY_iter;
	showmouse();
	}
}

void madevwitervisual(int isstart=0)
{
if(visualiter!=&VW_iter || isstart)
	{
	hidemouse();
	if(activeinputline==&XY_iter) XY_iter.deactivate();
	mygr.drawtwocoloredbox(2,436,221,450,8,15);
	Putstring(4,437,switchtext[5],15,7);
	VW_iter.redraw();
	if(activeinputline==&XY_iter) {VW_iter.activate();activeinputline=&VW_iter;}
	visualiter=&VW_iter;
	showmouse();
	}
}

int receivegraphkeyevent(void)
{
unsigned int capslockon=0,chr,code,keystatus;
keystatus=Getkeyboardflags();
//if(keychar&KBS_CTRLDOWN) ctrlpressed=1;
if(keystatus&KBS_CAPSLOCKON) capslockon=1;
code=Getkey();
chr=code&255;
code>>=8;

if(!chr && code==45) return KEY_exit;
if(chr==27 && code==1) return KEY_quit;

if(chr=='.') chr=',';
if(!isgraphhelp && ((chr>='0' && chr<='9') || chr==',')) return chr;
if(chr=='-') return chr;
if(capslockon)
	if(chr>='A' && chr<='Z') chr+=32;
		else if(chr>='a' && chr<='z') chr-=32;
if(!isgraphhelp && chr=='e') return 'E';
if(!chr || chr==224)
	{
	if(code==75)
		if(activeinputline) return KEY_leftcur;
	if(code==71)
		if(activeinputline) return KEY_leftend;
	if(code==79)
		if(activeinputline) return KEY_rightend;
	if(code==77)
		if(activeinputline) return KEY_rightcur;
	if(code==59) return KEY_graphrowslock;
	if(code==94) return KEY_graphhelplock;
	if(code==60) return KEY_movescrleft;
	if(code==95) return KEY_movescrright;
	if(code==61) return KEY_movescrup;
	if(code==96) return KEY_movescrdown;
	if(code==62) return KEY_movewallleft;
	if(code==97) return KEY_movewallleftright;
	if(code==63) return KEY_movewallright;
	if(code==98) return KEY_movewallrightleft;
	if(code==64) return KEY_movewallup;
	if(code==99) return KEY_movewallupdown;
	if(code==65) return KEY_movewalldown;
	if(code==100) return KEY_movewalldownup;
	if(code==66) return KEY_xexpand;
	if(code==101) return KEY_xcompress;
	if(code==67) return KEY_yexpand;
	if(code==102) return KEY_ycompress;
	if(code==68) return KEY_expand;
	if(code==103) return KEY_compress;
//	if(code==71) return KEY_eval;
//	if(code==79) return KEY_evalrev;
	if(code==83) return KEY_del;
	}
if(chr==8 && code==14) return KEY_bs;
if(chr==13 && (code==28 || code==224) && !(keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))) return KEY_draw;
if(chr==10 && (code==28 || code==224) && !(keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))) return KEY_graphsave;
if(chr==0 && code==14) return KEY_graphclear;
if(chr=='g') return KEY_graphgridlock;
if(chr=='s') return KEY_stop;
if(chr=='c') return KEY_cont;
if(chr=='+') return KEY_center;
if(chr=='|') return KEY_eval;
if(chr=='_') return KEY_evalrev;
if(chr==32) return KEY_step;
if(chr=='l') return KEY_join;
if(chr=='r') return KEY_redraw;
if(chr=='a') return KEY_auto;
if(chr=='v') return KEY_onlyvw;
if(chr=='x') return KEY_onlyxy;
if(chr=='p') return KEY_preview;
if(chr==9 && code==15 && !ispreview)
	{
	hidemouse();
	if(!activeinputline)
		{
		madexscalevisual();
		activeinputline=&X_scale;
		}
		else
		{
		activeinputline->deactivate();
		if(activeinputline==&X_scale)
			{
			madeyscalevisual();
			activeinputline=&Y_scale;
			}
			else if(activeinputline==&Y_scale)
				{
				madevwitervisual();
				activeinputline=&VW_iter;
				}
				else if(activeinputline==&VW_iter)
					{
					madexyitervisual();
					activeinputline=&XY_iter;
					}
					else if(activeinputline==&XY_iter && !isauto)
						{
						madexgridstepvisual();
						activeinputline=&X_Gridstep;
						}
						else if(activeinputline==&X_Gridstep && !isauto)
							{
							madeygridstepvisual();
							activeinputline=&Y_Gridstep;
							}
							else
							activeinputline=0;
		}
	if(activeinputline)
		activeinputline->activate();
	showmouse();
	}
if(chr==0 && code==15 && !ispreview)
	{
	hidemouse();
	if(!activeinputline)
		{
		if(!isauto)
			{
			madeygridstepvisual();
			activeinputline=&Y_Gridstep;
			}
			else
			{
			madexyitervisual();
			activeinputline=&XY_iter;
			}
		}
		else
		{
		activeinputline->deactivate();
		if(activeinputline==&Y_Gridstep && !isauto)
			{
			madexgridstepvisual();
			activeinputline=&X_Gridstep;
			}
			else if(activeinputline==&X_Gridstep)
				{
				madexyitervisual();
				activeinputline=&XY_iter;
				}
				else if(activeinputline==&XY_iter)
					{
					madevwitervisual();
					activeinputline=&VW_iter;
					}
					else if(activeinputline==&VW_iter)
						{
						madeyscalevisual();
						activeinputline=&Y_scale;
						}
						else if(activeinputline==&Y_scale)
							{
							madexscalevisual();
							activeinputline=&X_scale;
							}
							else
							activeinputline=0;
		}
	if(activeinputline)
		activeinputline->activate();
	showmouse();
	}
return KEY_no;
}

int receivegraphmouseevent(int isrepeat=0)
{
if(isrepeat && !ispreview)
	{
//	if(!(_MouseState.state&1)) return KEY_no;
	if(BUT_movescrleft.evente()) return what_button;
	if(BUT_movescrright.evente()) return what_button;
	if(BUT_movescrup.evente()) return what_button;
	if(BUT_movescrdown.evente()) return what_button;
	if(BUT_movewallleft.evente()) return what_button;
	if(BUT_movewallleftright.evente()) return what_button;
	if(BUT_movewallright.evente()) return what_button;
	if(BUT_movewallrightleft.evente()) return what_button;
	if(BUT_movewallup.evente()) return what_button;
	if(BUT_movewallupdown.evente()) return what_button;
	if(BUT_movewalldown.evente()) return what_button;
	if(BUT_movewalldownup.evente()) return what_button;
	if(BUT_xexpand.evente()) return what_button;
	if(BUT_xcompress.evente()) return what_button;
	if(BUT_yexpand.evente()) return what_button;
	if(BUT_ycompress.evente()) return what_button;
	if(BUT_expand.evente()) return what_button;
	if(BUT_compress.evente()) return what_button;
	if(BUT_step.evente()) return what_button;
	return KEY_no;
	}
mev=getmouseevent();
if(mev.ycoord<yscrsize && mev.xcoord<xscrsize)
	{
	if(mev.event&ME_LEFTPRESSED) return KEY_centerscreen;
	if(mev.event&ME_RIGHTPRESSED && mev.keystate==2)
		if(Getkeyboardflags()&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) return KEY_compresscenterscreen;
			else return KEY_expandcenterscreen;
	if(!(mev.event&ME_LEFTRELEASED) && !(mev.event&ME_RIGHTRELEASED)) return KEY_move;
	}
if(ispreview && mev.event&ME_LEFTPRESSED && mev.ycoord>=427)
	return KEY_quit;
if(ispreview) return KEY_no;
if(mev.event&(ME_LEFTPRESSED|ME_RIGHTPRESSED) && mev.xcoord>=3 && mev.xcoord<=319 && mev.ycoord>=401 && mev.ycoord<=412 && !isgraphhelp)
	if(mev.event&ME_LEFTPRESSED) shownextonleft();
		else if(mev.keystate==2) showprevonleft();
if(mev.event&(ME_LEFTPRESSED|ME_RIGHTPRESSED) && mev.xcoord>=323 && mev.xcoord<=638 && mev.ycoord>=401 && mev.ycoord<=412 && !isgraphhelp)
	if(mev.event&ME_LEFTPRESSED) shownextonright();
		else if(mev.keystate==2) showprevonright();
if(mev.event&ME_LEFTPRESSED && mev.xcoord>=3 && mev.xcoord<83 && mev.ycoord>=417 && mev.ycoord<429 && !isgraphhelp)
	if(visualscale==&X_scale) madeyscalevisual();
		else madexscalevisual();
if(mev.event&ME_LEFTPRESSED && mev.xcoord>=3 && mev.xcoord<219 && mev.ycoord>=437 && mev.ycoord<449 && !isgraphhelp)
	if(visualiter==&XY_iter) madevwitervisual();
		else madexyitervisual();
if(mev.event&ME_LEFTPRESSED && mev.xcoord>=290 && mev.xcoord<370 && mev.ycoord>=417 && mev.ycoord<429 && !isgraphhelp)
	if(visualgridstep==&X_Gridstep) madeygridstepvisual();
		else madexgridstepvisual();
if(mev.event&ME_LEFTPRESSED && !isgraphhelp) {countrepeat=2;lasttimerticks=Gettimerticks();}
	else
	if(mev.event&ME_LEFTRELEASED) countrepeat=0;
if(visualscale->event())
	if(activeinputline!=visualscale)
		{
		if(activeinputline)
			{
			activeinputline->hidemouse_edl();
			activeinputline->deactivate();
			showmouse();
			}
		activeinputline=visualscale;
		return KEY_no;
		}
if(visualiter->event())
	if(activeinputline!=visualiter)
		{
		if(activeinputline)
			{
			activeinputline->hidemouse_edl();
			activeinputline->deactivate();
			showmouse();
			}
		activeinputline=visualiter;
		return KEY_no;
		}
if(!isauto && visualgridstep->event())
	if(activeinputline!=visualgridstep)
		{
		if(activeinputline)
			{
			activeinputline->hidemouse_edl();
			activeinputline->deactivate();
			showmouse();
			}
		activeinputline=visualgridstep;
		return KEY_no;
		}
if(BUT_graphhelplock.event()) return what_button;

if(mev.xcoord>=87 && mev.xcoord<279 && mev.ycoord>=414  && mev.ycoord<432)
	if(isgraphhelp && mev.event&ME_LEFTPRESSED)
		{what_button=KEY_scalehelp;return what_button;}
		else
		if(mev.event&ME_RIGHTPRESSED && mev.keystate==2 && !isgraphhelp)
			{helpon(KEY_scalehelp);return KEY_no;}
if(mev.xcoord>=223 && mev.xcoord<311 && mev.ycoord>=434  && mev.ycoord<452)
	if(isgraphhelp && mev.event&ME_LEFTPRESSED)
		{what_button=KEY_iterhelp;return what_button;}
		else
		if(mev.event&ME_RIGHTPRESSED && mev.keystate==2 && !isgraphhelp)
			{helpon(KEY_iterhelp);return KEY_no;}
if(mev.xcoord>=381 && mev.xcoord<573 && mev.ycoord>=414  && mev.ycoord<432)
	if(isgraphhelp && mev.event&ME_LEFTPRESSED)
		{what_button=KEY_gridstephelp;return what_button;}
		else
		if(mev.event&ME_RIGHTPRESSED && mev.keystate==2 && !isgraphhelp)
			{helpon(KEY_gridstephelp);return KEY_no;}


if(Join.event()) return what_button;
if(Only_VW.event()) return what_button;
if(Only_XY.event()) return what_button;
if(Redraw.event()) return what_button;
if(Autogrid.event()) return what_button;


if(BUT_graphrowslock.event(isgraphhelp)) return what_button;
if(BUT_graphgridlock.event(isgraphhelp)) return what_button;
if(BUT_movescrleft.event(isgraphhelp)) return what_button;
if(BUT_movescrright.event(isgraphhelp)) return what_button;
if(BUT_movescrup.event(isgraphhelp)) return what_button;
if(BUT_movescrdown.event(isgraphhelp)) return what_button;
if(BUT_movewallleft.event(isgraphhelp)) return what_button;
if(BUT_movewallleftright.event(isgraphhelp)) return what_button;
if(BUT_movewallright.event(isgraphhelp)) return what_button;
if(BUT_movewallrightleft.event(isgraphhelp)) return what_button;
if(BUT_movewallup.event(isgraphhelp)) return what_button;
if(BUT_movewallupdown.event(isgraphhelp)) return what_button;
if(BUT_movewalldown.event(isgraphhelp)) return what_button;
if(BUT_movewalldownup.event(isgraphhelp)) return what_button;
if(BUT_xexpand.event(isgraphhelp)) return what_button;
if(BUT_xcompress.event(isgraphhelp)) return what_button;
if(BUT_yexpand.event(isgraphhelp)) return what_button;
if(BUT_ycompress.event(isgraphhelp)) return what_button;
if(BUT_expand.event(isgraphhelp)) return what_button;
if(BUT_compress.event(isgraphhelp)) return what_button;
if(BUT_eval.event(isgraphhelp)) return what_button;
if(BUT_evalrev.event(isgraphhelp)) return what_button;
if(BUT_draw.event(isgraphhelp)) return what_button;
if(BUT_clear_graph.event(isgraphhelp)) return what_button;
if(BUT_stop.event(isgraphhelp)) return what_button;
if(BUT_step.event(isgraphhelp)) return what_button;
if(BUT_cont.event(isgraphhelp)) return what_button;
if(BUT_center.event(isgraphhelp)) return what_button;
if(BUT_quit.event(isgraphhelp)) return what_button;
if(BUT_save.event(isgraphhelp)) return what_button;
if(BUT_preview.event(isgraphhelp)) return what_button;
return KEY_no;
}

int makefirststep(void)
{
long double work;
int x,y;
if(deactive==1 || !firststate) return 0;
if(firststate==1)
	{
	if((!firstrev && firstworking>firsthighlimit) ||
		(firstrev && firstworking<firsthighlimit)) return 0;
	if(!firstrev && firstworking<downborder) firstworking=downborder;
		else if(firstrev && firstworking>upborder) firstworking=upborder;
	if((!firstrev && firstworking>upborder)||
		(firstrev && firstworking<downborder)) return 0;
	variable['W'-'A'].number=firstworking;
	return 1;
	}
if(firststate==2)
	{
	if((!firstrev && firstworking>firsthighlimit) ||
		(firstrev && firstworking<firsthighlimit)) return 0;
	if(!firstrev && firstworking<leftborder) firstworking=leftborder;
		else if(firstrev && firstworking>rightborder) firstworking=rightborder;
	if((!firstrev && firstworking>rightborder)||
		(firstrev && firstworking<leftborder)) return 0;
	variable['V'-'A'].number=firstworking;
	return 1;
	}
if(firststate==3)
	{
	if(firstworkiter>=firstiter) return 0;
	firstworking=variable['V'-'A'].number;
	work=variable['W'-'A'].number;
	if(!variable['W'-'A'].iserror && !variable['V'-'A'].iserror)
		if(firstworking>=leftborder && firstworking<=rightborder && work>=downborder && work<=upborder)
			{
			x=FPU_round(FPU_div(FPUsub(firstworking,leftborder),xscale));
			y=yscrsize-1-FPU_round(FPU_div(FPUsub(work,downborder),yscale));
			if(x>=0 && x<xscrsize && y>=0 && y<yscrsize)
				{
				mygr.putpixel(x,y,ispreview?2:14);
				if(joinpoints && firstislast)
					mygr.drawline(firstlastx,firstlasty,x,y,ispreview?2:14);
				firstlastx=x;
				firstlasty=y;
				firstislast=1;
				}
				else firstislast=0;
			}
			else firstislast=0;
		else firstislast=0;
//	recountvariables(1);
	firstworkiter++;
	Counterror=0;FPUerror=0;
	return 1;
	}
return 0;
}

void contfirststep(void)
{
long double work;
int x,y;
if(firststate==1)
	{
	work=variable['V'-'A'].number;
	if(!variable['V'-'A'].iserror)
		{
		if(work>=leftborder && work<=rightborder)
			{
			x=FPU_round(FPU_div(FPUsub(work,leftborder),xscale));
			y=yscrsize-1-FPU_round(FPU_div(FPUsub(firstworking,downborder),yscale));
			if(x>=0 && x<xscrsize && y>=0 && y<yscrsize)
				{
				mygr.putpixel(x,y,ispreview?2:14);
				if(joinpoints && firstislast && Abs(firstlastx-x)>1)
					{
					int tmp=1;
					if(firstlastx>x)
						tmp=-tmp;
					mygr.drawxline(firstlastx,(firstlastx+x)/2,firstlasty,ispreview?2:14);
					mygr.drawxline((firstlastx+x)/2+tmp,x-tmp,y,ispreview?2:14);
					}
				firstlastx=x;
				firstlasty=y;
				firstislast=1;
				}
				else firstislast=0;
			}
			else firstislast=0;
		}
		else firstislast=0;
	if(!firstrev)
		firstworking=FPUadd(firstworking,yscale);
		else
		firstworking=FPUsub(firstworking,yscale);
	Counterror=0;FPUerror=0;
	return;
	}
if(firststate==2)
	{
	work=variable['W'-'A'].number;
	if(!variable['W'-'A'].iserror)
		{
		if(work>=downborder && work<=upborder)
			{
			x=FPU_round(FPU_div(FPUsub(firstworking,leftborder),xscale));
			y=yscrsize-1-FPU_round(FPU_div(FPUsub(work,downborder),yscale));
			if(x>=0 && x<xscrsize && y>=0 && y<yscrsize)
				{
				mygr.putpixel(x,y,ispreview?2:14);
				if(joinpoints && firstislast && Abs(firstlasty-y)>1)
					{
					int tmp=1;
					if(firstlasty>y)
						tmp=-tmp;
					mygr.drawyline(firstlasty,(firstlasty+y)/2,firstlastx,ispreview?2:14);
					mygr.drawyline((firstlasty+y)/2+tmp,y,x,ispreview?2:14);
					}
				firstlastx=x;
				firstlasty=y;
				firstislast=1;
				}
				else firstislast=0;
			}
			else firstislast=0;
		}
		else firstislast=0;
	if(!firstrev)
		firstworking=FPUadd(firstworking,xscale);
		else
		firstworking=FPUsub(firstworking,xscale);
	Counterror=0;FPUerror=0;
	}
return;
}


int makesecondstep(void)
{
long double work;
int x,y;
if(deactive==2 || !secondstate) return 0;
if(secondstate==1)
	{
	if((!secondrev && secondworking>secondhighlimit) ||
		(secondrev && secondworking<secondhighlimit)) return 0;
	if(!secondrev && secondworking<downborder) secondworking=downborder;
		else if(secondrev && secondworking>upborder) secondworking=upborder;
	if((!secondrev && secondworking>upborder) ||
		(secondrev && secondworking<downborder)) return 0;
	variable['Y'-'A'].number=secondworking;
	return 1;
	}
if(secondstate==2)
	{
	if((!secondrev && secondworking>secondhighlimit) ||
		(secondrev && secondworking<secondhighlimit)) return 0;
	if(secondworking<leftborder) secondworking=leftborder;
	if(!secondrev && secondworking<leftborder) secondworking=leftborder;
		else if(secondrev && secondworking>rightborder) secondworking=rightborder;
	if((!secondrev && secondworking>rightborder) ||
		(secondrev && secondworking<leftborder)) return 0;
	variable['X'-'A'].number=secondworking;
	return 1;
	}
if(secondstate==3)
	{
	if(secondworkiter>=seconditer) return 0;
	secondworking=variable['X'-'A'].number;
	work=variable['Y'-'A'].number;
	if(!variable['Y'-'A'].iserror && !variable['X'-'A'].iserror)
		if(secondworking>=leftborder && secondworking<=rightborder && work>=downborder && work<=upborder)
			{
			x=FPU_round(FPU_div(FPUsub(secondworking,leftborder),xscale));
			y=yscrsize-1-FPU_round(FPU_div(FPUsub(work,downborder),yscale));
			if(x>=0 && x<xscrsize && y>=0 && y<yscrsize)
				{
				mygr.putpixel(x,y,ispreview?1:11);
				if(joinpoints && secondislast)
					mygr.drawline(secondlastx,secondlasty,x,y,ispreview?1:11);
				secondlastx=x;
				secondlasty=y;
				secondislast=1;
				}
				else secondislast=0;
			}
			else secondislast=0;
		else secondislast=0;
//	recountvariables(1);
	secondworkiter++;
	Counterror=0;FPUerror=0;
	return 1;
	}
return 0;
}

void contsecondstep(void)
{
long double work;
int x,y;
if(secondstate==1)
	{
	work=variable['X'-'A'].number;
	if(!variable['X'-'A'].iserror)
		{
		if(work>=leftborder && work<=rightborder)
			{
			x=FPU_round(FPU_div(FPUsub(work,leftborder),xscale));
			y=yscrsize-1-FPU_round(FPU_div(FPUsub(secondworking,downborder),yscale));
			if(x>=0 && x<xscrsize && y>=0 && y<yscrsize)
				{
				mygr.putpixel(x,y,ispreview?1:11);
				if(joinpoints && secondislast && Abs(secondlastx-x)>1)
					{
					int tmp=1;
					if(secondlastx>x)
						tmp=-tmp;
					mygr.drawxline(secondlastx,(secondlastx+x)/2,secondlasty,ispreview?1:11);
					mygr.drawxline((secondlastx+x)/2+tmp,x,y,ispreview?1:11);
					}
				secondlastx=x;
				secondlasty=y;
				secondislast=1;
				}
				else secondislast=0;
			   }
			else secondislast=0;
		}
		else secondislast=0;
	if(!secondrev)
		secondworking=FPUadd(secondworking,yscale);
		else
		secondworking=FPUsub(secondworking,yscale);
	Counterror=0;FPUerror=0;
	return;
	}
if(secondstate==2)
	{
	work=variable['Y'-'A'].number;
	if(!variable['Y'-'A'].iserror)
		{
		if(work>=downborder && work<=upborder)
			{
			x=FPU_round(FPU_div(FPUsub(secondworking,leftborder),xscale));
			y=yscrsize-1-FPU_round(FPU_div(FPUsub(work,downborder),yscale));
			if(x>=0 && x<xscrsize && y>=0 && y<yscrsize)
				{
				mygr.putpixel(x,y,ispreview?1:11);
				if(joinpoints && secondislast && Abs(secondlasty-y)>1)
					{
					int tmp=1;
					if(secondlasty>y)
						tmp=-tmp;
					mygr.drawyline(secondlasty,(secondlasty+y)/2,secondlastx,ispreview?1:11);
					mygr.drawyline((secondlasty+y)/2+tmp,y,x,ispreview?1:11);
					}
				secondlastx=x;
				secondlasty=y;
				secondislast=1;
				}
				else secondislast=0;
			}
			else secondislast=0;
		}
		else secondislast=0;
	if(!secondrev)
		secondworking=FPUadd(secondworking,xscale);
		else
		secondworking=FPUsub(secondworking,xscale);
	Counterror=0;FPUerror=0;
	}
return;
}


void setgraphstate(int mode)
{
hidemouse();
BUT_graphhelplock.setactivities(mode);
BUT_graphrowslock.setactivities(mode);
BUT_graphgridlock.setactivities(mode);

BUT_movescrleft.setactivities(mode);
BUT_movescrright.setactivities(mode);
BUT_movescrup.setactivities(mode);
BUT_movescrdown.setactivities(mode);
BUT_movewallleft.setactivities(mode);
BUT_movewallleftright.setactivities(mode);
BUT_movewallright.setactivities(mode);
BUT_movewallrightleft.setactivities(mode);
BUT_movewallup.setactivities(mode);
BUT_movewallupdown.setactivities(mode);
BUT_movewalldown.setactivities(mode);
BUT_movewalldownup.setactivities(mode);
BUT_xexpand.setactivities(mode);
BUT_xcompress.setactivities(mode);
BUT_yexpand.setactivities(mode);
BUT_ycompress.setactivities(mode);
BUT_expand.setactivities(mode);
BUT_compress.setactivities(mode);
BUT_eval.setactivities(mode);
BUT_evalrev.setactivities(mode);
BUT_draw.setactivities(mode);
BUT_clear_graph.setactivities(mode);
BUT_stop.setactivities(mode);
BUT_step.setactivities(mode);
BUT_cont.setactivities(mode);
BUT_center.setactivities(mode);
BUT_quit.setactivities(mode);
BUT_preview.setactivities(mode);
BUT_save.setactivities(mode);
showmouse();
}

void clearworkfield(void)
{
int x,y,xr,yr;
hidemouse();
mygr.drawfilledbox(0,0,xscrsize-1,yscrsize-1,ispreview?15:0);
if(FPUsgn(leftborder)!=FPUsgn(rightborder) && isrows)
	{
	xr=FPU_round(FPU_sub(0,FPUdiv(leftborder,xscale)));
	if(xr<xscrsize)
		{
		mygr.drawyline(0,yscrsize-1,xr,ispreview?0:15);
		mygr.drawline(xr,0,xr-4,10,ispreview?0:15);
		mygr.drawline(xr,0,xr+4,10,ispreview?0:15);
		}
	}
if(FPUerror) FPUerror=0;
if(FPUsgn(upborder)!=FPUsgn(downborder) && isrows)
	{
	yr=FPU_round(FPU_add(yscrsize-1,FPU_div(downborder,yscale)));
	if(yr<yscrsize)
		{
		mygr.drawxline(0,xscrsize-1,yr,ispreview?0:15);
		mygr.drawline(xscrsize-1,yr,xscrsize-11,yr-4,ispreview?0:15);
		mygr.drawline(xscrsize-1,yr,xscrsize-11,yr+4,ispreview?0:15);
		}
	}
if(FPUerror) FPUerror=0;
if(isgrid)
	{
	long double work1,work2;
	if(isauto)
		{
		work1=FPU_power(10.0,FPU_int(FPU_lg(FPU_mul(xscale,100.0))));
		if(work1!=xgridstep)
			{
			xgridstep=work1;
			showxgridstep();
			}
		work1=FPU_power(10.0,FPU_int(FPU_lg(FPU_mul(yscale,100.0))));
		if(work1!=ygridstep)
			{
			ygridstep=work1;
			showygridstep();
			}
		}
		else
		{
		if(wasxgridstepin) {readxgridstep();wasxgridstepin=0;showxgridstep();}
		if(wasygridstepin) {readygridstep();wasygridstepin=0;showygridstep();}
		}
	if(FPUdiv(xgridstep,xscale)>=5.0 && !FPUerror)
		{
		work1=FPU_int(FPU_add(FPUdiv(leftborder,xgridstep),1.0));
		work2=FPU_int(FPUdiv(rightborder,xgridstep));
		while(work1<=work2 && !FPUerror)
			{
			x=FPU_round(FPU_div(FPU_sub(FPUmul(work1,xgridstep),leftborder),xscale));
			if(x!=xr && x<xscrsize)
				mygr.drawyline(0,yscrsize-1,x,7);
			work1=FPU_add(work1,1.0);
			}
		}
	if(FPUerror) FPUerror=0;
	if(FPUdiv(ygridstep,yscale)>=5.0 && !FPUerror)
		{
		work1=FPU_int(FPU_add(FPUdiv(downborder,ygridstep),1.0));
		work2=FPU_int(FPUdiv(upborder,ygridstep));
		while(work1<=work2 && !FPUerror)
			{
			y=yscrsize-1-FPU_round(FPU_div(FPU_sub(FPUmul(work1,ygridstep),downborder),yscale));
			if(y!=yr && y<yscrsize)
				mygr.drawxline(0,xscrsize-1,y,7);
			work1=FPU_add(work1,1.0);
			}
		if(FPUerror) FPUerror=0;
		}
	}
showmouse();
}

int convertgraphevent(int key)
{
if(key==KEY_no) return 1;
if(key==KEY_graphhelplock)
	{
	isgraphhelp=!isgraphhelp;
	if(!ispreview)
		if(isgraphhelp) BUT_graphhelplock.push();
			else
			BUT_graphhelplock.draw();
	hidemouse();
	if(isgraphhelp)
		SETGRAPHICSPOINTER(0,0,mousearrowquest);
		else
		SETGRAPHICSPOINTER(0,0,mousearrow);
	showmouse();
	return 1;
	}
if(!isgraphhelp && key>32000)
	{helpon(key-32000);return 1;}
if(isgraphhelp)
	{helpon(key);return 1;}
if(key==KEY_graphrowslock)
	{
	isrows=!isrows;
	if(!ispreview)
		if(isrows) BUT_graphrowslock.push();
			else
			BUT_graphrowslock.draw();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	}
if(key==KEY_graphgridlock)
	{
	isgrid=!isgrid;
	if(!ispreview)
		if(isgrid) BUT_graphgridlock.push();
			else
			BUT_graphgridlock.draw();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	}
if(key==KEY_exit)
	{
	Pushkey(0,45);
	return 0;
	}
if(key==KEY_quit)
	{
forquit:
	if(!ispreview) return 0;
		else
		{
		SETMOUSEXLIMIT(0,635);
		SETMOUSEYLIMIT(0,471);
		yscale=FPU_div(FPU_mul(yscale,107.0),100.0);
		xscale=FPU_div(FPU_mul(xscale,16.0),15.0);
		xscrsize=600;
		yscrsize=400;
		convert_round(xscale);
		convert_round(yscale);
		if(FPUerror) FPUerror=0;
		ispreview=0;
		drawmainview();
		return 1;
		}
	}
labelfordraw:
if(key==KEY_draw || key==KEY_cont)
	{
	if(wasyscalein) {readyscale();wasyscalein=0;}
	if(wasxscalein) {readxscale();wasxscalein=0;}
	if(wasvwiterin) {readvwiter();wasvwiterin=0;}
	if(wasxyiterin) {readxyiter();wasxyiterin=0;}
	if(!iserrormessage && (mainxerror() || mainyerror())) return 1;
	 showxscale();
	 showyscale();
	 showvwiter();
	 showxyiter();
	if(activeinputline==visualgridstep) {visualgridstep->deactivate();activeinputline=0;}
	int i,o,x,y,nostate=0;
	if(key==KEY_draw)
		{
		firstworkiter=0;
		firstworking=firstlowlimit;
		firstislast=0;
		secondworkiter=0;
		secondworking=secondlowlimit;
		secondislast=0;
		for(i=0;i<34;i++)
			{
			variable[i].number=forkeeping[i];
			variable[i].iserror=forkeepingerror[i];
			}
//		hidemouse();
		clearworkfield();
//		showmouse();
		}
	if(!ispreview)
		if(!countrepeat)
			{
			hidemouse();
			setgraphstate(1);
			showmouse();
			}
			else nostate=1;
	if(!nomouse)
		{
//		int x,y;
		GETMOUSEXY(x,y);
//		if(y<400) SETMOUSEXY(x,400);
//		SETMOUSEYLIMIT(400,479);
		SETMOUSEEXLUSIONAREA(0,0,xscrsize-1,yscrsize-1);
		}
//	showmouse();
	while(1)
		{
		i=makefirststep();
		o=makesecondstep();
		recountvariables(1);
		if(i) contfirststep();
		if(o) contsecondstep();
		if(!o && !i) break;
		if(Kbhit() || (!nomouse && ismouseevent()))
			{
			int ev;
			if(Kbhit())
				ev=receivegraphkeyevent();
				else
				{
				ev=receivegraphmouseevent();
				if(nostate && !countrepeat)
					{
					hidemouse();
					setgraphstate(1);
					showmouse();
					nostate=0;
					}
				SETMOUSEEXLUSIONAREA(0,0,xscrsize-1,yscrsize-1);
				}
			if(ev==KEY_stop)
				{
				if(deactive!=1)
					if(firststate==1)
						showcurw();
						else
						if(firststate==2)
							showcurv();
							else
							if(firststate==3)
								showcurvwiter();
				if(deactive!=2)
					if(secondstate==1)
						showcury();
						else
						if(secondstate==2)
							showcurx();
							else
							if(secondstate==3)
								showcurxyiter();
				break;
				}
			if(ev==KEY_quit)
				{
//				if(!nomouse)
//					{
//					hidemouse();
//					SETMOUSEYLIMIT(0,479);
					showmouse();
//					}
				goto forquit;
				}
			if(ev==KEY_exit)
			throw int(0);
			//				{
//				Pushkey(0,45);
//				return 0;
//				}
			if(ev==KEY_move || ev==KEY_expandcenterscreen || ev==KEY_compresscenterscreen || ev==KEY_centerscreen)
				{
				x=mev.xcoord;
				y=mev.ycoord;
				}
			if(!nomouse && mev.event&ME_MOVED && (mev.xcoord>=xscrsize || mev.ycoord>=yscrsize))
				if(x<xscrsize && y<yscrsize)
					{x=mev.xcoord;y=mev.ycoord;showmouse();SETMOUSEEXLUSIONAREA(0,0,xscrsize-1,yscrsize-1);}
			}
		}
	showmouse();
	showmouse();
	if(!nostate && !ispreview)
		{
		hidemouse();
		setgraphstate(0);
		showmouse();
		}
//	if(!nomouse) SETMOUSEYLIMIT(0,479);
//	showmouse();
	return 1;
	}
if(key==KEY_step)
	{
	if(wasyscalein) {readyscale();wasyscalein=0;}
	if(wasxscalein) {readxscale();wasxscalein=0;}
	if(wasvwiterin) {readvwiter();wasvwiterin=0;}
	if(wasxyiterin) {readxyiter();wasxyiterin=0;}
	if(!iserrormessage && (mainxerror() || mainyerror())) return 1;
//	if(activeinputline==&Gridstep) {Gridstep.deactivate();activeinputline=0;}
//	 setgraphstate(1);
	 showxscale();
	 showyscale();
	 showvwiter();
	 showxyiter();
	hidemouse();
	int i,o;
	i=makefirststep();
	o=makesecondstep();
	recountvariables(1);
	if(i) contfirststep();
	if(o) contsecondstep();
	showmouse();
	if(deactive!=1)
		if(firststate==1)
			showcurw();
			else
			if(firststate==2)
				showcurv();
				else
				if(firststate==3)
					showcurvwiter();
	if(deactive!=2)
		if(secondstate==1)
			showcury();
			else
			if(secondstate==2)
				showcurx();
				else
				if(secondstate==3)
					showcurxyiter();
	return 1;
	}
if(key==KEY_graphclear)
	{
	firstworkiter=0;
	firstworking=firstlowlimit;
	firstislast=0;
	secondworkiter=0;
	secondworking=secondlowlimit;
	secondislast=0;
//	hidemouse();
	clearworkfield();
	if(iserrormessage)
		{
		mainxerror();
		mainyerror();
		}
	for(int i=0;i<34;i++)
		{
		variable[i].number=forkeeping[i];
		variable[i].iserror=forkeepingerror[i];
		}
//	showmouse();
	return 1;
	}
if(key==KEY_graphsave)
	{
	for(int i=0;i<34;i++)
		{
		forkeeping[i]=variable[i].number;
		if(!variable[i].isstring)
			{
			int len=convert_number2string(forkeeping[i],DECSYS,2);
			if(num2str_buffer[0]=='+')
				Strcpy(variable[i].string,num2str_buffer+1,len);
				else
				Strcpy(variable[i].string,num2str_buffer,len+1);
			}
		forkeepingerror[i]=variable[i].iserror;
		}
	return 1;
	}
if(key==KEY_move)
	{
	if(ispreview) return 1;
	int x=mev.xcoord,y=mev.ycoord;
	long double temp=FPU_add(FPU_mul(xscale,x),leftborder);
	if(FPUerror) FPUerror=0;
	showxcoord(temp);
	temp=FPU_add(FPU_mul(yscale,399-y),downborder);
	if(FPUerror) FPUerror=0;
	showycoord(temp);
	return 1;
	}
if(key==KEY_join)
	{
	joinpoints^=1;
	showoptions();
	return 1;
	}
if(key==KEY_redraw)
	{
	isredraw^=1;
	showoptions();
	return 1;
	}
if(key==KEY_auto)
	{
	isauto^=1;
	showoptions();
	if(isauto && activeinputline==visualgridstep)
		{
		visualgridstep->deactivate();
		activeinputline=0;
		}
	return 1;
	}
if(key==KEY_onlyvw)
	{
	if(!deactive || deactive==1)
		deactive=2;
		else
		deactive=0;
	showoptions();
	return 1;
	}
if(key==KEY_onlyxy)
	{
	if(!deactive || deactive==2)
		deactive=1;
		else
		deactive=0;
	showoptions();
	return 1;
	}
if(activeinputline && key<256)
	{
	if(activeinputline->takesymbol(key))
		if(activeinputline==&X_scale) wasxscalein=1;
			else if(activeinputline==&Y_scale) wasyscalein=1;
				else if(activeinputline==&VW_iter) wasvwiterin=1;
					else if(activeinputline==&XY_iter) wasxyiterin=1;
						else if(activeinputline==&X_Gridstep) wasxgridstepin=1;
							else wasygridstepin=1;
	return 1;
	}
if(key==KEY_leftcur)
	{
	activeinputline->movecursorleft();
	return 1;
	}
if(key==KEY_leftend)
	{
	activeinputline->movecursorhome();
	return 1;
	}
if(key==KEY_rightend)
	{
	activeinputline->movecursorend();
	return 1;
	}
if(key==KEY_rightcur)
	{
	activeinputline->movecursorright();
	return 1;
	}
if(activeinputline && key==KEY_del)
	{
	if(activeinputline->delsymbol())
		if(activeinputline==&X_scale) wasxscalein=1;
			else if(activeinputline==&Y_scale) wasyscalein=1;
				else if(activeinputline==&VW_iter) wasvwiterin=1;
					else if(activeinputline==&XY_iter) wasxyiterin=1;
						else if(activeinputline==&X_Gridstep) wasxgridstepin=1;
							else wasygridstepin=1;
	return 1;
	}
if(activeinputline && key==KEY_bs)
	{
	if(activeinputline->backdelsymbol())
		if(activeinputline==&X_scale) wasxscalein=1;
			else if(activeinputline==&Y_scale) wasyscalein=1;
				else if(activeinputline==&VW_iter) wasvwiterin=1;
					else if(activeinputline==&XY_iter) wasxyiterin=1;
						else if(activeinputline==&X_Gridstep) wasxgridstepin=1;
							else wasygridstepin=1;
	return 1;
	}
long double forxscale,foryscale,forleftb,forrightb,forupb,fordownb;
forxscale=xscale;foryscale=yscale;forleftb=leftborder;forrightb=rightborder;
forupb=upborder;fordownb=downborder;
if(wasxscalein) {readxscale();wasxscalein=0;}
if(wasyscalein) {readyscale();wasyscalein=0;}
if(key==KEY_preview)
	{
	yscale=FPU_div(FPU_mul(yscale,100.0),107.0);
	xscale=FPU_div(FPU_mul(xscale,15.0),16.0);
	convert_round(xscale);
	convert_round(yscale);
	xscrsize=640;
	yscrsize=428;
	if(FPUerror) FPUerror=0;
	if(mainyerror() || mainxerror())
		{
		yscale=foryscale;
		xscale=forxscale;
		xscrsize=600;
		yscrsize=400;
		return 1;
		}
	SETMOUSEXLIMIT(0,639);
	SETMOUSEYLIMIT(0,479);
	if(wasxyiterin) {readxyiter();wasxyiterin=0;}
	if(wasvwiterin) {readvwiter();wasvwiterin=0;}
	if(wasxgridstepin) {readxgridstep();wasxgridstepin=0;}
	if(wasygridstepin) {readygridstep();wasygridstepin=0;}
	ispreview=1;
	if(activeinputline)
		{
		activeinputline->deactivate();
		activeinputline=0;
		}
	hidemouse();
	mygr.drawfilledbox(0,0,639,479,15);
	Putstring(3,436,alltext[4],0,15);
	Putstring(323,436,alltext[5],0,15);
	Putstring(3,448,alltext[7],0,15);
	Putstring(323,448,alltext[6],0,15);
	Putstring(3,460,switchtext[0],0,15);
	Putstring(323,460,switchtext[1],0,15);
	showmouse();
	showleftborder();
	showrightborder();
	showupborder();
	showdownborder();
	showxgridstep();
	showygridstep();
	key=KEY_draw;
	goto labelfordraw;
	}
if(key==KEY_expandcenterscreen)
	{
	long double temp=FPU_add(FPU_mul(xscale,mev.xcoord),leftborder);
	xscale=FPU_mul(xscale,0.5);
	convert_round(xscale);
	rightborder=FPU_mul(xscale,xscrsize>>1);
	leftborder=FPUsub(temp,rightborder);
	rightborder=FPUadd(temp,rightborder);
	temp=FPU_add(FPU_mul(yscale,yscrsize-1-mev.ycoord),downborder);
	yscale=FPU_mul(yscale,0.5);
	convert_round(yscale);
	upborder=FPU_mul(yscale,yscrsize>>1);
	downborder=FPUsub(temp,upborder);
	upborder=FPUadd(temp,upborder);
	if(FPUerror) FPUerror=0;
	if(mainyerror() || mainxerror())
		{
		yscale=foryscale;
		xscale=forxscale;
		downborder=fordownb;
		upborder=forupb;
		leftborder=forleftb;
		rightborder=forrightb;
		showxscale();
		showyscale();
		}
		else
		{
		showrightborder();
		showupborder();
		if(ispreview)
			{
			showleftborder();
			showdownborder();
			}
			else
			{
			convert_round(leftborder);
			convert_round(downborder);
			}
		key=KEY_draw;
		goto labelfordraw;
		}
	return 1;
	}
if(key==KEY_compresscenterscreen)
	{
	long double temp=FPU_add(FPU_mul(xscale,mev.xcoord),leftborder);
	xscale=FPU_mul(xscale,2.0);
	convert_round(xscale);
	rightborder=FPU_mul(xscale,xscrsize>>1);
	leftborder=FPUsub(temp,rightborder);
	rightborder=FPUadd(temp,rightborder);
	temp=FPU_add(FPU_mul(yscale,yscrsize-1-mev.ycoord),downborder);
	yscale=FPU_mul(yscale,2.0);
	convert_round(yscale);
	upborder=FPU_mul(yscale,yscrsize>>1);
	downborder=FPUsub(temp,upborder);
	upborder=FPUadd(temp,upborder);
	if(FPUerror) FPUerror=0;
	if(mainyerror() || mainxerror())
		{
		yscale=foryscale;
		xscale=forxscale;
		downborder=fordownb;
		upborder=forupb;
		leftborder=forleftb;
		rightborder=forrightb;
		showxscale();
		showyscale();
		}
		else
		{
		showrightborder();
		showupborder();
		if(ispreview)
			{
			showleftborder();
			showdownborder();
			}
			else
			{
			convert_round(leftborder);
			convert_round(downborder);
			}
		key=KEY_draw;
		goto labelfordraw;
		}
	return 1;
	}
if(key==KEY_centerscreen)
	{
	long double temp=FPU_add(FPU_mul(xscale,mev.xcoord),leftborder);
	rightborder=FPU_mul(xscale,xscrsize>>1);
	leftborder=FPUsub(temp,rightborder);
	rightborder=FPUadd(temp,rightborder);
	temp=FPU_add(FPU_mul(yscale,yscrsize-1-mev.ycoord),downborder);
	upborder=FPU_mul(yscale,yscrsize>>1);
	downborder=FPUsub(temp,upborder);
	upborder=FPUadd(temp,upborder);
	if(FPUerror) FPUerror=0;
	if(mainyerror() || mainxerror())
		{
		downborder=fordownb;
		upborder=forupb;
		leftborder=forleftb;
		rightborder=forrightb;
		}
		else
		{
		showrightborder();
		showupborder();
		if(ispreview)
			{
			showleftborder();
			showdownborder();
			}
			else
			{
			convert_round(leftborder);
			convert_round(downborder);
			}
		key=KEY_draw;
		goto labelfordraw;
		}
	return 1;
	}
if(key==KEY_center)
	{
	long double temp;
	temp=FPU_mul(xscale,xscrsize>>1);
	leftborder=FPU_sub(0,temp);
	rightborder=FPU_add(0,temp);
	if(FPUerror) FPUerror=0;
	if(mainxerror())
		{
		leftborder=forleftb;
		rightborder=forrightb;
		}
	temp=FPU_mul(yscale,yscrsize>>1);
	downborder=FPU_sub(0,temp);
	upborder=FPU_add(0,temp);
	if(FPUerror) FPUerror=0;
	if(mainyerror())
		{
		downborder=fordownb;
		upborder=forupb;
		}
	showupborder();
	showrightborder();
	if(ispreview)
		{
		showleftborder();
		showdownborder();
		}
		else
		{
		convert_round(leftborder);
		convert_round(downborder);
		}
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
//	clearworkfield();
	return 1;
	}
if(key==KEY_eval)
	{
	long double temp;
	xscale=yscale;
	temp=FPU_mul(xscale,xscrsize>>1);
	rightborder=FPU_div(FPUadd(leftborder,rightborder),2);
	leftborder=FPUsub(rightborder,temp);
	rightborder=FPUadd(rightborder,temp);
	if(FPUerror) FPUerror=0;
	if(mainxerror())
		{
		xscale=forxscale;
		leftborder=forleftb;
		rightborder=forrightb;
		}
//	hidemouse();
	showrightborder();
	showleftborder();
	showxscale();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_evalrev)
	{
	long double temp;
	yscale=xscale;
	temp=FPU_mul(yscale,yscrsize>>1);
	upborder=FPU_div(FPUadd(downborder,upborder),2);
	downborder=FPUsub(upborder,temp);
	upborder=FPUadd(upborder,temp);
	if(FPUerror) FPUerror=0;
	if(mainyerror())
		{
		yscale=foryscale;
		downborder=fordownb;
		upborder=forupb;
		}
//	hidemouse();
	showupborder();
	showdownborder();
	showyscale();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_movescrright || key==KEY_movescrleft)
	{
	if(key==KEY_movescrright)
		{
		rightborder=FPUadd(rightborder,xscale);
		leftborder=FPUadd(leftborder,xscale);
		}
		else
		{
		rightborder=FPUsub(rightborder,xscale);
		leftborder=FPUsub(leftborder,xscale);
		}
	if(FPUerror) FPUerror=0;
	if(mainxerror())
		{
		xscale=forxscale;
		leftborder=forleftb;
		rightborder=forrightb;
		}
//	hidemouse();
	showrightborder();
	showleftborder();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_movescrup || key==KEY_movescrdown)
	{
	if(key==KEY_movescrup)
		{
		upborder=FPUadd(upborder,yscale);
		downborder=FPUadd(downborder,yscale);
		}
		else
		{
		upborder=FPUsub(upborder,yscale);
		downborder=FPUsub(downborder,yscale);
		}
	if(FPUerror) FPUerror=0;
	if(mainyerror())
		{
		yscale=foryscale;
		downborder=fordownb;
		upborder=forupb;
		}
//  	hidemouse();
	showupborder();
	showdownborder();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_movewallupdown || key==KEY_movewallup)
	{
	if(key==KEY_movewallupdown)
		yscale=FPU_mul(yscale,0.8);
		else
		yscale=FPU_mul(yscale,1.25);
	convert_round(yscale);
	upborder=FPU_add(downborder,FPU_mul(yscale,yscrsize));
	if(FPUerror) FPUerror=0;
	if(mainyerror())
		{
		yscale=foryscale;
		downborder=fordownb;
		upborder=forupb;
		}
//	hidemouse();
	showupborder();
	showdownborder();
	showyscale();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_movewalldownup || key==KEY_movewalldown)
	{
	if(key==KEY_movewalldownup)
		yscale=FPU_mul(yscale,0.8);
		else
		yscale=FPU_mul(yscale,1.25);
	convert_round(yscale);
	downborder=FPU_sub(upborder,FPU_mul(yscale,yscrsize));
	if(FPUerror) FPUerror=0;
	if(mainyerror())
		{
		yscale=foryscale;
		downborder=fordownb;
		upborder=forupb;
		}
//	hidemouse();
	showupborder();
	showdownborder();
	showyscale();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_movewallleftright || key==KEY_movewallleft)
	{
	if(key==KEY_movewallleftright)
		xscale=FPU_mul(xscale,0.8);
		else
		xscale=FPU_mul(xscale,1.25);
	convert_round(xscale);
	leftborder=FPU_sub(rightborder,FPU_mul(xscale,xscrsize));
	if(FPUerror) FPUerror=0;
	if(mainxerror())
		{
		xscale=forxscale;
		leftborder=forleftb;
		rightborder=forrightb;
		}
//	hidemouse();
	showrightborder();
	showleftborder();
	showxscale();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_movewallrightleft || key==KEY_movewallright)
	{
	if(key==KEY_movewallrightleft)
		xscale=FPU_mul(xscale,0.8);
		else
		xscale=FPU_mul(xscale,1.25);
	convert_round(xscale);
	rightborder=FPU_add(leftborder,FPU_mul(xscale,xscrsize));
	if(FPUerror) FPUerror=0;
	if(mainxerror())
		{
		xscale=forxscale;
		leftborder=forleftb;
		rightborder=forrightb;
		}
//	hidemouse();
	showrightborder();
	showleftborder();
	showxscale();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_xexpand || key==KEY_xcompress)
	{
	if(key==KEY_xexpand)
		xscale=FPU_mul(xscale,0.8);
		else
		xscale=FPU_mul(xscale,1.25);
	long double temp;
	convert_round(xscale);
	temp=FPU_mul(xscale,xscrsize>>1);
	rightborder=FPU_div(FPUadd(leftborder,rightborder),2);
	leftborder=FPUsub(rightborder,temp);
	rightborder=FPUadd(rightborder,temp);
	if(FPUerror) FPUerror=0;
	if(mainxerror())
		{
		xscale=forxscale;
		leftborder=forleftb;
		rightborder=forrightb;
		}
//	hidemouse();
	showrightborder();
	showleftborder();
	showxscale();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_yexpand || key==KEY_ycompress)
	{
	if(key==KEY_yexpand)
		yscale=FPU_mul(yscale,0.8);
		else
		yscale=FPU_mul(yscale,1.25);
	convert_round(xscale);
	long double temp;
	temp=FPU_mul(yscale,yscrsize>>1);
	upborder=FPU_div(FPUadd(downborder,upborder),2);
	downborder=FPUsub(upborder,temp);
	upborder=FPUadd(upborder,temp);
	if(FPUerror) FPUerror=0;
	if(mainyerror())
		{
		yscale=foryscale;
		downborder=fordownb;
		upborder=forupb;
		}
//  	hidemouse();
	showyscale();
	showupborder();
	showdownborder();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
if(key==KEY_expand || key==KEY_compress)
	{
	long double temp;
	if(key==KEY_expand)
		{
		yscale=FPU_mul(yscale,0.8);
		xscale=FPU_mul(xscale,0.8);
		}
		else
		{
		yscale=FPU_mul(yscale,1.25);
		xscale=FPU_mul(xscale,1.25);
		}
	convert_round(xscale);
	convert_round(yscale);
	temp=FPU_mul(xscale,xscrsize>>1);
	rightborder=FPU_div(FPUadd(leftborder,rightborder),2);
	leftborder=FPUsub(rightborder,temp);
	rightborder=FPUadd(rightborder,temp);
	temp=FPU_mul(yscale,yscrsize>>1);
	upborder=FPU_div(FPUadd(downborder,upborder),2);
	downborder=FPUsub(upborder,temp);
	upborder=FPUadd(upborder,temp);
	if(FPUerror) FPUerror=0;
	if(mainyerror() || mainxerror())
		{
		yscale=foryscale;
		downborder=fordownb;
		upborder=forupb;
		xscale=forxscale;
		leftborder=forleftb;
		rightborder=forrightb;
		}
//	hidemouse();
	showrightborder();
	showupborder();
	if(ispreview)
		{
		showleftborder();
		showdownborder();
		}
		else
		{
		convert_round(leftborder);
		convert_round(downborder);
		}
	showyscale();
	showxscale();
//	showmouse();
	if(isredraw) {key=KEY_draw;goto labelfordraw;}
	return 1;
	}
yscale=foryscale;
xscale=forxscale;
showyscale();
showxscale();
return 1;
}

void drawgraphkeys(void)
{
BUT_graphhelplock.draw();
BUT_graphrowslock.draw();
if(isrows) BUT_graphrowslock.push();
BUT_graphgridlock.draw();
if(isgrid) BUT_graphgridlock.push();

BUT_movescrleft.draw();
BUT_movescrright.draw();
BUT_movescrup.draw();
BUT_movescrdown.draw();
BUT_movewallleft.draw();
BUT_movewallleftright.draw();
BUT_movewallright.draw();
BUT_movewallrightleft.draw();
BUT_movewallup.draw();
BUT_movewallupdown.draw();
BUT_movewalldown.draw();
BUT_movewalldownup.draw();
BUT_xexpand.draw();
BUT_xcompress.draw();
BUT_yexpand.draw();
BUT_ycompress.draw();
BUT_expand.draw();
BUT_compress.draw();
BUT_eval.draw();
BUT_evalrev.draw();
BUT_draw.draw();
BUT_clear_graph.draw();
BUT_preview.draw();
BUT_stop.draw();
BUT_step.draw();
BUT_cont.draw();
BUT_center.draw();
BUT_quit.draw();
BUT_save.draw();
}

void drawmainview(void)
{
iserrormessage=0;
activeinputline=0;
xscrsize=600;
yscrsize=400;
FPUerror=0;
//mygr.drawfilledbox(0,0,639,399,0);
hidemouse();
mygr.drawtwocoloredbox(600,0,639,479,15,8);
mygr.drawfilledbox(0,400,639,479,7);
mygr.drawtwocoloredbox(0,400,639,479,15,8);
mygr.drawfilledbox(601,1,638,478,7);
drawgraphkeys();
//hidemouse();
clearworkfield();
leftshow=rightshow=100;
Putstring(583,417,"Связь",15,7);
Putstring(336,437,"Авто шаг",15,7);
Putstring(446-8,437,"Только VW",15,7);
Putstring(551,437,"Только XY",15,7);
Putstring(551,457,"Обновлять",15,7);
X_scale.draw();
madexscalevisual(1);
VW_iter.draw();
madevwitervisual(1);
X_Gridstep.draw();
madexgridstepvisual(1);
wasxscalein=0;
wasyscalein=0;
wasxyiterin=0;
wasvwiterin=0;
wasxgridstepin=0;
wasygridstepin=0;
showrightborder();
showupborder();
showxscale();
showyscale();
showvwiter();
showxyiter();
showxgridstep();
showygridstep();
Join.draw();
Only_XY.draw();
Only_VW.draw();
Redraw.draw();
Autogrid.draw();
showoptions();
setgraphstate(0);
showmouse();
}

int graphdraw(void)
{
isgraphhelp=0;
ispreview=0;
//char workbuf[30];
//visualscale=&X_scale;
//visualiter=&XY_iter;
for(int i=0;i<34;i++)
	{
	forkeeping[i]=variable[i].number;
	forkeepingerror[i]=variable[i].iserror;
	}
//*************************************************************************
//*************************************************************************
if(variable['V'-'A'].ison && !variable['W'-'A'].ison)
	{
	firststate=1;
	firstscale=yscale;
	firstsize=400;
	}
	else if(!variable['V'-'A'].ison && variable['W'-'A'].ison)
		{
		firststate=2;
		firstscale=xscale;
		firstsize=600;
		}
		else if(variable['V'-'A'].ison && variable['W'-'A'].ison)
			firststate=3;
				else
				firststate=0;
if(firststate==1 || firststate==2)
	if(firstlowlimit>firsthighlimit)
		firstrev=1;
		else
		firstrev=0;
//*************************************************************************
//*************************************************************************

if(variable['X'-'A'].ison && !variable['Y'-'A'].ison)
	{
	secondstate=1;
	secondscale=yscale;
	secondsize=400;
	}
	else if(!variable['X'-'A'].ison && variable['Y'-'A'].ison)
		{
		secondstate=2;
		secondscale=xscale;
		secondsize=600;
		}
		else if(variable['X'-'A'].ison && variable['Y'-'A'].ison)
			secondstate=3;
				else
				secondstate=0;
if(secondstate==1 || secondstate==2)
	if(secondlowlimit>secondhighlimit)
		secondrev=1;
		else
		secondrev=0;
//*************************************************************************
//*************************************************************************
drawmainview();
firstworkiter=0;
firstworking=firstlowlimit;
firstislast=0;
secondworkiter=0;
secondworking=secondlowlimit;
secondislast=0;
countrepeat=0;
while(1)
{
what_button=0;
while(!Kbhit() && (nomouse || !ismouseevent()))
	if(countrepeat)
		{
		unsigned long temp=Gettimerticks();
		if((countrepeat==2 && temp-lasttimerticks>=PAUSE_BEFORE_REPEAT) ||
			(countrepeat==1 && temp-lasttimerticks>=PAUSE_BETWEEN_REPEAT))
			{
			countrepeat=1;
			lasttimerticks=temp;
			if(!convertgraphevent(receivegraphmouseevent(1))) goto toquit;
			}
		}
if(Kbhit())
	if(!convertgraphevent(receivegraphkeyevent())) break;
if(!nomouse && ismouseevent())
	if(!convertgraphevent(receivegraphmouseevent())) break;
}
readvwiter();
readxyiter();
readxscale();
readyscale();
readxgridstep();
readygridstep();
if(Kbhit())
	if(receivegraphkeyevent()==KEY_exit) throw int(0);
//Getkey();
toquit:
for(i=0;i<34;i++)
	{
	variable[i].number=forkeeping[i];
	variable[i].iserror=forkeepingerror[i];
	}
current_string=main_string;
current_flags=main_flags;
current_number=&main_number;
current_len=Strlen(current_string);
current_mode=prev_mode;
input_pointer=last_input_pointer;
indic.settext(Error_messages[0]);
drawconsol(1);
drawallkeys();
drawvariables();
if(current_mode==0)
	showcurrentstring(mainstate,0);
	else
	shownumonindic(main_number,cur_ans_system,1);
showmouse();
return 1;
}


