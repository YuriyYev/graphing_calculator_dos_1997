#include"..\express\calcedl.hpp"

//#ifndef __symbol__
struct symbol
{
int xsize,ysize;//Размер символа
unsigned char *buf;//Изображение символа
};
//#define __symbol__
//#endif
extern int nomouse;
extern _MouseEvent mev;
extern symbol *symboltable[];
extern symbol *asciisymboltable[];
extern Graph18 mygr;
void showmouse(void);
void hidemouse(void);
void Putsymbol(symbol *,int,int,int,int,int=0);
//void wait(long);
extern symbol S_LEFTARROW;
extern symbol S_RIGHTARROW;

extern int Indic_buffer_len;
extern char *Indic_buffer,*Indic_flags;
/**********************************************************************
***********************************************************************/

void Calc_indicator::hidemouse_ind(void)
{
hidemouse();
//if(!nomouse)
//	SETMOUSEEXLUSIONAREA(Xcoord-3,Ycoord-3,Xcoord+Xsize+2,Ycoord+Ysize+2);
}

void Calc_indicator::cursorflash(void)
	{
    if(!Curcount)
		{
		if(insertmode)
			hidemouse();
//			SETMOUSEEXLUSIONAREA(Curoffset+Leftborder-8,Ycoord-8,Curoffset+Leftborder+8,Ycoord+Ysize-1);
			else
			{
			int p_end;
			if(Curpos<Textlen) p_end=symboltable[Text[Curpos]]->xsize;
				else p_end=symboltable[' ']->xsize;
			hidemouse();
//			SETMOUSEEXLUSIONAREA(Curoffset+Leftborder-5,Ycoord,Curoffset+Leftborder+p_end+5,Ycoord+Ysize-1);
			}
//        hidemouse_ind();
		inversecursor();
		showmouse();
		}
	}



int Calc_indicator::changeinputtype(int ised,char*flags)
	{
	ismousedown=0;
	if(!ised)
		{
		hidemouse_ind();
		hidecursor();
		insertmode=!insertmode;
		if(isedit)
			{
			isedit=0;
			redraw();
			}
		showcursor();
		showmouse();
		}
		else if(ised==1) //shift
				{
				if(isedit)
					{
					int tmp=Righteditpos-Lefteditpos;
					if(Textlen-tmp+Indic_buffer_len>Maxtextlen) return 0;
					for(int i=Righteditpos;i<=Textlen;i++)
						{
						Text[i-tmp]=Text[i];
						flags[i-tmp]=flags[i];
						}
					Textlen-=tmp;
					isedit=0;
					hidemouse_ind();
					hidecursor();
					Curpos=Lefteditpos;
					}
					else
					{
					if(Textlen+Indic_buffer_len>Maxtextlen) return 0;
					if(!Indic_buffer_len) return 1;
					hidemouse_ind();
					hidecursor();
					}
				inserttexttocursor(Indic_buffer,flags,Indic_flags);
				redraw();
				showcursor();
				showmouse();
				}
				else if(ised==2 && isedit)
						{
						Indic_buffer_len=Righteditpos-Lefteditpos;
						Strcpy(Indic_buffer,Text+Lefteditpos,Indic_buffer_len);
						Strcpy(Indic_flags,flags+Lefteditpos,Indic_buffer_len);
						Indic_buffer[Indic_buffer_len]='\0';
						Indic_flags[Indic_buffer_len]='\0';
						}
	return 1;
	}


void Calc_indicator::settext(char far*text)
	{
	Vidpos=0;
	Curpos=0;
	Curoffset=0;
	Curstate=0;
	isedit=0;
	Firstsymboloffset=0;
	ismousedown=0;
//	int i=0;
//	for(;*text;text++)
//		if(symboltable[*text]!=0 && symboltable[*text]->ysize>0)
//			Text[i++]=*text;
//	Textlen=i;
	Text=text;
	Textlen=Strlen(text);
//	Text[i]='\0';
	}

