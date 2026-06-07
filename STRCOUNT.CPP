#include"..\express\fpu.hpp"
#include"..\express\common.hpp"

extern int NUMSTACK_SIZE,OPSTACK_SIZE,MULTITUDE_SIZE;

struct memory_element
{
int isstring;
int ison,iserror;
long double number,newnumber;
char *string,*flags;
};

struct mul_element
{
int isvar;
int var;
long double number;
};

extern memory_element *variable;
extern mul_element *multitude;
extern int Counterror,real_multitude_len;
extern unsigned long multitude_len;
extern long double xscale,yscale;

class Stack
{
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

Stack num_stk(10,NUMSTACK_SIZE),oper_stk(1,OPSTACK_SIZE);


const char ER=0,          //неправильные символы
PLUS=1,		   //плюс
MINUS=2,       //минус
MULTI=3,       //умножить
DIV=4,         //делить
RPAREN=5,      //)
LPAREN=6,      //(
POWER=7,	   //возведение в степень
SIN=8,COS=9,TAN=10,CTAN=11,LN=12,LG=13,EXP=14,ASIN=15,ACOS=16,ATAN=17,
ACTAN=18,SGN=19,MOD=20,E10=21,SINH=22,COSH=23,TANH=24,CTANH=25,
ASINH=26,ACOSH=27,ATANH=28,ACTANH=29,ROOT1=30,ROOT2=31,ROOT3=32,ROOT4=33,
ROOT5=34,ROOT6=35,ROOT7=36,ROOT8=37,ROOT9=38,POW1=39,POW2=40,POW3=41,
POW4=42,POW5=43,POW6=44,POW7=45,POW8=46,POW9=47,E2=48,E8=49,E16=50,FACTOR=51,
SUM=52,MUL=53,INDEX=54,MUL_ELEMENT=55,LESS=56,LESS_EQ=57,GREATER=58,
GREATER_EQ=59,EQ=60,NOT_EQ=61,NOT=62,AND=63,OR=64,XOR=65,MULTIFIRST=66,
NUMBER=67,      //число
VARIABLE=68,
NOPER=69,UN_MINUS=70,LOG=71;


int weight[72]={0,10,10,20,20,0,0,30,40,40,40,40,40,40,40,40,40,40,40,40
,20,55,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,50,50,50,50,50,
50,50,50,50,55,55,55,50,0,0,0,0,8,8,8,8,5,5,40,4,2,2,25,0,0,0,0,40};

enum status {NONE,OPERAND,RIGHT_OPER,LEFT_OPER,NUM,UNAR_MINUS,E_OPER,LOW_OPER};
enum parens {ROUND,SQUARE,MODULUS};

int isrightoperand[72]={0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,0,0,0,1};

int isleftoperand[72]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0};


enum systems {DECSYS=10,HEXSYS=16,OCTSYS=8,BINSYS=2} cur_system;
enum trig_systems {RAD=32,DEG=64,GRD=96} cur_trig_system;

extern long double Last_answer;

char *expstring,*expflags;
char *allopers;
long double folnum,*allnums;
int exppointer,numofopenedparens;
parens pars;
int Ignoreerror,Worklen;



int dooper(int onenum=0);

int doexpression(int numops,int numnums)
{
for (int i=numops-1;i>=0;i--)
	oper_stk.pop(allopers[i]);
for (i=numnums-1;i>=0;i--)
	num_stk.pop(allnums[i]);
int maxweight;
again:
maxweight=0;
for (i=0;i<numops;i++)
	if (weight[allopers[i]]>maxweight)
		maxweight=weight[allopers[i]];
for (i=0;i<numops;i++)
	if (weight[allopers[i]]==maxweight)
		{
		oper_stk.push(allopers[i]);
		num_stk.push(allnums[i]);
		num_stk.push(allnums[i+1]);
		if (!dooper()) {Ignoreerror=1;return 1;}
		num_stk.pop(allnums[i]);
		for (int q=i+1;q<numops;q++)
			allopers[q-1]=allopers[q];
		numops--;
		for (q=i+2;q<numnums;q++)
			allnums[q-1]=allnums[q];
		numnums--;
		break;
		}
if (numops>0) goto again;
num_stk.push(allnums[0]);
return 1;
}


