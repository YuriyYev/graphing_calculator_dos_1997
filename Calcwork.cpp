void reset(void)
{
isactlock=0;
input_pointer=0;
current_string=main_string;
current_flags=main_flags;
current_number=&main_number;
current_mode=0;
current_len=0;
Last_answer=0;
isinsert=1;
fix_num2=50;
sci_num2=0;
fix_num8=17;
sci_num8=0;
fix_num10=16;
sci_num10=0;
fix_num16=13;
sci_num16=0;
cur_str_system=DECSYS;
cur_ans_system=DECSYS;
cur_trig_str_system=RAD;
cur_trig_ans_system=RAD;
leftborder=-300;
rightborder=300;
upborder=200;
downborder=-200;
xscale=1;
yscale=1;
xgridstep=1;
ygridstep=1;
firstiter=100;
seconditer=100;
joinpoints=0;
deactive=0;
isredraw=0;
isauto=0;
main_string[0]='\0';
firstlowlimit_str[0]='\0';
secondlowlimit_str[0]='\0';
firsthighlimit_str[0]='\0';
secondhighlimit_str[0]='\0';
for(int i=0;i<34;i++)
	{
	variable[i].string[0]='0';
	variable[i].string[1]='\0';
	variable[i].flags[0]=char(RAD|DECSYS);
	variable[i].number=0;
	variable[i].isstring=0;
	variable[i].ison=0;
	variable[i].iserror=0;
	}
for(i=0;i<MULTITUDE_SIZE;i++)
	{
	multitude[i].isvar=0;
	multitude[i].var=0;
	multitude[i].number=0;
	}
for(i=0;i<4;i++)
	graphstate[i].init(0,0,0,0,0,0,0);
Indic_buffer_len=0;
Indic_buffer[0]='\0';
multitude_len=0;
real_multitude_len=0;
Counterror=FPUerror=0;
ishelp=0;
drawconsol(0);
hidemouse();
indic.activate();
setstate(0);
showmessage(message[1]);
showmouse();
drawallkeys();
drawvariables();
showmouse();
}

void showscifix(void)
{
int xc=485,yc=120,len,work;
hidemouse();
if(current_mode==0 || current_mode==3) work=cur_str_system;
	else if(current_mode==1) work=cur_ans_system;
if(work==BINSYS)
	{
	Putstring(xc,yc,"FIX2=",15,7);
	xc+=5*8;
	len=ulong2string_dec(fix_num2,num2str_buffer);
	num2str_buffer[len]='\0';
	Putstring(xc,yc,num2str_buffer,15,7);
	mygr.drawfilledbox(xc+len*8,yc,581,yc+11,7);
	yc+=12;
	xc=485;
	Putstring(xc,yc,"SCI2=",15,7);
	xc+=5*8;
	len=ulong2string_dec(sci_num2,num2str_buffer);
	num2str_buffer[len]='\0';
	Putstring(xc,yc,num2str_buffer,15,7);
	mygr.drawfilledbox(xc+len*8,yc,581,yc+11,7);
	}
	else if(work==OCTSYS)
	{
	Putstring(xc,yc,"FIX8=",15,7);
	xc+=5*8;
	len=ulong2string_dec(fix_num8,num2str_buffer);
	num2str_buffer[len]='\0';
	Putstring(xc,yc,num2str_buffer,15,7);
	mygr.drawfilledbox(xc+len*8,yc,581,yc+11,7);
	yc+=12;
	xc=485;
	Putstring(xc,yc,"SCI8=",15,7);
	xc+=5*8;
	len=ulong2string_dec(sci_num8,num2str_buffer);
	num2str_buffer[len]='\0';
	Putstring(xc,yc,num2str_buffer,15,7);
	mygr.drawfilledbox(xc+len*8,yc,581,yc+11,7);
	}
	else if(work==DECSYS)
	{
	Putstring(xc,yc,"FIX10=",15,7);
	xc+=6*8;
	len=ulong2string_dec(fix_num10,num2str_buffer);
	num2str_buffer[len]='\0';
	Putstring(xc,yc,num2str_buffer,15,7);
	mygr.drawfilledbox(xc+len*8,yc,581,yc+11,7);
	yc+=12;
	xc=485;
	Putstring(xc,yc,"SCI10=",15,7);
	xc+=6*8;
	len=ulong2string_dec(sci_num10,num2str_buffer);
	num2str_buffer[len]='\0';
	Putstring(xc,yc,num2str_buffer,15,7);
	mygr.drawfilledbox(xc+len*8,yc,581,yc+11,7);
	}
	else if(work==HEXSYS)
	{
	Putstring(xc,yc,"FIX16=",15,7);
	xc+=6*8;
	len=ulong2string_dec(fix_num16,num2str_buffer);
	num2str_buffer[len]='\0';
	Putstring(xc,yc,num2str_buffer,15,7);
	mygr.drawfilledbox(xc+len*8,yc,581,yc+11,7);
	yc+=12;
	xc=485;
	Putstring(xc,yc,"SCI16=",15,7);
	xc+=6*8;
	len=ulong2string_dec(sci_num16,num2str_buffer);
	num2str_buffer[len]='\0';
	Putstring(xc,yc,num2str_buffer,15,7);
	mygr.drawfilledbox(xc+len*8,yc,581,yc+11,7);
	}
showmouse();
}

void showsystems(void)
{
int work;
if(current_mode==0 || current_mode==3) work=cur_str_system;
	else if(current_mode==1) work=cur_ans_system;
if(work==BINSYS) F_BIN.turn_on();
	else F_BIN.turn_off();
if(work==OCTSYS) F_OCT.turn_on();
	else F_OCT.turn_off();
if(work==DECSYS) F_DEC.turn_on();
	else F_DEC.turn_off();
if(work==HEXSYS) F_HEX.turn_on();
	else F_HEX.turn_off();
if(current_mode==0 || current_mode==3) work=cur_trig_str_system;
	else if(current_mode==1) work=cur_trig_ans_system;
if(work==RAD) F_RAD.turn_on();
	else F_RAD.turn_off();
if(work==DEG) F_DEG.turn_on();
	else F_DEG.turn_off();
if(work==GRD) F_GRD.turn_on();
	else F_GRD.turn_off();
showscifix();
return;
}

void makefix(int sys,int noscifix)
{
int work,mem;
if(sys==2)
	{
	if(fix_num2==64 || noscifix==1) {num2str_pointer=fix_num2+1;return;}
	if(noscifix==2)
		work=50;
		else
		work=fix_num2;
	}
if(sys==8)
	{
	if(fix_num8==22 || noscifix==1) {num2str_pointer=fix_num8+1;return;}
	if(noscifix==2)
		work=17;
		else
		work=fix_num8;
	}
if(sys==10)
	{
	if(fix_num10==18 || noscifix==1) {num2str_pointer=fix_num10+1;return;}
	if(noscifix==2)
		work=16;
		else
		if(noscifix==3)
			work=15;
			else
			if(noscifix==4)
				work=15;
				else
				work=fix_num10;
	}
if(sys==16)
	{
	if(fix_num16==17 || noscifix==1) {num2str_pointer=fix_num16+1;return;}
	for(work=1;work<18;work++)
		if(num2str_buffer[work]>'9') num2str_buffer[work]-='A'-'9'-1;
	if(noscifix==2)
		work=13;
		else
		work=fix_num16;
	}
mem=work;
if(num2str_buffer[work+1]>=(sys/2+'0'))
	{
	do
		{
		if(num2str_buffer[work+1]==sys+'0') num2str_buffer[work+1]='0';
		num2str_buffer[work]++;
		work--;
		} while(work>0 && num2str_buffer[work+1]==sys+'0');
	if(num2str_buffer[1]==sys+'0')
		{
		num2str_buffer[1]='1';
		num2str_exp++;
		}
	}
if(sys==16)
	for(work=1;work<18;work++)
		if(num2str_buffer[work]>'9') num2str_buffer[work]+='\xc0'-'9'-1;
num2str_pointer=mem+1;
}

void makesci(int sys,int noscifix)
{
int work,work1=num2str_pointer-1;
if(sys==2)
	{
	work=sci_num2;
//	work1=64;
	}
	else
	if(sys==8)
		{
		work=sci_num8;
//		work1=22;
		}
		else
		if(sys==10)
			{
			work=sci_num10;
//			work1=18;
			}
			else
			{
			work=sci_num16;
//			work1=17;
			}
if(!work || noscifix)
	{
	if(num2str_exp>0 && num2str_exp<num2str_pointer-1)
		{
		Strcpyr(num2str_buffer+num2str_pointer-1+1,num2str_buffer+num2str_pointer-1,num2str_pointer-1-num2str_exp);
		num2str_buffer[num2str_exp+1]=',';
//		for(int i=num2str_exp+2;i<=num2str_pointer-1+1;i++)
//			if(num2str_buffer[i]>'0') break;
//		if(i==num2str_pointer+1) num2str_pointer=num2str_exp;
		num2str_exp=0;
		num2str_pointer++;
		}
		else
		if(num2str_exp>0 && num2str_exp>=num2str_pointer-1)
		{
		num2str_exp-=num2str_pointer-1;
//		num2str_buffer[num2str_pointer++-1+1]=',';
//		num2str_buffer[num2str_pointer++-1+1]='0';
		return;
		}
		else
		{
		while(num2str_buffer[num2str_pointer-1]=='0')
			num2str_pointer--;
		if(num2str_exp<=0 && num2str_pointer-1-num2str_exp<=work1)
			{
			Strcpyr(num2str_buffer+num2str_pointer-1-num2str_exp+2,num2str_buffer+num2str_pointer-1,num2str_pointer-1);
			for(int i=1;i<2-num2str_exp+1;i++)
				num2str_buffer[i]='0';
			num2str_buffer[2]=',';
			num2str_pointer+=2-num2str_exp;
			num2str_exp=0;
			}
			else
			if(num2str_exp<=0 && num2str_pointer-1-num2str_exp>work1)
			{
			Strcpyr(num2str_buffer+num2str_pointer-1+2,num2str_buffer+num2str_pointer-1,num2str_pointer-1);
			num2str_buffer[1]='0';
			num2str_buffer[2]=',';
			num2str_pointer+=2;
			}
		}
	while(num2str_buffer[num2str_pointer-1]=='0')
		num2str_pointer--;
	if(num2str_buffer[num2str_pointer-1]==',') num2str_pointer--;
	return;
	}
if(work==num2str_pointer-1)
	{
	num2str_exp-=work;
	if(num2str_exp)
		{
		num2str_buffer[work+1]=',';
		num2str_buffer[work+2]='0';
		num2str_pointer+=2;
		}
	return;
	}
Strcpyr(num2str_buffer+num2str_pointer-1+1,num2str_buffer+num2str_pointer-1,num2str_pointer-1-work);
num2str_buffer[work+1]=',';
num2str_exp-=work;
num2str_pointer++;
while(num2str_buffer[num2str_pointer-1]=='0')
	if(num2str_buffer[num2str_pointer-2]!=',')
		num2str_pointer--;
	else break;
}