void Calc_indicator::makearrows(int left,int right,int end)
{
if(left==1 && !Leftarrowstate)
	{
	Putsymbol(symboltable[17],Xcoord+2,Printyoffset-S_LEFTARROW.ysize,Symbolcolor,Backcolor);
	Leftarrowstate=1;
	}
	else
	if(left==-1 && Leftarrowstate)
		{
		mygr.drawfilledbox(Xcoord+2,Printyoffset-S_LEFTARROW.ysize,Xcoord+6,Printyoffset-1,Backcolor);
		Leftarrowstate=0;
		}
if(right==1 && !Rightarrowstate)
	{
	Putsymbol(symboltable[16],Rightborder+3,Printyoffset-S_RIGHTARROW.ysize,Symbolcolor,Backcolor);
	Rightarrowstate=1;
	}
	else
	if(right==-1 && (Rightarrowstate || Endarrowstate))
		{
		mygr.drawfilledbox(Rightborder+3,Printyoffset-S_LEFTARROW.ysize,Rightborder+7,Printyoffset-1,Backcolor);
		Rightarrowstate=0;
		Endarrowstate=0;
		}
if(end==1 && !Endarrowstate)
	{
	Putsymbol(symboltable[17],Rightborder+3,Printyoffset-S_LEFTARROW.ysize,Symbolcolor,Backcolor);
	Endarrowstate=1;
	}
}

void Calc_indicator::clear(void)
	{
	mygr.drawfilledbox(Xcoord,Ycoord,Xcoord+Xsize-1,Ycoord+Ysize-1,Backcolor);
	Curstate=0;
	}

void Calc_indicator::draw(void)
	{
	clear();
	mygr.drawtwocoloredbox(Xcoord-1,Ycoord-1,Xcoord+Xsize-1+1,Ycoord+Ysize-1+1,6,7);
	mygr.drawtwocoloredbox(Xcoord-2,Ycoord-2,Xcoord+Xsize-1+2,Ycoord+Ysize-1+2,8,15);
	mygr.drawtwocoloredbox(Xcoord-3,Ycoord-3,Xcoord+Xsize-1+3,Ycoord+Ysize-1+3,8,15);
	Leftarrowstate=0;Rightarrowstate=0;Endarrowstate=0;
	redraw();
	}

void Calc_indicator::putsymbol(char symbol,int xoffset,int symcol,int backcol)
{
int worky=Printyoffset-symboltable[symbol]->ysize;
int worky_end=worky+symboltable[symbol]->ysize;
int workx=xoffset;
int workx_end=workx+symboltable[symbol]->xsize;
if(workx>=Leftborder && workx_end<Rightborder) {Putsymbol(symboltable[symbol],xoffset,worky,symcol,backcol);return;}
int adr=0,i;
unsigned char worknum=0,work;
for(;worky<worky_end;worky++)
	for(i=workx;i<workx_end;i++)
		{
		if(!worknum)
			{
			worknum=128;
			work=symboltable[symbol]->buf[adr];
			adr++;
			}
		if(i>=Leftborder && i<Rightborder)
			if(work&worknum) mygr.putpixel(i,worky,symcol);
				else mygr.putpixel(i,worky,backcol);
		worknum>>=1;
		}
}

void Calc_indicator::redraw(void)
{
Curstate=0;
int worksymbol=Vidpos;
int workoffset=Leftborder-Firstsymboloffset;
if(worksymbol>0 || Firstsymboloffset) makearrows(1,0);
	else makearrows(-1,0);
while(workoffset<Rightborder)
	if(worksymbol<Textlen)
		{
		if(isedit && worksymbol>=Lefteditpos && worksymbol<Righteditpos)
			putsymbol(Text[worksymbol],workoffset,Symbolcolor,Editcolor);
			else
			putsymbol(Text[worksymbol],workoffset,Symbolcolor,Backcolor);
		workoffset+=symboltable[Text[worksymbol]]->xsize;
		worksymbol++;
		}
		else
		{
		mygr.drawfilledbox(workoffset,Printyoffset-18,Rightborder-1,Printyoffset-1,Backcolor);
		makearrows(0,-1);
		if(worksymbol==Maxtextlen) makearrows(0,0,1);
		return;
		}
if(workoffset==Rightborder && worksymbol==Textlen)
	{
	makearrows(0,-1);
	if(worksymbol==Maxtextlen) makearrows(0,0,1);
	}
	else makearrows(0,1);
}

