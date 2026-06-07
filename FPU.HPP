
#ifndef _FPU_HPP
extern "C" {
void FPUinit(void);
long double FPUmul(long double &,long double &);
long double FPUdiv(long double &,long double &);
void FPUdouble2string(long double &,char*,int &,int=0);
void FPUdouble2stringbin(long double &,char*,int &);
void FPUdouble2stringoct(long double &,char*,int &);
void FPUdouble2stringhex(long double &,char*,int &);
//void printdouble(void);
char * FPUgetmesptr(int);
long double FPUsin(long double &);
long double FPUcos(long double &);
long double FPUtan(long double &);
long double FPUctan(long double &);
long double FPUloadpi(void);
long double FPUlg(long double &);
long double FPUln(long double &);
long double FPUpower(long double &,long double &);
long double FPUmod(long double &,long double &);
long double FPUint(long double &);
long double FPUround(long double &);
long double FPUadd(long double &,long double &);
long double FPUsub(long double &,long double &);
long double FPUatan(long double &);
long double FPUactan(long double &);
long double FPUasin(long double &);
long double FPUacos(long double &);
long double FPUabs(long double &);
long double FPUsqrt(long double &);
long double FPUloadl2E(void);
long double FPUloadl2T(void);
int FPUsgn(long double &);
}
extern int FPUerror;

inline long double FPU_mul(long double num1,long double num2)
{
return FPUmul(num1,num2);
}

inline long double FPU_div(long double num1,long double num2)
{
return FPUdiv(num1,num2);
}

//void printdouble(void);
inline long double FPU_sin(long double num)
{
return FPUsin(num);
}

inline long double FPU_cos(long double num)
{
return FPUcos(num);
}

inline long double FPU_tan(long double num)
{
return FPUtan(num);
}

inline long double FPU_ctan(long double num)
{
return FPUctan(num);
}

inline long double FPU_lg(long double num)
{
return FPUlg(num);
}

inline long double FPU_ln(long double num)
{
return FPUln(num);
}

inline long double FPU_power(long double num1,long double num2)
{
return FPUpower(num1,num2);
}

inline long double FPU_mod(long double num1,long double num2)
{
return FPUmod(num1,num2);
}

inline long double FPU_int(long double num)
{
return FPUint(num);
}

inline long double FPU_round(long double num)
{
return FPUround(num);
}

inline long double FPU_add(long double num1,long double num2)
{
return FPUadd(num1,num2);
}

inline long double FPU_sub(long double num1,long double num2)
{
return FPUsub(num1,num2);
}

inline long double FPU_atan(long double num)
{
return FPUatan(num);
}

inline long double FPU_actan(long double num)
{
return FPUactan(num);
}

inline long double FPU_asin(long double num)
{
return FPUasin(num);
}

inline long double FPU_acos(long double num)
{
return FPUacos(num);
}

inline long double FPU_abs(long double num)
{
return FPUabs(num);
}

inline long double FPU_sqrt(long double num)
{
return FPUsqrt(num);
}

inline int FPU_sgn(long double num)
{
return FPUsgn(num);
}





/*

long double FPU_mul(long double num1,long double num2);

long double FPU_div(long double num1,long double num2);

long double FPU_sin(long double num);

long double FPU_cos(long double num);

long double FPU_tan(long double num);

long double FPU_ctan(long double num);

long double FPU_lg(long double num);

long double FPU_ln(long double num);

long double FPU_power(long double num1,long double num2);

long double FPU_mod(long double num1,long double num2);

long double FPU_int(long double num);

long double FPU_round(long double num);

long double FPU_add(long double num1,long double num2);

long double FPU_sub(long double num1,long double num2);

long double FPU_atan(long double num);

long double FPU_actan(long double num);

long double FPU_asin(long double num);

long double FPU_acos(long double num);

long double FPU_abs(long double num);

long double FPU_sqrt(long double num);

int FPU_sgn(long double num);*/

#define _FPU_HPP
#endif