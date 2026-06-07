			.386p
			model use16 large,cpp
;			.FARDATA
			extrn c _MouseState
			extrn c _MouseEvents
			extrn c _EventWritePtr
			extrn c _EventReadPtr
			.CODE
			public c MOUSEHANDLE
MOUSEHANDLE proc
			push gs
			push di
			push si
			push ax
			mov ax,seg _MouseState
			mov es,ax
			mov ax,seg _EventWritePtr
			mov gs,ax
			xor esi,esi
			mov si,gs:[_EventWritePtr]
			mov ax,seg _MouseEvents
			mov gs,ax
			xor edi,edi
			mov di,offset _MouseEvents
			pop ax
			push ax
			mov gs:[edi][esi*8],ax
			mov gs:[edi][esi*8][2],bx
			mov gs:[edi][esi*8][4],cx
			mov gs:[edi][esi*8][6],dx
			cmp ax,1
			jne _MouseLabel_00
			mov ax,seg _EventReadPtr
			mov gs,ax
			cmp si,gs:[_EventReadPtr]
			jne _MouseLabel_03
_MouseLabel_00:
			inc si
			cmp si,50d
			jb short _MouseLabel_01
			xor si,si
_MouseLabel_01:
			mov ax,seg _EventWritePtr
			mov gs,ax
			mov gs:[_EventWritePtr],si
			mov ax,seg _EventReadPtr
			mov gs,ax
			mov di,gs:[_EventReadPtr]
			cmp di,si
			jne short _MouseLabel_03
			inc di
			cmp di,50d
			jb short _MouseLabel_02
			xor di,di
_MouseLabel_02:	mov gs:[_EventReadPtr],di
_MouseLabel_03: pop ax
			pop si
			pop di
			mov es:[_MouseState],ax
			mov es:[_MouseState][2],bx
			mov es:[_MouseState][4],cx
			mov es:[_MouseState][6],dx
			mov es:[_MouseState][8],si
			mov es:[_MouseState][10],di
			mov es:[_MouseState][12],ds
			pop gs
			ret
MOUSEHANDLE endp
end