void Calc_indicator::setcursorposition(int pos)
{
ismousedown=0;
if(pos>Textlen) pos=Textlen;
if(pos<0) pos=0;
int o=0;
for(int i=pos;i>0;i--)
	if(o<Xsize/2) o+=symboltable[Text[i-1]]->xsize;
		else break;
Vidpos=i;
Firstsymboloffset=0;
Curoffset=o;
Curpos=pos;
//redraw();
}

int Calc_indicator::event(int noedit)
{
if(Curcount) return 0;
int x,y;
x=mev.xcoord;
y=mev.ycoord;
if(mev.event&ME_LEFTPRESSED)
	if(x>=Xcoord && x<Xcoord+Xsize && y>=Ycoord && y<Ycoord+Ysize)
		{
		hidemouse_ind();
		hidecursor();
		int smallestindex=Vidpos,smallestoffset=-Firstsymboloffset;
		int workindex=Vidpos+1;
		for(int i=-Firstsymboloffset+symboltable[Text[Vidpos]]->xsize;workindex<=Textlen && (i-symboltable[Text[workindex-1]]->xsize<Width) && (insertmode || i<=x-Leftborder);i+=symboltable[Text[workindex++]]->xsize)
			if(Abs(i-(x-Leftborder))<Abs(smallestoffset-(x-Leftborder)))
				{
				smallestoffset=i;
				smallestindex=workindex;
				}
		int ifnoinsert=symboltable[Text[smallestindex]]->xsize;
		if(smallestindex>=Textlen) ifnoinsert=symboltable[' ']->xsize;
		if(smallestoffset<0)
			{
			Firstsymboloffset=0;
			Curoffset=0;
			isedit=0;
			redraw();
			}
			else if(smallestoffset>=Width || (!insertmode && smallestoffset+ifnoinsert>=Width))
				{
				int temp=smallestoffset-Width;
				if(!insertmode)
					{
					temp+=ifnoinsert;
					Curoffset=Width-ifnoinsert;
					}
					else Curoffset=Width;
				while(symboltable[Text[Vidpos]]->xsize-Firstsymboloffset-temp<0)
					{
					Vidpos++;
					Firstsymboloffset-=symboltable[Text[Vidpos]]->xsize;
					}
				Firstsymboloffset=Firstsymboloffset+temp;
				isedit=0;
				redraw();
				}
				else Curoffset=smallestoffset;
		Curpos=smallestindex;
		if(isedit) {isedit=0;redraw();}
		showcursor();
		showmouse();
		if(!noedit)	ismousedown=1;
		Lefteditpos=Righteditpos=Curpos;
		return 1;
		}
if(mev.event&ME_LEFTRELEASED && ismousedown)
	{
	ismousedown=0;
	return 1;
	}
if(mev.event==ME_MOVED && mev.keystate==1 && (ismousedown && ismousedown<3) && x>=Leftborder && x<Rightborder && y>=Ycoord-50 && y<Ycoord+Ysize+50)
	{
	ismousedown=2;
	int fixedpos=Lefteditpos,movepos=Righteditpos,tCurpos=Curpos,tCuroffset=Curoffset;
	if(Curpos==Lefteditpos) {fixedpos=Righteditpos;movepos=Lefteditpos;}
	int smallestindex=Vidpos,smallestoffset=-Firstsymboloffset;
	int workindex=Vidpos+1;
	for(int i=-Firstsymboloffset+symboltable[Text[Vidpos]]->xsize;workindex<=Textlen && (i-symboltable[Text[workindex-1]]->xsize<Width) && (insertmode || i<=x-Leftborder);i+=symboltable[Text[workindex++]]->xsize)
		if(Abs(i-(x-Leftborder))<Abs(smallestoffset-(x-Leftborder)))
			{
			smallestoffset=i;
			smallestindex=workindex;
			}
	int ifnoinsert=symboltable[Text[smallestindex]]->xsize;
	if(smallestindex>=Textlen) ifnoinsert=symboltable[' ']->xsize;
	if(smallestoffset<0)
		{
		Firstsymboloffset=0;
		tCuroffset=0;
//		isedit=0;
//		redraw();
		}
		else if(smallestoffset>=Width || (!insertmode && smallestoffset+ifnoinsert>=Width))
			{
			int temp=smallestoffset-Width;
			if(!insertmode)
				{
				temp+=ifnoinsert;
				tCuroffset=Width-ifnoinsert;
				}
				else tCuroffset=Width;
			while(symboltable[Text[Vidpos]]->xsize-Firstsymboloffset-temp<0)
				{
				Vidpos++;
				Firstsymboloffset-=symboltable[Text[Vidpos]]->xsize;
				}
			Firstsymboloffset=Firstsymboloffset+temp;
//			isedit=0;
//			redraw();
			}
			else tCuroffset=smallestoffset;
	tCurpos=smallestindex;
	if(tCurpos!=movepos)
		{
		hidemouse();
		hidecursor();
		movepos=tCurpos;
		if(fixedpos==movepos)
			{
			Lefteditpos=Righteditpos=tCurpos;
			isedit=0;
			}
			else if(fixedpos>movepos)
					{
					Righteditpos=fixedpos;
					Lefteditpos=movepos;
					isedit=1;
					}
					else
					{
					Righteditpos=movepos;
					Lefteditpos=fixedpos;
					isedit=1;
					}

		redraw();
		Curpos=tCurpos;
		Curoffset=tCuroffset;
		showcursor();
		showmouse();
		}
	return 1;
	}
return 0;
}

