#include"..\express\graph18.hpp"

#pragma inline

Graph18::Graph18():Log_xleft(0),Log_yleft(0),Log_xright(639),Log_yright(479)
	{
	asm mov ah,0fh
	asm int 10h
	asm mov cl,al
	PrevMode=_CL;
	setvideomode18();
	Color=15;
	}

int Graph18::getvideomode(void)
{
asm mov ah,0fh
asm int 10h
asm mov cl,al
asm xor ch,ch
return _CX;
}

Graph18::~Graph18()
	{
	if(PrevMode!=getvideomode())
		{
		_AL=PrevMode;
		asm mov ah,0
		asm int 10h
		}
	}

void Graph18::setvideomode18(void)
	{
	asm mov bh,0
	asm mov ax,012h
	asm int 10h
	}

void Graph18::restorestate(void)
{
asm {
	mov dx,3ceh
	mov ax,0ff08h
	out dx,ax

	mov ax,0001h
	out dx,ax

//	mov dx,3c4h
//	mov ax,0f02h
//	out dx,ax
	}
}


void Graph18::putpixel(int xc,int yc,int color)
	{
	_CH=(char)color;
	_DI=xc;
	_BX=yc;
	asm  {
//		cli
		mov ax,0a000h
		mov es,ax

		imul bx,bx,80d
		mov ax,di
		shr ax,3
		add bx,ax

		mov ax,di
		and ax,0111b
		mov cl,al
		inc cl
		stc
		rcr ah,cl

		mov dx,3ceh
		mov al,8
		out dx,ax

		mov ah,ch
		mov al,0
		out dx,ax
		mov ax,0f01h
		out dx,ax
//		 ah,byte ptr es:[bx]
		or byte ptr es:[bx],0
		}
	}

void Graph18::put8pixel(unsigned char mask,int xc,int yc,int color)
	{
	_DI=xc;
	_BX=yc;
	asm  {
//		cli
		mov ax,0a000h
		mov es,ax

		imul bx,bx,80d
		mov ax,di
		shr ax,3
		add bx,ax

		mov cx,di
		and cx,0111b
		mov ah,mask
		xor al,al
//		inc cl
//		stc
		shr ax,cl
		or ax,ax
		mov cx,ax
//		mov ah,mask
		jz label_pp_02

		mov dx,3ceh
		mov ah,byte ptr color
		xor al,al
		out dx,ax
		mov ax,0f01h
		out dx,ax

		or ch,ch
		jz label_pp_01
		mov ah,ch
		mov al,8
		out dx,ax
		or byte ptr es:[bx],0
		}
label_pp_01:
asm		{
		or cl,cl
		jz label_pp_02
		mov ah,cl
		mov al,8
		out dx,ax
		inc bx
		or byte ptr es:[bx],0
		}
label_pp_02:;
	}


void Graph18::drawline_rel(int startx,int starty,int xlen,int ylen,int color)
{
drawline(startx,starty,startx+xlen-1,starty+ylen-1,color);
}

