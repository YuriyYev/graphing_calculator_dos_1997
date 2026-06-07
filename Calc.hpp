#include "..\express\mymouse.hpp"
#include "..\express\graph18.hpp"

int NUMSTACK_SIZE=10300;//Размер стека чисел для вычисления выражения
int OPSTACK_SIZE=2060;  //Размер стека операций для вычисления выражения
int STRING_LEN=1024;    //Максимальная длина строки
int MULTITUDE_SIZE=111; //Размер множества

_MouseEvent mev;        //Глобальная переменная для хранения события мыши
int nomouse=0;          //=1, если мышь не обнаружена

inline void showmouse(void)
{
if(!nomouse) SHOWMOUSE();
}

inline void hidemouse(void)
{
if(!nomouse) HIDEMOUSE();
}


Graph18 mygr;           //Вход в графический режим
int what_button;        //Используется для определения нажатой клавиши


#ifndef __symbol__
struct symbol
{
int xsize,ysize;        //Размер символа
unsigned char *buf;		//Изображение символа
};
#define __symbol__
#endif

#include "..\express\common.hpp"
#include "..\express\fpu.hpp"

#include "..\express\calcfont.cpp"

#include "..\express\calcedl.hpp"
#include "..\express\calcbut.hpp"

Calc_indicator indic;	//Объект индикатора;

void Putsymbol(symbol *sym,int xc,int yc,int forecolor,int backcolor,int deact=0)
{	//Печатает символ в указанных координатах.
	//Если параметр deact!=0, то символ печатается 8 цветом.
if((unsigned int)sym->xsize>50 || (unsigned int)sym->ysize>50) return;
if(deact) forecolor=8;
int worky=yc;
int worky_end=worky+sym->ysize;
int size=sym->xsize;
int adr=0,i,numbytes=size>>3;
int working=0;
unsigned char numshiftleft=0,nummaskright=8-(size&7),maskright=(unsigned char)(255)<<nummaskright;
for(;worky<worky_end;worky++)
	{
	for(i=0;i<numbytes;i++)
		{
		*((char*)(&working)+1)=sym->buf[i+adr];
		*((char*)(&working))=sym->buf[i+1+adr];
		working<<=numshiftleft;
		mygr.put8pixel(*((char*)(&working)+1),xc+(i<<3),worky,forecolor);
		mygr.put8pixel(~(*((char*)(&working)+1)),xc+(i<<3),worky,backcolor);
		}
	*((char*)(&working)+1)=sym->buf[i+adr];
	*((char*)(&working))=sym->buf[i+1+adr];
	working<<=numshiftleft;
	mygr.put8pixel((*((char*)(&working)+1))&maskright,xc+(i<<3),worky,forecolor);
	mygr.put8pixel((~(*((char*)(&working)+1)))&maskright,xc+(i<<3),worky,backcolor);
	adr+=i;
	numshiftleft+=8-nummaskright;
	if(numshiftleft>7) {adr+=numshiftleft>>3;numshiftleft&=7;}
	}
}

//Сообщения, выводимые или на индикатор, или до входа в графический режим
char *Error_messages[]={"","СИНТАКСИЧЕСКАЯ  ОШИБКА","ОШИБКА  СКОБОК","\nNot enough memory\n",
"СТРОКА  СЛИШКОМ  ДЛИННАЯ","МНОЖЕСТВО  ЗАПОЛНЕНО","МНОЖЕСТВО  ПУСТОЕ",
"НЕТ  АКТИВИРОВАННЫХ  ПЕРЕМЕННЫХ (V,W,X ИЛИ Y)",0,
0,0,0,
"\nError entering 640x480x16 video mode.\n","\nYou need at least 386th processor with at least 387th math coprocessor.\n",
0};

