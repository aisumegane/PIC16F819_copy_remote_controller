/*
 * File:   interrupt.c
 * Author: 氷MEGANE
 *
 * Created on 2024/03/27, 23:38
 */

/* ソースファイルまたいで使うレジスタ関連の関数はここで定義 */
/* よく使うもの以外はレジスタ直打ちにする */

/*ソース識別記号：gf*/

#include <xc.h>
#include "grobal_macro.h"
#include "grobal_function.h"

void gf_enable_interrupt(void);    /*割込み許可関数*/
void gf_disable_interrupt(void);   /*割込み禁止関数*/
void gf_timer1_start(void);        /*timer1 動作開始関数*/
void gf_timer1_stop(void);         /*timer1 動作停止関数*/



void gf_enable_interrupt(void)
{   /*interrup.cでは使えない(リエントラント?)*/
    INTCONbits.GIE = SET;         // グローバル割り込み許可
    INTCONbits.PEIE = SET;        // リフェラル割込み許可 
}

void gf_disable_interrupt(void)
{   /*interrupt.cでは使えない(リエントラント?)*/
    INTCONbits.GIE = CLEAR;         // グローバル割り込み禁止
    INTCONbits.PEIE = CLEAR;        // リフェラル割込み禁止
}

void gf_timer1_start(void)
{   /*初回起動で割込み要求等がないか確認すること*/
    T1CONbits.TMR1ON = SET;
}

void gf_timer1_stop(void)
{   /*初回起動で割込み要求等がないか確認すること*/
    T1CONbits.TMR1ON = CLEAR;
}