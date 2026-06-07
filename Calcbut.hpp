#include "..\express\mymouse.hpp"
#include "..\express\graph18.hpp"
#include "..\express\common.hpp"

#define PAUSE_BEFORE_REPEAT 9
#define PAUSE_BETWEEN_REPEAT 2

#ifndef __symbol__
struct symbol
{
int xsize,ysize;//Размер символа
unsigned char *buf;//Изображение символа
};
#define __symbol__
#endif


class Calc_2button
{
        int activity;//битовая маска, определяющая в каких режимах кнопка активирована
	int But1,islock,deactivated;
	int Xcoord,Ycoord,Xsize,Ysize,State;
	symbol *Icon1;
	int Backcolor,Iconcolor1,Firstbordercolor,Secondbordercolor;
public:
	Calc_2button(void) {}
	Calc_2button(int activ,int xc,int yc,int xs,int ys,int b1,int b2,symbol *s1,symbol *s2,int ic1,int ic2,int bc=7,int is=0)
		{
		islock=is;
		activity=activ;
		Xcoord=xc;
		Ycoord=yc;
		Xsize=xs;
		Ysize=ys;
		But1=b1;
		Firstbordercolor=15;
		Secondbordercolor=8;
		State=0;
		Icon1=s1;
		Backcolor=bc;
		Iconcolor1=ic1;
		deactivated=0;
		}
	~Calc_2button()	{}
void setcoordinate(int xc,int yc) {Xcoord=xc;Ycoord=yc;}
int getxcoord(void)	         {return Xcoord;}
int getycoord(void)	         {return Ycoord;}
void setsize(int xs,int ys)  {Xsize=xs;Ysize=ys;}
int getxsize(void)           {return Xsize;}
int getysize(void)           {return Ysize;}
int getstate(void) {return State;}
int isactive1(void) {return !deactivated;}
void setactivities(int);
void seticons(symbol *s1)
	{
	Icon1=s1;
	}
void seticonscolors(int fcol1,int bcol=7)
	{
	Backcolor=bcol;
	Iconcolor1=fcol1;
	}
void setbordercolors(int fir=15,int sec=0)
	{
	Firstbordercolor=fir;
	Secondbordercolor=sec;
	}
void setbuttons(int b1)
{
But1=b1;
}
void draw(void);
void push(void);
int event(int=0);
int evente(void);
void deactivate(void);
void activate(void);
void hidemouse_but(void);
};


class System_field
{
	int Xcoord,Ycoord,Xsize,Ysize,Activecolor,Deactivecolor;
	int Firstbordercolor,Secondbordercolor;
	int State,but;
public:
	System_field(void) {}
	System_field(int xc,int yc,int xs,int ys,int b,int acol,int dcol)
		{
		but=b;
		Xcoord=xc;
		Ycoord=yc;
		Xsize=xs;
		Ysize=ys;
		Activecolor=acol;
		Deactivecolor=dcol;
		Firstbordercolor=8;
		Secondbordercolor=15;
		State=0;
		}
	~System_field(void) {}
void init_System_field(int xc,int yc,int xs,int ys,int b,int acol,int dcol)
	{
	but=b;
	Xcoord=xc;
	Ycoord=yc;
	Xsize=xs;
	Ysize=ys;
	Activecolor=acol;
	Deactivecolor=dcol;
	Firstbordercolor=8;
	Secondbordercolor=15;
	State=0;
	}

void setbordercolors(int fir=0,int sec=15)
	{
	Firstbordercolor=fir;
	Secondbordercolor=sec;
	}

void turn_on(void);
void turn_off(void);
void draw();
int event(void);
void hidemouse_sys(void);
};

