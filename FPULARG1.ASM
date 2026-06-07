;ù‚® Ø‡ÆÊ•§„‡Î Ø‡•§≠†ß≠†Á•≠Î §´Ô ‡†°Æ‚Î · ·ÆØ‡ÆÊ•··Æ‡Æ¨ 80387 ® ¢ÎË•.
				ideal
				p386
				model use16 large,cpp
				DATASEG
mydouble        dt 1000000000000000000.0
for_dec2string  dt 0
exponent        dw 0
				public c FPUerror
FPUerror        dw 0
errormes1       db "éòàÅäÄ  èÖêÖèéãçÖçàü",0
errormes2       db "éòàÅäÄ  ÑÖãÖçàü  çÄ  çìãú",0
errormes3		db "éòàÅäÄ  ÄêÉìåÖçíÄ  Ç  íêàÉéçéåÖíêàóÖëäéâ  îìçäñàà",0
errormes4		db "éòàÅäÄ  ÇõóàëãÖçàü",0
errormes5		db "éòàÅäÄ  ãéÉÄêàîåàóÖëäéâ  îìçäñàà",0
errormes6		db "éòàÅäÄ  èéäÄáÄíÖãúçéâ  îìçäñàà",0
errormes7		db "éòàÅäÄ  Ç  éÅêÄíçéâ  íêàÉéçéåÖíêàóÖëäéâ  îìçäñàà",0
errormes8		db "éòàÅäÄ  èêÖèéãçÖçàü  -  èãûë  ÅÖëäéçÖóçéëíú",0
errormes9		db "éòàÅäÄ  èêÖèéãçÖçàü  -  åàçìë  ÅÖëäéçÖóçéëíú",0
errormes10		db "éòàÅäÄ  -  äéêÖçú  àá  éíêàñÄíÖãúçéÉé  óàëãÄ",0
errormes11		db "åçéÜÖëíÇé  èìëíéÖ",0
				public c FPUerrormes
FPUerrormes     dd errormes1
				dd errormes2
				dd errormes3
				dd errormes4
				dd errormes5
				dd errormes6
				dd errormes7
				dd errormes8
				dd errormes9
				dd errormes10
				dd errormes11
;dd 11 dup (0)
				CODESEG
				locals
				public c FPUinit
				public c FPUgetmesptr
				public c FPUmul
				public c FPUdiv
				public c FPUdouble2string
				public c FPUdouble2stringbin
				public c FPUdouble2stringoct
				public c FPUdouble2stringhex
				public c FPUsin
				public c FPUcos
				public c FPUtan
				public c FPUctan
				public c FPUloadpi
				public c FPUlg
				public c FPUln
				public c FPUpower
				public c FPUmod
				public c FPUint
				public c FPUround
				public c FPUadd
				public c FPUsub
				public c FPUatan
				public c FPUasin
				public c FPUacos
				public c FPUactan
				public c FPUabs
				public c FPUloadl2E
				public c FPUloadl2T
				public c FPUsgn
				public c FPUsqrt

proc			FPUinit
				local forinit:word
				mov ax,seg FPUerror
				mov es,ax
				mov [forinit],133fh
				mov [es:FPUerror],0
				fninit
				fldcw [forinit]
				ret
endp			FPUinit

proc			FPUloadl2E
				local forinit:word
				fclex
				mov [forinit],133fh
				fldcw [forinit]
				ffree st(7)
				fldl2e
				ret
endp			FPUloadl2E

proc			FPUloadl2T
				local forinit:word
				fclex
				mov [forinit],133fh
				fldcw [forinit]
				ffree st(7)
				fldl2t
				ret
endp			FPUloadl2T


proc			FPUgetmesptr
				arg numerror:word
				mov ax,seg FPUerrormes
				mov es,ax
				mov bx,offset FPUerrormes
				mov cx,[numerror]
				shl cx,2
				add bx,cx
				mov ax,[word ptr es:bx]
				mov dx,[word ptr es:bx+2]
				ret
endp			FPUgetmesptr