int convert_number2string(long double num,int sys,int noscifix)
{
if(num==0)
	{
	num2str_buffer[0]='0';
	num2str_buffer[1]='\0';
	return 1;
	}
if(sys==2)
	{
	FPUdouble2stringbin(num,num2str_buffer,num2str_exp);
	makefix(sys,noscifix);
	makesci(sys,noscifix);
	if(num2str_exp)
		{
		num2str_buffer[num2str_pointer++]=KEY_e;
		num2str_pointer+=int2string_bin(num2str_exp,num2str_buffer+num2str_pointer);
		}
	num2str_buffer[num2str_pointer]='\0';
	}
if(sys==8)
	{
	FPUdouble2stringoct(num,num2str_buffer,num2str_exp);
	makefix(sys,noscifix);
	makesci(sys,noscifix);
	if(num2str_exp)
		{
		num2str_buffer[num2str_pointer++]=KEY_e;
		num2str_pointer+=int2string_oct(num2str_exp,num2str_buffer+num2str_pointer);
		}
	num2str_buffer[num2str_pointer]='\0';
	}
if(sys==10)
	{
	if(noscifix!=1 || (fix_num10<18 && noscifix!=0))
		FPUdouble2string(num,num2str_buffer,num2str_exp,1);
		else
		FPUdouble2string(num,num2str_buffer,num2str_exp);
	if(num2str_buffer[0]=='0')
		{
		num2str_buffer[1]='\0';
		return 1;
		}
	makefix(sys,noscifix);
	makesci(sys,noscifix);
	if(num2str_exp)
		{
		num2str_buffer[num2str_pointer++]=KEY_e;
		num2str_pointer+=int2string_dec(num2str_exp,num2str_buffer+num2str_pointer);
		}
	num2str_buffer[num2str_pointer]='\0';
	}
if(sys==16)
	{
	FPUdouble2stringhex(num,num2str_buffer,num2str_exp);
	makefix(sys,noscifix);
	makesci(sys,noscifix);
	if(num2str_exp)
		{
		num2str_buffer[num2str_pointer++]=KEY_e;
		num2str_pointer+=int2string_hex(num2str_exp,num2str_buffer+num2str_pointer);
		}
	num2str_buffer[num2str_pointer]='\0';
	}
return num2str_pointer;
}

void drawvariable(int var)
{
int xc=(var/13)*240+5,yc=(var%13)*12,x=xc;
//int xc=(var%2)*230+5,yc=var/2*12;
if(var>=26) yc+=12;
int backcol=7,forecol=15;
if(variable[var].iserror) backcol=4;
if(variable[var].ison)
	if(backcol==4) backcol=5;
		else backcol=1;
hidemouse();
//if(!nomouse)
//	SETMOUSEEXLUSIONAREA(xc,yc,xc+219,yc+11);
if(var>=26)
	{
	Putsymbol(asciisymboltable['M'],xc,yc,forecol,backcol);
	Putsymbol(asciisymboltable['1'+var-mem1],xc+8,yc,forecol,backcol);
	showmouse();
	return;
	}
Putsymbol(asciisymboltable['A'+var],xc,yc,forecol,backcol);
xc+=8;
Putsymbol(asciisymboltable['='],xc,yc,forecol,backcol);
char *ptr=variable[var].string;
if(variable[var].isstring)
	{
	convert_number2string(variable[var].number,DECSYS,2);
	ptr=num2str_buffer;
	if(ptr[0]=='+') ptr++;
	}
for(;*ptr;ptr++)
	{
	xc+=8;
	if(*ptr==KEY_e)
		Putsymbol(asciisymboltable['E'],xc,yc,forecol,backcol);
		else
		Putsymbol(asciisymboltable[*ptr],xc,yc,forecol,backcol);
	}
xc+=8;
if(xc<x+220)
	mygr.drawfilledbox(xc,yc,x+219,yc+11,7);
showmouse();
}

void drawmulnum(void)
{
char txt[11],*ptr=txt;
txt[ulong2string_dec(multitude_len,ptr)]='\0';
int xc=485;
hidemouse();
//if(!nomouse)
//	SETMOUSEEXLUSIONAREA(xc,0,xc+95,17);
Putsymbol(&S_KEY_MUL_LEN,xc,3,15,7);
xc+=8;
Putsymbol(asciisymboltable['='],xc,0,15,7);
for(;*ptr;ptr++)
	{
	xc+=8;
	Putsymbol(asciisymboltable[*ptr],xc,0,15,7);
	}
xc+=8;
if(xc<580)
	mygr.drawfilledbox(xc,0,580,11,7);
showmouse();
}

void drawvariables(void)
{
for(int i=0;i<=mem8;i++)
	drawvariable(i);
drawmulnum();
}


void recountvariables(int switcher)
{
long double work;
for(int i=0;i<=mem8;i++)
	{
	if(!variable[i].ison || !variable[i].isstring) continue;
	variable[i].newnumber=variable[i].number;
	work=countstring(variable[i].string,variable[i].flags,1025);
	if(Counterror || FPUerror)
		{
		variable[i].iserror=1;
		Counterror=0;
		FPUerror=0;
		continue;
		}
	variable[i].newnumber=work;
	variable[i].iserror=0;
	}
for(i=0;i<=mem8;i++)
	if(variable[i].ison && variable[i].isstring)
		{
		variable[i].number=variable[i].newnumber;
		if(!switcher) drawvariable(i);
		}
}

void showerrormessage(void)
{
hidemouse();
indic.deactivate();
//Strcpy(current_string,indic.gettext(),Strlen(indic.gettext())+1);
if(Counterror)
	indic.settext(Error_messages[Counterror]);
	else
	indic.settext(FPUgetmesptr(FPUerror-1));
indic.redraw();
if(current_mode!=3 && !Counterror && ismore) setstate(2);
	else setstate(2,2);
last_mes=currentmessage;
showmessage(message[3]);
showmouse();
Counterror=0;
FPUerror=0;
last_mode=current_mode;
current_mode=2;
}

int makecount(void)
{
if(!indic.isedit)
	*current_number=countstring(current_string,current_flags,current_len);
	else
	*current_number=countstring(current_string+indic.Lefteditpos,current_flags+indic.Lefteditpos,indic.Righteditpos-indic.Lefteditpos);
if(Counterror || FPUerror)
	{
	input_pointer=exppointer;
	if(indic.isedit) input_pointer+=indic.Lefteditpos;
	return 0;
	}
return 1;
}

void showonlymessage(int);

int receivekeyevent(void)
{
int keychar,keycode,scrolllockon=0,capslockon=0,retval=KEY_no,ctrlpressed=0,
	numlockon=0;
again:
keystatus=Getkeyboardflags();
if(keystatus&KBS_CTRLDOWN) ctrlpressed=1;
if(keystatus&KBS_SCRLOCKON) scrolllockon=1;
if(keystatus&KBS_NUMLOCKON) numlockon=1;
if(keystatus&KBS_CAPSLOCKON) capslockon=1;
keychar=Getkey();
keycode=int(*((unsigned char*)(&keychar)+1));
keychar=int(*(unsigned char*)(&keychar));

if(keychar==27 && keycode==1) {retval=KEY_esc;goto endkey;}
if(keychar=='.') keychar=',';
if(keychar=='!' || (keychar>='(' && keychar<='/') || (keychar>='0' && keychar<='9' && keycode<=11) || (keychar>='[' && keychar<='^')) {retval=keychar;goto endkey;}
if(capslockon)
	if(keychar>='A' && keychar<='Z') keychar+=32;
		else if(keychar>='a' && keychar<='z') keychar-=32;
if(keychar=='R' && keystatus&KBS_LSHIFTDOWN && keystatus&KBS_RSHIFTDOWN)
	if(!ishelp) {reset();return KEY_break;}
		else {retval=KEY_reset;goto endkey;}
if(keychar=='S' && keystatus&KBS_LSHIFTDOWN && keystatus&KBS_RSHIFTDOWN)
	{retval=KEY_save;goto endkey;}
if(keychar=='L' && keystatus&KBS_LSHIFTDOWN && keystatus&KBS_RSHIFTDOWN)
	if(!ishelp)
		if(loadstate())
			return KEY_break;
			else
			return KEY_no;
		else {retval=KEY_load;goto endkey;}
if(keychar>='A' && keychar<='Z') {retval=keychar;goto endkey;}
if(keychar=='s')
	if(scrolllockon) {retval=KEY_sh;goto endkey;}
		else {retval=KEY_sin;goto endkey;}
if(keychar=='c')
	if(scrolllockon) {retval=KEY_ch;goto endkey;}
		else {retval=KEY_cos;goto endkey;}
if(keychar=='t')
	if(scrolllockon) {retval=KEY_th;goto endkey;}
		else {retval=KEY_tg;goto endkey;}
if(keychar=='g')
	if(scrolllockon) {retval=KEY_cth;goto endkey;}
		else {retval=KEY_ctg;goto endkey;}
if(!keychar && keycode==31)
	if(scrolllockon) {retval=KEY_arsh;goto endkey;}
		else {retval=KEY_arcsin;goto endkey;}
if(!keychar && keycode==46)
	if(scrolllockon) {retval=KEY_arch;goto endkey;}
		else {retval=KEY_arccos;goto endkey;}
if(!keychar && keycode==20)
	if(scrolllockon) {retval=KEY_arth;goto endkey;}
		else {retval=KEY_arctg;goto endkey;}
if(!keychar && keycode==34)
	if(scrolllockon) {retval=KEY_arcth;goto endkey;}
		else {retval=KEY_arcctg;goto endkey;}
if(keychar=='<') {retval=KEY_LESS;goto endkey;}
if(!keychar && keycode==51) {retval=KEY_LESS_EQ;goto endkey;}
if(keychar=='>') {retval=KEY_GREATER;goto endkey;}
if(!keychar && keycode==52) {retval=KEY_GREATER_EQ;goto endkey;}
if(keychar=='=') {retval=KEY_EQ;goto endkey;}
if(!keychar && keycode==131) {retval=KEY_NOT_EQ;goto endkey;}
if(keychar=='l') {retval=KEY_ln;goto endkey;}
if(!keychar && keycode==38) {retval=KEY_lg;goto endkey;}
if(keychar=='e') {retval=KEY_exp;goto endkey;}
if(!keychar && keycode==18) {retval=KEY_e;goto endkey;}
if(!keychar && keycode==49) {retval=KEY_not;goto endkey;}
if(keychar=='&') {retval=KEY_and;goto endkey;}
if(keychar=='|') {retval=KEY_or;goto endkey;}
if(keychar=='x') {retval=KEY_xor;goto endkey;}
if(keychar=='{') {retval=KEY_leftmp;goto endkey;}
if(keychar=='}') {retval=KEY_rightmp;goto endkey;}
if(keychar=='p') {retval=KEY_pi;goto endkey;}
if(keychar=='o') {retval=KEY_log;goto endkey;}
if(!keychar && keycode==24) {retval=KEY_sgn;goto endkey;}
if(keychar=='a') {retval=KEY_ans;goto endkey;}
if(!keychar && keycode==30) {retval=KEY_MUL_ELEM;goto endkey;}
if(keychar=='r') {retval=KEY_rnd;goto endkey;}
if(keychar=='y') {retval=KEY_yscale;goto endkey;}
if(!keychar && keycode==21) {retval=KEY_xscale;goto endkey;}
if(keychar=='m') {retval=KEY_SUM;goto endkey;}
if(!keychar && keycode==50) {retval=KEY_MUL;goto endkey;}
if(keychar=='n') {retval=KEY_MUL_LEN;goto endkey;}
if(keychar=='i') {retval=KEY_INDEX;goto endkey;}
if(keychar>=1 && keychar<=6) {retval=KEY_Ah+keychar-1;goto endkey;}
if(keychar==26) {retval=KEY_actlock;goto endkey;}
if(!keychar)
	if(keycode>=84 && keycode<=92) {retval=KEY_ROOT1+keycode-84;goto endkey;}
		else if(keycode>=104 && keycode<=112) {retval=KEY_POW1+keycode-104;goto endkey;}
if(keychar==224 && !(keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)))
	{
	if(keycode==75) {retval=KEY_leftcur;goto endkey;}
	if(keycode==77) {retval=KEY_rightcur;goto endkey;}
	if(keycode==73) {retval=KEY_leftqcur;goto endkey;}
	if(keycode==81) {retval=KEY_rightqcur;goto endkey;}
	if(keycode==71) {retval=KEY_leftend;goto endkey;}
	if(keycode==79) {retval=KEY_rightend;goto endkey;}
	if(keycode==82) {retval=KEY_insert;goto endkey;}
	if(keycode==83) {retval=KEY_del;goto endkey;}
	}
