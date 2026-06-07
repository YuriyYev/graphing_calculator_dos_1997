#include"..\express\calcbut.hpp"

extern _MouseEvent mev;
extern Graph18 mygr;
void showmouse(void);
void hidemouse(void);
void Putsymbol(symbol *,int,int,int,int,int=0);
extern int what_button,nomouse;
#define KEY_RAD     	0x12b
#define KEY_DEG     	0x12c
#define KEY_GRD     	0x12d

void Calc_2button::hidemouse_but(void)
{
hidemouse();
//SETMOUSEEXLUSIONAREA(Xcoord-2,Ycoord-2,Xcoord+Xsize+1,Ycoord+Ysize+1);
}


void Calc_2button::draw(void)
{
hidemouse();
mygr.drawfilledbox(Xcoord+2,Ycoord+2,Xcoord+Xsize-3,Ycoord+Ysize-3,Backcolor);
mygr.drawtwocoloredbox(Xcoord,Ycoord,Xcoord+Xsize-1,Ycoord+Ysize-1,Firstbordercolor,6);
mygr.drawtwocoloredbox(Xcoord+1,Ycoord+1,Xcoord+Xsize-2,Ycoord+Ysize-2,Backcolor,Secondbordercolor);
Putsymbol(Icon1,Xcoord+(Xsize-Icon1->xsize)/2,Ycoord+(Ysize-Icon1->ysize)/2,Iconcolor1,Backcolor,deactivated);
showmouse();
State=0;
}

void Calc_2button::setactivities(int mode)
{
char ifis=0;
_AX=activity;
//asm xor dl,dl
asm mov cx,[mode]
asm inc cx
asm shr ax,cl
asm adc [ifis],0
//asm add cx,7
//asm bt ax,cx
//asm adc dl,0
//asm add dl,dl
//asm add [ifis],dl
if(ifis)
	activate();
	else
	deactivate();
}

void Calc_2button::deactivate(void)
{
int d=0;
if(State==1) d=1;
deactivated=1;
Putsymbol(Icon1,Xcoord+(Xsize-Icon1->xsize)/2+d,Ycoord+(Ysize-Icon1->ysize)/2+d,Iconcolor1,Backcolor,1);
}

void Calc_2button::activate(void)
{
int d=0;
if(State==1) d=1;
deactivated=0;
Putsymbol(Icon1,Xcoord+(Xsize-Icon1->xsize)/2+d,Ycoord+(Ysize-Icon1->ysize)/2+d,Iconcolor1,Backcolor);
}


int Calc_2button::event(int noact)
{
int x,y;
x=mev.xcoord;
y=mev.ycoord;
if((!State || islock) && mev.event&ME_RIGHTPRESSED && mev.keystate==2)
	if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
		{
		what_button=But1+32000;
		return 1;
		}
if((!State || islock) && (!deactivated || noact))
	if(mev.event&ME_LEFTPRESSED)
		if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
			{
			if(!State && !noact)
				{
				push();
				}
				else if(!noact) draw();
			if(islock || noact) {what_button=But1;return 1;}
			return 0;
			}
if(State && !islock)
	if(mev.event&ME_LEFTRELEASED)
		{
		if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
			if((!deactivated || noact) && State==1)
				what_button=But1;
				else
				what_button=0;
		if(State==1) draw();
		State=0;
		return 1;
		}
	else
	if(mev.event&ME_MOVED)
		if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
			{
			if(State==2)
				{
            push();
				return 1;
				}
			}
			else if(State==1)
				{
				draw();
				State=2;
				return 1;
				}

/*if(!State || (islock && State && !deactivated))
	if((mev.event&ME_LEFTPRESSED && mev.keystate==1) || (mev.event&ME_RIGHTPRESSED && mev.keystate==2 && But2))
		if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
			{
			if(!State && (!islock || (!noact && !deactivated)))
				{
				hidemouse();
				mygr.drawfilledbox(Xcoord+2,Ycoord+2,Xcoord+Xsize-3,Ycoord+Ysize-3,Backcolor);
				mygr.drawtwocoloredbox(Xcoord,Ycoord,Xcoord+Xsize-1,Ycoord+Ysize-1,6,Firstbordercolor);
				mygr.drawtwocoloredbox(Xcoord+1,Ycoord+1,Xcoord+Xsize-2,Ycoord+Ysize-2,Secondbordercolor,Backcolor);
					Putsymbol(Icon1,Xcoord+(Xsize-Icon1->xsize)/2+1,Ycoord+(Ysize-Icon1->ysize)/2+1,Iconcolor1,Backcolor,deactivated);
				showmouse();
				if(mev.event&ME_LEFTPRESSED)
					State=1;
				if(mev.event&ME_RIGHTPRESSED)
					State=2;
				}
				else if(!noact) draw();
			if(islock) {what_button=But1;return 1;}
			return 0;
			}
if(State && !islock)
	if(mev.event&(ME_LEFTRELEASED|ME_RIGHTRELEASED))
		{
		if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
			{
			if(mev.event&ME_LEFTRELEASED && (!deactivated || noact) && State==1)
				what_button=But1;
				else
				if(mev.event&ME_RIGHTRELEASED && (!deactivated || noact) && State==2)
					what_button=But2;
					else what_button=0;
			}
		if(mev.event&ME_LEFTRELEASED && State==1) State=0;
		if(mev.event&ME_RIGHTRELEASED && State==2) State=0;
		if(!State) draw();
		return 1;
		}*/
return 0;
}