proc			testerrors
				mov ax,seg FPUerror
				mov es,ax
				fnstsw ax
				fnclex
				test ax,0008h
				jz short mynooverflow
				mov [es:FPUerror],1
				jmp short mynoii
mynooverflow:   test ax,0004h
				jz short mynozero
				mov [es:FPUerror],2
				jmp short mynoii
mynozero:       test ax,1
				jz short mynoii
				mov [es:FPUerror],4
mynoii:			ret
endp			testerrors

proc			FPUadd
				arg add1:dword,add2:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_add_cont
				fldz
				ret
label label_add_cont short
				mov [forinit],133fh
				fldcw [forinit]
				mov bx,[word ptr add1]
				mov es,[word ptr add1+2]
				fld [tbyte ptr es:bx]
				mov bx,[word ptr add2]
				mov es,[word ptr add2+2]
				ffree st(7)
				fld [tbyte ptr es:bx]
				faddp st(1),st
				call testerrors
				ret
endp			FPUadd

proc			FPUsub
				arg sub1:dword,sub2:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [word ptr es:FPUerror],0
				je short label_sub_cont
				fldz
				ret
label label_sub_cont short
				mov [forinit],133fh
				fldcw [forinit]
				mov bx,[word ptr sub1]
				mov es,[word ptr sub1+2]
				fld [tbyte ptr es:bx]
				mov bx,[word ptr sub2]
				mov es,[word ptr sub2+2]
				ffree st(7)
				fld [tbyte ptr es:bx]
				fsubp st(1),st
				call testerrors
				ret
endp			FPUsub

proc			FPUsqrt
				arg sqr1:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [word ptr es:FPUerror],0
				je short label_sqrt_cont
				fldz
				ret
label label_sqrt_cont short
				mov [forinit],133fh
				fldcw [forinit]
				mov bx,[word ptr sqr1]
				mov es,[word ptr sqr1+2]
				fld [tbyte ptr es:bx]
				fsqrt
				call testerrors
				ret
endp			FPUsqrt

proc			FPUmul
				arg mul1:dword,mul2:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [word ptr es:FPUerror],0
				je short label_mul_cont
				fldz
				ret
label label_mul_cont short
				mov [forinit],133fh
				fldcw [forinit]
				mov bx,[word ptr mul1]
				mov es,[word ptr mul1+2]
				fld [tbyte ptr es:bx]
				mov bx,[word ptr mul2]
				mov es,[word ptr mul2+2]
				ffree st(7)
				fld [tbyte ptr es:bx]
				fmulp st(1),st
				call testerrors
				ret
endp			FPUmul

proc			FPUdiv
				arg div1:dword,div2:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [word ptr es:FPUerror],0
				je short label_div_cont
				fldz
				ret
label label_div_cont short
				mov [forinit],133fh
				fldcw [forinit]
				mov bx,[word ptr div1]
				mov es,[word ptr div1+2]
				fld [tbyte ptr es:bx]
				mov bx,[word ptr div2]
				mov es,[word ptr div2+2]
				ffree st(7)
				fld [tbyte ptr es:bx]
				fdivp st(1),st
				call testerrors
				ret
endp			FPUdiv


proc			FPUdouble2string
				arg num_adress:dword,string_adress:dword,exp_adress:dword,donotopt:word
				local forinit:word
				push si
				push di
				fclex
				mov [forinit],133fh
				fldcw [forinit]
				mov bx,[word ptr num_adress]
				mov es,[word ptr num_adress+2]
				ffree st(7)
				fld [tbyte ptr es:bx]
				mov bx,[word ptr string_adress]
				mov es,[word ptr string_adress+2]
				ftst
				fstsw ax
				sahf
				jnz short notzero
				mov [byte ptr es:bx],'0'
				jmp enddouble2str
notzero:        jnc short notminus
				fabs
				mov [byte ptr es:bx],'-'
				jmp short after_notminus