if(keychar==8 && keycode==14 && !(keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))) {retval=KEY_bs;goto endkey;}
if(keychar==13 && (keycode==28 || keycode==224) && !(keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))) {retval=KEY_exe;goto endkey;}
if(keychar==10 && (keycode==28 || keycode==224)) {retval=KEY_more;goto endkey;}
if(keychar==13 && (keycode==28 || keycode==224) && (keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))) {retval=KEY_stay;goto endkey;}
if(keychar==9 && keycode==15)
	{
	int temper=cur_str_system;
	if(current_mode==1) temper=cur_ans_system;
	if(temper==HEXSYS) {retval=KEY_BIN;goto endkey;}
	if(temper==DECSYS) {retval=KEY_HEX;goto endkey;}
	if(temper==OCTSYS) {retval=KEY_DEC;goto endkey;}
	if(temper==BINSYS) {retval=KEY_OCT;goto endkey;}
	}
if(!keychar && (keycode==148 || keycode==15))
	{
	int temper=cur_trig_str_system;
	if(current_mode==1) temper=cur_trig_ans_system;
	if(temper==RAD) retval=KEY_DEG;
    	else if(temper==DEG) retval=KEY_GRD;
				else if(temper==GRD) retval=KEY_RAD;
	if(keycode==148) retval+=42;
    goto endkey;
	}
if(!keychar)
	{
	if(keycode==59)
		if(!ishelp)
			if(!gethelp()) return KEY_exit;
				else {showonlymessage(currentmessage);return KEY_no;}
			else
			{retval=KEY_help;goto endkey;}
	if(keycode==94) {retval=KEY_helplock;goto endkey;}
	if(keycode==60) {retval=KEY_savenumto;goto endkey;}
	if(keycode==95) {retval=KEY_savestrto;goto endkey;}
	if(keycode==61) {retval=KEY_read_num;goto endkey;}
	if(keycode==96) {retval=KEY_read_str;goto endkey;}
	if(keycode==62) {retval=KEY_add_to_mul;goto endkey;}
	if(keycode==97) {retval=KEY_add_var_to_mul;goto endkey;}
	if(keycode==63) {retval=KEY_M1_plus;goto endkey;}
	if(keycode==98) {retval=KEY_M1_minus;goto endkey;}
	if(keycode==64) {retval=KEY_M1_mul;goto endkey;}
	if(keycode==99) {retval=KEY_M1_div;goto endkey;}
	if(keycode==65) {retval=KEY_Mn_plus;goto endkey;}
	if(keycode==100) {retval=KEY_Mn_minus;goto endkey;}
	if(keycode==66) {retval=KEY_Mn_mul;goto endkey;}
	if(keycode==101) {retval=KEY_Mn_div;goto endkey;}
	if(keycode==67) {retval=KEY_toggle;goto endkey;}
	if(keycode==102) {retval=KEY_swap;goto endkey;}
	if(keycode==68) {retval=KEY_graph;goto endkey;}
	if(keycode==103) {retval=KEY_multitude;goto endkey;}
	if(keycode==93) {retval=KEY_fix;goto endkey;}
	if(keycode==113) {retval=KEY_sci;goto endkey;}
	if(keycode==14) {retval=KEY_clear;goto endkey;}
	if(keycode==45) {retval=KEY_exit;goto endkey;}
	if(keycode>=120 && keycode<=127) {retval=KEY_M1+keycode-120;goto endkey;}
	}
//if(keychar>=1 && keychar<=8 && !keycode) {retval=KEY_M1+keychar-1;goto endkey;}
if((!keychar || keychar==224) && keycode==146) {retval=KEY_bufcopy;goto endkey;}
if(keycode==82 && ((keychar==224 && keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) || (!numlockon && keychar=='0') || (numlockon && !keychar))) {retval=KEY_bufinsert;goto endkey;}
if(keycode==83 && ((keychar==224 && keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) || (!numlockon && keychar=='.') || (numlockon && !keychar))) {retval=KEY_bufcopydel;goto endkey;}
if(keycode==75 && ((keychar==224 && keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) || (!numlockon && keychar=='4') || (numlockon && !keychar))) {retval=KEY_bufleft;goto endkey;}
if(keycode==77 && ((keychar==224 && keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) || (!numlockon && keychar=='6') || (numlockon && !keychar))) {retval=KEY_bufright;goto endkey;}
if(keycode==73 && ((keychar==224 && keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) || (!numlockon && keychar=='9') || (numlockon && !keychar))) {retval=KEY_bufqleft;goto endkey;}
if(keycode==81 && ((keychar==224 && keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) || (!numlockon && keychar=='3') || (numlockon && !keychar))) {retval=KEY_bufqright;goto endkey;}
if(keycode==71 && ((keychar==224 && keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) || (!numlockon && keychar=='7') || (numlockon && !keychar))) {retval=KEY_bufhome;goto endkey;}
if(keycode==79 && ((keychar==224 && keystatus&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN)) || (!numlockon && keychar=='1') || (numlockon && !keychar))) {retval=KEY_bufend;goto endkey;}
if(keychar!=224)
	{
	switch(keycode)
		{
		case 83: {retval=KEY_coma;goto endkey;}
		case 82: {retval=KEY_0;goto endkey;}
		case 81: {retval=KEY_3;goto endkey;}
		case 80: {retval=KEY_2;goto endkey;}
		case 79: {retval=KEY_1;goto endkey;}
		case 77: {retval=KEY_6;goto endkey;}
		case 76: {retval=KEY_5;goto endkey;}
		case 75: {retval=KEY_4;goto endkey;}
		case 73: {retval=KEY_9;goto endkey;}
		case 72: {retval=KEY_8;goto endkey;}
		case 71: {retval=KEY_7;goto endkey;}
		}
	}
endkey:
if(retval==KEY_helplock)
	{
	ishelp=!ishelp;
	if(ishelp) BUT_helplock.push();
		else
		BUT_helplock.draw();
	hidemouse();
	if(ishelp)
		SETGRAPHICSPOINTER(0,0,mousearrowquest);
		else
		SETGRAPHICSPOINTER(0,0,mousearrow);
	showmouse();
	return KEY_no;
	}
if(ishelp)
	{helpon(retval);return KEY_no;}
return retval;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
void shownumonindic(long double num,int sys,int keyst=0)
{
int len=convert_number2string(num,sys);
if(num2str_buffer[0]=='+')
	Strcpy(curnumbuf,num2str_buffer+1,len);
	else
	Strcpy(curnumbuf,num2str_buffer,len+1);
//if(!keyst)
//	indic.hidemouse_ind();
//	else
	hidemouse();
indic.deactivate();
indic.settext(curnumbuf);
//indic.draw();
indic.setcursorposition(0);
indic.redraw();
if(!indic.insertmode) indic.changeinputtype(0);
indic.activate();
if(keyst) setstate(keyst);
showmouse();
}

void showcurrentstring(CursorState st,int keyst)
{
hidemouse();
indic.deactivate();
indic.settext(current_string);
indic.restorecursorstate(st);
indic.redraw();
if(isinsert ^ indic.insertmode) indic.changeinputtype(0);
indic.activate();
setstate(keyst);
showmouse();
}

void showonlymessage(int num)
{
hidemouse();
//if(!nomouse)
//	SETMOUSEEXLUSIONAREA(2,161,637,176);
showmessage(message[num]);
showmouse();
}

void showmessagewithstate(int num,int st,int ifind=0)
{
hidemouse();
showmessage(message[num]);
setstate(st);
if(ifind) indic.activate();
showmouse();
}

void if_exit(void)
{
	last_mes=currentmessage;
	hidemouse();
		showmessage("‚ëå®¤...");
	showmouse();
	long beg=Gettimerticks();
	while(Gettimerticks()-beg<18)
		if(Kbhit())
			{
			hidemouse();
			if(last_mes)
				showmessage(message[last_mes]);
				else
				showmessage(num2str_buffer);
			showmouse();
			Getkey();
			return;
			}
	throw (int)0;
}

int convertevent(int key)
{
int morekey,i;
if(key==KEY_exit)
	{
	if_exit();
	return 1;
	}
if(key==KEY_actlock)
	{
	isactlock=!isactlock;
	if(isactlock) BUT_actlock.push();
		else
		BUT_actlock.draw();
   return 1;
	}
if(key==KEY_no) return 1;
if(key==KEY_save && current_mode<2) {savestate();return 1;}
//begconv:
if(key<256 && (current_mode==0 || current_mode==3))
	{
	if(!indic.takesymbol(key,current_flags,(unsigned char)cur_str_system|cur_trig_str_system)) return 1;
	input_pointer=indic.getcursorposition();
	current_len=indic.gettextlength();
	return 1;
	}
if(current_mode==0)
	{
	switch(key)
		{
		case KEY_savestrto:
//			mainstate=indic.getcursorstate();
			makecount();
			if(Counterror) {ismore=0;showerrormessage();return 1;}
			hidemouse();
			indic.deactivate();
			showmessage(message[4]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  ‡€ˆ‘ˆ  ‘’ŽŠˆ  ‚  ……");//4
//			indic.redraw();
			setstate(4,1);
			showmouse();
			morekey=0;
			while(1)
				{
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc) {FPUerror=0;showmessagewithstate(1,0,1);return 1;}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
						{
						if(morekey>=KEY_M1 && morekey<=KEY_M8) morekey=morekey-KEY_M1+mem1+KEY_A;
						if(!indic.isedit)
							{
							Strcpy(variable[morekey-KEY_A].string,current_string,current_len+1);
							Strcpy(variable[morekey-KEY_A].flags,current_flags,current_len);
							}
							else
							{
							Strcpy(variable[morekey-KEY_A].string,current_string+indic.Lefteditpos,indic.Righteditpos-indic.Lefteditpos);
							Strcpy(variable[morekey-KEY_A].flags,current_flags+indic.Lefteditpos,indic.Righteditpos-indic.Lefteditpos);
							variable[morekey-KEY_A].string[indic.Righteditpos-indic.Lefteditpos]='\0';
							}
						variable[morekey-KEY_A].isstring=1;
						if(!FPUerror)
							{
							if(!variable[morekey-KEY_A].ison)
								variable[morekey-KEY_A].number=main_number;
							variable[morekey-KEY_A].iserror=0;
							}
							else
							{
							variable[morekey-KEY_A].iserror=1;
							FPUerror=0;
							}
						drawvariable(morekey-KEY_A);
						showmessagewithstate(1,0,1);
//						showcurrentstring(mainstate,0);
						return 1;
						}
					morekey=0;
					}
				}
		case KEY_savenumto:
//			mainstate=indic.getcursorstate();
			makecount();
			if(Counterror || FPUerror) {ismore=0;showerrormessage();return 1;}
			hidemouse();
			indic.deactivate();
			showmessage(message[5]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  ‡€ˆ‘ˆ  ’Ž‹œŠŽ  —ˆ‘‹€  ‚  ……");//5
//			indic.redraw();
			setstate(4);
			showmouse();
			morekey=0;
			while(1)
				{
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc) {FPUerror=0;showmessagewithstate(1,0,1);return 1;}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8) || morekey==KEY_MUL_LEN)
						{
						if(morekey==KEY_MUL_LEN)
							{
							if(main_number>4294967295.0) multitude_len=4294967295ul;
								else if(main_number<0) multitude_len=real_multitude_len;
										else
										multitude_len=(unsigned long)main_number;
							if(multitude_len<real_multitude_len)
//								{
//								for(int i=(int)multitude_len;i<real_multitude_len;i++)
//									{
//									multitude[i].isvar=0;
//									multitude[i].number=0;
//									}
								real_multitude_len=(int)multitude_len;
//								}
							drawmulnum();
							}
							else
							{
							if(morekey>=KEY_M1 && morekey<=KEY_M8) morekey=morekey-KEY_M1+mem1+KEY_A;
							if(!variable[morekey-KEY_A].isstring)
								{
								int ifplus=0;
								int len=convert_number2string(main_number,DECSYS,2);
								if(num2str_buffer[0]=='+') ifplus++;
								len-=ifplus;
								Strcpy(variable[morekey-KEY_A].string,num2str_buffer+ifplus,len+1);
								for(len--;len>=0;len--)
									variable[morekey-KEY_A].flags[len]=cur_trig_ans_system|DECSYS;
								variable[morekey-KEY_A].iserror=0;
								}
							variable[morekey-KEY_A].number=main_number;
							drawvariable(morekey-KEY_A);
							}
						showmessagewithstate(1,0,1);
//						showcurrentstring(mainstate,0);
						return 1;
						}
					morekey=0;
					}
				}
		case KEY_exe:
			mainstate=indic.getcursorstate();