void Graph18::drawline(int startx,int starty,int endx,int endy,int color)
{
	register int t,distance;
	int xerr=0,yerr=0,delta_x,delta_y;
	int incx,incy,yincmul,halfdist,adr;
	   /* вычисление расстояния в обоих направлениях  */
	delta_x=endx-startx;
	delta_y=endy-starty;
	   /* определение направления шага,
		  шаг вычисляется либо по вертикальной, либо горизонтальной
		  линии   */
		asm xor ax,ax
		asm cmp word ptr [delta_x],0
		asm mov [incx],ax
		asm mov [incy],ax
		asm mov [yincmul],ax
		asm jl label_dl_04
		asm jz label_dl_05
		asm inc word ptr [incx]
		asm jmp label_dl_05
label_dl_04:
		asm dec word ptr [incx]
		asm neg word ptr [delta_x]
label_dl_05:

/*		if (delta_x>0) incx=1;
			else
				if(delta_x<0)
				{
				incx=-1;
				asm neg word ptr [delta_x]
				}
				else incx=0;*/
		asm cmp word ptr [delta_y],0
		asm jl label_dl_06
		asm jz label_dl_07
		asm inc word ptr [incy]
		asm mov word ptr [yincmul],80d
		asm jmp label_dl_07
label_dl_06:
		asm dec word ptr [incy]
		asm mov word ptr [yincmul],-80d
		asm neg word ptr [delta_y]
label_dl_07:

/*		if (delta_y>0) {incy=1;yincmul=80;}
			else
				if(delta_y)
				{
				incy=-1;
				yincmul=-80;
//			delta_y=-delta_y;
				asm neg word ptr [delta_y]
				}
				else {incy=0;yincmul=0;}*/
		/* определение какое расстояние больше */
	if (delta_x>delta_y) distance=delta_x;
		else distance=delta_y;
	halfdist=distance>>1;
		/* вычерчивание линии */
	asm	mov ax,0a000h
	asm	mov fs,ax

	asm mov ax,[starty]
	asm mov bx,ax
	asm shl ax,4
	asm shl bx,6
	asm add bx,ax
	asm mov ax,[startx]
	asm shr ax,3
	asm add bx,ax

	asm	mov dx,3ceh
	asm xor al,al
	asm	mov ah,byte ptr[color]
	asm	out dx,ax

	asm mov ax,0f01h
	asm out dx,ax


	asm	mov ax,[startx]
	asm	and ax,0111b
	asm	mov cl,al
	asm	inc cl
	asm	stc
	asm	rcr ah,cl
	asm mov cl,ah

	asm	mov al,8
	asm	out dx,ax
	asm inc dx

	for (t=0; t<=distance; t++)
		{
		asm mov [adr],bx
		if(startx>=Log_xleft && startx<=Log_xright && starty>=Log_yleft && starty<=Log_yright)
			{
			asm mov bx,[adr]
			asm or fs:[bx],al
			}
		asm mov bx,[adr]
		xerr+=delta_x;
		if (xerr>halfdist)
			{
			xerr-=distance;
			startx+=incx;
			asm cmp word ptr[incx],0
			asm jl label_dl_02
			asm jz label_dl_03
				asm ror cl,1
				asm adc bx,0
				asm jmp label_dl_03
label_dl_02:
				asm rol cl,1
				asm sbb bx,0
label_dl_03:	asm mov al,cl
				asm	out dx,al
			}

		yerr+=delta_y;
		if (yerr>halfdist)
			{
			yerr-=distance;
			starty+=incy;
			asm add bx,[yincmul]
			}
		}

}


int Graph18::getpixel(int xc,int yc)
	{
	_DI=xc;
	_BX=yc;
	asm  {
//		cli
		mov ax,0a000h
		mov es,ax

		imul si,bx,80d
		mov ax,di
		shr ax,3
		add si,ax

		mov cx,di
		and cx,0111b
		inc cl
		stc
		rcr ch,cl
		xor cl,cl
		xor bh,bh

		mov dx,3ceh
		mov al,4
		mov ah,3
		out dx,ax

		mov bl,byte ptr es:[si]
		and bl,ch
		setnz bl
		shr bl,1
		rcl bh,1

		dec ah
		out dx,ax
		mov bl,byte ptr es:[si]
		and bl,ch
		setnz bl
		shr bl,1
		rcl bh,1

		dec ah
		out dx,ax
		mov bl,byte ptr es:[si]
		and bl,ch
		setnz bl
		shr bl,1
		rcl bh,1

		dec ah
		out dx,ax
		mov bl,byte ptr es:[si]
		and bl,ch
		setnz bl
		shr bl,1
		rcl bh,1

		xor ah,ah
		mov al,bh
//		sti
		}
	return _AX;
	}

void Graph18::move(int left,int up,int right,int bottom,int newx,int newy)
{
move_rel(left,up,right,bottom,newx-left,newy-up);
}