notminus:       mov [byte ptr es:bx],'+'
after_notminus: ffree st(7)
				mov ax,@data
				mov fs,ax
				fld [tbyte ptr fs:mydouble]
				ffree st(7)
				fld st(1)
				ffree st(7)
				fxtract
				fincstp
				ffree st(7)
				fld1
				faddp st(1),st
				ffree st(7)
				fldlg2
				fmulp st(1),st
				mov [forinit],1f3fh
				fldcw [forinit]
				frndint
				fist [word ptr fs:exponent]
				mov [forinit],133fh
				fldcw [forinit]
				fldl2t
				fmulp st(1),st
				fld st
				mov [forinit],1f3fh
				fldcw [forinit]
				frndint
				mov [forinit],133fh
				fldcw [forinit]
				fsub st(1),st
				ffree st(7)
				fld st(1)
				frndint
				ftst
				fstsw ax
				fincstp
				ffree st(7)
				fld1
				sahf
				jz short label_dec_4
				fincstp
				ffree st(7)
				jc short label_ifminus
				fist [word ptr forinit]
				fld1
				cmp [word ptr forinit],16383
				je short label_dec_4
				jl short label_caninc
				fincstp
				ffree st(7)
				fincstp
				ffree st(7)
				mov [forinit],16383
				fild [word ptr forinit]
				fld1
				jmp short label_dec_4
label_caninc:   fsub st(2),st
				fadd st(1),st
				jmp short label_dec_4
label_ifminus:  fist [word ptr forinit]
				fld1
				cmp [word ptr forinit],-16382
				je short label_dec_4
				jg short label_candec
				fincstp
				ffree st(7)
				fincstp
				ffree st(7)
				mov [forinit],-16382
				fild [word ptr forinit]
				fld1
				jmp short label_dec_4
label_candec:	fadd st(2),st
				fsub st(1),st
label_dec_4:    fscale
				fstp st(1)
				fxch st(1)
				f2xm1
				fld1
				faddp st(1),st
				fmulp st(1),st
				fdivp st(2),st
				fmul st(1),st
				fxch st(1)
				frndint
				fxch st(1)

				fcom st(1)
				fstsw ax
				mov [forinit],10
				fild [word ptr forinit]
				sahf
				ja short label_dec_1
				fdivp st(2),st
				inc [word ptr fs:exponent]
				fincstp
				ffree st(7)
				jmp short label_dec_2
label_dec_1:    fdivp st(1),st
				fcomp st(1)
				fstsw ax
				sahf
				jbe short label_dec_2
				fild [word ptr forinit]
				fmulp st(1),st
				dec [word ptr fs:exponent]
label_dec_2:    mov di,offset for_dec2string
				cmp [donotopt],0
				jz label_is_opt
				mov [forinit],1f3fh
				fldcw [forinit]
label_is_opt:	fbstp [tbyte ptr fs:di]
				mov cx,9
				xor dh,dh
				mov si,18
label_dec_3:	mov al,[byte ptr fs:di]
				mov ah,al
				shr ah,4
				and al,0fh
				add al,'0'
				mov [es:bx+si],al
				add dh,al
				dec si
				mov al,ah
				add al,'0'
				mov [es:bx+si],al
				add dh,al
				dec si
				inc di
				loop label_dec_3
				cmp dh,0
				jnz short nooverflow_dec
				mov [byte ptr es:bx+si],'0'
nooverflow_dec:	mov bx,[word ptr exp_adress]
				mov es,[word ptr exp_adress+2]
				mov ax,[fs:exponent]
				mov [es:bx],ax
enddouble2str:  pop di
				pop si
				ret
endp            FPUdouble2string



proc            FPUsin
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_sin_cont
				fldz
				ret
label label_sin_cont short
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				mov [forinit],133fh
				fldcw [forinit]
				fld [tbyte ptr gs:bx]
				fsin
				fstsw ax
				fclex
				test ax,400h
				jz short goodsin
				mov [es:FPUerror],3
goodsin:		ret
endp			FPUsin

proc            FPUcos
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_cos_cont
				fldz
				ret
label label_cos_cont short
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				mov [forinit],133fh
				fldcw [forinit]
				fld [tbyte ptr gs:bx]
				fcos
				fstsw ax
				fclex
				test ax,400h
				jz short goodcos
				mov [es:FPUerror],3
goodcos:		ret
endp			FPUcos

proc            FPUtan
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_tan_cont
				fldz
				ret
