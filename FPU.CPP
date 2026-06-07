#include"..\express\fpu.hpp"

extern int FPUerror;

long double FPU_mul(long double num1,long double num2)
{
return FPUmul(num1,num2);
}

long double FPU_div(long double num1,long double num2)
{
return FPUdiv(num1,num2);
}

//void printdouble(void);
long double FPU_sin(long double num)
{
return FPUsin(num);
}

long double FPU_cos(long double num)
{
return FPUcos(num);
}

long double FPU_tan(long double num)
{
return FPUtan(num);
}

long double FPU_ctan(long double num)
{
return FPUctan(num);
}

long double FPU_lg(long double num)
{
return FPUlg(num);
}

long double FPU_ln(long double num)
{
return FPUln(num);
}

long double FPU_power(long double num1,long double num2)
{
return FPUpower(num1,num2);
}

long double FPU_mod(long double num1,long double num2)
{
return FPUmod(num1,num2);
}

long double FPU_int(long double num)
{
return FPUint(num);
}

long double FPU_round(long double num)
{
return FPUround(num);
}

long double FPU_add(long double num1,long double num2)
{
return FPUadd(num1,num2);
}

long double FPU_sub(long double num1,long double num2)
{
return FPUsub(num1,num2);
}

long double FPU_atan(long double num)
{
return FPUatan(num);
}

long double FPU_actan(long double num)
{
return FPUactan(num);
}

long double FPU_asin(long double num)
{
return FPUasin(num);
}

long double FPU_acos(long double num)
{
return FPUacos(num);
}

long double FPU_abs(long double num)
{
return FPUabs(num);
}

long double FPU_sqrt(long double num)
{
return FPUsqrt(num);
}

int FPU_sgn(long double num)
{
return FPUsgn(num);
}
