#include<..\express\mymouse.hpp>

int X_Coord_Data;//Переменные, устанавливаемые некоторыми функциями мыши, и
int Y_Coord_Data;//несущие информацию об X или Y координате соответственно.
volatile MouseHandleState _MouseState;
volatile _MouseEvent _MouseEvents[50];
volatile int _EventWritePtr,_EventReadPtr;

/*
	Этот файл содержит набор функций и процедур для работы с Microsoft
	совместимой мышью.
*/

int ismouseevent(void)
{
return (_EventWritePtr!=_EventReadPtr);
}

_MouseEvent getmouseevent(void)
{
int tempptr;
//asm cli
while(_EventWritePtr==_EventReadPtr);
tempptr=_EventReadPtr++;
if(_EventReadPtr==50) _EventReadPtr=0;
//asm sti
return _MouseEvents[tempptr];
}

void CLEARMOUSEEVENTS(void)
{
_EventReadPtr=_EventWritePtr=0;
}


int RESETMOUSE (int &numbuttons)
{
/*  Инициализирует драйвер мыши и возвращает состояние драйвера.
	Если указатель мыши был включен,он удаляется с экрана.
	Любые установки пользователя на события мыши удаляются.
*/
_EventReadPtr=_EventWritePtr=0;
asm xor ax,ax
asm int 33h
numbuttons=_BX;
return _AX;
}
/* Возвращает:  Если мышь поддерживается:
					RESETMOUSE = 0ffffh
					numbuttons = количество клавиш у мыши
				иначе если мышь не присутствует:
					RESETMOUSE = 0
*/

void SHOWMOUSE(void)
{
/*  Показывает указатель мыши и отменяет все зоны исключения
	определенные MOUSEEXCLUSIONAREA().
*/
asm mov ax,1
asm int 33h
}
/* Возвращает:  AX=1
*/

void HIDEMOUSE(void)
{
/* Удаляет указатель мыши с экрана, если он видим.
*/
asm mov ax,2
asm int 33h
}
/* Возвращает:  AX=2
*/

int GETMOUSEXY(int &xc,int &yc)
{
/* Получает координаты указателя и состояние кнопок.
*/
asm mov ax,3
asm int 33h
xc=_CX;
yc=_DX;
return _BX;
}
/* Возвращает:  Состояние кнопок мыши:
					[0]=1, если левая кнопка нажата
					[1]=1, если правая кнопка нажата
					[2]=1, если средняя кнопка нажата
				Координаты указателя.
*/


void SETMOUSEXY(int xc,int yc)
{
/* Устанавливает координаты указателя.
*/
//_BX=xc;
_CX=xc;
//asm mov bx,[yc]
//asm mov dx,bx
_DX=yc;
asm mov ax,4
asm int 33h
}
/* Возвращает:  AX=4
*/

int GETMOUSEPRESS(int buttonnumber,int &presscounter)
{
/* Получает информацию о кнопке мыши(buttonnumber=0 для левой,1 для правой и
   2 для средней), количестве ее нажатий с момента последнего вызова этой
   функции для данной кнопки, а также координаты последнего нажатия на кнопку.
*/
//asm mov bx,[word ptr buttonnumber]
asm push di
_BX=buttonnumber;
asm mov ax,5
asm int 33h
asm mov di,bx
asm push ax
presscounter=_DI;
X_Coord_Data=_CX;
Y_Coord_Data=_DX;
asm pop di
asm pop ax
return _AX;
}
/* Возвращает: Состояние кнопок:
					[0]=1, если левая кнопка нажата
					[1]=1, если правая кнопка нажата
					[2]=1, если средняя кнопка нажата
			   presscounter=количество нажатий
			   В переменных X_Coord_Data и Y_Coord_Data содержатся координаты
			   последнего нажатия
*/

int GETMOUSERELEASE(int buttonnumber,int &releasecounter)
{
/* Получает информацию о кнопке мыши(buttonnumber=0 для левой,1 для правой и
   2 для средней), количестве ее отпусканий с момента последнего вызова этой
   функции для данной кнопки, а также координаты последнего отпускания кнопки.
*/
asm push di
_BX=buttonnumber;
asm mov ax,6
asm int 33h
asm mov di,bx
asm push ax
releasecounter=_DI;
X_Coord_Data=_CX;
Y_Coord_Data=_DX;
asm pop di
asm pop ax
return _AX;
}
/* Возвращает: Состояние кнопок:
					[0]=1, если левая кнопка нажата
					[1]=1, если правая кнопка нажата
					[2]=1, если средняя кнопка нажата
			   releasecounter=количество отпусканий
			   В переменных X_Coord_Data и Y_Coord_Data содержатся координаты
			   последнего отпускания
*/

void SETMOUSEXLIMIT(int min,int max)
{
/* Устанавливает минимальную и максимальную х координату указателя мыши
*/
_CX=min;
_DX=max;
asm mov ax,7
asm int 33h
}
/* Возвращает:  AX=7
*/

void SETMOUSEYLIMIT(int min,int max)
{
/* Устанавливает минимальную и максимальную y координату указателя мыши
*/
_CX=min;
_DX=max;
asm mov ax,8
asm int 33h
}
/* Возвращает:  AX=8
*/

void SETMOUSEHANDLE(unsigned eventmask)
{
/* Устанавливает адрес и маску событий для обработчика событий мыши.
   Маска событий такая, как описано ниже, а адрес - дальний.
   Обработчит будет вызываться драйвером каждый раз при возникновении
   любого из указанных событий, при этом регистры будут иметь следующие
   значения:
	   AX = Флаги события:
			[0]=1 - передвижение мыши
			[1]=1 - левая кнопка нажата
			[2]=1 - левая кнопка отпущена
			[3]=1 - правая кнопка нажата
			[4]=1 - правая кнопка отпущена
			[5]=1 - средняя кнопка нажата
			[6]=1 - средняя кнопка отпущена
	   BX = Состояние кнопок:
			[0]=1 - левая кнопка нажата
			[1]=1 - правая кнопка нажата
			[2]=1 - средняя кнопка нажата
	   CX = x координата указателя мыши
	   DX = y координата указателя мыши
	   DI = last raw horizontal mickey counter
	   SI = last raw vertical mickey counter
	   DS = Сегмент данных драйвера мыши
   Обработчик должен заканчиваться командой RETF.
*/
_CX=eventmask;
_ES=(unsigned)(void _seg*)(MOUSEHANDLE);
_DX=(unsigned)(void *)(MOUSEHANDLE);
asm mov ax,0ch
asm int 33h
}
/* Возвращает:  AX=0ch
				ES=сегмент обработчика
				DX=смещение обработчика
*/
void SETGRAPHICSPOINTER(int xoffset,int yoffset,void far* adress)
{
asm mov es,word ptr[adress+2]
asm mov dx,word ptr[adress]
asm mov bx,[xoffset]
asm mov cx,[yoffset]
asm mov ax,9
asm int 33h
return;
}

void SETMOUSEEXLUSIONAREA(int left,int up,int right,int down)
{
asm mov ax,10h
asm mov cx,[left]
asm mov dx,[up]
asm mov si,[right]
asm mov di,[down]
asm int 33h
return;
}

void SETMOUSEMICKEYSRATIO(int xmickey,int ymickey)
{
asm mov ax,0fh
asm mov cx,[xmickey]
asm mov dx,[ymickey]
asm int 33h
}