void Graph18::move_rel(int left,int up,int right,int bottom,int offsx,int offsy)
{
static int o,p,u,oy,py,uy;
if(!offsx && !offsy) return;
offsy*=80;
//asm	cli
asm	mov ax,0a000h
asm	mov es,ax
if(offsx<0) {p=right;u=1;}
	else {p=left;u=-1;}
if(offsy<0) {oy=up;py=bottom;uy=80;}
	else {oy=bottom;py=up;uy=-80;}
_SI=oy*80;
//for(;oy!=py+uy;oy+=uy)
for(py=up;py<=bottom;py++)
	{
	if(offsx<0) o=left;
		else o=right;
	for(;o!=p+u;o+=u)
		{
		_DI=o;
		asm {
			push cx
			push si
			mov cx,di
			shr cx,3
			add si,cx

			mov cx,di
			and cx,0111b
			inc cl
			stc
			rcr ch,cl

			xor bh,bh

			mov dx,3ceh
			mov al,4
			mov ah,3
			out dx,ax

			mov bl,byte ptr es:[si]
			and bl,ch
			setnz bl
			shr bl,1
			rcl bh,1

			dec ah
			out dx,ax
			mov bl,byte ptr es:[si]
			and bl,ch
			setnz bl
			shr bl,1
			rcl bh,1

			dec ah
			out dx,ax
			mov bl,byte ptr es:[si]
			and bl,ch
			setnz bl
			shr bl,1
			rcl bh,1

			dec ah
			out dx,ax
			mov bl,byte ptr es:[si]
			and bl,ch
			setnz bl
			shr bl,1
			rcl bh,1

//			mov ah,ch
//			mov al,8
//			out dx,ax
//
//			mov al,byte ptr es:[bx]

			pop si
			push si
			add di,[offsx]
			mov cx,di
			shr cx,3
			add si,cx
			add si,[offsy]

			mov cx,di
			and cx,0111b
			inc cl
			stc
			rcr ch,cl

//            mov cl,al
			mov ah,ch
			mov al,8
			out dx,ax

			mov al,0
			mov ah,bh
			out dx,ax

			mov ax,0f01h
			out dx,ax


//			mov dx,3c4h
//			mov ax,0f02h
//			out dx,ax
			mov ah,byte ptr es:[si]
			mov byte ptr es:[si],ah

//			mov ah,bh
//			out dx,ax
	//		mov ah,byte ptr es:[bx]
//			mov byte ptr es:[si],255d


//			mov byte ptr es:[si],bh
			pop si
			pop cx
			}
		}
	asm add si,[uy]
	}
}

void Graph18::_putpixel(int xc,int yc)
	{
	putpixel(xc,yc,Color);
	}


void Graph18::drawbox_rel(int left,int up,int xsize,int ysize,int color)
{
drawbox(left,up,left+xsize-1,up+ysize-1,color);
}

void Graph18::drawbox(int left,int up,int right,int bottom,int color)
{					//Рисует рамку заданного цвета
drawxline(left,right-1,up,color);
drawxline(left+1,right,bottom,color);
drawyline(up+1,bottom,left,color);
drawyline(up,bottom-1,right,color);
}

void Graph18::drawtwocoloredbox_rel(int left,int up,int xsize,int ysize,
						int color1,int color2)
{
drawtwocoloredbox(left,up,left+xsize-1,up+ysize-1,color1,color2);
}

void Graph18::drawtwocoloredbox(int left,int up,int right,int bottom,
						int color1,int color2)
{                      //Рисует рамку, у которой левая и верхняя стороны
					   //имеют цвет color1, а остальные-color2
drawxline(left,right-1,up,color1);
drawxline(left+1,right,bottom,color2);
drawyline(up+1,bottom,left,color1);
drawyline(up,bottom-1,right,color2);
}

void Graph18::drawxline_rel(int left,int len,int high,int color)
{
drawxline(left,left+len-1,high,color);
}

void Graph18::drawxline(int left,int right,int high,int color)
{            //Рисует горизонтальную линию
    if(high<0 || high>=480) return;
	if(left>right)
		{
		asm mov ax,[left]
		asm xchg ax,[right]
		asm mov [left],ax
		}
		_BX=high;
		_SI=right;
	asm  {
//		cli
		mov ax,0a000h
		mov es,ax

		mov dx,3ceh
		mov al,0
		mov ah,[color]
		out dx,ax
		mov ax,0f01h
		out dx,ax

		mov dx,[left]
		imul bx,80d

		mov di,dx
		shr di,3

		mov ax,dx
		xor ax,si
		and ax,0fff8h
		jnz _dxl_5
		jmp _dxl_1 }
_dxl_5:
asm		{
		and dx,111b
		mov ah,0ffh
		mov cl,dl
		shr ah,cl

		mov dx,3ceh
		mov al,8
		out dx,ax


//		mov dx,3c4h
//		mov al,02h
//		mov ah,15
//		out dx,ax
		or es:[bx+di],ah
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],ah

//		mov ah,ch
//		out dx,ax
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],255d

		mov dx,si
		and dx,111b
		mov cl,dl
		xchg cx,si
		shr cx,3
		dec cx
		sub cx,di
		jcxz _dxl_2
		mov dx,3ceh
		mov al,8
		mov ah,0ffh
		out dx,ax
//		mov al,2
//		mov dx,3c4h
					}
_dxl_3:
asm		{
		inc di

//		mov ah,15
//		out dx,ax
		or es:[bx+di],ah
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],ah

//		mov ax,si
//		mov al,2
//		out dx,ax
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],255d

		loop _dxl_3 }