///			Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
			if(!makecount()) {ismore=1;main_number=0;Last_answer=0;showerrormessage();ismore=0;return 1;}
			Last_answer=main_number;
			last_trig_ans_system=cur_trig_ans_system;
			shownumonindic(main_number,cur_ans_system,1);
			current_mode=1;
			if(isactlock) recountvariables();
			showsystems();
			showonlymessage(2);
			return 1;
		}
	}
if(current_mode==0 || current_mode==3)
	{
	if(key>=KEY_M1 && key<=KEY_M8)
		{
//							len=convert_number2string(variable[morekey-KEY_A].number,cur_str_system);
		indic.hidemouse_ind();
		indic.deactivate();
		if(!indic.inserttexttocursor(variable[key-KEY_M1+mem1].string,current_flags,variable[key-KEY_M1+mem1].flags))
			{
			Counterror=4;
			showmouse();
			showerrormessage();
			return 1;
			}
		indic.redraw();
		indic.activate();
		showmouse();
//		int len=Strlen(variable[key-KEY_M1+mem1].string);
//		Insstr(current_flags+input_pointer,variable[key-KEY_M1+mem1].flags,current_len-input_pointer,len);
		current_len=indic.gettextlength();
		input_pointer=indic.getcursorposition();
		return 1;
		}
	switch(key)
		{
		case KEY_indicuse:
			input_pointer=indic.getcursorposition();
			if(input_pointer<current_len)
				{
				if(cur_str_system!=((systems)current_flags[input_pointer]&31) || cur_trig_str_system!=((trig_systems)current_flags[input_pointer]&96))
					{
					cur_str_system=(systems)current_flags[input_pointer]&31;
					cur_trig_str_system=(trig_systems)current_flags[input_pointer]&96;
					showsystems();
					}
				}
				else if(input_pointer>0 && (cur_str_system!=((systems)current_flags[current_len-1]&31) || cur_trig_str_system!=((trig_systems)current_flags[current_len-1]&96)))
					{
					cur_str_system=(systems)current_flags[current_len-1]&31;
					cur_trig_str_system=(trig_systems)current_flags[current_len-1]&96;
					showsystems();
					}
			break;
		case KEY_bufleft:
//			indic.movecursorleft(1);
		case KEY_leftcur:
			if(Getkeyboardflags()&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))
				indic.movecursorleft(1);
				else
				indic.movecursorleft();
			input_pointer=indic.getcursorposition();
			if(input_pointer<current_len)
				{
				if(cur_str_system!=((systems)current_flags[input_pointer]&31) || cur_trig_str_system!=((trig_systems)current_flags[input_pointer]&96))
					{
					cur_str_system=(systems)current_flags[input_pointer]&31;
					cur_trig_str_system=(trig_systems)current_flags[input_pointer]&96;
					showsystems();
					}
				}
				else if(input_pointer>0 && (cur_str_system!=((systems)current_flags[current_len-1]&31) || cur_trig_str_system!=((trig_systems)current_flags[current_len-1]&96)))
					{
					cur_str_system=(systems)current_flags[current_len-1]&31;
					cur_trig_str_system=(trig_systems)current_flags[current_len-1]&96;
					showsystems();
					}
			return 1;
		case KEY_bufright:
//			indic.movecursorright(1);
		case KEY_rightcur:
			if(Getkeyboardflags()&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))
				indic.movecursorright(1);
				else
				indic.movecursorright();
			input_pointer=indic.getcursorposition();
			if(input_pointer<current_len)
				{
				if(cur_str_system!=((systems)current_flags[input_pointer]&31) || cur_trig_str_system!=((trig_systems)current_flags[input_pointer]&96))
					{
					cur_str_system=(systems)current_flags[input_pointer]&31;
					cur_trig_str_system=(trig_systems)current_flags[input_pointer]&96;
					showsystems();
					}
				}
				else if(input_pointer>0 && (cur_str_system!=((systems)current_flags[current_len-1]&31) || cur_trig_str_system!=((trig_systems)current_flags[current_len-1]&96)))
					{
					cur_str_system=(systems)current_flags[current_len-1]&31;
					cur_trig_str_system=(trig_systems)current_flags[current_len-1]&96;
					showsystems();
					}
			return 1;
		case KEY_bufhome:
//			indic.movehome(1);
		case KEY_leftend:
			if(Getkeyboardflags()&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))
				indic.movehome(1);
				else
				indic.movehome();
			input_pointer=indic.getcursorposition();
			if(input_pointer<current_len)
				{
				if(cur_str_system!=((systems)current_flags[input_pointer]&31) || cur_trig_str_system!=((trig_systems)current_flags[input_pointer]&96))
					{
					cur_str_system=(systems)current_flags[input_pointer]&31;
					cur_trig_str_system=(trig_systems)current_flags[input_pointer]&96;
					showsystems();
					}
				}
				else if(input_pointer>0 && (cur_str_system!=((systems)current_flags[current_len-1]&31) || cur_trig_str_system!=((trig_systems)current_flags[current_len-1]&96)))
					{
					cur_str_system=(systems)current_flags[current_len-1]&31;
					cur_trig_str_system=(trig_systems)current_flags[current_len-1]&96;
					showsystems();
					}
			return 1;
		case KEY_bufend:
//			indic.moveend(1);
		case KEY_rightend:
			if(Getkeyboardflags()&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))
				indic.moveend(1);
				else
				indic.moveend();
			input_pointer=indic.getcursorposition();
			if(input_pointer==current_len && (cur_str_system!=((systems)current_flags[current_len-1]&31) || cur_trig_str_system!=((trig_systems)current_flags[current_len-1]&96)))
				{
				cur_str_system=(systems)current_flags[current_len-1]&31;
				cur_trig_str_system=(trig_systems)current_flags[current_len-1]&96;
				showsystems();
				}
//			if(input_pointer<current_len)
//				{
//				cur_str_system=(systems)current_flags[input_pointer]&31;
//				cur_trig_str_system=(trig_systems)current_flags[input_pointer]&96;
//				showsystems();
//				}
			return 1;
		case KEY_bufqleft:
//			indic.movepageleft(1);
		case KEY_leftqcur:
			if(Getkeyboardflags()&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))
				indic.movepageleft(1);
				else
				indic.movepageleft();
			input_pointer=indic.getcursorposition();
			if(input_pointer<current_len)
				{
				if(cur_str_system!=((systems)current_flags[input_pointer]&31) || cur_trig_str_system!=((trig_systems)current_flags[input_pointer]&96))
					{
					cur_str_system=(systems)current_flags[input_pointer]&31;
					cur_trig_str_system=(trig_systems)current_flags[input_pointer]&96;
					showsystems();
					}
				}
				else if(input_pointer>0 && (cur_str_system!=((systems)current_flags[current_len-1]&31) || cur_trig_str_system!=((trig_systems)current_flags[current_len-1]&96)))
					{
					cur_str_system=(systems)current_flags[current_len-1]&31;
					cur_trig_str_system=(trig_systems)current_flags[current_len-1]&96;
					showsystems();
					}
			return 1;
		case KEY_bufqright:
//			indic.movepageright(1);
		case KEY_rightqcur:
			if(Getkeyboardflags()&(KBS_LSHIFTDOWN|KBS_RSHIFTDOWN))
				indic.movepageright(1);
				else
				indic.movepageright();
			input_pointer=indic.getcursorposition();
			if(input_pointer<current_len)
				{
				if(cur_str_system!=((systems)current_flags[input_pointer]&31) || cur_trig_str_system!=((trig_systems)current_flags[input_pointer]&96))
					{
					cur_str_system=(systems)current_flags[input_pointer]&31;
					cur_trig_str_system=(trig_systems)current_flags[input_pointer]&96;
					showsystems();
					}
				}
				else if(input_pointer>0 && (cur_str_system!=((systems)current_flags[current_len-1]&31) || cur_trig_str_system!=((trig_systems)current_flags[current_len-1]&96)))
					{
					cur_str_system=(systems)current_flags[current_len-1]&31;
					cur_trig_str_system=(trig_systems)current_flags[current_len-1]&96;
					showsystems();
					}
			return 1;
		case KEY_bufcopydel:
			if(!(morekey=indic.delsymbol(1,current_flags))) return 1;
		case KEY_del:
			if(key==KEY_del) if(!(morekey=indic.delsymbol(0,current_flags))) return 1;
			input_pointer=indic.getcursorposition();
			current_len=indic.gettextlength();
			if(input_pointer<current_len)
				{
				if(cur_str_system!=((systems)current_flags[input_pointer]&31) || cur_trig_str_system!=((trig_systems)current_flags[input_pointer]&96))
					{
					cur_str_system=(systems)current_flags[input_pointer]&31;
					cur_trig_str_system=(trig_systems)current_flags[input_pointer]&96;
					showsystems();
					}
				}
				else if(input_pointer>0 && (cur_str_system!=((systems)current_flags[current_len-1]&31) || cur_trig_str_system!=((trig_systems)current_flags[current_len-1]&96)))
					{
					cur_str_system=(systems)current_flags[current_len-1]&31;
					cur_trig_str_system=(trig_systems)current_flags[current_len-1]&96;
					showsystems();
					}
			return 1;
		case KEY_bs:
			if(!(morekey=indic.backdelsymbol(current_flags))) return 1;
			input_pointer=indic.getcursorposition();
			current_len=indic.gettextlength();
			return 1;
		case KEY_bufcopy:
			indic.changeinputtype(2,current_flags);
			return 1;
		case KEY_bufinsert:
			if(!indic.changeinputtype(1,current_flags))
				{
				Counterror=4;
				ismore=0;
				showerrormessage();
				}
			input_pointer=indic.getcursorposition();
			current_len=indic.gettextlength();
			return 1;
		case KEY_insert:
//			indic.hidemouse_ind();
//			indic.deactivate();
			indic.changeinputtype(0);