/*//Сообщения, выводимые в окно сообщений
char *message[]={"","ВВОДИТЕ СТРОКУ ДЛЯ ВЫЧИСЛЕНИЯ","РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ","ОШИБКА ВЫЧИСЛЕНИЯ ИЛИ ОПЕРАЦИИ",
"ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ ЗАПИСИ СТРОКИ В НЕЕ","ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ ЗАПИСИ ТОЛЬКО ЧИСЛА В НЕЕ",
"ВВЕДИТЕ КОЛИЧЕСТВО ЗНАЧАЩИХ ЦИФР В ","ВВЕДИТЕ ЗНАЧЕНИЕ НАУЧНОЙ НОТАЦИИ В ",
"ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ ЧТЕНИЯ СТРОКИ ИЗ НЕЕ","ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ ЧТЕНИЯ ЧИСЛА ИЗ НЕЕ",
"ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ ЗАПИСИ ЧИСЛА В НЕЕ","ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ ПРИБАВЛЕНИЯ ЧИСЛА К НЕЙ",
"ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ ВЫЧИТАНИЯ ЧИСЛА ИЗ НЕЕ","ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ УМНОЖЕНИЯ ЕЕ НА ЧИСЛО",
"ВВЕДИТЕ ПЕРЕМЕННУЮ ДЛЯ ДЕЛЕНИЯ ЕЕ НА ЧИСЛО","ВВЕДИТЕ ПЕРЕМЕННЫЕ, ЗНАЧЕНИЯ КОТОРЫХ НУЖНО ОБМЕНЯТЬ: ",
"ВВЕДИТЕ ПЕРЕМЕННУЮ, КОТОРУЮ НУЖНО ПЕРЕКЛЮЧИТЬ","ВВЕДИТЕ ПЕРЕМЕННУЮ, КОТОРУЮ НУЖНО ДОБАВИТЬ В МНОЖЕСТВО",
"ВВЕДИТЕ НИЖНИЙ ПРЕДЕЛ ДЛЯ W","ВВЕДИТЕ НИЖНИЙ ПРЕДЕЛ ДЛЯ V","ВВЕДИТЕ НИЖНИЙ ПРЕДЕЛ ДЛЯ Y",
"ВВЕДИТЕ НИЖНИЙ ПРЕДЕЛ ДЛЯ X","ВВЕДИТЕ ВЕРХНИЙ ПРЕДЕЛ ДЛЯ W","ВВЕДИТЕ ВЕРХНИЙ ПРЕДЕЛ ДЛЯ V",
"ВВЕДИТЕ ВЕРХНИЙ ПРЕДЕЛ ДЛЯ Y","ВВЕДИТЕ ВЕРХНИЙ ПРЕДЕЛ ДЛЯ X","ОШИБКА: СТРОКА СЛИШКОМ ДЛИННАЯ",
" И"
};*/

//Сообщения, выводимые в окно сообщений
char *message[]={"","Вводите строку для вычисления","Результат вычисления","Ошибка вычисления или операции",
"Введите переменную для записи строки в нее","Введите переменную для записи только числа в нее",
"Введите количество значащих цифр в ","Введите значение научной нотации в ",
"Введите переменную для чтения строки из нее","Введите переменную для чтения числа из нее",
"Введите переменную для записи числа в нее","Введите переменную для прибавления числа к ней",
"Введите переменную для вычитания числа из нее","Введите переменную для умножения ее на число",
"Введите переменную для деления ее на число","Введите переменные, значения которых нужно обменять: ",
"Введите переменную, которую нужно переключить","Введите переменную, которую нужно добавить в множество",
"Введите нижний предел для W","Введите нижний предел для V","Введите нижний предел для Y",
"Введите нижний предел для X","Введите верхний предел для W","Введите верхний предел для V",
"Введите верхний предел для Y","Введите верхний предел для X","ОШИБКА: строка слишком длинная",
" и","Выберите номер файла, в который хотите сохранить состояние",
"Выберите номер файла, из которого нужно восстановить состояние",
"Ошибка создания файла состояния. Попытайтесь еще раз",
"Ошибка записи файла состояния. Попытайтесь еще раз",
"Ошибка открытия файла состояния. Попытайтесь еще раз",
"Ошибка чтения файла состояния. Попытайтесь еще раз",
"Ошибка данных в файле состояния. Попытайтесь еще раз"
};


int Counterror,     //Ошибка вычисления не связанная с сопроцессором
	currentmessage; //Номер сообщения в массиве message, которое отображено



void showmessage(char *mes)
{ 	//Отображает сообщение в окне сообщений
mygr.drawtwocoloredbox_rel(2,158,636,18,8,15);
mygr.drawtwocoloredbox_rel(3,159,634,16,6,7);
mygr.drawbox_rel(4,160,632,14,11);
int xc=5,yc=161;
char *temp=mes;
for(;*mes;mes++,xc+=8)
	Putsymbol(asciisymboltable[*mes],xc,yc,0,11);
mygr.drawfilledbox(xc,160,635,160+14-1,11);
currentmessage=0;
for(int i=0;i<sizeof(message)/sizeof(message[0]);i++)
	if(message[i]==temp)
		currentmessage=i;
}