_dxl_2:
asm		{
		mov cx,si
		inc di

		mov ah,0ffh
		sub cl,7
		neg cl
		shl ah,cl

		mov dx,3ceh
		mov al,8
		out dx,ax

//		mov al,2
//		mov dx,3c4h
//		mov ah,15
//		out dx,ax
		or es:[bx+di],ah
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],ah

//		mov ah,ch
//		out dx,ax
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],255d

		jmp _dxl_4 }

_dxl_1:
asm 	{
		mov dx,[left]
		mov di,dx
		shr di,3
		and dx,111b
		mov dh,0ffh
		mov cl,dl
		shr dh,cl

		and si,111b
		mov ax,si
		mov ah,0ffh
		sub al,7
		neg al
		mov cl,al
		shl ah,cl
		and ah,dh

		mov dx,3ceh
		mov al,8
		out dx,ax

//		mov al,2
//		mov dx,3c4h
//		mov ah,15
//		out dx,ax
		or es:[bx+di],ah
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],ah

//		mov ah,ch
//		out dx,ax
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],255

			 }
_dxl_4:
//		asm sti
}



void Graph18::drawyline_rel(int up,int len,int width,int color)
{
drawyline(up,up+len-1,width,color);
}


void Graph18::drawyline(int up,int bottom,int width,int color)
{                 //Рисует вертикальную линию
	if(width<0 || width>=640) return;
	if(up<=bottom)
		{
		_BX=up;
		_SI=bottom;
		}
		else
		{
		_BX=bottom;
		_SI=up;
		}
	_DX=width;
	asm  {
//		cli

		mov ax,0a000h
		mov es,ax

		mov di,dx
		and dx,0111b
		mov cl,dl
		inc cl
		stc
		rcr dh,cl

		mov ah,dh
		mov al,8
		mov dx,3ceh
		out dx,ax

//		mov cl,2
		mov cx,si
		sub cx,bx
		inc cx
		shr di,3
//		mov dx,3c4h
		imul bx,80d
//		mov al,2
		mov al,0
		mov ah,[color]
		out dx,ax
		mov ax,0f01h
		out dx,ax


					}
_dyl_1:
asm 	{

//		mov ah,15
//		out dx,ax
		or es:[bx+di],ah
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],ah

//		mov ax,si
//		out dx,ax
//		mov ah,byte ptr es:[bx+di]
//		mov byte ptr es:[bx+di],255d

		add bx,80d

		loop _dyl_1

//		sti
		}
}

void Graph18::drawfilledbox_rel(int left,int up,int xsize,int ysize,int color)
{
drawfilledbox(left,up,left+xsize-1,up+ysize-1,color);
}

void Graph18::drawfilledbox(int left,int up,int right,int bottom,int color)
{
register int i;
if(up>bottom)
	{
	asm mov ax,[up]
	asm xchg ax,[bottom]
	asm mov [up],ax
	}
for(i=up;i<=bottom;i++)
	drawxline(left,right,i,color);
}

void Graph18::getrectangle_rel(void huge *buf,int left,int up,int xsize,int ysize)
{
getrectangle(buf,left,up,left+xsize-1,up+ysize-1);
}

void Graph18::getrectangle(void huge *buf,int left,int up,int right,int bottom)
{
if(left>right)
	{
	asm mov ax,[left]
	asm xchg ax,[right]
	asm mov [left],ax
	}
if(up>bottom)
	{
	asm mov ax,[up]
	asm xchg ax,[bottom]
	asm mov [up],ax
	}
((int*)buf)[0]=right-left;
((int*)buf)[1]=bottom-up;
(char*)buf+=4;
asm {
	mov ax,0a000h
	mov fs,ax
	mov es,word ptr buf+2
	mov di,word ptr buf

	mov dx,[right]
	mov ax,[left]
	sub dx,ax
//    inc dx
	mov cl,dl
	and cl,111b
	mov bl,10000000b
	sar bl,cl
	shr dx,3

	imul si,[up],80d
	mov cl,al
	and cl,111b
	shr ax,3
	add si,ax

	mov ax,[up]
	sub [bottom],ax
	inc word ptr[bottom]
	}
_gr_1:
asm mov bh,4
_gr_15:
asm	{
	push dx
	mov dx,3ceh
	mov al,4
	mov ah,bh
	dec ah
	out dx,ax
	pop dx

    push dx
	push si
	mov al,fs:[si]
    inc si
	mov ah,al
	}
_gr_2:
asm {
	mov al,fs:[si]
    inc si
	mov ch,al
	shl ax,cl
	and dx,dx
	jz _gr_3
	mov es:[di],ah
	inc di
	mov ah,ch
	dec dx
	jmp _gr_2
	}
_gr_3:
asm {
	and ah,bl
	mov es:[di],ah
	inc di
	pop si
    pop dx

	dec bh
	jne _gr_15

	add si,80d
	dec word ptr[bottom]
	jne _gr_1
	}

/*
register int i,o;
char temp=0;
for(o=up;o<=bottom;o++)
	for(i=left;i<=right;i++)
		if(!temp)
			{
			temp=(char)getpixel(i,o);
			*buf=temp<<4;
			temp=1;
			}
			else
			{
			temp=(char)getpixel(i,o);
			*buf|=temp;buf++;
			temp=0;
			}*/
}