label label_tan_cont short
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				mov [forinit],133fh
				fldcw [forinit]
				fld [tbyte ptr gs:bx]
				ffree st(7)
				fptan
				fincstp
				ffree st(7)
				fstsw ax
				fclex
				test ax,400h
				jz short goodtan
				mov [es:FPUerror],3
goodtan:		ret
endp			FPUtan

proc            FPUctan
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_ctan_cont
				fldz
				ret
label label_ctan_cont short
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				mov [forinit],133fh
				fldcw [forinit]
				fld [tbyte ptr gs:bx]
				ffree st(7)
				fptan
				fstsw ax
				fclex
				test ax,400h
				jz short goodctan
				mov [es:FPUerror],3
				jmp short ctanend
goodctan:       fdivrp st(1),st
				fstsw ax
				fclex
				test ax,1100b
				jz short ctanend
				mov [es:FPUerror],1
ctanend:		ret
endp			FPUctan

proc			FPUloadpi
				local forinit:word
				fclex
				mov [forinit],133fh
				fldcw [forinit]
				ffree st(7)
				fldpi
				ret
endp			FPUloadpi

proc			FPUlg
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_lg_cont
				fldz
				ret
label label_lg_cont short
				mov [forinit],133fh
				fldcw [forinit]
				fld1
				ffree st(7)
				fldl2t
				fdivp st(1),st
				ffree st(7)
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				mov [forinit],2
				ffree st(7)
				fild [forinit]
				fsqrt
				ffree st(7)
				fld st
				fidiv [forinit]
				fcomp st(2)
				fstsw ax
				sahf
				jb short lg_cont_opt
				fincstp
				ffree st(7)
				jmp short lg_no_opt
lg_cont_opt:	fcomp st(1)
				jna short lg_no_opt
				fld1
				fsubp st(1),st
				fyl2xp1
				jmp short lg_after_opt
lg_no_opt:		fyl2x
lg_after_opt:	fstsw ax
				fclex
				test ax,101b
				jz short nobadlg
				mov [es:FPUerror],5
				jmp short lgend
nobadlg:		test ax,0008h
				jz short lgend
				mov [es:FPUerror],1
lgend:			ret
endp			FPUlg

proc			FPUln
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_ln_cont
				fldz
				ret
label label_ln_cont short
				mov [forinit],133fh
				fldcw [forinit]
				fld1
				ffree st(7)
				fldl2e
				fdivp st(1),st
				ffree st(7)
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				mov [forinit],2
				ffree st(7)
				fild [forinit]
				fsqrt
				ffree st(7)
				fld st
				fidiv [forinit]
				fcomp st(2)
				fstsw ax
				sahf
				jb short ln_cont_opt
				fincstp
				ffree st(7)
				jmp short ln_no_opt
ln_cont_opt:	fcomp st(1)
				jna short ln_no_opt
				fld1
				fsubp st(1),st
				fyl2xp1
				jmp short ln_after_opt
ln_no_opt:		fyl2x
ln_after_opt:	fstsw ax
				fclex
				test ax,101b
				jz short nobadln
				mov [es:FPUerror],5
				jmp short lnend
nobadln:		test ax,0008h
				jz short lnend
				mov [es:FPUerror],1
lnend:			ret
endp			FPUln

proc			FPUpower
				arg doubleptr1:dword,doubleptr2:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_power_cont
				fldz
				ret
label label_power_cont short
				mov [forinit],133fh
				fldcw [forinit]
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr2]
				mov gs,[word ptr doubleptr2+2]
				fld [tbyte ptr gs:bx]
				mov bx,[word ptr doubleptr1]
				mov gs,[word ptr doubleptr1+2]
				ffree st(7)
				fld [tbyte ptr gs:bx]
				fxam
				fstsw ax
				sahf
				jnz short power_may_cont
				fincstp
				ffree st(7)
				fincstp
				ffree st(7)
				fldz
				jmp powerend
power_may_cont:
				mov [forinit],2
				ffree st(7)
				fild [forinit]
				fsqrt
				ffree st(7)
				fld st
				fidiv [forinit]
				fcomp st(2)
				fstsw ax
				sahf
				jb short power_cont_opt
				fincstp
				ffree st(7)
				jmp short power_no_opt
