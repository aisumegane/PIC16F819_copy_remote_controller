/*
 * File:   interrupt.c
 * Author: 氷MEGANE
 *
 * Created on 2024/03/27, 23:38
 */

#ifndef GROBAL_FUNCTION_H
#define	GROBAL_FUNCTION_H

#ifdef	__cplusplus
extern "C" {
#endif


extern void gf_enable_interrupt(void);    /*割込み許可関数*/
extern void gf_disable_interrupt(void);   /*割込み禁止関数*/
extern void gf_timer1_start(void);        /*timer1 動作開始関数*/
extern void gf_timer1_stop(void);         /*timer1 動作停止関数*/
extern void gf_timer2_start(void);
extern void gf_timer2_stop(void);
extern void gf_option_integ_edge_select(unsigned int state);

#ifdef	__cplusplus
}
#endif

#endif	/* GROBAL_FUNCTION_H */

