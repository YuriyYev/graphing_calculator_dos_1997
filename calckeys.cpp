#define m0 1
#define m1 2
#define m2 4
#define m3 8
#define m4 16
#define m5 32
#define m6 64
#define m7 128

//0
Calc_2button far BUT_leftcur(m0+m1+m3,200-54,220+13,18,16,KEY_leftcur,0/*KEY_bufleft*/,&S_KEY_leftcur,0,15,0);
Calc_2button far BUT_rightcur(m0+m1+m3,218-54,220+13,18,16,KEY_rightcur,0/*KEY_bufright*/,&S_KEY_rightcur,0,15,0);
Calc_2button far BUT_leftqcur(m0+m1+m3,236-54,220+13,18,16,KEY_leftqcur,0/*KEY_bufqleft*/,&S_KEY_leftqcur,0,15,0);
Calc_2button far BUT_rightqcur(m0+m1+m3,254-54,220+13,18,16,KEY_rightqcur,0/*KEY_bufqright*/,&S_KEY_rightqcur,0,15,0);
Calc_2button far BUT_leftend(m0+m1+m3,272-54,220+13,18,16,KEY_leftend,0/*KEY_bufhome*/,&S_KEY_leftend,0,15,0);
Calc_2button far BUT_rightend(m0+m1+m3,290-54,220+13,18,16,KEY_rightend,0/*KEY_bufend*/,&S_KEY_rightend,0,15,0);
Calc_2button far BUT_bufcopy(m0+m3,290-54+18,220+13,18,16,KEY_bufcopy,0,&S_KEY_bufcopy,0,15,0);
Calc_2button far BUT_bufcopydel(m0+m3,290-54+36,220+13,18,16,KEY_bufcopydel,0,&S_KEY_bufcopydel,0,15,0);
Calc_2button far BUT_bufinsert(m0+m3,290,220+13,18,16,KEY_bufinsert,0,&S_KEY_bufinsert,0,15,0);
//6
Calc_2button far BUT_savenumto(m0+m1,5,245+16,57,18,KEY_savenumto,0,&S_KEY_savenumto,0,9,9);
Calc_2button far BUT_savestrto(m0,5,261+16+4,57,18,KEY_savestrto,0,&S_KEY_savestrto,0,9,9);
Calc_2button far BUT_readnum(m0+m3,66,245+16,57,18,KEY_read_num,0,&S_KEY_readnum,0,9,9);
Calc_2button far BUT_readstr(m0+m3,66,261+16+4,57,18,KEY_read_str,0,&S_KEY_readstr,0,9,9);
Calc_2button far BUT_addtomul(m0+m1,127,245+16,57,18,KEY_add_to_mul,0,&S_KEY_addnumtomul,0,9,9);
Calc_2button far BUT_addvartomul(m0+m1,127,261+16+4,57,18,KEY_add_var_to_mul,0,&S_KEY_addvartomul,0,9,9);
Calc_2button far BUT_M1_1(m1,188,245+16,29,18,KEY_M1_plus,0,&S_KEY_M1plus,0,9,9);
Calc_2button far BUT_M1_2(m1,188,261+16+4,29,18,KEY_M1_minus,0,&S_KEY_M1minus,0,9,9);
Calc_2button far BUT_M1_3(m1,221,245+16,29,18,KEY_M1_mul,0,&S_KEY_M1mul,0,9,9);
Calc_2button far BUT_M1_4(m1,221,261+16+4,29,18,KEY_M1_div,0,&S_KEY_M1div,0,9,9);
Calc_2button far BUT_Mn_1(m1,254,245+16,29,18,KEY_Mn_plus,0,&S_KEY_Mnplus,0,9,9);
Calc_2button far BUT_Mn_2(m1,254,261+16+4,29,18,KEY_Mn_minus,0,&S_KEY_Mnminus,0,9,9);
Calc_2button far BUT_Mn_3(m1,287,245+16,29,18,KEY_Mn_mul,0,&S_KEY_Mnmul,0,9,9);
Calc_2button far BUT_Mn_4(m1,287,261+16+4,29,18,KEY_Mn_div,0,&S_KEY_Mndiv,0,9,9);
Calc_2button far BUT_mem1(m0+m3+m4,320,245+16,15,18,KEY_M1,0,&S_KEY_mem1,0,11,11);
Calc_2button far BUT_mem2(m0+m3+m4,320,261+16+4,15,18,KEY_M2,0,&S_KEY_mem2,0,11,11);
Calc_2button far BUT_mem3(m0+m3+m4,339,245+16,15,18,KEY_M3,0,&S_KEY_mem3,0,11,11);
Calc_2button far BUT_mem4(m0+m3+m4,339,261+16+4,15,18,KEY_M4,0,&S_KEY_mem4,0,11,11);
Calc_2button far BUT_mem5(m0+m3+m4,358,245+16,15,18,KEY_M5,0,&S_KEY_mem5,0,11,11);
Calc_2button far BUT_mem6(m0+m3+m4,358,261+16+4,15,18,KEY_M6,0,&S_KEY_mem6,0,11,11);
Calc_2button far BUT_mem7(m0+m3+m4,377,245+16,15,18,KEY_M7,0,&S_KEY_mem7,0,11,11);
Calc_2button far BUT_mem8(m0+m3+m4,377,261+16+4,15,18,KEY_M8,0,&S_KEY_mem8,0,11,11);
Calc_2button far BUT_toggle(m0+m1,396,245+16,57,18,KEY_toggle,0,&S_KEY_toggle,0,9,9);
Calc_2button far BUT_swap(m0+m1,396,261+16+4,57,18,KEY_swap,0,&S_KEY_swap,0,9,9);
Calc_2button far BUT_ins(m0+m3,457,245+16,57,18,KEY_insert,0,&S_KEY_ins,0,9,9);
Calc_2button far BUT_cancel(m2+m3+m4+m5+m6+m7,457,261+16+4,57,18,KEY_esc,0,&S_KEY_cancel,0,9,9);
Calc_2button far BUT_del(m0+m3,518,245+16,57,18,KEY_del,0,&S_KEY_del,0,12,12);
Calc_2button far BUT_bs(m0+m3,518,261+16+4,57,18,KEY_bs,0,&S_KEY_bs,0,12,12);
Calc_2button far BUT_clear(m0+m1+m2+m3,580,245+16,55,38,KEY_clear,0,&S_KEY_clear,0,12,12);

