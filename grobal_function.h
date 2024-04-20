/*
 * File:   interrupt.c
 * Author: •XMEGANE
 *
 * Created on 2024/03/27, 23:38
 */

#ifndef GROBAL_FUNCTION_H
#define	GROBAL_FUNCTION_H

#ifdef	__cplusplus
extern "C" {
#endif


extern void gf_enable_interrupt(void);    /*Š„‚İ‹–‰ÂŠÖ”*/
extern void gf_disable_interrupt(void);   /*Š„‚İ‹Ö~ŠÖ”*/
extern void gf_timer1_start(void);        /*timer1 “®ìŠJnŠÖ”*/
extern void gf_timer1_stop(void);         /*timer1 “®ì’â~ŠÖ”*/
extern void gf_timer2_start(void);
extern void gf_timer2_stop(void);
extern void gf_option_integ_edge_select(unsigned int state);

#ifdef	__cplusplus
}
#endif

#endif	/* GROBAL_FUNCTION_H */

