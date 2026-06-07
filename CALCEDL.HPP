#include "..\express\mymouse.hpp"
#include "..\express\graph18.hpp"
#include "..\express\common.hpp"


#define INDIC_X_COOR 5   //Х-координата начала индикатора
#define INDIC_Y_COOR 180  //Y-координата начала индикатора
#define INDIC_X_SIZE 630
#define INDIC_Y_SIZE 36
#define BUFFER_SIZE 1024 //Размер буфера индикатора

struct CursorState
{
int curpos,vidpos,firstoffset,curoffset,isedit,Lefteditpos,Righteditpos;
void init(int c,int v,int f,int co,int ed,int lp,int rp)
	{
	curpos=c;
	vidpos=v;
	firstoffset=f;
	curoffset=co;
	isedit=ed;
	Lefteditpos=lp;
	Righteditpos=rp;
	}
};


class Calc_indicator
{
	const int Xcoord,Ycoord,Xsize,Ysize,Maxtextlen;
	int Printyoffset,Textlen,Curpos,Vidpos,Width;
	int Curstate,Curoffset,Curcount,ismousedown;
	int Symbolcolor,Backcolor,Editcolor;
	char *Text;
	int Leftborder,Rightborder,Firstsymboloffset;
	int Leftarrowstate,Rightarrowstate,Endarrowstate;
public:
	int insertmode;
	int isedit,Lefteditpos,Righteditpos;
	Calc_indicator():Xcoord(INDIC_X_COOR),Ycoord(INDIC_Y_COOR),Xsize(INDIC_X_SIZE),
		Ysize(INDIC_Y_SIZE),Maxtextlen(BUFFER_SIZE)
		{
		Printyoffset=Ycoord+Ysize-(Ysize-18)/2;
		Leftborder=10+Xcoord;
		Rightborder=Xcoord+Xsize-11;
		Width=Rightborder-Leftborder;
		Symbolcolor=0;
		Backcolor=11;
		Editcolor=3;
		insertmode=1;
		isedit=0;
		Curstate=-1;
		Leftarrowstate=0;Rightarrowstate=0;Endarrowstate=0;
		ismousedown=0;
//		Text=new char[BUFFER_SIZE+1];
		}

	~Calc_indicator()
		{
//		delete Text;
		}
CursorState getcursorstate(void)
	{
	CursorState temp;
	temp.curpos=Curpos;
	temp.vidpos=Vidpos;
	temp.firstoffset=Firstsymboloffset;
	temp.curoffset=Curoffset;
	temp.isedit=isedit;
    temp.Lefteditpos=Lefteditpos;
	temp.Righteditpos=Righteditpos;
	return temp;
	}
void restorecursorstate(CursorState state)
	{
	isedit=0;
	Curpos=state.curpos;
	Vidpos=state.vidpos;
	Firstsymboloffset=state.firstoffset;
	Curoffset=state.curoffset;
	isedit=state.isedit;
	Lefteditpos=state.Lefteditpos;
	Righteditpos=state.Righteditpos;
	}
void setcolors(int tex=0,int back=11)
	{
	Backcolor=back;
	Symbolcolor=tex;
	}

void settext(char far*text);
const char *gettext(void)
	{
//	Text[Textlen]='\0';
	return Text;
	}
int gettextlength(void) {return Textlen;}
int getcursorposition(void) {return Curpos;}
void inversecursor(void);
void showcursor(void)
	{
	if(Curcount<0) Curcount++;
	if(!Curcount) if(!Curstate) inversecursor();
	}
void hidecursor(void)
	{
	Curcount--;
	if(Curcount) if(Curstate) inversecursor();
	}
void cursorflash(void);
void scroll(void);
void activate(void)
	{
	Curcount=-1;
	showcursor();
	}
void makearrows(int,int,int=0);

void deactivate(void)
	{
//	makearrows(-1,-1);
	hidecursor();
	Curcount=-1;
	}

void clear(void);
void draw(void);
void redraw(void);

void setcursorposition(int);

int event(int=0);
//void event(int keycode);

int changeinputtype(int,char* =0);
void putsymbol(char symbol,int xoffset,int,int);
void movecursorleft(int=0,int=0);
void movecursorright(int=0,int=0);
void movehome(int=0);
void moveend(int=0);
void movepageleft(int=0);
void movepageright(int=0);
int takesymbol(char,char*,char);
int delsymbol(int,char*);
int backdelsymbol(char*);
int inserttexttocursor(char *src,char*,char*);

void hidemouse_ind(void);
int operator!(void) {return (!Text);}
};



class Editline
{
	int Xcoord,Ycoord,Width,Curpos;
	char far*Text;
	int Textlen;
	int Backc,Textc,Curstate;
public:
	Editline(int xc,int yc,int size,char far*text,int bc,int tc)
		{
		Xcoord=xc;
		Ycoord=yc;
		Width=size;
		Backc=bc;
		Textc=tc;
		Curstate=0;
		Textlen=Strlen(text);
		Curpos=0;
		Text=new char[Width+1];
		if(Text) Strcpy(Text,text,Textlen+1);
		}

	~Editline(void)
		{
		if(Text) delete Text;
		}

//void setcoordinate(int xc,int yc) {lin_xcoord=xc;lin_ycoord=yc;}
//int getxcoord(void)	         {return lin_xcoord;}
//int getycoord(void)	         {return lin_ycoord;}
//void setwidth(int size)  {lin_width=size;}
//int getwidth(void)           {return lin_width;}

void settext(char far*text);
char *gettext(void) {Text[Textlen]='\0';return Text;}
int gettextlength(void) {return Textlen;}
//int getmaxtextlength(void) {return lin_maxtextlen;}

void movecursorleft(void);// {this->event('K'*256);}
void movecursorhome(void);// {this->event('K'*256);}
void movecursorright(void);// {this->event('M'*256);}
void movecursorend(void);// {this->event('M'*256);}
int delsymbol(void);
int backdelsymbol(void);
int takesymbol(char);
//int getcursorposition(void) {return lin_curpos;}
void inversecursor(void);
void deactivate(void)
	{
	if(Curstate) inversecursor();
	}
void activate(void)
	{
	if(!Curstate) inversecursor();
	}
void clear(void);
void draw(void);
void redraw(void);


void hidemouse_edl(void);
int event(void);
int operator!() {return !Text;}

};


