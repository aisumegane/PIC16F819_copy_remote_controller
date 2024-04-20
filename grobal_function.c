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
#include <pic16f819.h>
#include "grobal_macro.h"
#include "grobal_function.h"


void gf_enable_interrupt(void);    /*割込み許可関数*/
void gf_disable_interrupt(void);   /*割込み禁止関数*/
void gf_timer1_start(void);        /*timer1 動作開始関数*/
void gf_timer1_stop(void);         /*timer1 動作停止関数*/
void gf_timer2_start(void);
void gf_timer2_stop(void);

void gf_option_integ_edge_select(unsigned int state);


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

void gf_timer2_start()
{
    T2CONbits.TMR2ON = SET;
}

void gf_timer2_stop()
{
    T2CONbits.TMR2ON = CLEAR;
}

void gf_option_integ_edge_select(unsigned int state)
{
    if(state == SET)
    {
        OPTION_REGbits.INTEDG  = SET;      /* RB0/INT pin Interrupt Edge Select bit (1:rising edge / 0:falling edge) */ /* 初回は信号待ち(0→1待ち)なので立ち上がりエッジ */
    }
    else /*if(state == CLEAR)*/
    {
        OPTION_REGbits.INTEDG  = CLEAR;
    }
}