Calc_2button far BUT_power(m0+m3,450,307,21,32,KEY_power,0,&S_POWER,0,12,0);
Calc_2button far BUT_7(m0+m3+m6,476,307,21,32,KEY_7,0,&S_7,0,9,0);
Calc_2button far BUT_8(m0+m3+m6,502,307,21,32,KEY_8,0,&S_8,0,9,0);
Calc_2button far BUT_9(m0+m3+m6,528,307,21,32,KEY_9,0,&S_9,0,9,0);
Calc_2button far BUT_minus(m0+m3,554,307,21,32,KEY_minus,0,&S_MINUS,0,12,0);
Calc_2button far BUT_exe(m0+m1+m2+m3+m6,580,307,55,32,KEY_exe,0,&S_KEY_exe,0,9,9);

Calc_2button far BUT_rem(m0+m3,450,350,21,32,KEY_rem,0,&S_REM,0,12,0);
Calc_2button far BUT_4(m0+m3+m6,476,350,21,32,KEY_4,0,&S_4,0,9,0);
Calc_2button far BUT_5(m0+m3+m6,502,350,21,32,KEY_5,0,&S_5,0,9,0);
Calc_2button far BUT_6(m0+m3+m6,528,350,21,32,KEY_6,0,&S_6,0,9,0);
Calc_2button far BUT_plus(m0+m3,554,350,21+8,32,KEY_plus,0,&S_PLUS,0,12,0);
Calc_2button far BUT_mul(m0+m3,580+8,350,21,32,KEY_mul,0,&S_MUL,0,12,0);
Calc_2button far BUT_div(m0+m3,606+8,350,21,32,KEY_div,0,&S_DIV,0,12,0);