class Stack
{	//Используется при вычислении выражения
	char *stk;
	int stk_top;
	int stk_size;
	int opsize;
public:
	Stack (int ops,int stksize)
		{
		opsize=ops;
		stk_size=stksize;
		stk=new char[stk_size];
		 }
	~Stack () {delete stk;}
void init(void)
	{
	stk_top=stk_size-opsize;
	}
int push (char achar)
	{
	stk[stk_top--]=achar;
	return (stk_top>0?0:1);
	}
int push (long double adouble)
	{
	*(long double*)(stk+stk_top)=adouble;
	stk_top-=10;
	return (stk_top>0?0:1);
	}
int pop (char &achar)
	{
	achar=stk[++stk_top];
	return ((stk_size>stk_top)?0:1);
	}
int pop (long double &adouble)
	{
	stk_top+=10;
	adouble=*(long double*)(stk+stk_top);
	return ((stk_size>stk_top)?0:1);
	}
char getontop()	{return stk[stk_top+1];}
int operator !(void)
	{
	return !stk;
	}
};



extern Stack num_stk,oper_stk;

long lasttimertick,nexttimertick;
int numbuttons,Indic_buffer_len;

char *num2str_buffer,*Indic_buffer,*Indic_flags,*curnumbuf;
int num2str_exp,sci_num10,fix_num10,sci_num2,fix_num2;
int sci_num8,fix_num8,sci_num16,fix_num16,num2str_pointer;

struct memory_element
{	//Переменная или ячейка памяти
int isstring;
int ison,iserror;
long double number,newnumber;
char *string,*flags;
};

struct mul_element
{	//Элемент множества
int isvar;
int var;
long double number;
};

enum systems {DECSYS=10,HEXSYS=16,OCTSYS=8,BINSYS=2};
enum trig_systems {RAD=32,DEG=64,GRD=96};

systems cur_str_system,cur_ans_system;
trig_systems cur_trig_str_system,cur_trig_ans_system,last_trig_ans_system;


memory_element *variable; //Массив с переменными и ячейками памяти
#define mem1 26
#define mem2 27
#define mem3 28
#define mem4 29
#define mem5 30
#define mem6 31
#define mem7 32
#define mem8 33
mul_element *multitude;//[50];//MULTITUDE_SIZE];Множество


CursorState mainstate,graphstate[4];//Состояние курсора индикатора
unsigned char *current_string,*current_flags,*main_string,*main_flags;
unsigned char *last_string,*last_flags,*firstlowlimit_str,*secondlowlimit_str;
unsigned char *firsthighlimit_str,*secondhighlimit_str,*firstlowlimit_flag;
unsigned char *secondlowlimit_flag,*firsthighlimit_flag,*secondhighlimit_flag;
long double firstlowlimit,secondlowlimit,firsthighlimit,secondhighlimit;
int current_len,input_pointer,real_multitude_len,ismore,keystatus;
unsigned long multitude_len;
long double main_number,*current_number,Last_answer=0;
int current_mode,isinsert,last_mode,last_mes,graph_mode,last_input_pointer,prev_mode;
//				=0 - Выражение
//				=1 - Ответ
//				=2 - Сообщение об ошибке
//				=3 - График


