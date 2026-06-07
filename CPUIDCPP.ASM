;       CPU detector program.
;
;       Format: int GetcurrentCPU(void)
;
;       Returns: 0 if 8086
;                2 if 80286
;                3 if 80386
;                4 if 80486
;                5 if Pentium or 586
;                more than 5 if more than Pentium
;				 +32 if 80287 on 386
;				 +64 if 80387 on 386 or greater

.8086            ; This part of the program must run on an 8086
		.model use16 large ,cpp
		extrn c ctrl_breakpressed

.code
		public c GetcurrentCPU
		public c ctrlchandler
		public c criticalerror
		global get_cpuid:PROC

GetcurrentCPU   proc
		push    di
		mov     di,sp
		and     sp, not 3               ;align stack to avoid AC fault
		push    di
		call    get_cpuid
		pop     di
		mov     sp,di
		pop     di
		ret
GetcurrentCPU   endp

get_cpuid        proc

;       8086 CPU check
;       Bits 12-15 are always set on the 8086 processor
;
check_8086:
		pushf                           ;save FLAGS
		pop     bx                      ;store FLAGS in BX
		mov     ax, 0fffh               ;clear bits 12-15
		and     ax, bx                  ;  in FLAGS
		push    ax                      ;store new FLAGS calue on stack
		popf                            ;replace current FLAGS value
		pushf                           ;set new flags
		pop     ax                      ;store new flags in AX
		and     ax, 0f000h              ;if bits 12-15 are set, then CPU
		cmp     ax, 0f000h              ;  is an 8086/8088
		mov     ax, 0             ; save the CPU type
		je  short 	end_get_cpuid


;
;       Intel 286 CPU check
;       Bits 12-15 are always clear on the Intel processor.
;
check_80286:
.286
		or      bx, 0f000h              ;try to set bits 12-15
		push    bx
		popf
		pushf
		pop     ax
		and     ax, 0f000h              ; if bits 12-15 are cleared,
										;       CPU=Intel 286
		mov     ax, 2                   ; turn on Intel 286 Cpu flag
		jz   short    end_get_cpuid     ; if CPU is intel 286, check
										; for Intel 287 math coprocessor

;       Intel386 CPU check
;       The AC bit (bit 18), is a new bit introduced in the EFLAGS
;       register on the Intel486 DX CPU to generate alignment faults.
;       This bit can not be set on the Intel386 CPU.
;
check_intel386:
.386
		pushfd
		pop     eax                     ;get original EFLAGS
		mov     ecx,eax                 ; save original EFLAGS
		xor     eax,40000h              ;flip AC bit in EFLAGS
		push    eax                     ; save for EFLAGS
		popfd                           ; copy to EFLAGS
		pushfd                          ; push EFLAGS
		pop     eax                     ; get new EFLAGS value
		xor     eax,ecx                 ; can't toggle AC bit, CPU=Intel386
		mov     ax, 3                   ; turn on Intel386 CPU flag
		je   short    checkFPU          ; if CPU is Intel386, now check
										; for an Intel 287 or Intel387 MCP

;     Intel486 DX CPU, Intel 487 SX MCP, and Intel486 SX CPU checking
;
;     Checking for the ability to set/clear the ID flag (bit 21) in EFLAGS
;     which diferentiates between Pentium (or greater) and the Intel486.
;     If the ID flag is set then the CPUID instruction can be used to
;     determine the final version of the chip, else it's a 486
;
;
check_Intel486:
.486
		pushfd                          ;push original EFLAGS
		pop     eax                     ; get original EFLAGS in eax
		mov     ecx,eax                 ;save original EFLAGS in ecx
		xor     eax,200000h             ; flip ID bit in EFLAGS
		push    eax                     ;save for EFLAGS
		popfd                           ;copy to EFLAGS
		pushfd                          ;push EFLAGS
		pop     eax                     ;get new EFLAGS value
		xor     eax,ecx
		mov     ax,4
		je  short 	checkFPU            ;if ID bit cannot be changed,
										;CPU=Intel486 without CPUID
										;instruction functionality

;       Otherwise, execute CPUID instruction to determine vendor,
;       family, model and stepping.

.586
cpuid_data:
		mov     eax, 1
		cpuid
		and     eax, 0F00H              ; mask everything but family
		shr     eax, 8
		or ax,64
		jmp short end_get_cpuid
checkFPU:
.386p
		smsw bx
		test bx,2
		jz short end_get_cpuid
		or ax,64
		cmp ax,67
		jne short end_get_cpuid
		test bx,16
		jnz short end_get_cpuid
		sub ax,32

end_get_cpuid:
.8086
		ret

get_cpuid       endp

ctrlchandler  	proc far
		push ds
		push bx
		mov bx,seg ctrl_breakpressed
		mov ds,bx
		mov bx,offset ctrl_breakpressed
		mov word ptr ds:[bx],1
		pop bx
		pop ds
		iret
ctrlchandler	endp

criticalerror proc far
		mov al,3
		iret
criticalerror endp
		end