Calc_2button far BUT_factor(m0+m3,450,393,21,32,KEY_factor,0,&S_FACTOR,0,9,0);
Calc_2button far BUT_1(m0+m3+m6,476,393,21,32,KEY_1,0,&S_1,0,9,0);
Calc_2button far BUT_2(m0+m3+m6,502,393,21,32,KEY_2,0,&S_2,0,9,0);
Calc_2button far BUT_3(m0+m3+m6,528,393,21,32,KEY_3,0,&S_3,0,9,0);
Calc_2button far BUT_0(m0+m3+m6,554,393,55,32,KEY_0,0,&S_0,0,9,0);
Calc_2button far BUT_coma(m0+m3,606+8,393,21,32,KEY_coma,0,&S_COMA,0,9,0);

Calc_2button far BUT_Ah(m0+m3,450,436,21,32,KEY_Ah,0,&S_Ah,0,9,0);
Calc_2button far BUT_Bh(m0+m3,476,436,21,32,KEY_Bh,0,&S_Bh,0,9,0);
Calc_2button far BUT_Ch(m0+m3,502,436,21,32,KEY_Ch,0,&S_Ch,0,9,0);
Calc_2button far BUT_Dh(m0+m3,528,436,21,32,KEY_Dh,0,&S_Dh,0,9,0);
Calc_2button far BUT_Eh(m0+m3,554,436,21,32,KEY_Eh,0,&S_Eh,0,9,0);
Calc_2button far BUT_Fh(m0+m3,580,436,21,32,KEY_Fh,0,&S_Fh,0,9,0);
Calc_2button far BUT_pi(m0+m3,606,436,29,32,KEY_pi,0,&S_PI,0,9,9);

Calc_2button far BUT_sin(m0+m3,5,307-4,25,18,KEY_sin,0,&S_KEY_sin,0,14,14);
Calc_2button far BUT_sh(m0+m3,5,328-5,25,18,KEY_sh,0,&S_KEY_sh,0,14,14);
Calc_2button far BUT_cos(m0+m3,35-2+1,307-4,25,18,KEY_cos,0,&S_KEY_cos,0,14,14);
Calc_2button far BUT_ch(m0+m3,35-2+1,328-5,25,18,KEY_ch,0,&S_KEY_ch,0,14,14);
Calc_2button far BUT_tan(m0+m3,65-4+2,307-4,25,18,KEY_tg,0,&S_KEY_tan,0,14,14);
Calc_2button far BUT_th(m0+m3,65-4+2,328-5,25,18,KEY_th,0,&S_KEY_th,0,14,14);
Calc_2button far BUT_ctg(m0+m3,95-6+3,307-4,25,18,KEY_ctg,0,&S_KEY_ctg,0,14,14);
Calc_2button far BUT_cth(m0+m3,95-6+3,328-5,25,18,KEY_cth,0,&S_KEY_cth,0,14,14);
Calc_2button far BUT_arcsin(m0+m3,125-8+4,307-4,43,18,KEY_arcsin,0,&S_KEY_arcsin,0,14,14);
Calc_2button far BUT_arsh(m0+m3,125-8+4,328-5,43,18,KEY_arsh,0,&S_KEY_arsh,0,14,14);
Calc_2button far BUT_arccos(m0+m3,173-10+5,307-4,43,18,KEY_arccos,0,&S_KEY_arccos,0,14,14);
Calc_2button far BUT_arch(m0+m3,173-10+5,328-5,43,18,KEY_arch,0,&S_KEY_arch,0,14,14);
Calc_2button far BUT_arctan(m0+m3,221-12+6,307-4,43,18,KEY_arctg,0,&S_KEY_arctan,0,14,14);
Calc_2button far BUT_arth(m0+m3,221-12+6,328-5,43,18,KEY_arth,0,&S_KEY_arth,0,14,14);
Calc_2button far BUT_arcctg(m0+m3,269-14+7,307-4,43,18,KEY_arcctg,0,&S_KEY_arcctg,0,14,14);
Calc_2button far BUT_arcth(m0+m3,269-14+7,328-5,43,18,KEY_arcth,0,&S_KEY_arcth,0,14,14);
Calc_2button far BUT_fix(m0+m1,317-16+9,307-4,25,18,KEY_fix,0,&S_KEY_fix,0,9,9);
Calc_2button far BUT_sci(m0+m1,317-16+9,328-5,25,18,KEY_sci,0,&S_KEY_sci,0,9,9);
Calc_2button far BUT_stay(m1,347-18+10,307-4,50,18,KEY_stay,0,&S_KEY_stay,0,12,12);
Calc_2button far BUT_more(m1+m2,347-18+10,328-5,50,18,KEY_more,0,&S_KEY_more,0,9,9);
Calc_2button far BUT_graph(m0+m1,402-20+11,307-4,50,18,KEY_graph,0,&S_KEY_graph,0,15,15);
Calc_2button far BUT_multitude(m0+m1+m3,402-20+11,328-5,50,18,KEY_multitude,0,&S_KEY_mul,0,15,15);

