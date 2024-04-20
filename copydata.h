/*
 * File:   interrupt.c
 * Author: 氷MEGANE
 *
 * Created on 2024/04/14, 23:38
 */

#ifndef COPYDATA_H
#define	COPYDATA_H

#ifdef	__cplusplus
extern "C" {
#endif

extern unsigned char copydata_copy_comp;    /* コピー処理完了フラグ */
extern unsigned char copydata_ex_interrupt_go_flag;    /*割込み用*/

extern void copydata_main(void);

#ifdef	__cplusplus
}
#endif

#endif	/* COPYDATA_H */