void Graph18::setrectangle(char huge *buf,int left,int up)
{
int xsize=((int*)buf)[0],ysize=((int*)buf)[1]+1;
(char*)buf+=4;
asm {
    pushf
    cld
	mov ax,0a000h
	mov es,ax
    mov ax,ds
    mov fs,ax
	mov ds,word ptr buf+2
	mov si,word ptr buf
    mov dx,3ceh
    mov ax,01h
    out dx,ax
    mov al,03h
    out dx,ax
    mov ax,0ff08h
    out dx,ax

	mov ax,[left]
	mov cl,al
	and cl,111b
	mov dx,[xsize]

	mov bh,255d
	shr bh,cl

    xor ch,ch
//	mov cl,dl
    add cx,dx///
    mov di,cx
	and cl,111b
	mov bl,10000000b
	sar bl,cl
	mov ch,bh

	shr dx,3

    shr di,3
	jnz _pr_05
	and bl,ch
	}
_pr_05:
asm {
	imul di,[up],80d
	mov cl,al
	and cl,111b

	shr ax,3
	add di,ax

    not ch
    not bl
	}
_pr_1:
asm mov bh,4
_pr_15:
asm	{
    push dx
	push di
	push cx

	push dx
	mov dx,3ceh
	mov al,4
	mov ah,bh
	dec ah
	out dx,ax

    mov dl,cl
    mov cl,ah
    mov ah,1
    shl ah,cl
    mov cl,dl

	mov dx,3c4h
	mov al,2
	out dx,ax
	pop dx

//	lodsb fs:[si]
//	push dx
//	mov dx,3ceh
//	mov ah,ch
//    mov al,8
//	out dx,ax
//	pop dx
    push bx
    mov bh,ch
	xor ah,ah

//	mov al,[si]
	lodsb
	mov ch,al
	shr ax,cl
	and dx,dx
	jz _pr_3
    mov ah,es:[di]
    and ah,bh
    or al,ah
    xor bh,bh
    jmp _pr_27
//	mov es:[di],al
//	inc di
//	mov ah,ch
//	dec dx
	}
_pr_25:
asm {
//	mov al,[si]
	lodsb
	mov ch,al
	shr ax,cl
	and dx,dx
	jz _pr_3
    }
_pr_27:
asm {
//	mov es:[di],al
    stosb
	mov ah,ch
	dec dx
	jmp _pr_25
	}
_pr_3:
asm {
//	mov dx,3cfh
//    mov ah,al
//	mov al,bl
//	out dx,al
    mov dx,[xsize]
    and dl,111b
    add dl,cl
    and dl,11111000b
    jz _pr_4

    mov ah,es:[di]
    and ah,bh
    or al,ah

//	mov es:[di],al
    stosb
	mov ah,ch
    xor al,al
	shr ax,cl
    }
_pr_4:
asm {
    mov ah,es:[di]
    and ah,bl
//    not bl
//    and al,bl
    or al,ah
//	mov es:[di],al
    stosb
//	inc di
    pop bx
	pop cx
	pop di
    pop dx

	dec bh
	jne _pr_15

	add di,80d
	dec word ptr[ysize]
	jne _pr_1
	mov dx,3c4h
	mov al,2
	mov ah,0fh
	out dx,ax
    mov ax,fs
    mov ds,ax
    popf
	}


/*
if(left>right)
	{
	asm mov ax,[left]
	asm xchg ax,[right]
	asm mov [left],ax
	}
if(up>bottom)
	{
	asm mov ax,[up]
	asm xchg ax,[bottom]
	asm mov [up],ax
	}
register int i,o;
char temp=0;
for(o=up;o<=bottom;o++)
	for(i=left;i<=right;i++)
		if(!temp)
			{
			temp=(*buf)>>4;
			putpixel(i,o,temp);
			temp=1;
			}
			else
			{
			temp=(*buf)&0x0f;buf++;
			putpixel(i,o,temp);
			temp=0;
			}*/
}
