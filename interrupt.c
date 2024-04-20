/*
 * File:   interrupt.c
 * Author: 氷MEGANE
 *
 * Created on 2024/03/27, 23:38
 */

#include <xc.h>

#include "grobal_macro.h"
#include "interrupt.h"
#include "grobal_function.h"
#include "copydata.h"


unsigned int cnt = 0;
unsigned char interrupt__maintask_go = CLEAR;

static void interrupt isr(void);
static void interrupt_timer0_tmr0if(void);
static void interrupt_timer1_tmr1if(void);
static void interrupt_timer1_ccp1if(void);
static void interrupt_timer2_tmr2if(void);
static void interrupt_inte(void);


static void interrupt isr(void)
{   /*割込みベクタは1本、全部ここに呼ばれる*/   /*datasheet P.98*/
    
    /*割込みされた時点で他の割込み禁止*/
    INTCONbits.GIE = CLEAR;         // グローバル割り込み禁止
    INTCONbits.PEIE = CLEAR;        // リフェラル割込み禁止
    
    
    if(INTCONbits.TMR0IF == SET)
    {
        interrupt_timer0_tmr0if();
        INTCONbits.TMR0IF = CLEAR;
    }
    if(PIR1bits.TMR1IF == SET)  /*timer1オーバーフロー割込み*/
    {
        interrupt_timer1_tmr1if();
        PIR1bits.TMR1IF = CLEAR;
    }
    if(PIR1bits.CCP1IF == SET)
    {
        interrupt_timer1_ccp1if();
        PIR1bits.CCP1IF = CLEAR;
    }
    if(INTCONbits.INTF == SET)
    {
        interrupt_inte();
        INTCONbits.INTF = CLEAR;
    }
    if(PIR1bits.TMR2IF == SET)
    {
        interrupt_timer2_tmr2if();
        PIR1bits.TMR2IF = CLEAR;
    }
    
    INTCONbits.GIE = SET;         // グローバル割り込み許可
    INTCONbits.PEIE = SET;        // リフェラル割込み許可
}

static void interrupt_timer0_tmr0if(void)
{   
    if (cnt == 10)
    {
        cnt = 0;            // オーバーフローカウンタをリセット
    }
    TMR0 = 160;            // Timer0 を再設定
    cnt++;                  // オーバーフローカウンタをインクリ
}

static void interrupt_timer1_tmr1if(void)
{
    if(RA1 == CLEAR)
    {
        RA1 = SET;
    }
    else
    {
        RA1 = CLEAR;
    }
}

static void interrupt_timer1_ccp1if(void)
{
    ;
}

static void interrupt_timer2_tmr2if(void)
{
    ;
}

static void interrupt_inte(void)
{
    unsigned int edge_select_now;
    
    edge_select_now = OPTION_REGbits.INTEDG; /* リードは基本どこでもいいかな */
    
    edge_select_now =~edge_select_now;  /* 現在のエッジ選択と反転 */
    gf_option_integ_edge_select(edge_select_now);
    
    copydata_ex_interrupt_go_flag = SET;
}