Calc_2button far BUT_A(m0+m3+m4+m5,5,353-8,22,18,KEY_A,0,&SYM_A,0,11,11);
Calc_2button far BUT_B(m0+m3+m4+m5,32-1,353-8,22,18,KEY_B,0,&SYM_B,0,11,11);
Calc_2button far BUT_C(m0+m3+m4+m5,59-2,353-8,22,18,KEY_C,0,&SYM_C,0,11,11);
Calc_2button far BUT_D(m0+m3+m4+m5,86-3,353-8,22,18,KEY_D,0,&SYM_D,0,11,11);
Calc_2button far BUT_E(m0+m3+m4+m5,113-4,353-8,22,18,KEY_E,0,&SYM_E,0,11,11);
Calc_2button far BUT_F(m0+m3+m4+m5,140-5,353-8,22,18,KEY_F,0,&SYM_F,0,11,11);
Calc_2button far BUT_G(m0+m3+m4+m5,167-6,353-8,22,18,KEY_G,0,&SYM_G,0,11,11);
Calc_2button far BUT_H(m0+m3+m4+m5,194-7,353-8,22,18,KEY_H,0,&SYM_H,0,11,11);
Calc_2button far BUT_I(m0+m3+m4+m5,221-8,353-8,22,18,KEY_I,0,&SYM_I,0,11,11);
Calc_2button far BUT_J(m0+m3+m4+m5,248-9,353-8,22,18,KEY_J,0,&SYM_J,0,11,11);
Calc_2button far BUT_K(m0+m3+m4+m5,275-10,353-8,22,18,KEY_K,0,&SYM_K,0,11,11);
Calc_2button far BUT_L(m0+m3+m4+m5,302-11,353-8,22,18,KEY_L,0,&SYM_L,0,11,11);
Calc_2button far BUT_M(m0+m3+m4+m5,329-12,353-8,22,18,KEY_M,0,&SYM_M,0,11,11);
Calc_2button far BUT_N(m0+m3+m4+m5,5,374-9,22,18,KEY_N,0,&SYM_N,0,11,11);
Calc_2button far BUT_O(m0+m3+m4+m5,32-1,374-9,22,18,KEY_O,0,&SYM_O,0,11,11);
Calc_2button far BUT_P(m0+m3+m4+m5,59-2,374-9,22,18,KEY_P,0,&SYM_P,0,11,11);
Calc_2button far BUT_Q(m0+m3+m4+m5,86-3,374-9,22,18,KEY_Q,0,&SYM_Q,0,11,11);
Calc_2button far BUT_R(m0+m3+m4+m5,113-4,374-9,22,18,KEY_R,0,&SYM_R,0,11,11);
Calc_2button far BUT_S(m0+m3+m4+m5,140-5,374-9,22,18,KEY_S,0,&SYM_S,0,11,11);
Calc_2button far BUT_T(m0+m3+m4+m5,167-6,374-9,22,18,KEY_T,0,&SYM_T,0,11,11);
Calc_2button far BUT_U(m0+m3+m4+m5,194-7,374-9,22,18,KEY_U,0,&SYM_U,0,11,11);
Calc_2button far BUT_V(m0+m3+m4+m5,221-8,374-9,22,18,KEY_V,0,&SYM_V,0,11,11);
Calc_2button far BUT_W(m0+m3+m4+m5,248-9,374-9,22,18,KEY_W,0,&SYM_W,0,11,11);
Calc_2button far BUT_X(m0+m3+m4+m5,275-10,374-9,22,18,KEY_X,0,&SYM_X,0,11,11);
Calc_2button far BUT_Y(m0+m3+m4+m5,302-11,374-9,22,18,KEY_Y,0,&SYM_Y,0,11,11);
Calc_2button far BUT_Z(m0+m3+m4+m5,329-12,374-9,22,18,KEY_Z,0,&SYM_Z,0,11,11);
Calc_2button far BUT_num(m0+m3+m4,343,353-8,22,18,KEY_MUL_LEN,0,&S_KEY_MUL_LEN,0,9,9);
Calc_2button far BUT_index(m0+m3,343,374-9,22,18,KEY_INDEX,0,&S_KEY_INDEX,0,9,9);
Calc_2button far BUT_mparensl(m0+m3,370,353-8,21,18,KEY_leftmp,0,&S_KEY_leftmp,0,12,12);
Calc_2button far BUT_mparensr(m0+m3,370,374-9,21,18,KEY_rightmp,0,&S_KEY_rightmp,0,12,12);
Calc_2button far BUT_sparensl(m0+m3,396,353-8,21,18,KEY_leftsp,0,&S_KEY_leftsp,0,12,12);
Calc_2button far BUT_sparensr(m0+m3,396,374-9,21,18,KEY_rightsp,0,&S_KEY_rightsp,0,12,12);
Calc_2button far BUT_rparensl(m0+m3,422,353-8,21,18,KEY_leftrp,0,&S_KEY_leftrp,0,12,12);
Calc_2button far BUT_rparensr(m0+m3,422,374-9,21,18,KEY_rightrp,0,&S_KEY_rightrp,0,12,12);

