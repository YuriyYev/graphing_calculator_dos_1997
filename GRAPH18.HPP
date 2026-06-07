#ifndef __GRAPH18_HPP

class Graph18
{
	char PrevMode;
	int Log_xleft,Log_yleft,Log_xright,Log_yright;
public:
	void setvideomode18(void);
	int Color;
	enum {BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,
	YELLOW,WHITE,GREY,LIGHT_BLUE,LIGHT_GREEN,LIGHT_CYAN,
	LIGHT_RED,LIGHT_MAGENTA,LIGHT_YELLOW,LIGHT_WHITE};
Graph18();
~Graph18();
	int getvideomode(void);
void setlimits(int l,int u,int r,int d)
	{
	Log_xleft=l;
	Log_yleft=u;
	Log_xright=r;
	Log_yright=d;
	}
void drawline(int,int,int,int,int);
void drawline_rel(int,int,int,int,int);
int  getcolor(void) {return Color;}
void setcolor(int aC) {Color=aC;}
void restorestate(void);
void putpixel(int xc,int yc,int color);
void put8pixel(unsigned char mask,int xc,int yc,int color);
void _putpixel(int xc,int yc);
int  getpixel(int xc,int yc);
void drawbox(int left,int up,int right,int bottom,int color);
void drawbox_rel(int left,int up,int right,int bottom,int color);
void drawtwocoloredbox(int left,int up,int right,int bottom,
						int color1,int color2);
void drawtwocoloredbox_rel(int left,int up,int right,int bottom,
						int color1,int color2);
void drawxline(int left,int right,int high,int color);
void drawxline_rel(int left,int right,int high,int color);
void drawyline(int up,int bottom,int width,int color);
void drawyline_rel(int up,int bottom,int width,int color);
void drawfilledbox(int left,int up,int right,int bottom,int color);
void drawfilledbox_rel(int left,int up,int right,int bottom,int color);
void getrectangle(void huge *buf,int left,int up,int right,int bottom);
void getrectangle_rel(void huge *buf,int left,int up,int right,int bottom);
void setrectangle(char huge *buf,int left,int up);
void move(int,int,int,int,int,int);
void move_rel(int,int,int,int,int,int);
};

#define __GRAPH18_HPP
#else
#endif
