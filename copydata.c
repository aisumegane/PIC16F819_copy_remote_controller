/*
 * File:   copydata.c
 * Author: �XMEGANE
 *
 * Created on 2024/04/14, 23:38
 */

#include <xc.h>

#include "grobal_macro.h"
#include "interrupt.h"
#include "grobal_function.h"

#include "copydata.h"

/* 40byte�����A���̈�m�ۂł��Ȃ��̂ŕ����� */
unsigned char copydata_led_data_ary0[40] = {0}; /* LED�M���ۑ��p�z�� */
unsigned char copydata_led_data_ary1[40] = {0}; /* LED�M���ۑ��p�z�� */
unsigned char copydata_led_data_ary2[40] = {0}; /* LED�M���ۑ��p�z�� */
unsigned char copydata_led_data_ary3[40] = {0}; /* LED�M���ۑ��p�z�� */
unsigned char copydata_led_data_ary4[40] = {0}; /* LED�M���ۑ��p�z�� */

unsigned char copydata_copy_comp = CLEAR;   /* �R�s�[�����̗v���I�Ȃ��� */
unsigned char copydata_copy_ovf_comp = CLEAR;   /* �R�s�[��timer1��OVF(���̐M���Ȃ�)�ɂ��I�� */

unsigned char copydata_ex_interrupt_go_flag = CLEAR;

static unsigned char led_data_ary_index = 0;    /* 0?4 */
static unsigned char led_data_copy_fin = CLEAR;


static unsigned char led_data_index = 0;    /* �ő�200 */

void copydata_main(void);
void copydata_1byte_copy(void);



void copydata_main(void)
{   /* �O�������݂����������̂݃R�s�[���s */
    if( (copydata_ex_interrupt_go_flag == SET) && (copydata_copy_comp == CLEAR) )    /* ���e�̃G�b�W���o�O��ƐM���S�����]���� */
    {
        copydata_1byte_copy();
        copydata_ex_interrupt_go_flag = CLEAR;
    }
}

void copydata_1byte_copy(void)
{
    if(led_data_ary_index == 0)
    {
        copydata_led_data_ary0[led_data_index] = TMR1L;  /* 256��char�z��Ȃ̂�TMR1L���� */
        if(led_data_index == 39)
        {
            led_data_ary_index = 1;
            led_data_index = 0;
        }
        else
        {
            led_data_index++;
        }
    }
    else if(led_data_ary_index == 1)
    {
        copydata_led_data_ary1[led_data_index] = TMR1L;  /* 256��char�z��Ȃ̂�TMR1L���� */
        if(led_data_index == 39)
        {
            led_data_ary_index = 2;
            led_data_index = 0;
        }
        else
        {
            led_data_index++;
        }
    }
    else if(led_data_ary_index == 2)
    {
        copydata_led_data_ary2[led_data_index] = TMR1L;  /* 256��char�z��Ȃ̂�TMR1L���� */
        if(led_data_index == 39)
        {
            led_data_ary_index = 3;
            led_data_index = 0;
        }
        else
        {
            led_data_index++;
        }
    }
    else if(led_data_ary_index == 3)
    {
        copydata_led_data_ary3[led_data_index] = TMR1L;  /* 256��char�z��Ȃ̂�TMR1L���� */
        if(led_data_index == 39)
        {
            led_data_ary_index = 4;
            led_data_index = 0;
        }
        else
        {
            led_data_index++;
        }
    }
    else if(led_data_ary_index == 4)
    {
        copydata_led_data_ary4[led_data_index] = TMR1L;  /* 256��char�z��Ȃ̂�TMR1L���� */
        if(led_data_index == 39)
        {
            led_data_ary_index = 0;
            led_data_index = 0;
            copydata_copy_comp = SET;    /* �v200byte�ǂݎ�芮�� */
        }
        else
        {
            led_data_index++;
        }
    }
}