Calc_2button far BUT_GR(m0+m3,5,387,24,18,KEY_GREATER,0,&S_KEY_GR,0,12,12);
Calc_2button far BUT_LS(m0+m3,5,407,24,18,KEY_LESS,0,&S_KEY_LS,0,12,12);
Calc_2button far BUT_GR_EQ(m0+m3,33,387,24,18,KEY_GREATER_EQ,0,&S_KEY_GREQ,0,12,12);
Calc_2button far BUT_LS_EQ(m0+m3,33,407,24,18,KEY_LESS_EQ,0,&S_KEY_LSEQ,0,12,12);
Calc_2button far BUT_EQ(m0+m3,61,387,24,18,KEY_EQ,0,&S_KEY_EQ,0,12,12);
Calc_2button far BUT_NEQ(m0+m3,61,407,24,18,KEY_NOT_EQ,0,&S_KEY_NEQ,0,12,12);
Calc_2button far BUT_ln(m0+m3,89,387,25,18,KEY_ln,0,&S_KEY_ln,0,14,14);
Calc_2button far BUT_lg(m0+m3,89,407,25,18,KEY_lg,0,&S_KEY_lg,0,14,14);
Calc_2button far BUT_exp(m0+m3,118,387,25,18,KEY_exp,0,&S_KEY_exp,0,14,14);
Calc_2button far BUT_e(m0+m3,118,407,25,18,KEY_e,0,&S_KEY_e,0,14,14);
Calc_2button far BUT_log(m0+m3,146,387,25,18,KEY_log,0,&S_KEY_log,0,14,14);
Calc_2button far BUT_sgn(m0+m3,146,407,25,18,KEY_sgn,0,&S_KEY_sgn,0,14,14);
Calc_2button far BUT_sum(m0+m3,194,387,24,32,KEY_SUM,0,&S_SUMMA,0,9,9);
Calc_2button far BUT_ROOT1(m0+m3,223,399-12,20,32,KEY_ROOT1,0,&S_ROOT1,0,12,0);
Calc_2button far BUT_ROOT2(m0+m3,248,399-12,20,32,KEY_ROOT2,0,&S_ROOT2,0,12,0);
Calc_2button far BUT_ROOT3(m0+m3,273,399-12,20,32,KEY_ROOT3,0,&S_ROOT3,0,12,0);
Calc_2button far BUT_ROOT4(m0+m3,298,399-12,20,32,KEY_ROOT4,0,&S_ROOT4,0,12,0);
Calc_2button far BUT_ROOT5(m0+m3,323,399-12,20,32,KEY_ROOT5,0,&S_ROOT5,0,12,0);
Calc_2button far BUT_ROOT6(m0+m3,348,399-12,20,32,KEY_ROOT6,0,&S_ROOT6,0,12,0);
Calc_2button far BUT_ROOT7(m0+m3,373,399-12,20,32,KEY_ROOT7,0,&S_ROOT7,0,12,0);
Calc_2button far BUT_ROOT8(m0+m3,398,399-12,20,32,KEY_ROOT8,0,&S_ROOT8,0,12,0);
Calc_2button far BUT_ROOT9(m0+m3,423,399-12,20,32,KEY_ROOT9,0,&S_ROOT9,0,12,0);