void Calc_indicator::scroll(void)
{
int x,y;
GETMOUSEXY(x,y);
if(!ismousedown || x<Xcoord || (x>=Leftborder && x<=Rightborder) || x>=Xcoord+Xsize || y<Ycoord-50 || y>Ycoord+Ysize+50) return;
int speed;
int fixedpos=Lefteditpos,movepos=Righteditpos;
if(Curpos==Lefteditpos) {fixedpos=Righteditpos;movepos=Lefteditpos;}
if(x<Leftborder)
	{
	if(!Curpos) return;
	hidemouse();
	hidecursor();
	speed=(Leftborder-x)*(Leftborder-x);
	if(Vidpos>=speed) Vidpos-=speed;
		else Vidpos=0;
	Curpos=Vidpos;
	Curoffset=0;
	Firstsymboloffset=0;
	}
	else
	{
	if(Curpos==Textlen) return;
	hidemouse();
	hidecursor();
	speed=(x-Rightborder)*(x-Rightborder);
	int temp=-Firstsymboloffset,tempindex=Vidpos;
	while(temp<Width && tempindex<Textlen)
		temp+=symboltable[Text[tempindex++]]->xsize;
	if(tempindex+speed<Textlen) tempindex+=speed;
		else tempindex=Textlen;
	Curpos=tempindex;
	temp=0;
	while(temp<Width && tempindex>0)
		{
		temp+=symboltable[Text[tempindex-1]]->xsize;
		tempindex--;
		}
	if(temp>=Width)
		{
		Vidpos=tempindex;
		Firstsymboloffset=temp-Width;
		Curoffset=Width;
		}
		else
		{
		Vidpos=0;
		Firstsymboloffset=0;
		Curoffset=temp;
		}
	}
movepos=Curpos;
if(ismousedown==1 || ismousedown==3) {isedit=0;ismousedown=3;}
	else
	if(fixedpos==movepos)
		{
		Lefteditpos=Righteditpos=Curpos;
		isedit=0;
		}
		else if(fixedpos>movepos)
				{
				Righteditpos=fixedpos;
				Lefteditpos=movepos;
				isedit=1;
				}
				else
				{
				Righteditpos=movepos;
				Lefteditpos=fixedpos;
				isedit=1;
				}
redraw();
showcursor();
showmouse();
Wait(400000l);
return;
}


void Calc_indicator::inversecursor(void)
{
Curstate=!Curstate;
int workxoffset=Leftborder+Curoffset;
int workyoffset=Printyoffset-18-6;
int i;
int p_end;
if(Curpos<Textlen) p_end=symboltable[Text[Curpos]]->xsize;
	else p_end=symboltable[' ']->xsize;
if(workxoffset+p_end>=Rightborder) p_end=Rightborder-workxoffset;
for(int p=0;(p<p_end && !insertmode) || p<1;p++)
	for(i=0;i<30;i++)
		if(mygr.getpixel(workxoffset+p,workyoffset+i)==Symbolcolor)
			if(isedit && Curpos>=Lefteditpos && Curpos<Righteditpos && i>=6 && i<24)
				mygr.putpixel(workxoffset+p,workyoffset+i,Editcolor);
				else
				mygr.putpixel(workxoffset+p,workyoffset+i,Backcolor);
			else
			mygr.putpixel(workxoffset+p,workyoffset+i,Symbolcolor);
}

