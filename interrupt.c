/*
 * File:   interrupt.c
 * Author: �XMEGANE
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
{   /*�����݃x�N�^��1�{�A�S�������ɌĂ΂��*/   /*datasheet P.98*/
    
    /*�����݂��ꂽ���_�ő��̊����݋֎~*/
    INTCONbits.GIE = CLEAR;         // �O���[�o�����荞�݋֎~
    INTCONbits.PEIE = CLEAR;        // ���t�F���������݋֎~
    
    
    if(INTCONbits.TMR0IF == SET)
    {
        interrupt_timer0_tmr0if();
        INTCONbits.TMR0IF = CLEAR;
    }
    if(PIR1bits.TMR1IF == SET)  /*timer1�I�[�o�[�t���[������*/
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
    
    INTCONbits.GIE = SET;         // �O���[�o�����荞�݋���
    INTCONbits.PEIE = SET;        // ���t�F���������݋���
}

static void interrupt_timer0_tmr0if(void)
{   
    if (cnt == 10)
    {
        cnt = 0;            // �I�[�o�[�t���[�J�E���^�����Z�b�g
    }
    TMR0 = 160;            // Timer0 ���Đݒ�
    cnt++;                  // �I�[�o�[�t���[�J�E���^���C���N��
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
    
    edge_select_now = OPTION_REGbits.INTEDG; /* ���[�h�͊�{�ǂ��ł��������� */
    
    edge_select_now =~edge_select_now;  /* ���݂̃G�b�W�I���Ɣ��] */
    gf_option_integ_edge_select(edge_select_now);
    
    copydata_ex_interrupt_go_flag = SET;
}