//			indic.activate();
//			showmouse();
			isinsert=indic.insertmode;
			return 1;
		case KEY_DEC:
			cur_str_system=DECSYS;
			if(indic.isedit)
				for(i=indic.Lefteditpos;i<indic.Righteditpos;i++)
					current_flags[i]=(unsigned char)cur_str_system|cur_trig_str_system;
				else
				if(input_pointer<STRING_LEN) current_flags[input_pointer]=(unsigned char)cur_str_system|cur_trig_str_system;
			showsystems();
			return 1;
		case KEY_BIN:
			cur_str_system=BINSYS;
			if(indic.isedit)
				for(i=indic.Lefteditpos;i<indic.Righteditpos;i++)
					current_flags[i]=(unsigned char)cur_str_system|cur_trig_str_system;
				else
				if(input_pointer<STRING_LEN) current_flags[input_pointer]=(unsigned char)cur_str_system|cur_trig_str_system;
			showsystems();
			return 1;
		case KEY_OCT:
			cur_str_system=OCTSYS;
				if(indic.isedit)
					 for(i=indic.Lefteditpos;i<indic.Righteditpos;i++)
						current_flags[i]=(unsigned char)cur_str_system|cur_trig_str_system;
					else
				if(input_pointer<STRING_LEN) current_flags[input_pointer]=(unsigned char)cur_str_system|cur_trig_str_system;
			showsystems();
			return 1;
		case KEY_HEX:
			cur_str_system=HEXSYS;
				if(indic.isedit)
					 for(i=indic.Lefteditpos;i<indic.Righteditpos;i++)
						current_flags[i]=(unsigned char)cur_str_system|cur_trig_str_system;
					else
				if(input_pointer<STRING_LEN) current_flags[input_pointer]=(unsigned char)cur_str_system|cur_trig_str_system;
			showsystems();
			return 1;
		case KEY_RAD:
			cur_trig_str_system=RAD;
				if(indic.isedit)
					 for(i=indic.Lefteditpos;i<indic.Righteditpos;i++)
						current_flags[i]=(unsigned char)cur_str_system|cur_trig_str_system;
					else
				if(input_pointer<STRING_LEN) current_flags[input_pointer]=(unsigned char)cur_str_system|cur_trig_str_system;
			showsystems();
			return 1;
		case KEY_DEG:
			cur_trig_str_system=DEG;
			if(indic.isedit)
					 for(i=indic.Lefteditpos;i<indic.Righteditpos;i++)
						current_flags[i]=(unsigned char)cur_str_system|cur_trig_str_system;
					else
				if(input_pointer<STRING_LEN) current_flags[input_pointer]=(unsigned char)cur_str_system|cur_trig_str_system;
			showsystems();
			return 1;
		case KEY_GRD:
			cur_trig_str_system=GRD;
				if(indic.isedit)
					 for(i=indic.Lefteditpos;i<indic.Righteditpos;i++)
						current_flags[i]=(unsigned char)cur_str_system|cur_trig_str_system;
					else
				if(input_pointer<STRING_LEN) current_flags[input_pointer]=(unsigned char)cur_str_system|cur_trig_str_system;
			showsystems();
			return 1;
		case KEY_read_str:
			hidemouse();
//			indic.deactivate();
			last_mes=currentmessage;
			showmessage(message[8]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  —’…ˆŸ  ‘’ŽŠˆ  ˆ‡  ……");//8
//			indic.redraw();
			setstate(4,1);
			showmouse();
			morekey=0;
			while(1)
				{
                nexttimertick=Gettimerticks()&4;if(lasttimertick!=nexttimertick) {lasttimertick=nexttimertick;indic.cursorflash();}
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc)
						{
						showmessagewithstate(last_mes,current_mode);
						return 1;
						}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
						{
						if(morekey>=KEY_M1 && morekey<=KEY_M8) morekey=morekey-KEY_M1+mem1+KEY_A;
						hidemouse();
						indic.deactivate();
						if(!indic.inserttexttocursor(variable[morekey-KEY_A].string,current_flags,variable[morekey-KEY_A].flags))
							{
//							Counterror=4;
							indic.activate();
							showmouse();
//							showerrormessage();
							showonlymessage(26);
							while(!Kbhit() && (nomouse || !ismouseevent())) {nexttimertick=Gettimerticks()&4;if(lasttimertick!=nexttimertick) {lasttimertick=nexttimertick;indic.cursorflash();}}
							showmessagewithstate(last_mes,current_mode);
							return 1;
							}
						indic.redraw();
						indic.activate();
						current_len=indic.gettextlength();
						input_pointer=indic.getcursorposition();
						showmessage(message[last_mes]);
						setstate(current_mode);
						showmouse();
						return 1;
						}
					morekey=0;
					}
				}
		case KEY_read_num:
			hidemouse();
//			indic.deactivate();
			last_mes=currentmessage;
			showmessage(message[9]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  —’…ˆŸ  —ˆ‘‹€  ˆ‡  ……");//9
//			indic.redraw();
			setstate(4,1);
			showmouse();
			morekey=0;
			while(1)
				{
                nexttimertick=Gettimerticks()&4;if(lasttimertick!=nexttimertick) {lasttimertick=nexttimertick;indic.cursorflash();}
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc)
						{
						showmessagewithstate(last_mes,current_mode);
						return 1;
						}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
						{
						if(morekey>=KEY_M1 && morekey<=KEY_M8) morekey=morekey-KEY_M1+mem1+KEY_A;
						hidemouse();
						indic.deactivate();
						int len;
						int ifplus=0;
						len=convert_number2string(variable[morekey-KEY_A].number,cur_str_system,2);
						if(num2str_buffer[0]=='+') ifplus++;
						len-=ifplus;
						if(!indic.inserttexttocursor(num2str_buffer+ifplus,current_flags,0))
							{
							indic.activate();
							showmouse();
	//							showerrormessage();
							showonlymessage(26);
							while(!Kbhit() && (nomouse || !ismouseevent())) {nexttimertick=Gettimerticks()&4;if(lasttimertick!=nexttimertick) {lasttimertick=nexttimertick;indic.cursorflash();}}
							showmessagewithstate(last_mes,current_mode);
							return 1;
							}
//							Strcpyr(current_flags+current_len+len,current_flags+current_len,current_len-input_pointer);
						for(int i=0;i<len;i++)
							current_flags[input_pointer+i]=cur_trig_str_system|cur_str_system;
//							current_len+=len;
//							input_pointer+=len;
//						showcurrentstring();
						current_len=indic.gettextlength();
						input_pointer=indic.getcursorposition();
						indic.redraw();
						indic.activate();
						showmessage(message[last_mes]);
						setstate(current_mode);
						showmouse();
						return 1;
						}
					morekey=0;
					}
				}
		case KEY_stay:
			if(!indic.isedit) return 1;
			indic.hidemouse_ind();
			indic.deactivate();
			Strcpy(current_string,current_string+indic.Lefteditpos,indic.Righteditpos-indic.Lefteditpos);
			Strcpy(current_flags,current_flags+indic.Lefteditpos,indic.Righteditpos-indic.Lefteditpos);
			current_string[indic.Righteditpos-indic.Lefteditpos]='\0';
			indic.settext(current_string);
			indic.activate();
			indic.moveend();
			showmouse();
			current_len=indic.gettextlength();
			input_pointer=indic.getcursorposition();
//			if(BUT_clear_stay.isactive2()) {BUT_clear_stay.hidemouse_but();BUT_clear_stay.deactivate(2);showmouse();}
			return 1;
		}
	}