power_cont_opt:	fcomp st(1)
				jna short power_no_opt
				fld1
				fsubp st(1),st
				fyl2xp1
				jmp short power_after_opt
power_no_opt:	fyl2x
power_after_opt:fstsw ax
				fclex
				test ax,101b
				jz short nobadpower
				mov [es:FPUerror],6
				jmp short powerend
nobadpower:		test ax,0008h
				jz short nopoweroverflow
				mov [es:FPUerror],1
				jmp short powerend
nopoweroverflow:mov [forinit],1f3fh
				fldcw [forinit]
				ffree st(7)
				fld st
				frndint
				mov [forinit],133fh
				fldcw [forinit]
				fxch st(1)
				fsub st,st(1)
				f2xm1
				ffree st(7)
				fld1
				faddp st(1),st
				fscale
				fstsw ax
				fclex
				test ax,101b
				jz short nobadpower2
				mov [es:FPUerror],6
				jmp short powerend
nobadpower2:	test ax,0008h
				jz short nopoweroverflo2
				mov [es:FPUerror],1
				jmp short powerend
nopoweroverflo2:fxch st(1)
				fincstp
				ffree st(7)
powerend:		ret
endp			FPUpower

proc			FPUmod
				arg mod1:dword,mod2:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_mod_cont
				fldz
				ret
label label_mod_cont short
				mov [forinit],133fh
				fldcw [forinit]
				mov bx,[word ptr mod2]
				mov gs,[word ptr mod2+2]
				fld [tbyte ptr gs:bx]
				mov bx,[word ptr mod1]
				mov gs,[word ptr mod1+2]
				ffree st(7)
				fld [tbyte ptr gs:bx]
modagain:		fprem
				fstsw ax
				fclex
				test ax,1101b
				jnz short isilegalmod
				test ax,10000000000b
				jnz short modagain
				fxch st(1)
				fincstp
				ffree st(7)
				jmp short modend
isilegalmod:	call testerrors
modend:			ret
endp			FPUmod

proc			FPUint
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_int_cont
				fldz
				ret
label label_int_cont short
				mov [forinit],173fh
				fldcw [forinit]
				mov ax,@data
				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				frndint
				fstsw ax
				fclex
				test ax,1
				jz short intend
				mov [es:FPUerror],4
intend:			ret
endp			FPUint

proc			FPUround
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_round_cont
				fldz
				ret
label label_round_cont short
				mov [forinit],133fh
				fldcw [forinit]
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				frndint
				fstsw ax
				fclex
				test ax,1
				jz short roundend
				mov [es:FPUerror],4
roundend:		ret
endp			FPUround

proc			FPUsgn
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [word ptr es:FPUerror],0
				je short label_sgn_cont
				xor ax,ax
				ret
label label_sgn_cont short
				mov [forinit],133fh
				fldcw [forinit]
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				ftst
				fstsw ax
				fincstp
				ffree st(7)
				fclex
				test ax,1
				jz short whatsign
				mov [es:FPUerror],4
				jmp short sgnend
whatsign:		sahf
				mov ax,0
				jz short sgnend
				mov ax,1
				jnc short sgnend
				neg ax
sgnend:			ret
endp			FPUsgn


proc			FPUatan
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_atan_cont
				fldz
				ret
label label_atan_cont short
				mov [forinit],133fh
				fldcw [forinit]
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				ffree st(7)
				fld1
				fpatan
				fstsw ax
				fclex
				test ax,1
				jz short atanend
				mov [es:FPUerror],4
atanend:		ret
endp			FPUatan

proc			FPUactan
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_actan_cont
				fldz
				ret
label label_actan_cont short
				mov [forinit],133fh
				fldcw [forinit]
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld1
				ffree st(7)
				fld [tbyte ptr gs:bx]
				fpatan
				fstsw ax
				fclex
				test ax,1
				jz short actanend
				mov [es:FPUerror],4
actanend:		ret
endp			FPUactan

proc			FPUasin
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_asin_cont
				fldz
				ret