void Calc_indicator::movecursorleft(int ised,int istake)
{
ismousedown=0;
int i,k,dodraw=0;
if(Curpos>0)
	{
	hidemouse_ind();
	hidecursor();
	if(ised)
		if(isedit)
			{
			if(Curpos==Lefteditpos)
				{
				Lefteditpos--;
				if(Curpos>Vidpos+1)
					putsymbol(Text[Lefteditpos],Leftborder+Curoffset-symboltable[Text[Curpos-1]]->xsize,Symbolcolor,Editcolor);
				}
				else
				{
				Righteditpos--;
				if(Curpos>Vidpos+1)
					putsymbol(Text[Righteditpos],Leftborder+Curoffset-symboltable[Text[Curpos-1]]->xsize,Symbolcolor,Backcolor);
				}
			if(Lefteditpos==Righteditpos) isedit=0;
			}
			else
			{
			Righteditpos=Curpos;
			Lefteditpos=Curpos-1;
			if(Curpos>Vidpos+1)
				putsymbol(Text[Lefteditpos],Leftborder+Curoffset-symboltable[Text[Curpos-1]]->xsize,Symbolcolor,Editcolor);
			isedit=1;
			}
		else if(isedit) {isedit=0;dodraw=1;}
	if(Curpos<=Vidpos+1)
		{
		if(Curpos>=10) k=10;
			else k=Curpos;
		Curoffset=0;
		for(i=k;i>0;i--)
			Curoffset+=symboltable[Text[Curpos-i]]->xsize;
		if(Curpos==Vidpos+1) Vidpos-=k-1;
			else Vidpos-=k;
		Firstsymboloffset=0;
		if(!istake && !dodraw) redraw();
		}
	Curoffset-=symboltable[Text[Curpos-1]]->xsize;
	Curpos--;
	if(dodraw) redraw();
	showcursor();
//	SETMOUSEXY(_MouseState.xcoord,_MouseState.ycoord);
	showmouse();
	}
return;
}

void Calc_indicator::movecursorright(int ised,int istake)
{
ismousedown=0;
int i,temp,k;
if(Curpos<Textlen)
	{
	if(!istake || insertmode)
		{
		hidemouse_ind();
		hidecursor();
		}
	if(ised)
		if(isedit)
			{
			if(Curpos==Lefteditpos)
				{
				Lefteditpos++;
				if(symboltable[Text[Curpos]]->xsize+Curoffset<Width)
					putsymbol(Text[Curpos],Leftborder+Curoffset,Symbolcolor,Backcolor);
				}
				else
				{
				Righteditpos++;
				if(symboltable[Text[Curpos]]->xsize+Curoffset<Width)
					putsymbol(Text[Curpos],Leftborder+Curoffset,Symbolcolor,Editcolor);
				}
			if(Lefteditpos==Righteditpos) isedit=0;
			}
			else
			{
			Righteditpos=Curpos+1;
			Lefteditpos=Curpos;
			if(symboltable[Text[Curpos]]->xsize+Curoffset<Width)
				putsymbol(Text[Curpos],Leftborder+Curoffset,Symbolcolor,Editcolor);
			isedit=1;
			}
		else if(isedit) {isedit=0;istake=1;}
	if(symboltable[Text[Curpos]]->xsize+Curoffset>=Width)
		{
		if(Textlen-Curpos>10) k=10;
			else k=Textlen-Curpos-1;
		temp=Curoffset;
		for(i=0;i<k+1;i++)
			temp+=symboltable[Text[Curpos+i]]->xsize;
		temp-=Width;
		Curoffset-=temp-symboltable[Text[Curpos]]->xsize;
		temp+=Firstsymboloffset;
		while(symboltable[Text[Vidpos]]->xsize<=temp)
			{
			temp-=symboltable[Text[Vidpos]]->xsize;
			Vidpos++;
			}
		Firstsymboloffset=temp;
		redraw();
		}
		else
		{
		Curoffset+=symboltable[Text[Curpos]]->xsize;
		if(istake) redraw();
		}
	Curpos++;
	showcursor();
//	hidemouse();
	showmouse();
	}
return;
}
void Calc_indicator::movehome(int ised)
{
ismousedown=0;
if(Curpos)
	{
	hidemouse_ind();
	hidecursor();
	if(ised)
		if(isedit)
			{
			if(Curpos==Lefteditpos) Lefteditpos=0;
				else {Righteditpos=Lefteditpos;Lefteditpos=0;}
			if(Lefteditpos==Righteditpos) isedit=0;
			}
			else
			{
			Righteditpos=Curpos;
				Lefteditpos=0;
			isedit=1;
			}
		else isedit=0;
	Curpos=0;
	Curoffset=0;
	Vidpos=0;
	Firstsymboloffset=0;
	redraw();
	showcursor();
	showmouse();
	}
return;
}