if(current_mode==1)
	{
	switch(key)
		{
		case KEY_leftcur:
			indic.movecursorleft();
			break;
		case KEY_rightcur:
			indic.movecursorright();
			break;
		case KEY_leftend:
			indic.movehome();
			break;
		case KEY_rightend:
			indic.moveend();
			break;
		case KEY_leftqcur:
			indic.movepageleft();
			break;
		case KEY_rightqcur:
			indic.movepageright();
			break;
		case KEY_stay:
			{
			Strcpy(main_string,indic.gettext(),indic.gettextlength()+1);
			current_len=indic.gettextlength();
			for(int i=0;i<current_len;i++)
				main_flags[i]=cur_trig_ans_system|cur_ans_system;
			cur_trig_str_system=cur_trig_ans_system;
			cur_str_system=cur_ans_system;
			hidemouse();
			indic.deactivate();
			indic.settext(main_string);
			indic.moveend();
//			hidemouse();
			input_pointer=indic.getcursorposition();
			if(!isinsert && indic.insertmode)
				indic.changeinputtype(0);
			indic.activate();
			current_mode=0;
			showmessage(message[1]);
			setstate(0);
			showmouse();
			return 1;
			}
		case KEY_DEC:
			cur_ans_system=DECSYS;
			shownumonindic(main_number,cur_ans_system);
			showsystems();
			break;
		case KEY_BIN:
			cur_ans_system=BINSYS;
			shownumonindic(main_number,cur_ans_system);
			showsystems();
			break;
		case KEY_OCT:
			cur_ans_system=OCTSYS;
			shownumonindic(main_number,cur_ans_system);
			showsystems();
			break;
		case KEY_HEX:
			cur_ans_system=HEXSYS;
			shownumonindic(main_number,cur_ans_system);
			showsystems();
			break;
		case KEY_RAD:
			if(cur_trig_ans_system!=RAD)
				{
				long double tmp;
				if(last_trig_ans_system==DEG)
					tmp=FPU_mul(FPU_div(Last_answer,180.0),FPUloadpi());
					else if(last_trig_ans_system==GRD)
						tmp=FPU_mul(FPU_div(Last_answer,200.0),FPUloadpi());
						else tmp=Last_answer;
				if(!FPUerror)
					{
					main_number=tmp;
					shownumonindic(main_number,cur_ans_system);
					}
					else
					{
					FPUerror=0;
					return 1;
					}
				}
				else break;
		case KEY_altRAD:
			if(key==KEY_altRAD)
				{
				Last_answer=main_number;
				last_trig_ans_system=RAD;
				}
			cur_trig_ans_system=RAD;
			showsystems();
			break;
		case KEY_DEG:
			if(cur_trig_ans_system!=DEG)
				{
				long double tmp;
				if(last_trig_ans_system==RAD)
					tmp=FPU_mul(FPU_div(Last_answer,FPUloadpi()),180.0);
					else if(last_trig_ans_system==GRD)
					tmp=FPU_mul(Last_answer,0.9);
						else tmp=Last_answer;
				if(!FPUerror)
					{
					main_number=tmp;
					shownumonindic(main_number,cur_ans_system);
					}
					else
					{
					FPUerror=0;
					return 1;
					}
				}
				else break;
		case KEY_altDEG:
			if(key==KEY_altDEG)
				{
				Last_answer=main_number;
				last_trig_ans_system=DEG;
				}
			cur_trig_ans_system=DEG;
			showsystems();
			break;
		case KEY_GRD:
			if(cur_trig_ans_system!=GRD)
				{
				long double tmp;
				if(last_trig_ans_system==RAD)
					tmp=FPU_mul(FPU_div(Last_answer,FPUloadpi()),200.0);
					else if(last_trig_ans_system==DEG)
						tmp=FPU_div(Last_answer,0.9);
						else tmp=Last_answer;
				if(!FPUerror)
					{
					main_number=tmp;
					shownumonindic(main_number,cur_ans_system);
					}
					else
					{
					FPUerror=0;
					return 1;
					}
				}
				else break;
		case KEY_altGRD:
			if(key==KEY_altGRD)
				{
				Last_answer=main_number;
				last_trig_ans_system=GRD;
				}
			cur_trig_ans_system=GRD;
			showsystems();
			break;
		case KEY_savenumto:
			hidemouse();
			indic.deactivate();
			showmessage(message[10]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  ‡€ˆ‘ˆ  —ˆ‘‹€  ‚  ……");//10
//			indic.redraw();
			setstate(4);
			showmouse();
			morekey=0;
			while(1)
				{
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc) {showmessagewithstate(2,1,1);return 1;}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8) || morekey==KEY_MUL_LEN)
						{
						if(morekey==KEY_MUL_LEN)
							{
							if(main_number>4294967295.0) multitude_len=4294967295ul;
								else if(main_number<0) multitude_len=real_multitude_len;
										else
										multitude_len=(unsigned long)main_number;
							if(multitude_len<real_multitude_len)
								real_multitude_len=(int)multitude_len;
							drawmulnum();
							}
							else
							{
							if(morekey>=KEY_M1 && morekey<=KEY_M8) morekey=morekey-KEY_M1+mem1+KEY_A;
							int ifplus=0;
							int len=convert_number2string(main_number,DECSYS,2);
							if(num2str_buffer[0]=='+') ifplus++;
							len-=ifplus;
							Strcpy(variable[morekey-KEY_A].string,num2str_buffer+ifplus,len+1);
							for(len--;len>=0;len--)
								variable[morekey-KEY_A].flags[len]=cur_trig_ans_system|DECSYS;
							variable[morekey-KEY_A].isstring=0;
							variable[morekey-KEY_A].number=main_number;
							variable[morekey-KEY_A].iserror=0;
							if(morekey-KEY_A<=mem8) drawvariable(morekey-KEY_A);
							}
						showmessagewithstate(2,1,1);
//						shownumonindic(main_number,cur_ans_system,1);
						return 1;
						}
					morekey=0;
					}
				}
		case KEY_Mn_plus:
			hidemouse();
			indic.deactivate();
			showmessage(message[11]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  ˆ€‚‹…ˆŸ  Š  …‰");//11
//			indic.redraw();
			setstate(4,1);
			showmouse();
			morekey=0;
			while(1)
				{
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc) {showmessagewithstate(2,1,1);return 1;}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
						{
						key=morekey-KEY_A+KEY_M1_plus-mem1;
						if(morekey>=KEY_M1 && morekey<=KEY_M8) key=key-KEY_M1+mem1+KEY_A;
						showmessagewithstate(2,1,1);
//						shownumonindic(main_number,cur_ans_system,1);
						break;
						}
					morekey=0;
					}
				}
		case KEY_M1_plus:
			{
			long double temp=variable[key-KEY_M1_plus+mem1].number;
			temp=FPU_add(temp,*current_number);
			if(FPUerror) {ismore=0;showerrormessage();return 1;}
			if(!variable[key-KEY_M1_plus+mem1].isstring)
				{
				int ifplus=0;
				int len=convert_number2string(temp,DECSYS,2);
				if(num2str_buffer[0]=='+') ifplus++;
				len-=ifplus;
				Strcpy(variable[key-KEY_M1_plus+mem1].string,num2str_buffer+ifplus,len+1);
				for(len--;len>=0;len--)
					variable[key-KEY_M1_plus+mem1].flags[len]=cur_trig_ans_system|DECSYS;
				}
			variable[key-KEY_M1_plus+mem1].number=temp;
			drawvariable(key-KEY_M1_plus+mem1);
			return 1;
			}
		case KEY_Mn_minus:
			hidemouse();
			indic.deactivate();
			showmessage(message[12]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  ‚›—ˆ’€ˆŸ  ˆ‡  ……");//12
//			indic.redraw();
			setstate(4,1);
			showmouse();
			morekey=0;
			while(1)
				{
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc) {showmessagewithstate(2,1,1);return 1;}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
						{
						key=morekey-KEY_A+KEY_M1_minus-mem1;
						if(morekey>=KEY_M1 && morekey<=KEY_M8) key=key-KEY_M1+mem1+KEY_A;
						showmessagewithstate(2,1,1);
//						shownumonindic(main_number,cur_ans_system,1);
						break;
						}
					morekey=0;
					}
				}
		case KEY_M1_minus:
			{
			long double temp=variable[key-KEY_M1_minus+mem1].number;
			temp=FPU_sub(temp,*current_number);
			if(FPUerror) {ismore=0;showerrormessage();return 1;}
			if(!variable[key-KEY_M1_minus+mem1].isstring)
				{
				int ifplus=0;
				int len=convert_number2string(temp,DECSYS,2);
				if(num2str_buffer[0]=='+') ifplus++;
				len-=ifplus;
				Strcpy(variable[key-KEY_M1_minus+mem1].string,num2str_buffer+ifplus,len+1);
				for(len--;len>=0;len--)
					variable[key-KEY_M1_minus+mem1].flags[len]=cur_trig_ans_system|DECSYS;
				}
			variable[key-KEY_M1_minus+mem1].number=temp;
			drawvariable(key-KEY_M1_minus+mem1);
			return 1;
			}
		case KEY_Mn_mul:
			hidemouse();
			indic.deactivate();
			showmessage(message[13]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  “ŒŽ†…ˆŸ  ……");//13
//			indic.redraw();
			setstate(4,1);
			showmouse();
			morekey=0;
			while(1)
				{
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc) {showmessagewithstate(2,1,1);return 1;}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
						{
						key=morekey-KEY_A+KEY_M1_mul-mem1;
						if(morekey>=KEY_M1 && morekey<=KEY_M8) key=key-KEY_M1+mem1+KEY_A;
//						shownumonindic(main_number,cur_ans_system,1);
						showmessagewithstate(2,1,1);
						break;
						}
					morekey=0;
					}
				}
		case KEY_M1_mul:
			{
			long double temp=variable[key-KEY_M1_mul+mem1].number;
			temp=FPU_mul(temp,*current_number);
			if(FPUerror) {ismore=0;showerrormessage();return 1;}
			if(!variable[key-KEY_M1_mul+mem1].isstring)
				{
				int ifplus=0;
				int len=convert_number2string(temp,DECSYS,2);
				if(num2str_buffer[0]=='+') ifplus++;
				len-=ifplus;
				Strcpy(variable[key-KEY_M1_mul+mem1].string,num2str_buffer+ifplus,len+1);
				for(len--;len>=0;len--)
					variable[key-KEY_M1_mul+mem1].flags[len]=cur_trig_ans_system|DECSYS;
				}
			variable[key-KEY_M1_mul+mem1].number=temp;
			drawvariable(key-KEY_M1_mul+mem1);
			return 1;
			}
		case KEY_Mn_div:
			hidemouse();
			indic.deactivate();
			showmessage(message[14]);
//			indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  „…‹…ˆŸ  ……");//14
//			indic.redraw();
			setstate(4,1);
			showmouse();
			morekey=0;
			while(1)
				{
				if(Kbhit())
					morekey=receivekeyevent();
				if(!nomouse && ismouseevent())
					morekey=receivemouseevent();
				if(morekey)
					{
					if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
					if(morekey==KEY_break) return 1;
					if(morekey==KEY_esc) {showmessagewithstate(2,1,1);return 1;}
					if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
						{
						key=morekey-KEY_A+KEY_M1_div-mem1;
						if(morekey>=KEY_M1 && morekey<=KEY_M8) key=key-KEY_M1+mem1+KEY_A;
						showmessagewithstate(2,1,1);
//						shownumonindic(main_number,cur_ans_system,1);
						break;
						}
					morekey=0;
					}
				}
		case KEY_M1_div:
			{
			long double temp=variable[key-KEY_M1_div+mem1].number;
			temp=FPU_div(temp,*current_number);
			if(FPUerror) {ismore=0;showerrormessage();return 1;}
			if(!variable[key-KEY_M1_div+mem1].isstring)
				{
				int ifplus=0;
				int len=convert_number2string(temp,DECSYS,2);
				if(num2str_buffer[0]=='+') ifplus++;
				len-=ifplus;
				Strcpy(variable[key-KEY_M1_div+mem1].string,num2str_buffer+ifplus,len+1);
				for(len--;len>=0;len--)
					variable[key-KEY_M1_div+mem1].flags[len]=cur_trig_ans_system|DECSYS;
				}
			variable[key-KEY_M1_div+mem1].number=temp;
			drawvariable(key-KEY_M1_div+mem1);
			return 1;
			}
		}
	}
if(current_mode<4)
	{
	if(key==KEY_clear)
		{
		current_len=0;
		input_pointer=0;
		current_string[0]='\0';
		hidemouse();
		if(current_mode==1)
			{
			current_mode=0;
			showonlymessage(1);
			showsystems();
//			hidemouse();
			}
			else if(current_mode==2)
					{
					current_mode=last_mode;
//					hidemouse();
					showmessage(message[last_mes]);
					}
//					else hidemouse();
		indic.deactivate();
		indic.settext(current_string);
		indic.redraw();
		indic.activate();
		setstate(current_mode);
		showmouse();
		return 1;
		}
	if(current_mode!=2 && key==KEY_multitude)
		{
		if(!drawmultitude()) return 0;
		showonlymessage(currentmessage);
		return 1;
		}
	}
if(current_mode==2 || current_mode==1)
	{
	if(key==KEY_exe || (key==KEY_esc && current_mode==2))
		{
		hidemouse();
		indic.deactivate();
		indic.settext(current_string);
		if(current_mode==1 || (current_mode==2 && last_mode==1))
			{
			current_mode=0;
			Last_answer=main_number;
			indic.restorecursorstate(mainstate);
			showmessage(message[1]);
			}
			else
			{
			current_mode=last_mode;
			showmessage(message[last_mes]);
			indic.setcursorposition(input_pointer);
			}
		indic.redraw();
		if(isinsert ^ indic.insertmode) indic.changeinputtype(0);
		indic.activate();
		setstate(current_mode);
		if(current_mode==0) showsystems();
		showmouse();
		return 1;
		}
	if(key==KEY_more)
		if(BUT_more.isactive1())
			{
			Last_answer=main_number;
			if(current_mode==2 && isactlock) recountvariables();
			if(!makecount()) {current_mode=0;currentmessage=1;ismore=1;main_number=0;Last_answer=0;showerrormessage();ismore=0;return 1;}
			shownumonindic(main_number,cur_ans_system);
			if(isactlock) recountvariables();
			if(current_mode==2) {hidemouse();setstate(1);showmouse();}
			current_mode=1;
			showonlymessage(2);
			return 1;
			}
	}
