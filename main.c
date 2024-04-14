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
#include "sequence.h"
#include "peripheral_out.h"




void main_init(void);
void maintask(void);

void main(void) {
    main_init();
    gf_enable_interrupt();
    gf_timer1_start();
    
    while(1)
    {
        sequence_main();    
        maintask();
    }   
}

void main_init(void)
{
    /* PIC16F819 �n�[�h�E�F�A�ݒ� */
    pic819_register_setup();
    
    peripheral_in_init();
    peripheral_out_init();
}

void maintask(void)
{
   peripheral_in_main();       /* �|�[�g�̓��͔�����s�� */
   peripheral_out_main();      /* �|�[�g�̏o�͔�����s�� */
}