void Calc_indicator::moveend(int ised)
{
ismousedown=0;
if(!Textlen || (Curpos>=Textlen && (Curoffset>=Width || (!Vidpos && !Firstsymboloffset)))) return ;
	if(ised)
		{
		if(isedit)
			{
			if(Curpos==Righteditpos) Righteditpos=Textlen;
				else {Lefteditpos=Righteditpos;Righteditpos=Textlen;}
			if(Lefteditpos==Righteditpos) isedit=0;
			}
			else if(Curpos!=Textlen)
					{
					Righteditpos=Textlen;
					Lefteditpos=Curpos;
					isedit=1;
					}
		}
		else isedit=0;
int temp=0;
int workindex=Textlen;
do
	{
	workindex--;
	temp+=symboltable[Text[workindex]]->xsize;
	} while(temp<Width && workindex);
hidemouse_ind();
hidecursor();
if(temp>=Width)
	{
	Curpos=Textlen;
	Curoffset=Width;
	Vidpos=workindex;
	Firstsymboloffset=temp-Curoffset;
	}
	else
	{
	Curpos=Textlen;
	Curoffset=temp;
	Vidpos=0;
	Firstsymboloffset=0;
	}
redraw();
showcursor();
showmouse();
return;
}

void Calc_indicator::movepageleft(int ised)
{
ismousedown=0;
if(!Curpos) return;
if(!Vidpos && !Firstsymboloffset)
	{
	hidemouse_ind();
	hidecursor();
	if(ised)
		{
		if(isedit)
			{
			if(Curpos==Lefteditpos) Lefteditpos=0;
				else {Righteditpos=Lefteditpos;Lefteditpos=0;}
			if(Lefteditpos==Righteditpos) isedit=0;
			}
			else
			{
			Righteditpos=Curpos;
			Lefteditpos=0;
			isedit=1;
			}
		redraw();
		}
		else if(isedit) {isedit=0;redraw();}
	Curpos=0;
	Curoffset=0;
	showcursor();
	showmouse();
	return;
	}
int temp=Curoffset+Firstsymboloffset;
int workindex=Vidpos;
while(temp<Width && workindex)
	{
	workindex--;
	temp+=symboltable[Text[workindex]]->xsize;
	}
hidemouse_ind();
hidecursor();
if(ised)
	if(isedit)
		{
		if(Curpos==Lefteditpos) Lefteditpos=workindex;
			else if(workindex>Lefteditpos) Righteditpos=workindex;
					else {Righteditpos=Lefteditpos;Lefteditpos=workindex;}
		if(Lefteditpos==Righteditpos) isedit=0;
		}
		else
		{
		Righteditpos=Curpos;
		Lefteditpos=workindex;
		isedit=1;
		}
	else isedit=0;
Curpos=workindex;
Firstsymboloffset=0;
Vidpos=workindex;
Curoffset=0;
redraw();
showcursor();
showmouse();
return;
}