char getnextoper()
{
if(exppointer>=Worklen) return ER;
int isin=0;
char nextchar;
getagain:
cur_system=(systems)expflags[exppointer]&31;
//cur_trig_system=(trig_systems)expflags[exppointer]&96;
nextchar=expstring[exppointer++];
   #ifdef TRACE
		 cout<<"getnextoper для "<<nextchar<<"  "<<exppointer-1<<"\n";
   #endif
switch (nextchar) {
	case ' ': goto getagain;
	case '!': return FACTOR;
	case '(': pars=ROUND;return LPAREN;
	case ')': pars=ROUND;return RPAREN;
	case '[': pars=SQUARE;return LPAREN;
	case ']': pars=SQUARE;return RPAREN;
	case '\xb4': pars=MODULUS;return LPAREN;
	case '\xb5': pars=MODULUS;return RPAREN;
	case '+': return PLUS;
	case '-': return MINUS;
	case '*': return MULTI;
	case '/': return DIV;
	case '\\': return MOD;
	case '^': return POWER;
	case '\xb3':
		if(cur_system==DECSYS) return E10;
			else if(cur_system==BINSYS) return E2;
				else if(cur_system==OCTSYS) return E8;
					else return E16;
	case '\xa0': return SIN;
	case '\xa1': return COS;
	case '\xa2': return TAN;
	case '\xa3': return CTAN;
	case '\xa4': return ASIN;
	case '\xa5': return ACOS;
	case '\xa6': return ATAN;
	case '\xa7': return ACTAN;
	case '\xa8': return SINH;
	case '\xa9': return COSH;
	case '\xaa': return TANH;
	case '\xab': return CTANH;
	case '\xac': return ASINH;
	case '\xad': return ACOSH;
	case '\xae': return ATANH;
	case '\xaf': return ACTANH;
	case '\xb0': return LN;
	case '\xb1': return LG;
	case '\xb2': return EXP;
	case '\xb6': return SGN;
	case '\xb7': folnum=FPUloadpi();return VARIABLE;
	case '\xb8': folnum=Last_answer;return VARIABLE;
	case '\xb9': return SUM;
	case '\xba': return MUL;
	case '\xbb': folnum=multitude_len;return VARIABLE;
	case '\xbc': return INDEX;
	case '\xbd': return MUL_ELEMENT;
	case '\xc6': return ROOT1;
	case '\xc7': return ROOT2;
	case '\xc8': return ROOT3;
	case '\xc9': return ROOT4;
	case '\xca': return ROOT5;
	case '\xcb': return ROOT6;
	case '\xcc': return ROOT7;
	case '\xcd': return ROOT8;
	case '\xce': return ROOT9;
	case '\xcf': return POW1;
	case '\xd0': return POW2;
	case '\xd1': return POW3;
	case '\xd2': return POW4;
	case '\xd3': return POW5;
	case '\xd4': return POW6;
	case '\xd5': return POW7;
	case '\xd6': return POW8;
	case '\xd7': return POW9;
	case '\xd8': folnum=Getrandom();return VARIABLE;
	case '\xd9': return LESS;
	case '\xda': return LESS_EQ;
	case '\xdb': return GREATER;
	case '\xdc': return GREATER_EQ;
	case '\xdd': return EQ;
	case '\xde': return NOT_EQ;
	case '\xdf': return NOT;
	case '\xe0': return AND;
	case '\xe1': return OR;
	case '\xe2': return XOR;
	case '\xe3': return LOG;
	case '\xe4': folnum=xscale;return VARIABLE;
	case '\xe5': folnum=yscale;return VARIABLE;
}

if (nextchar>='A' && nextchar<='Z')
	{folnum=variable[nextchar-'A'].number;return VARIABLE;}

if (!((nextchar>='0' && nextchar<='9') || nextchar==',' || (nextchar>='\xc0' && nextchar<='\xc5')))
	return ER;

int end_pos;
long double temper=0.0,ap=0.0;
unsigned char digit;

again:
if (nextchar==',')
	{
	if(isin>0) return ER;
	isin++;
	end_pos=exppointer;
	while((nextchar=expstring[end_pos]) && end_pos<Worklen)
		{
		if((nextchar>='0' && nextchar<='9') || nextchar==',' || (nextchar>='\xc0' && nextchar<='\xc5'))
			{
			if(nextchar!=',')
				{
				if((nextchar<'0' || nextchar>'1') && cur_system==BINSYS) {exppointer=end_pos+1;return ER;}
				if((nextchar<'0' || nextchar>'7') && cur_system==OCTSYS) {exppointer=end_pos+1;return ER;}
				if((nextchar<'0' || nextchar>'9') && cur_system==DECSYS) {exppointer=end_pos+1;return ER;}
				if((nextchar<'0' || (nextchar>'9' && (nextchar<'\xc0' || nextchar>'\xc5'))) && cur_system==HEXSYS) {exppointer=end_pos+1;return ER;}
				end_pos++;
				}
				else {exppointer=end_pos+1;return ER;}
			continue;
			}
		break;
		}
	if(!FPUerror)
		for(int works=end_pos-1;works>=exppointer;works--)
			{
			nextchar=expstring[works];
			if(nextchar>=0xc0 && nextchar<=0xc5) digit=nextchar-'\xc0'+10;
				else digit=nextchar-48;
			ap=FPU_div(FPU_add(ap,(long double)(digit)),(long double)(cur_system));
			if(FPUerror) {exppointer=end_pos+1;Ignoreerror=1;return NUMBER;}
			}
	if(exppointer==end_pos) return ER;
	exppointer=end_pos;
	goto after;
	}
if ((nextchar>='0' && nextchar<='9') || (nextchar>='\xc0' && nextchar<='\xc5'))
	{
	if((nextchar<'0' || nextchar>'1') && cur_system==BINSYS) return ER;
	if((nextchar<'0' || nextchar>'7') && cur_system==OCTSYS) return ER;
	if((nextchar<'0' || nextchar>'9') && cur_system==DECSYS) return ER;
	if((nextchar<'0' || (nextchar>'9' && (nextchar<'\xc0' || nextchar>'\xc5'))) && cur_system==HEXSYS) return ER;
	if(!FPUerror)
		{
		if(nextchar>=0xc0 && nextchar<=0xc5) digit=nextchar-'\xc0'+10;
			else digit=nextchar-48;
		temper=FPU_add(FPU_mul(temper,(long double)cur_system),(long double)(digit));
		if(FPUerror) {Ignoreerror=1;return NUMBER;}
		}
	if(exppointer<Worklen) nextchar=expstring[exppointer++];
		else goto after;
	goto again;
	}
exppointer--;
after:

if(FPUerror) Ignoreerror=1;
	else
	folnum=FPU_add(temper,ap);
return NUMBER;
}