if(current_mode<2)
	{
	if(key==KEY_fix)
		{
//		mainstate=indic.getcursorstate();
///		Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
		int work,num=0,*ptr,mesptr,sys=cur_str_system;
		if(current_mode==1)
			sys=cur_ans_system;
		morekey=0;
		hidemouse();
		indic.deactivate();
		last_mes=currentmessage;
		mesptr=Strlen(message[6]);
		Strcpy(num2str_buffer,message[6],mesptr);//6
//		showmessage(message[6]);
		if(sys==BINSYS)
			{
			Strcpy(num2str_buffer+mesptr,"¤¢®¨ç­®© § ¯¨á¨ ç¨á«  (1-64): ",31);//6
			mesptr+=30;
			work=64;
			ptr=&fix_num2;
			}
			else
			if(sys==DECSYS)
				{
				Strcpy(num2str_buffer+mesptr,"¤¥áïâ¨ç­®© § ¯¨á¨ ç¨á«  (1-18): ",33);//6
				mesptr+=32;
				work=18;
				ptr=&fix_num10;
				}
				else
				if(sys==OCTSYS)
					{
					Strcpy(num2str_buffer+mesptr,"¢®áì¬¥à¨ç­®© § ¯¨á¨ ç¨á«  (1-22): ",35);//6
					mesptr+=34;
					work=22;
					ptr=&fix_num8;
					}
					else
					{
					Strcpy(num2str_buffer+mesptr,"è¥áâ­ ¤æ â¥à¨ç­®© § ¯¨á¨ ç¨á«  (1-17): ",40);//6
					mesptr+=39;
					work=17;
					ptr=&fix_num16;
					}
		showmessage(num2str_buffer);
//		indic.settext(num2str_buffer);
//		indic.redraw();
		setstate(6);
		showmouse();
//		indic.moveend();
		while(1)
			{
			if(Kbhit())
				morekey=receivekeyevent();
			if(!nomouse && ismouseevent())
				morekey=receivemouseevent();
			if(morekey)
				{
				if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
				if(morekey==KEY_break) return 1;
				if(morekey==KEY_esc)
					{
//					showcurrentstring(mainstate,0);
					showmessagewithstate(last_mes,current_mode,1);
					return 1;
					}
				if(morekey>=KEY_0 && morekey<=KEY_9)
					{
					if(num>0 || morekey!=KEY_0)
						{
						num=num*10+morekey-KEY_0;
						num2str_buffer[mesptr++]=morekey;
						num2str_buffer[mesptr]='\0';
						hidemouse();
						showmessage(num2str_buffer);
						showmouse();
//						indic.takesymbol(morekey,0,0);
						}
					if(num>=10)
						{
						if(num>work) num=work;
						*ptr=num;
// 						showcurrentstring(mainstate,0);
						showmessagewithstate(last_mes,current_mode,1);
//						showonlymessage(1);
						if(current_mode==1)
							shownumonindic(main_number,cur_ans_system,1);
						showscifix();
						return 1;
						}
					}
				if(morekey==KEY_exe)
					{
					if(num!=0) *ptr=num;
//					showcurrentstring(mainstate,0);
					showmessagewithstate(last_mes,current_mode,1);
//					showonlymessage(1);
					if(current_mode==1)
						shownumonindic(main_number,cur_ans_system,1);
					showscifix();
					return 1;
					}
				}
			morekey=0;
			}
		}
	if(key==KEY_sci)
		{
//		mainstate=indic.getcursorstate();
///		Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
		int work,num=0,*ptr,mesptr,sys=cur_str_system;
		if(current_mode==1)
			sys=cur_ans_system;
		morekey=0;
		hidemouse();
		indic.deactivate();
		last_mes=currentmessage;
		mesptr=Strlen(message[7]);
		Strcpy(num2str_buffer,message[7],mesptr);//7
//		showmessage(message[6]);
		if(sys==BINSYS)
			{
			Strcpy(num2str_buffer+mesptr,"¤¢®¨ç­®© § ¯¨á¨ ç¨á«  (0-FIX): ",32);//6
			mesptr+=31;
			work=fix_num2;
			ptr=&sci_num2;
			}
			else
			if(sys==DECSYS)
				{
				Strcpy(num2str_buffer+mesptr,"¤¥áïâ¨ç­®© § ¯¨á¨ ç¨á«  (0-FIX): ",34);//6
				mesptr+=33;
				work=fix_num10;
				ptr=&sci_num10;
				}
				else
				if(sys==OCTSYS)
					{
					Strcpy(num2str_buffer+mesptr,"¢®áì¬¥à¨ç­®© § ¯¨á¨ ç¨á«  (0-FIX): ",36);//6
					mesptr+=35;
					work=fix_num8;
					ptr=&sci_num8;
					}
					else
					{
					Strcpy(num2str_buffer+mesptr,"è¥áâ­ ¤æ â¥à¨ç­®© § ¯¨á¨ ç¨á«  (0-FIX): ",41);//6
					mesptr+=40;
					work=fix_num16;
					ptr=&sci_num16;
					}
		showmessage(num2str_buffer);
//		indic.settext(num2str_buffer);
//		indic.redraw();
		setstate(6);
		showmouse();
//		indic.moveend();
		while(1)
			{
			if(Kbhit())
				morekey=receivekeyevent();
			if(!nomouse && ismouseevent())
				morekey=receivemouseevent();
			if(morekey)
				{
				if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
				if(morekey==KEY_break) return 1;
				if(morekey==KEY_esc)
					{
//					showcurrentstring(mainstate,0);
					showmessagewithstate(last_mes,current_mode,1);
					return 1;
					}
				if(morekey>=KEY_0 && morekey<=KEY_9)
					{
					if(num>0 || morekey!=KEY_0)
						{
						num=num*10+morekey-KEY_0;
						num2str_buffer[mesptr++]=morekey;
						num2str_buffer[mesptr]='\0';
						hidemouse();
						showmessage(num2str_buffer);
						showmouse();
//						indic.takesymbol(morekey,0,0);
						}
					if(num>=10)
						{
						if(num>work) num=work;
						*ptr=num;
// 						showcurrentstring(mainstate,0);
						showmessagewithstate(last_mes,current_mode,1);
//						showonlymessage(1);
						if(current_mode==1)
							shownumonindic(main_number,cur_ans_system,1);
						showscifix();
						return 1;
						}
					}
				if(morekey==KEY_exe)
					{
					if(num>work) num=work;
					*ptr=num;
//					showcurrentstring(mainstate,0);
					showmessagewithstate(last_mes,current_mode,1);
//					showonlymessage(1);
					if(current_mode==1)
						shownumonindic(main_number,cur_ans_system,1);
					showscifix();
					return 1;
					}
				}
			morekey=0;
			}
		}
	if(key==KEY_swap)
		{
		hidemouse();
//		if(current_mode==0)
//			{
///			Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
//			mainstate=indic.getcursorstate();
//			}
		indic.deactivate();
		last_mes=currentmessage;
		int mesptr=Strlen(message[15]);
		Strcpy(num2str_buffer,message[15],mesptr+1);
		showmessage(num2str_buffer);
//		indic.settext("‚‚…„ˆ’…  ……Œ…›…, ŠŽ’Ž›…  •Ž’ˆ’…  ŽŒ…Ÿ’œ");//15
//		indic.redraw();
		setstate(4,1);
		showmouse();
		int morekey2=0;
		morekey=0;
		while(1)
			{
			if(Kbhit())
				morekey=receivekeyevent();
			if(!nomouse && ismouseevent())
				morekey=receivemouseevent();
			if(morekey)
				{
				if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
				if(morekey==KEY_break) return 1;
				if(morekey==KEY_esc)
					{
//					if(current_mode==0)
//						showcurrentstring(mainstate,0);
//						else
//						shownumonindic(main_number,cur_ans_system,1);
					showmessagewithstate(last_mes,current_mode,1);
					return 1;
					}
				if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
					{
					if(morekey>=KEY_M1 && morekey<=KEY_M8) morekey=morekey-KEY_M1+mem1+KEY_A;
					if(morekey2==0)
						{
						morekey2=morekey;
						if(morekey2<=KEY_Z)
							{
							num2str_buffer[mesptr]=morekey2;
							Strcpy(num2str_buffer+mesptr+1,message[27],3);
							}
							else
							{
							num2str_buffer[mesptr]='M';
							num2str_buffer[mesptr+1]=morekey2-mem1-KEY_A+'1';
							Strcpy(num2str_buffer+mesptr+2,message[27],3);
							}
						hidemouse();
//						if(!nomouse)
//							SETMOUSEEXLUSIONAREA(2,161,637,176);
						showmessage(num2str_buffer);
						showmouse();
						}
						else
						{
						char *ptr=variable[morekey-KEY_A].string;
						variable[morekey-KEY_A].string=variable[morekey2-KEY_A].string;
						variable[morekey2-KEY_A].string=ptr;
						ptr=variable[morekey-KEY_A].flags;
						variable[morekey-KEY_A].flags=variable[morekey2-KEY_A].flags;
						variable[morekey2-KEY_A].flags=ptr;
						long double temp=variable[morekey-KEY_A].number;
						variable[morekey-KEY_A].number=variable[morekey2-KEY_A].number;
						variable[morekey2-KEY_A].number=temp;
						int tmp=variable[morekey-KEY_A].isstring;
						variable[morekey-KEY_A].isstring=variable[morekey2-KEY_A].isstring;
						variable[morekey2-KEY_A].isstring=tmp;
						tmp=variable[morekey-KEY_A].iserror;
						variable[morekey-KEY_A].iserror=variable[morekey2-KEY_A].iserror;
						variable[morekey2-KEY_A].iserror=tmp;
						drawvariable(morekey-KEY_A);
						drawvariable(morekey2-KEY_A);
//						if(current_mode==0)
//							showcurrentstring(mainstate,0);
//							else
//							shownumonindic(main_number,cur_ans_system,1);
						showmessagewithstate(last_mes,current_mode,1);
						return 1;
						}
					}
				morekey=0;
				}
			}
		}
	if(key==KEY_toggle)
		{
		hidemouse();
//		if(current_mode==0)
//			{
///			Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
//			mainstate=indic.getcursorstate();
//			}
		indic.deactivate();
		last_mes=currentmessage;
		showmessage(message[16]);
//		indic.settext("‚‚…„ˆ’…  ……Œ…“ž, ŠŽ’Ž“ž  •Ž’ˆ’…  ……Š‹ž—ˆ’œ");//16
//		indic.redraw();
		setstate(4,1);
		showmouse();
		morekey=0;
		while(1)
			{
			if(Kbhit())
				morekey=receivekeyevent();
			if(!nomouse && ismouseevent())
				morekey=receivemouseevent();
			if(morekey)
				{
				if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
				if(morekey==KEY_break) return 1;
				if(morekey==KEY_esc)
					{
//					if(current_mode==0)
//						showcurrentstring(mainstate,0);
//						else
//						shownumonindic(main_number,cur_ans_system,1);
					showmessagewithstate(last_mes,current_mode,1);
					return 1;
					}
				if((morekey>=KEY_A && morekey<=KEY_Z) || (morekey>=KEY_M1 && morekey<=KEY_M8))
					{
					if(morekey>=KEY_M1 && morekey<=KEY_M8) morekey=morekey-KEY_M1+mem1+KEY_A;
					variable[morekey-KEY_A].ison^=1;
					drawvariable(morekey-KEY_A);
//					if(current_mode==0) showcurrentstring(mainstate,0);
//						else shownumonindic(main_number,cur_ans_system,1);
					showmessagewithstate(last_mes,current_mode,1);
					return 1;
					}
				morekey=0;
				}
			}
		}
	if(key==KEY_add_var_to_mul)
		{
		hidemouse();
//		if(current_mode==0)
//			{
///			Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
//			mainstate=indic.getcursorstate();
//			}
		indic.deactivate();
		last_mes=currentmessage;
		showmessage(message[17]);
//		indic.settext("‚‚…„ˆ’…  ……Œ…“ž  „‹Ÿ  „Ž€‚‹…ˆŸ  ‚  ŒŽ†…‘’‚Ž");//17
//		indic.redraw();
		setstate(5);
		showmouse();
		morekey=0;
		while(1)
			{
			if(Kbhit())
				morekey=receivekeyevent();
			if(!nomouse && ismouseevent())
				morekey=receivemouseevent();
			if(morekey)
				{
				if(morekey==KEY_exit) {if_exit();morekey=0;continue;}
				if(morekey==KEY_break) return 1;
				if(morekey==KEY_esc)
					{
//					if(current_mode==0)
//						showcurrentstring(mainstate,0);
//						else
//						shownumonindic(main_number,cur_ans_system,1);
					showmessagewithstate(last_mes,current_mode,1);
					return 1;
					}
				if(morekey>=KEY_A && morekey<=KEY_Z)
					{
					if(real_multitude_len<MULTITUDE_SIZE)
						{
						multitude[real_multitude_len].isvar=1;
						multitude[real_multitude_len].var=morekey-KEY_A;
						real_multitude_len++;
						multitude_len++;
						drawmulnum();
//						if(current_mode==0) showcurrentstring(mainstate,0);
//							else shownumonindic(main_number,cur_ans_system,1);
						showmessagewithstate(last_mes,current_mode,1);
						return 1;
						}
					Counterror=5;
					currentmessage=last_mes;
					showerrormessage();
					return 1;
					}
				morekey=0;
				}
			}
		}
	if(key==KEY_add_to_mul)
		{
		if(current_mode!=1)
			{
//			mainstate=indic.getcursorstate();
///			Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
			makecount();
			if(Counterror || FPUerror) {showerrormessage();return 1;}
			}
		if(real_multitude_len<MULTITUDE_SIZE)
			{
			multitude[real_multitude_len].isvar=0;
			multitude[real_multitude_len].number=*current_number;
			real_multitude_len++;
			multitude_len++;
			drawmulnum();
			}
			else
			{
			Counterror=5;
			showerrormessage();
			}
		return 1;
		}
	if(key==KEY_graph)
		{
		if(current_mode==0)
			{
///			Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
			mainstate=indic.getcursorstate();
			}
		prev_mode=current_mode;
		if(variable['V'-'A'].ison && !variable['W'-'A'].ison)
			{
			hidemouse();
			indic.deactivate();
			current_string=firstlowlimit_str;
			current_flags=firstlowlimit_flag;
			current_number=&firstlowlimit;
			graph_mode=0;
			showmessage(message[18]);
//			indic.settext("‚‚…„ˆ’…  ˆ†ˆ‰  …„…‹  „‹Ÿ  W");//18
			}
			else
			if(!variable['V'-'A'].ison && variable['W'-'A'].ison)
				{
				hidemouse();
				indic.deactivate();
				current_string=firstlowlimit_str;
				current_flags=firstlowlimit_flag;
				current_number=&firstlowlimit;
				graph_mode=0;
				showmessage(message[19]);
//				indic.settext("‚‚…„ˆ’…  ˆ†ˆ‰  …„…‹  „‹Ÿ  V");//19
				}
				else
				if(variable['X'-'A'].ison && !variable['Y'-'A'].ison)
					{
					hidemouse();
					indic.deactivate();
					current_string=secondlowlimit_str;
					current_flags=secondlowlimit_flag;
					current_number=&secondlowlimit;
					graph_mode=2;
					showmessage(message[20]);
//					indic.settext("‚‚…„ˆ’…  ˆ†ˆ‰  …„…‹  „‹Ÿ  Y");//20
					}
					else
					if(!variable['X'-'A'].ison && variable['Y'-'A'].ison)
						{
						hidemouse();
						indic.deactivate();
						current_string=secondlowlimit_str;
						current_flags=secondlowlimit_flag;
						current_number=&secondlowlimit;
						graph_mode=2;
						showmessage(message[21]);
//						indic.settext("‚‚…„ˆ’…  ˆ†ˆ‰  …„…‹  „‹Ÿ  X");//21
						}
						else
						if(!variable['X'-'A'].ison && !variable['V'-'A'].ison)
							{
							Counterror=7;
							showerrormessage();
							return 1;
							}
							else
//							if(variable['X'-'A'].ison || variable['V'-'A'].ison)
							{
//							hidemouse();
							if(!graphdraw()) return 0;
							showonlymessage(currentmessage);
//							setstate(current_mode);
							return 1;
							}
//		indic.redraw();
		setstate(3);
//		showmouse();
		current_mode=3;
		current_len=Strlen(current_string);
		last_input_pointer=input_pointer;
		indic.settext(current_string);
		indic.restorecursorstate(graphstate[graph_mode]);
//		indic.hidemouse_ind();
		indic.redraw();
		indic.activate();
		input_pointer=0;
		showmouse();
//		key=morekey;
//		goto begconv;
		return 1;
		}
	}