void Calc_indicator::movepageright(int ised)
{
ismousedown=0;
if(!Textlen || (Curpos>=Textlen && (Curoffset>=Width || (!Vidpos && !Firstsymboloffset)))) return ;
int temp=0;
int workindex=Curpos;
while(temp<Width && workindex<Textlen)
	{
	temp+=symboltable[Text[workindex]]->xsize;
	workindex++;
	}
hidemouse_ind();
hidecursor();
Vidpos=Curpos; //только для выделения
if(temp<Width)
	{
	Curpos=workindex;
	if(Curoffset+temp>Width)
		Curoffset=Width;
		else
		Curoffset+=temp;
	}
	else
	{
	Curpos=workindex-1;
	Curoffset=temp-symboltable[Text[workindex-1]]->xsize;
	}
if(ised)
	if(isedit)
		{
		if(Vidpos==Righteditpos) Righteditpos=Curpos;
			else if(Curpos<Righteditpos) Lefteditpos=Curpos;
					else {Lefteditpos=Righteditpos;Righteditpos=Curpos;}
		if(Lefteditpos==Righteditpos) isedit=0;
		}
		else
		{
		Righteditpos=Curpos;
		Lefteditpos=Vidpos;
		isedit=1;
		}
	else isedit=0;
Vidpos=Curpos;
temp=Curoffset;
while(temp>0 && Vidpos)
	{
	Vidpos--;
	temp-=symboltable[Text[Vidpos]]->xsize;
	}
Firstsymboloffset=-temp;
redraw();
showcursor();
showmouse();
return;
}

int Calc_indicator::takesymbol(char symbol,char *flags,char flag)
{
ismousedown=0;
if(Curpos==Maxtextlen || (Textlen==Maxtextlen && insertmode)) return 0;
if(!symboltable[symbol] || !symboltable[symbol]->xsize) return 0;
if(!insertmode)
	{
	hidemouse_ind();
	hidecursor();
	Text[Curpos]=symbol;
	if(flags)flags[Curpos]=flag;
	if(Curpos==Textlen)	{Text[++Textlen]='\0';if(flags)flags[Textlen]='\0';}
	}
	else
	{
	for(int i=Textlen+1;i>Curpos;i--)
		{
		Text[i]=Text[i-1];
		if(flags)flags[i]=flags[i-1];
		}
	Textlen++;
	Text[Curpos]=symbol;
	if(flags)flags[Curpos]=flag;
	}
movecursorright(0,1);
return 1;
}

int Calc_indicator::delsymbol(int ised,char *flags)
{
ismousedown=0;
if(!isedit && ised) return 0;
if(!isedit)
	{
	if(Curpos==Textlen) return 0;
	hidemouse_ind();
	hidecursor();
	for(int i=Curpos+1;i<=Textlen;i++)
		{
		Text[i-1]=Text[i];
		flags[i-1]=flags[i];
		}
	Textlen--;
	}
	else
	{
	if(ised)
		{
		Indic_buffer_len=Righteditpos-Lefteditpos;
		Strcpy(Indic_buffer,Text+Lefteditpos,Indic_buffer_len);
		Strcpy(Indic_flags,flags+Lefteditpos,Indic_buffer_len);
		Indic_buffer[Indic_buffer_len]='\0';
		Indic_flags[Indic_buffer_len]='\0';
		}
	int tmp=Righteditpos-Lefteditpos;
	for(int i=Righteditpos;i<=Textlen;i++)
		{
		Text[i-tmp]=Text[i];
		flags[i-tmp]=flags[i];
		}
	Textlen-=tmp;
	isedit=0;
	hidemouse_ind();
	hidecursor();
	setcursorposition(Lefteditpos);
	}
redraw();
showcursor();
showmouse();
return 1;
}

int Calc_indicator::backdelsymbol(char *flags)
{
ismousedown=0;
if(isedit) return delsymbol(0,flags);
if(!Curpos) return 0;
movecursorleft(0,1);
delsymbol(0,flags);
return 1;
}

int Calc_indicator::inserttexttocursor(char *src,char *flagdst,char *flagsrc)
{
ismousedown=0;
int len=0,ptr=0;
while(src[ptr++])
	if(symboltable[src[ptr-1]] && symboltable[src[ptr-1]]->xsize) len++;
if(len+Textlen>Maxtextlen) return 0;
if(!len) return 1;
for(int i=Textlen+len;i>=Curpos+len;i--)
	{
	Text[i]=Text[i-len];
	flagdst[i]=flagdst[i-len];
	}
for(i=Curpos,ptr=0;i<Curpos+len;i++,ptr++)
	{
	while(!symboltable[src[ptr]] || !symboltable[src[ptr]]->xsize) ptr++;
	Text[i]=src[ptr];
	if(flagsrc) flagdst[i]=flagsrc[ptr];
	}
Textlen+=len;
isedit=0;
//hidecursor();
setcursorposition(Curpos+len);
//showcursor();
return 1;
}