#define KEY_no			0x00
#define KEY_factor     	0x21
#define KEY_leftrp     	0x28
#define KEY_rightrp    	0x29
#define KEY_mul      	0x2a
#define KEY_plus      	0x2b
#define KEY_coma       	0x2c
#define KEY_minus      	0x2d
#define KEY_div      	0x2f
#define KEY_0       	0x30
#define KEY_1       	0x31
#define KEY_2       	0x32
#define KEY_3       	0x33
#define KEY_4       	0x34
#define KEY_5       	0x35
#define KEY_6       	0x36
#define KEY_7       	0x37
#define KEY_8       	0x38
#define KEY_9       	0x39
#define KEY_A       	0x41
#define KEY_B       	0x42
#define KEY_C       	0x43
#define KEY_D       	0x44
#define KEY_E       	0x45
#define KEY_F       	0x46
#define KEY_G       	0x47
#define KEY_H       	0x48
#define KEY_I       	0x49
#define KEY_J       	0x4a
#define KEY_K       	0x4b
#define KEY_L       	0x4c
#define KEY_M       	0x4d
#define KEY_N       	0x4e
#define KEY_O       	0x4f
#define KEY_P       	0x50
#define KEY_Q       	0x51
#define KEY_R       	0x52
#define KEY_S       	0x53
#define KEY_T       	0x54
#define KEY_U       	0x55
#define KEY_V       	0x56
#define KEY_W       	0x57
#define KEY_X       	0x58
#define KEY_Y       	0x59
#define KEY_Z       	0x5a
#define KEY_leftsp     	0x5b
#define KEY_rem       	0x5c
#define KEY_rightsp    	0x5d
#define KEY_power     	0x5e
#define KEY_sin      	0xa0
#define KEY_cos      	0xa1
#define KEY_tg      	0xa2
#define KEY_ctg      	0xa3
#define KEY_arcsin     	0xa4
#define KEY_arccos     	0xa5
#define KEY_arctg     	0xa6
#define KEY_arcctg     	0xa7
#define KEY_sh      	0xa8
#define KEY_ch      	0xa9
#define KEY_th      	0xaa
#define KEY_cth      	0xab
#define KEY_arsh     	0xac
#define KEY_arch     	0xad
#define KEY_arth     	0xae
#define KEY_arcth     	0xaf
#define KEY_ln      	0xb0
#define KEY_lg      	0xb1
#define KEY_exp       	0xb2
#define KEY_e       	0xb3
#define KEY_leftmp     	0xb4
#define KEY_rightmp    	0xb5
#define KEY_sgn     	0xb6
#define KEY_pi      	0xb7
#define KEY_ans     	0xb8
#define KEY_SUM     	0xb9
#define KEY_MUL     	0xba
#define KEY_MUL_LEN    	0xbb
#define KEY_INDEX     	0xbc
#define KEY_MUL_ELEM   	0xbd
#define KEY_Ah       	0xc0
#define KEY_Bh       	0xc1
#define KEY_Ch       	0xc2
#define KEY_Dh       	0xc3
#define KEY_Eh       	0xc4
#define KEY_Fh       	0xc5
#define KEY_ROOT1      	0xc6
#define KEY_ROOT2      	0xc7
#define KEY_ROOT3      	0xc8
#define KEY_ROOT4      	0xc9
#define KEY_ROOT5      	0xca
#define KEY_ROOT6      	0xcb
#define KEY_ROOT7      	0xcc
#define KEY_ROOT8      	0xcd
#define KEY_ROOT9      	0xce
#define KEY_POW1    	0xcf
#define KEY_POW2    	0xd0
#define KEY_POW3    	0xd1
#define KEY_POW4    	0xd2
#define KEY_POW5    	0xd3
#define KEY_POW6    	0xd4
#define KEY_POW7    	0xd5
#define KEY_POW8    	0xd6
#define KEY_POW9    	0xd7
#define KEY_rnd     	0xd8
#define KEY_LESS     	0xd9
#define KEY_LESS_EQ    	0xda
#define KEY_GREATER    	0xdb
#define KEY_GREATER_EQ 	0xdc
#define KEY_EQ      	0xdd
#define KEY_NOT_EQ    	0xde
#define KEY_not	    	0xdf
#define KEY_and	    	0xe0
#define KEY_or	    	0xe1
#define KEY_xor	    	0xe2
#define KEY_log	    	0xe3
#define KEY_xscale    	0xe4
#define KEY_yscale    	0xe5


#define KEY_savenumto 	0x100
#define KEY_savestrto 	0x101
#define KEY_read_str   	0x102
#define KEY_swap      	0x103
#define KEY_M1_plus    	0x104
#define KEY_M1_minus   	0x105
#define KEY_M1_mul     	0x106
#define KEY_M1_div     	0x107
#define KEY_Mn_plus    	0x108
#define KEY_Mn_minus   	0x109
#define KEY_Mn_mul     	0x10a
#define KEY_Mn_div     	0x10b
#define KEY_M1      	0x10c
#define KEY_M2      	0x10d
#define KEY_M3      	0x10e
#define KEY_M4      	0x10f
#define KEY_M5      	0x110
#define KEY_M6      	0x111
#define KEY_M7      	0x112
#define KEY_M8      	0x113
#define KEY_del      	0x114
#define KEY_bs      	0x115
#define KEY_clear      	0x116
#define KEY_stay      	0x117
#define KEY_graph      	0x118
#define KEY_multitude  	0x119
#define KEY_add_to_mul 	0x11a
#define KEY_exe     	0x11b
#define KEY_leftcur    	0x11c
#define KEY_rightcur   	0x11d
#define KEY_leftqcur   	0x11e
#define KEY_rightqcur  	0x11f
#define KEY_leftend    	0x120
#define KEY_rightend   	0x121
#define KEY_help    	0x122
#define KEY_exit     	0x123
#define KEY_reset   	0x124
#define KEY_fix     	0x125
#define KEY_sci     	0x126
#define KEY_DEC     	0x127
#define KEY_HEX     	0x128
#define KEY_OCT     	0x129
#define KEY_BIN     	0x12a
#define KEY_RAD     	0x12b
#define KEY_DEG     	0x12c
#define KEY_GRD     	0x12d
#define KEY_insert     	0x12e
#define KEY_esc     	0x12f
#define KEY_add_var_to_mul     	0x130
#define KEY_read_num   	0x131
#define KEY_more    	0x132
#define KEY_toggle    	0x133
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
#define KEY_save            0x14c
#define KEY_join            0x14d
#define KEY_onlyvw          0x14e
#define KEY_onlyxy          0x14f
#define KEY_move            0x150
#define KEY_load            0x151
#define KEY_helplock        0x152
#define KEY_consoluse		0x154
#define KEY_altRAD     		0x155
#define KEY_altDEG     		0x156
#define KEY_altGRD     		0x157
#define KEY_cont     		0x158
#define KEY_graphclear     	0x159
#define KEY_center   	  	0x15a
#define KEY_expandcenterscreen 0x15b
#define KEY_centerscreen 	0x15c
#define KEY_graphhelplock   0x15d
#define KEY_graphsave       0x15e
#define KEY_graphrowslock        0x15f
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