if(current_mode==3)
	{
	if(key==KEY_esc)
		{
		current_string=main_string;
		current_flags=main_flags;
		current_number=&main_number;
		current_len=Strlen(current_string);
		current_mode=prev_mode;
		input_pointer=last_input_pointer;
		if(current_mode==0) showcurrentstring(mainstate,0);
			else shownumonindic(main_number,cur_ans_system,1);
		if(current_mode==0) showonlymessage(1);
			else showonlymessage(2);
		return 1;
		}
	if(key==KEY_exe)
		{
		graphstate[graph_mode]=indic.getcursorstate();
///		Strcpy(current_string,indic.gettext(),indic.gettextlength()+1);
		if(!makecount()) {showerrormessage();return 1;}
		if(graph_mode==0)
			{
			indic.hidemouse_ind();
			indic.deactivate();
			current_string=firsthighlimit_str;
			current_flags=firsthighlimit_flag;
			current_number=&firsthighlimit;
			graph_mode=1;
			if(variable['V'-'A'].ison && !variable['W'-'A'].ison)
				showmessage(message[22]);
//				indic.settext("‚‚…„ˆ’…  ‚…•ˆ‰  …„…‹  „‹Ÿ  W");//22
				else
				showmessage(message[23]);
//				indic.settext("‚‚…„ˆ’…  ‚…•ˆ‰  …„…‹  „‹Ÿ  V");//23
//			indic.redraw();
			}
			else if(graph_mode==1)
			{
			if(!(variable['X'-'A'].ison ^ variable['Y'-'A'].ison))
				{
				if(!graphdraw()) return 0;
				if(current_mode==0) showonlymessage(1);
					else showonlymessage(2);
				return 1;
				}
			indic.hidemouse_ind();
			indic.deactivate();
			current_string=secondlowlimit_str;
			current_flags=secondlowlimit_flag;
			current_number=&secondlowlimit;
			graph_mode=2;
			if(variable['X'-'A'].ison && !variable['Y'-'A'].ison)
				showmessage(message[20]);
//				indic.settext("‚‚…„ˆ’…  ˆ†ˆ‰  …„…‹  „‹Ÿ  Y");//20
				else
				showmessage(message[21]);
//				indic.settext("‚‚…„ˆ’…  ˆ†ˆ‰  …„…‹  „‹Ÿ  X");//21
//			indic.redraw();
			}
			else if(graph_mode==2)
			{
			indic.hidemouse_ind();
			indic.deactivate();
			current_string=secondhighlimit_str;
			current_flags=secondhighlimit_flag;
			current_number=&secondhighlimit;
			graph_mode=3;
			if(variable['X'-'A'].ison && !variable['Y'-'A'].ison)
				showmessage(message[24]);
//				indic.settext("‚‚…„ˆ’…  ‚…•ˆ‰  …„…‹  „‹Ÿ  Y");//24
				else
				showmessage(message[25]);
//				indic.settext("‚‚…„ˆ’…  ‚…•ˆ‰  …„…‹  „‹Ÿ  X");//25
//			indic.redraw();
			}
			else if(graph_mode==3)
					{
					if(!graphdraw()) return 0;
					if(current_mode==0) showonlymessage(1);
						else showonlymessage(2);
					return 1;
					}
		current_len=Strlen(current_string);
		indic.settext(current_string);
		indic.restorecursorstate(graphstate[graph_mode]);
//		indic.hidemouse_ind();
		indic.redraw();
		indic.activate();
		input_pointer=0;
		showmouse();
//		key=morekey;
//		goto begconv;
		return 1;
		}
	}
return 1;
}

int receivemouseevent(void)
{
mev=getmouseevent();
if(!ishelp && indic.event(current_mode!=0 && current_mode!=3)) return KEY_indicuse;
//if(mev.event==ME_MOVED) return KEY_no;
what_button=KEY_no;


if(BUT_helplock.event()) goto endkey;
if(BUT_actlock.event(ishelp)) goto endkey;
if(F_RAD.event() || F_DEG.event() || F_GRD.event())
	{
	if(what_button>32000)
		if(current_mode==1 || ishelp)
			what_button=what_button-32000+42;
//		{int temp=what_button-32000;what_button=32760;if(!ishelp) return temp;else what_button=temp+42;}
	goto endkey;
	}
if(F_BIN.event()) goto endkey;
if(F_OCT.event()) goto endkey;
if(F_DEC.event()) goto endkey;
if(F_HEX.event()) goto endkey;

if(current_mode<2 && !ishelp)
	{
	if(mev.event&ME_LEFTPRESSED && mev.xcoord>=5 && mev.xcoord<5+16 && mev.ycoord<156)
		{
		int work=mev.ycoord/12;
		variable[work].ison^=1;
		drawvariable(work);
		return KEY_no;
		}
	if(mev.event&ME_LEFTPRESSED && mev.xcoord>=245 && mev.xcoord<245+16 && mev.ycoord<156)
		{
		int work=mev.ycoord/12+13;
		variable[work].ison^=1;
		drawvariable(work);
		return KEY_no;
		}
	if(mev.event&ME_LEFTPRESSED && mev.xcoord>=485 && mev.xcoord<485+16 && mev.ycoord>=12 && mev.ycoord<108)
		{
		int work=(mev.ycoord-12)/12+26;
		variable[work].ison^=1;
		drawvariable(work);
		return KEY_no;
		}
	}

if(mev.xcoord>=2 && mev.xcoord<638 && mev.ycoord>=177  && mev.ycoord<219)
	if(ishelp && mev.event&ME_LEFTPRESSED)
		{what_button=KEY_indicuse;goto endkey;}
		else
		if(mev.event&ME_RIGHTPRESSED && mev.keystate==2 && !ishelp)
			{helpon(KEY_indicuse);return 0;}

if(mev.xcoord>=5 && mev.xcoord<561 && mev.ycoord<156)
	if(ishelp && mev.event&ME_LEFTPRESSED)
		{what_button=KEY_consoluse;goto endkey;}
		else
		if(mev.event&ME_RIGHTPRESSED && mev.keystate==2 && !ishelp)
			{helpon(KEY_consoluse);return 0;}

if(mev.xcoord>=205 && mev.xcoord<439 && mev.ycoord>=468 && mev.ycoord<478)
	if(ishelp && mev.event&ME_LEFTPRESSED)
		{what_button=KEY_yuraused;goto endkey;}
		else
		if(mev.event&ME_RIGHTPRESSED && mev.keystate==2 &&  !ishelp)
			{helpon(KEY_yuraused);return 0;}

int i;
for(i=0;i<=BUT_INDEX_LAST;i++)
	if(BUTTON_ARRAY[i]->event(ishelp)) break;
endkey:
if(what_button==KEY_helplock)
	{
	ishelp=!ishelp;
	if(ishelp) BUT_helplock.push();
		else
		BUT_helplock.draw();
	hidemouse();
	if(ishelp)
		SETGRAPHICSPOINTER(0,0,mousearrowquest);
		else
		SETGRAPHICSPOINTER(0,0,mousearrow);
	showmouse();
	return KEY_no;
	}
if(what_button>32000)
	{
	if(!ishelp)
		helpon(what_button-32000);
	return KEY_no;
	}
if(ishelp)
	{helpon(what_button);return KEY_no;}
if(what_button==KEY_reset) {reset();return KEY_break;}
if(what_button==KEY_load)
	if(loadstate())
		return KEY_break;
		else
		return KEY_no;
if(what_button==KEY_help)
	if(!gethelp()) return KEY_exit;
		else {showonlymessage(currentmessage);return KEY_no;}
return what_button;
}