int dooper(int onenumber)
{
long double num1,num2,tempo,tempo2;
char op;
oper_stk.pop(op);
num_stk.pop(num1);
if(!onenumber) num_stk.pop(num2);
   #ifdef TRACE
		 cout<<"dooper "<<num1<<" "<<int(op)<<" "<<num2<<"\n";
   #endif
if(op==MULTIFIRST) op=MULTI;
if(isrightoperand[op])
	{
	char tmp;
	oper_stk.pop(tmp);
	cur_trig_system=(trig_systems)(tmp&96);
	}
switch (op)
	{
	case XOR:
		if(num1==0)
			num_stk.push(num2);
			else
			num_stk.push((long double)0);
		break;
	case NOT:
		if(num1==0)
			num_stk.push((long double)1);
			else
			num_stk.push((long double)0);
		break;
	case LESS:
		if(num2<num1)
			num_stk.push((long double)1);
			else
			num_stk.push((long double)0);
		break;
	case LESS_EQ:
		if(num2<=num1)
			num_stk.push((long double)1);
			else
			num_stk.push((long double)0);
		break;
	case GREATER:
		if(num2>num1)
			num_stk.push((long double)1);
			else
			num_stk.push((long double)0);
		break;
	case GREATER_EQ:
		if(num2>=num1)
			num_stk.push((long double)1);
			else
			num_stk.push((long double)0);
		break;
	case EQ:
		if(num2==num1)
			num_stk.push((long double)1);
			else
			num_stk.push((long double)0);
		break;
	case NOT_EQ:
		if(num2!=num1)
			num_stk.push((long double)1);
			else
			num_stk.push((long double)0);
		break;
	case PLUS:
		tempo=FPU_add(num1,num2);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case MINUS:
		tempo=FPU_sub(num2,num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case MULTI:
		tempo=FPU_mul(num1,num2);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case ROOT1:
		tempo=FPU_div(1.0,num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case ROOT2:
		if(num1<0) {FPUerror=10;return 0;}
		tempo=FPU_sqrt(num1);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ROOT3:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_div(1.0,3.0);
		tempo=FPU_power(FPU_abs(num1),tempo);
		if(FPU_sgn(num1)==-1) tempo=-tempo;
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ROOT4:
		if(num1<0) {FPUerror=10;return 0;}
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_div(1.0,4.0);
		tempo=FPU_power(num1,tempo);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ROOT5:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_div(1.0,5.0);
		tempo=FPU_power(FPU_abs(num1),tempo);
		if(FPU_sgn(num1)==-1) tempo=-tempo;
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ROOT6:
		if(num1<0) {FPUerror=10;return 0;}
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_div(1.0,6.0);
		tempo=FPU_power(num1,tempo);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ROOT7:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_div(1.0,7.0);
		tempo=FPU_power(FPU_abs(num1),tempo);
		if(FPU_sgn(num1)==-1) tempo=-tempo;
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ROOT8:
		if(num1<0) {FPUerror=10;return 0;}
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_div(1.0,8.0);
		tempo=FPU_power(num1,tempo);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ROOT9:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_div(1.0,9.0);
		tempo=FPU_power(FPU_abs(num1),tempo);
		if(FPU_sgn(num1)==-1) tempo=-tempo;
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case POW1:
		tempo=FPU_div(1,num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case POW2:
		tempo=FPU_mul(num1,num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case POW3:
		tempo=FPU_mul(num1,num1);
		tempo=FPU_mul(tempo,num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case POW4:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_power(FPU_abs(num1),4.0);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case POW5:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_power(FPU_abs(num1),5.0);
		if(FPU_sgn(num1)==-1) tempo=-tempo;
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case POW6:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_power(FPU_abs(num1),6.0);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case POW7:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_power(FPU_abs(num1),7.0);
		if(FPU_sgn(num1)==-1) tempo=-tempo;
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case POW8:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_power(FPU_abs(num1),8.0);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case POW9:
		if(num1==0) {num_stk.push((long double)0);break;}
		tempo=FPU_power(FPU_abs(num1),9.0);
		if(FPU_sgn(num1)==-1) tempo=-tempo;
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case FACTOR:
		tempo=FPU_int(FPU_abs(num1));
		if(tempo>1754) {FPUerror=8;return 0;}
		{
		int tmp=(int)tempo,work;
		tempo=1.0;
		if(!tmp) {num_stk.push(tempo);break;}
		for(work=2;work<=tmp;work++)
			tempo=FPU_mul(tempo,(long double)work);
		}
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case DIV:
		tempo=FPU_div(num2,num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case POWER:
		tempo=FPU_power(num2,num1);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case E10:
		tempo=FPU_power(10,num1);
		tempo=FPU_mul(num2,tempo);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case E2:
		tempo=FPU_power(2.0,num1);
		tempo=FPU_mul(num2,tempo);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case E8:
		tempo=FPU_power(8.0,num1);
		tempo=FPU_mul(num2,tempo);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case E16:
		tempo=FPU_power(16.0,num1);
		tempo=FPU_mul(num2,tempo);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case SIN:
		if(cur_trig_system==DEG)
			{
			num1=FPU_div(num1,180.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			num1=FPU_div(num1,200.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
		if(FPU_mod(num1,FPUloadpi())==0 && !FPUerror)
			tempo=0;
			else
			{
			tempo=FPU_sin(num1);
			if(FPUerror) return 0;
			}
		num_stk.push(tempo);
		break;
	case COS:
		if(cur_trig_system==DEG)
			{
			num1=FPU_div(num1,180.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			num1=FPU_div(num1,200.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
		if(FPU_mod(FPU_sub(num1,FPU_div(FPUloadpi(),2)),FPUloadpi())==0 && !FPUerror)
			tempo=0;
			else
			{
			tempo=FPU_cos(num1);
			if(FPUerror) return 0;
			}
		num_stk.push(tempo);
		break;
	case TAN:
		if(cur_trig_system==DEG)
			{
			num1=FPU_div(num1,180.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			num1=FPU_div(num1,200.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
		if(FPUerror) return 0;
		tempo=FPU_tan(num1);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case CTAN:
		if(cur_trig_system==DEG)
			{
			num1=FPU_div(num1,180.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			num1=FPU_div(num1,200.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
		if(FPUerror) return 0;
		tempo=FPU_ctan(num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case LN:
		tempo=FPU_ln(num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case LG:
		tempo=FPU_lg(num1);
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
			return 0;
			}
		num_stk.push(tempo);
		break;
	case LOG:
		tempo=FPU_div(FPUln(num1),FPUln(num2));
		if(FPUerror)
			{
			if(FPUerror==1)
				{
				FPUerror=0;
				if(FPUsgn(tempo)==1) FPUerror=8;
					else FPUerror=9;
				}
				else
				if(FPUerror==2) FPUerror=5;
			return 0;
			}
		num_stk.push(tempo);
		break;
	case EXP:
		tempo=FPU_mul(num1,FPUloadl2E());
		if(FPUerror) return 0;
		tempo=FPU_power(2.0,tempo);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ASIN:
		tempo=FPU_asin(num1);
		if(FPUerror) return 0;
		if(cur_trig_system==DEG)
			{
			tempo=FPU_mul(tempo,180.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			tempo=FPU_mul(tempo,200.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ACOS:
		tempo=FPU_acos(num1);
		if(FPUerror) return 0;
		if(cur_trig_system==DEG)
			{
			tempo=FPU_mul(tempo,180.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			tempo=FPU_mul(tempo,200.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ATAN:
		tempo=FPU_atan(num1);
		if(FPUerror) return 0;
		if(cur_trig_system==DEG)
			{
			tempo=FPU_mul(tempo,180.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			tempo=FPU_mul(tempo,200.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ACTAN:
		tempo=FPU_actan(num1);
		if(FPUerror) return 0;
		if(cur_trig_system==DEG)
			{
			tempo=FPU_mul(tempo,180.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			tempo=FPU_mul(tempo,200.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case SINH:
		if(cur_trig_system==DEG)
			{
			num1=FPU_div(num1,180.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			num1=FPU_div(num1,200.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
		if(FPUerror) return 0;
		tempo=FPU_mul(num1,FPUloadl2E());
		if(FPUerror) return 0;
		tempo2=FPU_power(2.0,tempo);
		if(FPUerror) return 0;
		tempo=FPU_sub(tempo2,FPU_power(2.0,-tempo));
		if(FPUerror) return 0;
		tempo=FPU_div(tempo,2.0);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case COSH:
		if(cur_trig_system==DEG)
			{
			num1=FPU_div(num1,180.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			num1=FPU_div(num1,200.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
		if(FPUerror) return 0;
		tempo=FPU_mul(num1,FPUloadl2E());
		if(FPUerror) return 0;
		tempo2=FPU_power(2.0,tempo);
		tempo=FPU_add(tempo2,FPU_power(2.0,-tempo));
		if(FPUerror) return 0;
		tempo=FPU_div(tempo,2.0);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case TANH:
		if(cur_trig_system==DEG)
			{
			num1=FPU_div(num1,180.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			num1=FPU_div(num1,200.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
		if(FPUerror) return 0;
		tempo=FPU_mul(num1,FPUloadl2E());
		if(FPUerror) return 0;
		tempo2=FPU_power(2.0,tempo);
		if(FPUerror) return 0;
		tempo=FPU_power(2.0,-tempo);
		if(FPUerror) return 0;
		tempo=FPU_div(FPU_sub(tempo2,tempo),FPU_add(tempo2,tempo));
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case CTANH:
		if(cur_trig_system==DEG)
			{
			num1=FPU_div(num1,180.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			num1=FPU_div(num1,200.0);
			if(FPUerror) return 0;
			num1=FPU_mul(num1,FPUloadpi());
			}
		if(FPUerror) return 0;
		tempo=FPU_mul(num1,FPUloadl2E());
		if(FPUerror) return 0;
		tempo2=FPU_power(2.0,tempo);
		if(FPUerror) return 0;
		tempo=FPU_power(2.0,-tempo);
		if(FPUerror) return 0;
		tempo=FPU_div(FPU_add(tempo2,tempo),FPU_sub(tempo2,tempo));
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ASINH:
		tempo=FPU_mul(num1,num1);
		if(FPUerror) return 0;
		tempo=FPU_add(tempo,1.0);
		if(FPUerror) return 0;
		tempo=FPU_sqrt(tempo);
		if(FPUerror) return 0;
		tempo=FPU_add(tempo,num1);
		if(FPUerror) return 0;
		tempo=FPU_ln(tempo);
		if(FPUerror) return 0;
		if(cur_trig_system==DEG)
			{
			tempo=FPU_mul(tempo,180.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			tempo=FPU_mul(tempo,200.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ACOSH:
		tempo=FPU_mul(num1,num1);
		if(FPUerror) return 0;
		tempo=FPU_sub(tempo,1.0);
		if(FPUerror) return 0;
		tempo=FPU_sqrt(tempo);
		if(FPUerror) return 0;
		tempo=FPU_add(tempo,num1);
		if(FPUerror) return 0;
		tempo=FPU_ln(tempo);
		if(FPUerror) return 0;
		if(cur_trig_system==DEG)
			{
			tempo=FPU_mul(tempo,180.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			tempo=FPU_mul(tempo,200.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ATANH:
		tempo=FPU_div(FPU_add(1.0,num1),FPU_sub(1.0,num1));
		if(FPUerror) return 0;
		tempo=FPU_ln(tempo);
		if(FPUerror) return 0;
		tempo=FPU_div(tempo,2.0);
		if(FPUerror) return 0;
		if(cur_trig_system==DEG)
			{
			tempo=FPU_mul(tempo,180.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			tempo=FPU_mul(tempo,200.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case ACTANH:
		tempo=FPU_div(FPU_add(num1,1.0),FPU_sub(num1,1.0));
		if(FPUerror) return 0;
		tempo=FPU_ln(tempo);
		if(FPUerror) return 0;
		tempo=FPU_div(tempo,2.0);
		if(FPUerror) return 0;
		if(cur_trig_system==DEG)
			{
			tempo=FPU_mul(tempo,180.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
			else if(cur_trig_system==GRD)
			{
			tempo=FPU_mul(tempo,200.0);
			if(FPUerror) return 0;
			tempo=FPU_div(tempo,FPUloadpi());
			}
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case MOD:
		tempo=FPU_mod(num2,num1);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	case SGN:
		tempo=(long double)FPU_sgn(num1);
		if(FPUerror) return 0;
		num_stk.push(tempo);
		break;
	default:
   #ifdef TRACE
		 cout<<"dooper default error "<<int(op)<<"\n";
   #endif
	Counterror=1;return 0;
	}
return 1;
}


int funmain(parens whatparen,int ignoreerror,unsigned long index=0)
{
   #ifdef TRACE
		 cout<<"funmain in "<<"\n";
   #endif

status lastoper=NONE;
int numoperations=0,numnumbers=0;
char operand,lastlogoper=NOPER;
while (expstring[exppointer] && exppointer<Worklen)
{
	operand=getnextoper();
	if (operand==NOPER) continue;
	if (operand!=RPAREN && lastoper==LOW_OPER) lastoper=NONE;
	if (operand==INDEX) {folnum=index;operand=VARIABLE;}
	if (operand==SUM)
		{
		if(getnextoper()==LPAREN)
			{
			if(multitude_len==0 && !(ignoreerror|Ignoreerror)) {FPUerror=11;Ignoreerror=1;}
			if(ignoreerror|Ignoreerror)
				{
				numofopenedparens++;
				if(!funmain(pars,ignoreerror,0)) return 0;
				operand=VARIABLE;
				goto afterparen;
				}
			long double temp=0;
			int oldexppointer=exppointer;
			for(unsigned long i=0;i<multitude_len;i++)
				{
				if(Kbhit())
					if(Getkey()==283) break;
				exppointer=oldexppointer;
				numofopenedparens++;
				if(!funmain(pars,ignoreerror,i)) return 0;
				if(Ignoreerror) {operand=VARIABLE;goto afterparen;}
				num_stk.pop(folnum);
				temp=FPUadd(temp,folnum);
				if(FPUerror) {Ignoreerror=1;operand=VARIABLE;goto afterparen;}
				}
			folnum=temp;
			operand=VARIABLE;
			goto afterparen;
			}
		Counterror=1;return 0;
		}
	if (operand==MUL)
		{
		if(getnextoper()==LPAREN)
			{
			if(multitude_len==0 && !(ignoreerror|Ignoreerror)) {FPUerror=11;Ignoreerror=1;}
			if(ignoreerror|Ignoreerror)
				{
				numofopenedparens++;
				if(!funmain(pars,ignoreerror,0)) return 0;
				operand=VARIABLE;
				goto afterparen;
				}
			long double temp=1.0;
			int oldexppointer=exppointer;
			for(unsigned long i=0;i<multitude_len;i++)
				{
				if(Kbhit()==283) break;
				exppointer=oldexppointer;
				numofopenedparens++;
				if(!funmain(pars,ignoreerror,i)) return 0;
				if(Ignoreerror) {operand=VARIABLE;goto afterparen;}
				num_stk.pop(folnum);
				temp=FPUmul(temp,folnum);
				if(FPUerror) {Ignoreerror=1;operand=VARIABLE;goto afterparen;}
				}
			folnum=temp;
			operand=VARIABLE;
			goto afterparen;
			}
		Counterror=1;return 0;
		}
	if (operand==MUL_ELEMENT)
		{
		if(getnextoper()==LPAREN)
			{
			if(multitude_len==0 && !(ignoreerror|Ignoreerror)) {FPUerror=11;Ignoreerror=1;}
			numofopenedparens++;
			if(!funmain(pars,ignoreerror,index)) return 0;
			if(!(ignoreerror|Ignoreerror))
				{
				num_stk.pop(folnum);
				folnum=FPUint(folnum);
				folnum=FPU_mod(folnum,multitude_len);
				if(folnum<0) FPU_add(folnum,multitude_len);
				if(FPUerror) {Ignoreerror=1;operand=VARIABLE;goto afterparen;}
				if(folnum>=real_multitude_len) folnum=0;
					else
					{
					int work=(int)folnum;
					if(multitude[work].isvar)
						folnum=variable[multitude[work].var].number;
						else
						folnum=multitude[work].number;
					}
				}
			operand=VARIABLE;
			goto afterparen;
			}
		Counterror=1;return 0;
		}
	if (operand==OR)
		{
		if(lastoper==NUM)
			{
			if((ignoreerror && weight[lastlogoper]!=4)|Ignoreerror) {lastoper=LOW_OPER;continue;}
			if(ignoreerror && lastlogoper==AND)
				{
				num_stk.pop(folnum);
				numnumbers=0;
				lastoper=LOW_OPER;
				ignoreerror=0;
				lastlogoper=NOPER;
				continue;
				}
			if(numnumbers>1 && numoperations)
				doexpression(numoperations,numnumbers);
			if(Ignoreerror) {lastoper=OPERAND;continue;}
			numnumbers=1;numoperations=0;
			num_stk.pop(folnum);
			if(folnum==0) {numnumbers=0;lastoper=LOW_OPER;continue;}
			num_stk.push(folnum);
			lastlogoper=OR;
			ignoreerror=1;
			lastoper=LOW_OPER;
			continue;
			}
		Counterror=1;return 0;
		}
	if (operand==XOR)
		{
		if(lastoper==NUM)
			{
			if((ignoreerror && weight[lastlogoper]!=4)|Ignoreerror) {lastoper=LOW_OPER;continue;}
			if(ignoreerror && lastlogoper==AND)
				{
				num_stk.pop(folnum);
				numnumbers=0;
				lastoper=LOW_OPER;
				ignoreerror=0;
				lastlogoper=NOPER;
				continue;
				}
			if(numnumbers>1 && numoperations)
				doexpression(numoperations,numnumbers);
			if(Ignoreerror) {lastoper=OPERAND;continue;}
			numnumbers=1;numoperations=0;
			num_stk.pop(folnum);
			if(folnum==0) {numnumbers=0;lastoper=LOW_OPER;continue;}
			num_stk.push(folnum);
			oper_stk.push(XOR);
			numoperations++;
			lastoper=LOW_OPER;
			continue;
			}
		Counterror=1;return 0;
		}
	if (operand==AND)
		{
		if(lastoper==NUM)
			{
			if(ignoreerror|Ignoreerror) {lastoper=LOW_OPER;continue;}
			if(numnumbers>1 && numoperations)
				doexpression(numoperations,numnumbers);
			if(Ignoreerror) {lastoper=OPERAND;continue;}
			numnumbers=1;numoperations=0;
			num_stk.pop(folnum);
			if(folnum!=0) {numnumbers=0;lastoper=LOW_OPER;continue;}
			num_stk.push(folnum);
			lastlogoper=AND;
			ignoreerror=1;
			lastoper=LOW_OPER;
			continue;
			}
		Counterror=1;return 0;
		}
	if (operand==LOG)
		{
		if(getnextoper()==LPAREN)
			{
			numofopenedparens++;
			char tempp=expflags[exppointer-2];
			if(!funmain(pars,ignoreerror,index)) return 0;
			if (lastoper==NUM)
				{
				if(ignoreerror|Ignoreerror) {lastoper=RIGHT_OPER;continue;}
				oper_stk.push(MULTIFIRST);
				numoperations++;
				lastoper=OPERAND;
				}  //Дальше работает следующая часть
			if (lastoper==OPERAND || lastoper==RIGHT_OPER || lastoper==NONE || lastoper==E_OPER || lastoper==UNAR_MINUS)
				{
	//			if(lastoper==E_OPER || lastoper==UNAR_MINUS) oldlastoper=lastoper;
	//				else oldlastoper=NONE;
				if(ignoreerror|Ignoreerror) {lastoper=RIGHT_OPER;continue;}
				oper_stk.push(tempp);
				oper_stk.push(operand);
				numoperations++;
				lastoper=RIGHT_OPER;
				continue;
				}
			}
		Counterror=1;return 0;
		}
	if (isrightoperand[operand])
		{
		if (lastoper==NUM)
			{
			if(ignoreerror|Ignoreerror) {lastoper=RIGHT_OPER;continue;}
			oper_stk.push(MULTIFIRST);
			numoperations++;
			lastoper=OPERAND;
			}  //Дальше работает следующая часть
		if (lastoper==OPERAND || lastoper==RIGHT_OPER || lastoper==NONE || lastoper==E_OPER || lastoper==UNAR_MINUS)
			{
//			if(lastoper==E_OPER || lastoper==UNAR_MINUS) oldlastoper=lastoper;
//				else oldlastoper=NONE;
			if(ignoreerror|Ignoreerror) {lastoper=RIGHT_OPER;continue;}
			oper_stk.push(expflags[exppointer-1]);
			oper_stk.push(operand);
			numoperations++;
			lastoper=RIGHT_OPER;
			continue;
			}
		Counterror=1;return 0;
		}
	if (isleftoperand[operand])
		{
		if (lastoper==NUM)
			{
			if(ignoreerror|Ignoreerror) {lastoper=NUM;continue;}
			oper_stk.push(operand);
			if (!dooper(1)) Ignoreerror=1;
			lastoper=NUM;
			continue;
			}
		Counterror=1;return 0;
		}
	if (operand==PLUS)
		{
		if (lastoper==OPERAND && !(ignoreerror|Ignoreerror))
			{
			char tmpoper=oper_stk.getontop();
			if(tmpoper>=LESS && tmpoper<=XOR && tmpoper!=NOT) lastoper=NONE;
			}
		if (lastoper==NONE || lastoper==E_OPER) continue;
		if (lastoper==NUM)
			{
			if(ignoreerror|Ignoreerror) {lastoper=OPERAND;continue;}
			oper_stk.push(PLUS);
			numoperations++;
			lastoper=OPERAND;
			continue;
			}
		Counterror=1;return 0;
		}
	if (operand==MINUS)
		{
		if (lastoper==OPERAND && !(ignoreerror|Ignoreerror))
			{
			char tmpoper=oper_stk.getontop();
			if(tmpoper>=LESS && tmpoper<=XOR && tmpoper!=NOT) lastoper=NONE;
			}
		if(lastoper==NONE)
			{
			if(ignoreerror|Ignoreerror) {lastoper=OPERAND;continue;}
			num_stk.push((long double)0);
			oper_stk.push(MINUS);
			numnumbers++;
			numoperations++;
			lastoper=OPERAND;
			continue;
			}
		if (lastoper==E_OPER)
			{
			if(!(ignoreerror|Ignoreerror)) oper_stk.push(UN_MINUS);
			lastoper=UNAR_MINUS;
			continue;
			}
		if (lastoper==NUM)
			{
			if(ignoreerror|Ignoreerror) {lastoper=OPERAND;continue;}
			oper_stk.push(MINUS);
			numoperations++;
			lastoper=OPERAND;
			continue;
			}
		Counterror=1;return 0;
		}
	if (operand==MULTI || operand==DIV || operand==MOD || operand==POWER || operand==LESS || operand==LESS_EQ || operand==GREATER || operand==GREATER_EQ || operand==EQ || operand==NOT_EQ)
		{
		if (lastoper==NUM)
			{
			if(ignoreerror|Ignoreerror)
				if(operand==MULTI || operand==DIV || operand==MOD || operand==POWER)
					{lastoper=OPERAND;continue;}
					else
					{lastoper=LOW_OPER;continue;}
			oper_stk.push(operand);
			numoperations++;
			lastoper=OPERAND;
			continue;
			}
		Counterror=1;return 0;
		}
	if (operand==E2 || operand==E8 || operand==E10 || operand==E16)
		{
		if (lastoper==NUM)
			{
			if(ignoreerror|Ignoreerror) {lastoper=E_OPER;continue;}
			oper_stk.push(operand);
			numoperations++;
			lastoper=E_OPER;
			continue;
			}
		Counterror=1;return 0;
		}
afterparen:
	if (operand==VARIABLE)
		{
		if (lastoper==NUM)
			{
			if(ignoreerror|Ignoreerror) {lastoper=NUM;continue;}
			oper_stk.push(MULTIFIRST);
			numoperations++;
			lastoper=OPERAND;
			}
		operand=NUMBER;
		}
	if (operand==NUMBER)
		{
		if (lastoper==UNAR_MINUS)
			{
			char temp;
			oper_stk.pop(temp);
			folnum=-folnum;
			lastoper=E_OPER;
			}
		if (lastoper==E_OPER)
			{
			if(ignoreerror|Ignoreerror) {lastoper=NUM;continue;}
			num_stk.push(folnum);
			if(!dooper())
				{
				Ignoreerror=1;
				lastoper=NUM;
				continue;
				}
			numnumbers--;
			numoperations--;
			num_stk.pop(folnum);
			if(!numoperations)
				lastoper=NONE;
				else
				if(isrightoperand[oper_stk.getontop()])
					lastoper=RIGHT_OPER;
					else
					lastoper=OPERAND;
			}
		if (lastoper==NONE || lastoper==OPERAND)
			{
			if(ignoreerror|Ignoreerror) {lastoper=NUM;continue;}
			num_stk.push(folnum);
			numnumbers++;
			lastoper=NUM;
			continue;
			}
		if (lastoper==RIGHT_OPER)
			{
			if(ignoreerror|Ignoreerror) {lastoper=NUM;continue;}
			num_stk.push(folnum);
			if(expstring[exppointer]!='\xb3')
				while (numoperations && isrightoperand[oper_stk.getontop()])
					{
					if(oper_stk.getontop()==LOG)
						{
						if (!dooper()) {Ignoreerror=1;lastoper=NUM;break;}
						}
						else
						if (!dooper(1)) {Ignoreerror=1;lastoper=NUM;break;}
					numoperations--;
					}
			if(Ignoreerror) continue;
			char temp;
			if(numoperations) temp=oper_stk.getontop();
				else temp=NOPER;
			if(temp==E10 || (temp>=E2 && temp<=E16))
				{
				num_stk.pop(folnum);
				lastoper=E_OPER;
				operand=NUMBER;
				goto afterparen;
				}
			if(temp==UN_MINUS)
				{
				num_stk.pop(folnum);
				lastoper=UNAR_MINUS;
				operand=NUMBER;
				goto afterparen;
				}
			numnumbers++;
			lastoper=NUM;
			continue;
			}
		Counterror=1;return 0;
		}
	if (operand==LPAREN)
		{
		numofopenedparens++;
		if(!funmain(pars,ignoreerror,index)) return 0;
		if(!(ignoreerror|Ignoreerror)) num_stk.pop(folnum);
		operand=VARIABLE;
		goto afterparen;
		}
	if(numofopenedparens==1 && operand==RPAREN) {Counterror=2;return 0;}
	if (operand==RPAREN)
		{
		if (pars!=whatparen) {Counterror=2;return 0;}
forclose:
		if (lastoper==NONE)
			{
			if(numofopenedparens==1) {num_stk.push((long double)0);numofopenedparens--;return 1;}
				else {Counterror=1;return 0;}
			}
		if (lastoper==NUM)
			{
			numofopenedparens--;
			if(Ignoreerror) return 1;
			if(numnumbers>1 && numoperations)
				doexpression(numoperations,numnumbers);
			if(Ignoreerror) return 1;
			if (whatparen==SQUARE)
				{
				num_stk.pop(folnum);
				folnum=FPU_int(folnum);
				if(FPUerror) {Ignoreerror=1;return 1;}
				num_stk.push(folnum);
				}
			if (whatparen==MODULUS)
				{
				num_stk.pop(folnum);
				folnum=FPU_abs(folnum);
				if(FPUerror) {Ignoreerror=1;return 1;}
				num_stk.push(folnum);
				}
			return 1;
			}
		Counterror=1;return 0;
		}
	Counterror=1;return 0;
	}
goto forclose;
}


long double countstring(char *str,char *flg,int worklen)
{
expstring=str;
expflags=flg;
Worklen=worklen;
FPUinit();
long double mynum;
exppointer=0;
num_stk.init();
oper_stk.init();
numofopenedparens=1;
//lastlogoper=NOPER;
Ignoreerror=0;
Counterror=0;
FPUerror=0;
if(!funmain(ROUND,0)) return 0;
if(numofopenedparens) {Counterror=2;return 0;}
if(Ignoreerror) return 0;
num_stk.pop(mynum);
return mynum;
}