#define KEY_break			0x170
#define KEY_bufcopy         0x171
#define KEY_bufinsert       0x172
#define KEY_bufcopydel      0x173
#define KEY_bufleft         0x174
#define KEY_bufright        0x175
#define KEY_bufqleft        0x176
#define KEY_bufqright       0x177
#define KEY_bufhome         0x178
#define KEY_bufend          0x179
#define KEY_indicuse        0x17a
#define KEY_redraw				0x17b
#define KEY_graphgridlock		0x17c
#define KEY_auto				0x17d
#define KEY_preview				0x17e
#define KEY_compresscenterscreen 0x17f
#define KEY_yuraused            0x180
#define KEY_scalehelp		0x181
#define KEY_iterhelp		0x182
#define KEY_gridstephelp  	0x183
#define KEY_actlock		  	0x184

//void multitudework(void) {return;}
int receivemouseevent(void);

extern char *allopers;
extern long double *allnums;
long double countstring(char *,char *,int);
extern int exppointer;

int drawmultitude(void);
int graphdraw(void);
void drawconsol(int);
void drawvariables(void);
int convert_number2string(long double,int,int=0);
void recountvariables(int=0);
void showerrormessage(void);
void drawallkeys(void);
int Putstring(int xc,int yc,char *ptr,int fc,int bc);


int ishelp,isactlock;
extern char huge *graphic_buffer;

int gethelp(void);
void helpon(int);

char *mousearrow=
"\xff""\x3f"
"\xff""\x1f"
"\xff""\xf"
"\xff""\x7"
"\xff""\x3"
"\xff""\x1"
"\xff""\x0"
"\x7f""\x0"
"\x3f""\x0"
"\x1f""\x0"
"\xff""\x1"
"\xff""\x10"
"\xff""\x30"
"\x7f""\xf8"
"\x7f""\xf8"
"\x7f""\xfc"
"\x0""\x0"
"\x0""\x40"
"\x0""\x60"
"\x0""\x70"
"\x0""\x78"
"\x0""\x7c"
"\x0""\x7e"
"\x0""\x7f"
"\x80""\x7f"
"\x0""\x7c"
"\x0""\x6c"
"\x0""\x46"
"\x0""\x6"
"\x0""\x3"
"\x0""\x3"
"\x0""\x0";

char *mousearrowquest=
"\xff""\x3f"
"\xff""\x1f"
"\xff""\xf"
"\xff""\x7"
"\x83""\x3"
"\x1""\x1"
"\x1""\x0"
"\x1""\x0"
"\x1""\x3"
"\xc1""\x1"
"\xc1""\xc1"
"\xc3""\xe1"
"\xc7""\xe1"
"\xc7""\xff"
"\xc7""\xff"
"\xc7""\xff"
"\x0""\x0"
"\x0""\x40"
"\x0""\x60"
"\x0""\x70"
"\x0""\x78"
"\x38""\x7c"
"\x6c""\x7e"
"\x44""\x78"
"\x4""\x58"
"\xc""\x18"
"\x18""\xc"
"\x10""\xc"
"\x10""\x0"
"\x0""\x0"
"\x10""\x0"
"\x0""\x0";




