/*
 * File:   interrupt.c
 * Author: �XMEGANE
 * Mid-Range 8-bit MCUs PIC16F819
 * Created on 2024/03/27, 23:38
 */

#include "config_bits.h"
#include <xc.h>
#include "grobal_macro.h"
#include "grobal_function.h"
#include "register_setup.h"         /* ���W�X�^�ݒ� */
#include "interrupt.h"
#include "peripheral_in.h"
#include "peripheral_out.h"
#include "copydata.h"
#include "senddata.h"

#include "main.h"


unsigned char sequence_num = 0;

void main_init(void);
void main_task(void);

void main(void) {
    main_init();
    gf_enable_interrupt();
    gf_timer1_start();
    gf_timer2_start();
    
    while(1)
    {
        main_task();
    }   
}

void main_init(void)
{
    /* PIC16F819 �n�[�h�E�F�A�ݒ� */
    pic819_register_setup();
    
    peripheral_in_init();
    peripheral_out_init();
    
    sequence_num = SEQUENCE_MAIN;
}

void main_task(void)
{
   switch(sequence_num){
        case SEQUENCE_MAIN:
            peripheral_in_main();       /* �|�[�g�̓��� */
            peripheral_out_main();      /* �|�[�g�̏o�� */
#if 0
            if(copysw_state == SET)
            {
                peripheral_in_init();   /* 2��A���ŏ���������Ȃ��悤�� */
                sequence_num = SEQUENCE_COPY_DATA;   
            }
            else if(sendsw_state == SET)
            {
                peripheral_in_init();   /* 2��A���ŏ���������Ȃ��悤�� */
                sequence_num = SEQUENCE_SEND_DATA;   
            }
            else
            {
                ;
            }
#endif       
            break;
            
       case SEQUENCE_COPY_DATA:
            /* external interrupt �J�n */
            /* if external interrupt ���m �� timer1 ON */ /* 2��ڈȍ~��ON��ON�ŏ㏑�����Ă��ς��Ȃ� */
           
            //copydata_main();
            
            if(copydata_copy_comp == SET)
            {
                /* external interrupt ��~ */
                /* timer1 ON */
                /* tmr1H/L�����Z�b�g ��TMR1H�͖��g�p */
                
                copydata_copy_comp = CLEAR;
                sequence_num = SEQUENCE_MAIN;
            }
            break;
            
        case SEQUENCE_SEND_DATA:
            senddata_main();
            
            if(senddata_send_comp == SET)
            {
                senddata_send_comp = CLEAR;
                sequence_num = SEQUENCE_MAIN;
            }
            break;
            
       default:
           break;
    }
}