void Calc_2button::push(void)
{
if(State!=1)
	{
	hidemouse();
	mygr.drawxline_rel(Xcoord+(Xsize-Icon1->xsize)/2,Icon1->xsize,Ycoord+(Ysize-Icon1->ysize)/2,Backcolor);
	mygr.drawyline_rel(Ycoord+(Ysize-Icon1->ysize)/2,Icon1->ysize,Xcoord+(Xsize-Icon1->xsize)/2,Backcolor);
	mygr.drawtwocoloredbox(Xcoord,Ycoord,Xcoord+Xsize-1,Ycoord+Ysize-1,6,Firstbordercolor);
	mygr.drawtwocoloredbox(Xcoord+1,Ycoord+1,Xcoord+Xsize-2,Ycoord+Ysize-2,Secondbordercolor,Backcolor);
	Putsymbol(Icon1,Xcoord+(Xsize-Icon1->xsize)/2+1,Ycoord+(Ysize-Icon1->ysize)/2+1,Iconcolor1,Backcolor,deactivated);
	showmouse();
	State=1;
	}
}

int Calc_2button::evente(void)
{
int x,y;
x=mev.xcoord;
y=mev.ycoord;
if(State)
	if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
		{
		if(!deactivated && State==1)
			what_button=But1;
//			else
//			if(Iconcolor2!=8 && State==2)
//				what_button=But2;
				else what_button=0;
		return 1;
		}
return 0;
}

void System_field::hidemouse_sys(void)
{
hidemouse();
//	SETMOUSEEXLUSIONAREA(Xcoord,Ycoord,Xcoord+Xsize-1,Ycoord+Ysize-1);
}


void System_field::draw(void)
{
int col=Deactivecolor;
if(State) col=Activecolor;
hidemouse_sys();
mygr.drawtwocoloredbox_rel(Xcoord,Ycoord,Xsize,Ysize,Firstbordercolor,Secondbordercolor);
mygr.drawtwocoloredbox_rel(Xcoord+1,Ycoord+1,Xsize-2,Ysize-2,6,7);
mygr.drawfilledbox_rel(Xcoord+2,Ycoord+2,Xsize-4,Ysize-4,col);
showmouse();
}

void System_field::turn_on(void)
{
if(!State) {State=1;draw();}
}

void System_field::turn_off(void)
{
if(State) {State=0;draw();}
}

int System_field::event(void)
{
int x,y;
x=mev.xcoord;
y=mev.ycoord;
if(mev.event&(ME_LEFTPRESSED|ME_RIGHTPRESSED))
	if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
		{
		if(mev.event&ME_LEFTPRESSED)
			what_button=but;
			else if(mev.keystate==2)
//					if(but>=KEY_RAD && but<=KEY_GRD)
						what_button=but+32000;
		return 1;
		}
return 0;
}