Calc_2button far BUT_and(m0+m3,5,429,25,18,KEY_and,0,&S_KEY_and,0,12,12);
Calc_2button far BUT_or(m0+m3,5,449,25,18,KEY_or,0,&S_KEY_or,0,12,12);
Calc_2button far BUT_xor(m0+m3,34,429,25,18,KEY_xor,0,&S_KEY_xor,0,12,12);
Calc_2button far BUT_not(m0+m3,34,449,25,18,KEY_not,0,&S_KEY_not,0,12,12);
Calc_2button far BUT_xscale(m0+m3,63,429,41,18,KEY_xscale,0,&S_KEY_xscale,0,9,9);
Calc_2button far BUT_yscale(m0+m3,63,449,41,18,KEY_yscale,0,&S_KEY_yscale,0,9,9);
Calc_2button far BUT_ans(m0+m3,108,429,25,18,KEY_ans,0,&S_KEY_ans,0,9,9);
Calc_2button far BUT_rnd(m0+m3,108,449,25,18,KEY_rnd,0,&S_KEY_rnd,0,9,9);
Calc_2button far BUT_multi(m0+m3,194,423,24,32,KEY_MUL,0,&S_MULLA,0,9,9);
Calc_2button far BUT_mul_elem(m0+m3,223,423,22,32,KEY_MUL_ELEM,0,&S_MUL_ELEM,0,9,0);
Calc_2button far BUT_POW1(m0+m3,250,423,17,32,KEY_POW1,0,&S_POW1,0,12,0);
Calc_2button far BUT_POW2(m0+m3,272,423,17,32,KEY_POW2,0,&S_POW2,0,12,0);
Calc_2button far BUT_POW3(m0+m3,294,423,17,32,KEY_POW3,0,&S_POW3,0,12,0);
Calc_2button far BUT_POW4(m0+m3,316,423,17,32,KEY_POW4,0,&S_POW4,0,12,0);
Calc_2button far BUT_POW5(m0+m3,338,423,17,32,KEY_POW5,0,&S_POW5,0,12,0);
Calc_2button far BUT_POW6(m0+m3,360,423,17,32,KEY_POW6,0,&S_POW6,0,12,0);
Calc_2button far BUT_POW7(m0+m3,382,423,17,32,KEY_POW7,0,&S_POW7,0,12,0);
Calc_2button far BUT_POW8(m0+m3,404,423,17,32,KEY_POW8,0,&S_POW8,0,12,0);
Calc_2button far BUT_POW9(m0+m3,426,423,17,32,KEY_POW9,0,&S_POW9,0,12,0);