label label_asin_cont short
				mov [forinit],133fh
				fldcw [forinit]
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				ffree st(7)
				fld1
				ffree st(7)
				fld st(1)
				fmul st,st
				fsubp st(1),st
				fsqrt
				fstsw ax
				fclex
				test ax,1
				jnz short isasinilegal
				fpatan
				fstsw ax
				fclex
				test ax,1
				jz short asinend
isasinilegal:	mov [es:FPUerror],7
asinend:		ret
endp			FPUasin

proc			FPUacos
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_acos_cont
				fldz
				ret
label label_acos_cont short
				mov [forinit],133fh
				fldcw [forinit]
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				ffree st(7)
				fld1
				ffree st(7)
				fld st(1)
				fmul st,st
				fsubp st(1),st
				fsqrt
				fstsw ax
				fclex
				test ax,1
				jnz short isacosilegal
				fxch st(1)
				fpatan
				fstsw ax
				fclex
				test ax,1
				jz short acosend
isacosilegal:   mov [es:FPUerror],7
acosend:		ret
endp			FPUacos

proc			FPUabs
				arg doubleptr:dword
				local forinit:word
				fclex
				ffree st(7)
				mov ax,seg FPUerror
				mov es,ax
				cmp [es:FPUerror],0
				je short label_abs_cont
				fldz
				ret
label label_abs_cont short
				mov [forinit],133fh
				fldcw [forinit]
;				mov ax,@data
;				mov es,ax
				mov bx,[word ptr doubleptr]
				mov gs,[word ptr doubleptr+2]
				fld [tbyte ptr gs:bx]
				fabs
				fstsw ax
				fclex
				test ax,1
				jz short absend
				mov [es:FPUerror],4
absend: 		ret
endp			FPUabs

proc			FPUdouble2stringbin
				arg num_adress:dword,string_adress:dword,exp_adress:dword
				local forinit:word
				push si
				push di
				fclex
				mov [forinit],1f3fh
				fldcw [forinit]
				mov ax,@data
				mov es,ax
				mov bx,[word ptr num_adress]
				mov gs,[word ptr num_adress+2]
				mov fs,[word ptr string_adress+2]
				ffree st(7)
				fld [tbyte ptr gs:bx]
				mov gs,[word ptr exp_adress+2]
				ftst
				fstsw ax
				sahf
				jnz short label_00
				mov bx,[word ptr string_adress]
				mov [byte ptr fs:bx],'0'
				jmp short label_end_bin
label_00:		ffree st(7)
				fxtract
				fstp [tbyte ptr es:for_dec2string]
				fistp [word ptr forinit]
				mov cx,[forinit]
				mov bx,[word ptr exp_adress]
				inc cx
				mov [gs:bx],cx
				mov bx,[word ptr string_adress]
				mov di,1
				mov [byte ptr fs:bx],'+'
				shl [byte ptr es:for_dec2string+9],1
				jnc short label_1
				mov [byte ptr fs:bx],'-'
label_1:        mov dx,bx
				mov bx,offset es:for_dec2string
				mov cx,64
label_15:		mov si,cx
				dec si
				shr si,3
				shl [byte ptr es:bx+si],1
				xchg bx,dx
				jnc short label_2
				mov [byte ptr fs:bx+di],'1'
				jmp short label_3
label_2:		mov [byte ptr fs:bx+di],'0'
label_3:		inc di
				xchg dx,bx
				loop label_15
label_end_bin:	pop di
				pop si
				ret
endp 			FPUdouble2stringbin


proc			FPUdouble2stringoct
				arg num_adress:dword,string_adress:dword,exp_adress:dword
				local forinit:word
				push si
				push di
				fclex
				mov [forinit],1f3fh
				fldcw [forinit]
				mov ax,@data
				mov es,ax
				mov bx,[word ptr num_adress]
				mov gs,[word ptr num_adress+2]
				mov fs,[word ptr string_adress+2]
				ffree st(7)
				fld [tbyte ptr gs:bx]
				mov gs,[word ptr exp_adress+2]
				ftst
				fstsw ax
				sahf
				jnz short label_00_oct
				mov bx,[word ptr string_adress]
				mov [byte ptr fs:bx],'0'
				jmp label_end_oct