void Editline::hidemouse_edl(void)
{
hidemouse();
//if(!nomouse)
//	SETMOUSEEXLUSIONAREA(Xcoord-1,Ycoord-1,Xcoord+8*(Width+1),Ycoord+12+8);
}

void Editline::settext(char far*text)
	{
	Textlen=Strlen(text);
	Curpos=0;
	Curstate=0;
	for(int i=0;i<=Textlen;i++)
		if(text[i]=='\xb3') Text[i]='E';
			else Text[i]=text[i];
//	if(Text) Strcpy(Text,text,Textlen+1);
	}

void Editline::clear(void)
	{
	mygr.drawtwocoloredbox(Xcoord,Ycoord,Xcoord+8*(Width+1)-1,Ycoord+12+6-1,8,15);
	mygr.drawfilledbox(Xcoord+1,Ycoord+1,Xcoord+8*(Width+1)-2,Ycoord+12+6-2,Backc);
	Curstate=0;
	}
void Editline::draw(void)
	{
	clear();
	redraw();
	Curstate=0;
	}

void Editline::redraw(void)
{
int xc=Xcoord+4;
for(int i=0;i<Width;i++)
	if(i<Textlen)
		{
		Putsymbol(asciisymboltable[Text[i]],xc,Ycoord+3,Textc,Backc);
		xc+=8;
		}
		else
		{
		mygr.drawfilledbox_rel(xc,Ycoord+3,8*(Width-i),12,Backc);
		break;
		}
}

void Editline::inversecursor(void)
{
Curstate=!Curstate;
int i;
int o=Xcoord+3+Curpos*8;
for(i=Ycoord+3;i<Ycoord+15;i++)
	if(mygr.getpixel(o,i)==Textc)
		mygr.putpixel(o,i,Backc);
		else
		mygr.putpixel(o,i,Textc);
}


int Editline::event(void)
{
int x,y;
x=mev.xcoord;
y=mev.ycoord;
if(mev.event & ME_LEFTPRESSED)
	if(x>=Xcoord && x<Xcoord+8*(Width+1) && y>=Ycoord && y<Ycoord+12+8)
		{
		hidemouse_edl();
		deactivate();
		Curpos=(x-Xcoord)/8;
		if(Curpos>Textlen) Curpos=Textlen;
		activate();
		showmouse();
		return 1;
		}
return 0;
}

void Editline::movecursorleft(void)
{
if(Curpos>0 && Curstate)
	{
	hidemouse_edl();
	deactivate();
	Curpos--;
	activate();
	showmouse();
	}
}

void Editline::movecursorhome(void)
{
if(Curpos>0 && Curstate)
	{
	hidemouse_edl();
	deactivate();
	Curpos=0;
	activate();
	showmouse();
	}
}

void Editline::movecursorright(void)
{
if(Curpos<Textlen && Curstate)
	{
	hidemouse_edl();
	deactivate();
	Curpos++;
	activate();
	showmouse();
	}
}

void Editline::movecursorend(void)
{
if(Curpos<Textlen && Curstate)
	{
	hidemouse_edl();
	deactivate();
	Curpos=Textlen;
	activate();
	showmouse();
	}
}

int Editline::delsymbol(void)
{
if(Curpos<Textlen && Curstate)
	{
	hidemouse_edl();
	deactivate();
	Strcpy(Text+Curpos,Text+Curpos+1,Textlen-Curpos);
	Textlen--;
	redraw();
	activate();
	showmouse();
	return 1;
	}
return 0;
}

int Editline::backdelsymbol(void)
{
if(Curpos>0 && Curstate)
	{
	hidemouse_edl();
	deactivate();
	Curpos--;
	activate();
	delsymbol();
	showmouse();
	return 1;
	}
return 0;
}

int Editline::takesymbol(char sym)
{
if(!asciisymboltable[sym] || !asciisymboltable[sym]->xsize) return 0;
if(Textlen<Width && Curstate)
	{
	hidemouse_edl();
	deactivate();
	Strcpyr(Text+Textlen+1,Text+Textlen,Textlen-Curpos+1);
	Textlen++;
	Text[Curpos]=sym;
	Curpos++;
	redraw();
	activate();
	showmouse();
	return 1;
	}
return 0;
}