Calc_2button far BUT_exit(m0+m1+m2+m3+m4+m5+m6+m7,585,5,50,18,KEY_exit,0,&S_KEY_exit,0,15,15);
Calc_2button far BUT_reset(m0+m1+m2+m3+m4+m5+m6+m7,585,28,50,18,KEY_reset,0,&S_KEY_reset,0,15,15);
static Calc_2button BUT_save(m0+m1,585,51,50,18,KEY_save,0,&S_KEY_save,0,15,15);
Calc_2button far BUT_load(m0+m1+m2+m3+m4+m5+m6,585,74,50,18,KEY_load,0,&S_KEY_load,0,15,15);
Calc_2button far BUT_help(m0+m1+m2+m3+m4+m5+m6,585,97,50,18,KEY_help,0,&S_KEY_help,0,15,15);

Calc_2button far BUT_helplock(m0+m1+m2+m3+m4+m5+m6,585,120,18,18,KEY_helplock,0,&SYM_QUESTION,0,15,15,7,1);
Calc_2button far BUT_actlock(m0+m1+m2+m3+m4+m5+m6,402,233,16,16,KEY_actlock,0,&SYM_MONKEY,0,15,15,7,1);


Calc_2button *BUTTON_ARRAY[166]={
		&BUT_leftcur,&BUT_rightcur,&BUT_leftqcur,&BUT_rightqcur,&BUT_leftend,&BUT_rightend,&BUT_bufcopy,&BUT_bufcopydel,&BUT_bufinsert,&BUT_savenumto,&BUT_savestrto,&BUT_readnum,&BUT_readstr,&BUT_addtomul,&BUT_addvartomul,&BUT_M1_1,
		&BUT_M1_2,&BUT_M1_3,&BUT_M1_4,&BUT_Mn_1,&BUT_Mn_2,&BUT_Mn_3,&BUT_Mn_4,&BUT_mem1,&BUT_mem2,&BUT_mem3,&BUT_mem4,&BUT_mem5,&BUT_mem6,&BUT_mem7,&BUT_mem8,&BUT_toggle,
		&BUT_swap,&BUT_ins,&BUT_cancel,&BUT_0,&BUT_1,&BUT_2,&BUT_3,&BUT_4,&BUT_5,&BUT_6,&BUT_7,&BUT_8,&BUT_9,&BUT_minus,&BUT_exe,&BUT_rem,
		&BUT_plus,&BUT_mul,&BUT_div,&BUT_factor,&BUT_coma,&BUT_del,&BUT_bs,&BUT_clear,&BUT_power,&BUT_Ah,&BUT_Bh,&BUT_Ch,&BUT_Dh,&BUT_Eh,&BUT_Fh,&BUT_pi,
		&BUT_sin,&BUT_sh,&BUT_cos,&BUT_ch,&BUT_tan,&BUT_th,&BUT_ctg,&BUT_cth,&BUT_arcsin,&BUT_arsh,&BUT_arccos,&BUT_arch,&BUT_arctan,&BUT_arth,&BUT_arcctg,&BUT_arcth,
		&BUT_fix,&BUT_sci,&BUT_stay,&BUT_more,&BUT_graph,&BUT_multitude,&BUT_A,&BUT_B,&BUT_C,&BUT_D,&BUT_E,&BUT_F,&BUT_G,&BUT_H,&BUT_I,&BUT_J,
		&BUT_K,&BUT_L,&BUT_M,&BUT_N,&BUT_O,&BUT_P,&BUT_Q,&BUT_R,&BUT_S,&BUT_T,&BUT_U,&BUT_V,&BUT_W,&BUT_X,&BUT_Y,&BUT_Z,
		&BUT_num,&BUT_index,&BUT_mparensl,&BUT_mparensr,&BUT_sparensl,&BUT_sparensr,&BUT_rparensl,&BUT_rparensr,&BUT_GR,&BUT_LS,&BUT_GR_EQ,&BUT_LS_EQ,&BUT_EQ,&BUT_NEQ,&BUT_ln,&BUT_lg,
		&BUT_exp,&BUT_e,&BUT_log,&BUT_sgn,&BUT_sum,&BUT_ROOT1,&BUT_ROOT2,&BUT_ROOT3,&BUT_ROOT4,&BUT_ROOT5,&BUT_ROOT6,&BUT_ROOT7,&BUT_ROOT8,&BUT_ROOT9,&BUT_and,&BUT_or,
		&BUT_xor,&BUT_not,&BUT_xscale,&BUT_yscale,&BUT_ans,&BUT_rnd,&BUT_multi,&BUT_mul_elem,&BUT_POW1,&BUT_POW2,&BUT_POW3,&BUT_POW4,&BUT_POW5,&BUT_POW6,&BUT_POW7,&BUT_POW8,
		&BUT_POW9,&BUT_exit,&BUT_reset,&BUT_save,&BUT_load,&BUT_help};