label_00_oct:	ffree st(7)
				fxtract
				fstp [tbyte ptr es:for_dec2string]
				fistp [word ptr forinit]
				mov cx,[forinit]
				inc cx
				mov bx,2
				mov si,1
				jns short label_01_oct
				neg cx
				mov si,-1
				mov bx,0
label_01_oct:	add cx,bx
				mov ax,cx
				cwd
				mov di,3
				div di
				sub bx,dx
				imul bx,si
				mov cx,bx
				mov bx,[word ptr exp_adress]
				imul ax,si
				mov [gs:bx],ax
				mov ah,3
				sub ah,cl
				mov bx,[word ptr string_adress]
				mov di,1
				mov [byte ptr fs:bx],'+'
				shl [byte ptr es:for_dec2string+9],1
				jnc short label_1_oct
				mov [byte ptr fs:bx],'-'
label_1_oct:    mov dx,bx
				mov bx,offset es:for_dec2string
				xor al,al
				mov cx,66
label_15_oct:	mov si,cx
				sub si,3
				jns short label_2_oct
				mov si,0
label_2_oct:	shr si,3
				shl [byte ptr es:bx+si],1
				rcl al,1
				dec ah
				jz short label_3_oct
				jmp short label_4_oct
label_3_oct:	xchg bx,dx
				add al,'0'
				mov ah,3
				mov [byte ptr fs:bx+di],al
				xor al,al
				inc di
				xchg dx,bx
label_4_oct:	loop label_15_oct
label_end_oct:	pop di
				pop si
				ret
endp 			FPUdouble2stringoct

proc			FPUdouble2stringhex
				arg num_adress:dword,string_adress:dword,exp_adress:dword
				local forinit:word
				push si
				push di
				fclex
				mov [forinit],1f3fh
				fldcw [forinit]
				mov ax,@data
				mov es,ax
				mov bx,[word ptr num_adress]
				mov gs,[word ptr num_adress+2]
				mov fs,[word ptr string_adress+2]
				ffree st(7)
				fld [tbyte ptr gs:bx]
				mov gs,[word ptr exp_adress+2]
				ftst
				fstsw ax
				sahf
				jnz short label_00_hex
				mov bx,[word ptr string_adress]
				mov [byte ptr fs:bx],'0'
				jmp label_end_hex
label_00_hex:	ffree st(7)
				fxtract
				fstp [tbyte ptr es:for_dec2string]
				fistp [word ptr forinit]
				mov cx,[forinit]
				inc cx
				mov bx,3
				mov si,1
				jns short label_01_hex
				neg cx
				mov si,-1
				mov bx,0
label_01_hex:	add cx,bx
				mov ax,cx
				cwd
				mov di,4
				div di
				sub bx,dx
				imul bx,si
				mov cx,bx
				mov bx,[word ptr exp_adress]
				imul ax,si
				mov [gs:bx],ax
				mov ah,4
				sub ah,cl
				mov bx,[word ptr string_adress]
				mov di,1
				mov [byte ptr fs:bx],'+'
				shl [byte ptr es:for_dec2string+9],1
				jnc short label_1_hex
				mov [byte ptr fs:bx],'-'
label_1_hex:    mov dx,bx
				mov bx,offset es:for_dec2string
				xor al,al
				mov cx,68
label_15_hex:	mov si,cx
				sub si,5
				jns short label_2_hex
				mov si,0
label_2_hex:	shr si,3
				shl [byte ptr es:bx+si],1
				rcl al,1
				dec ah
				jz short label_3_hex
				jmp short label_4_hex
label_3_hex:	xchg bx,dx
				add al,'0'
				cmp al,'9'
				jbe short label_35_hex
				add al,7
label_35_hex:	mov [byte ptr fs:bx+di],al
				mov ah,4
				xor al,al
				inc di
				xchg dx,bx
label_4_hex:	loop label_15_hex
label_end_hex:	pop di
				pop si
				ret
endp 			FPUdouble2stringhex




end