#define BUT_INDEX_0 0x23
#define BUT_INDEX_9 0x2c
#define BUT_INDEX_A 0x56
#define BUT_INDEX_Z 0x6f
#define BUT_INDEX_LAST 0xa5

void drawallkeys(void)
{
for(int i=0;i<=BUT_INDEX_LAST;i++)
	BUTTON_ARRAY[i]->draw();

BUT_helplock.draw();
BUT_actlock.draw();
hidemouse();
int xc=320+11,yc=210+16;
Putsymbol(asciisymboltable['è'],xc,yc,11,7);
xc+=8;
Putsymbol(asciisymboltable['Ä'],xc,yc,11,7);
xc+=8;
Putsymbol(asciisymboltable['å'],xc,yc,11,7);
xc+=8;
Putsymbol(asciisymboltable['ü'],xc,yc,11,7);
xc+=8;
Putsymbol(asciisymboltable['í'],xc,yc,11,7);
xc+=8;
Putsymbol(asciisymboltable['ú'],xc,yc,11,7);
mygr.drawxline(326,383,227+16,11);
mygr.drawyline(228+16,243+16,326,11);
mygr.drawyline(228+16,243+16,383,11);
showmouse();
}

int last_setstate_mode,last_setstate_fl;

void setstate(int mode,int fl=0)
{
last_setstate_fl=fl;
last_setstate_mode=mode;
for(int i=0;i<=BUT_INDEX_LAST;i++)
	{
	if(BUTTON_ARRAY[i]==&BUT_more)
		if(fl==2) {BUT_more.deactivate();continue;}
	if(BUTTON_ARRAY[i]==&BUT_num)
		if(fl==1) {BUT_num.deactivate();continue;}
	if(BUTTON_ARRAY[i]==&BUT_bufcopy)
		if((mode==0 || mode==3) && !indic.isedit)
			{BUT_bufcopy.deactivate();continue;}
	if(BUTTON_ARRAY[i]==&BUT_bufcopydel)
		if((mode==0 || mode==3) && !indic.isedit)
			{BUT_bufcopydel.deactivate();continue;}
	BUTTON_ARRAY[i]->setactivities(mode);
	}

}

