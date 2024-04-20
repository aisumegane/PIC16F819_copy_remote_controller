/*
 * File:   copydata.c
 * Author: 氷MEGANE
 *
 * Created on 2024/04/14, 23:38
 */

#include <xc.h>

#include "grobal_macro.h"
#include "interrupt.h"
#include "grobal_function.h"

#include "copydata.h"

/* 40byteしか連続領域確保できないので分ける */
unsigned char copydata_led_data_ary0[40] = {0}; /* LED信号保存用配列 */
unsigned char copydata_led_data_ary1[40] = {0}; /* LED信号保存用配列 */
unsigned char copydata_led_data_ary2[40] = {0}; /* LED信号保存用配列 */
unsigned char copydata_led_data_ary3[40] = {0}; /* LED信号保存用配列 */
unsigned char copydata_led_data_ary4[40] = {0}; /* LED信号保存用配列 */

unsigned char copydata_copy_comp = CLEAR;   /* コピー処理の要求的なもの */
unsigned char copydata_copy_ovf_comp = CLEAR;   /* コピーがtimer1のOVF(次の信号なし)により終了 */

unsigned char copydata_ex_interrupt_go_flag = CLEAR;

static unsigned char led_data_ary_index = 0;    /* 0?4 */
static unsigned char led_data_copy_fin = CLEAR;


static unsigned char led_data_index = 0;    /* 最大200 */

void copydata_main(void);
void copydata_1byte_copy(void);



void copydata_main(void)
{   /* 外部割込みがあった時のみコピー実行 */
    if( (copydata_ex_interrupt_go_flag == SET) && (copydata_copy_comp == CLEAR) )    /* 初弾のエッジがバグると信号全部反転する */
    {
        copydata_1byte_copy();
        copydata_ex_interrupt_go_flag = CLEAR;
    }
}

void copydata_1byte_copy(void)
{
    if(led_data_ary_index == 0)
    {
        copydata_led_data_ary0[led_data_index] = TMR1L;  /* 256のchar配列なのでTMR1Lだけ */
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
        copydata_led_data_ary1[led_data_index] = TMR1L;  /* 256のchar配列なのでTMR1Lだけ */
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
        copydata_led_data_ary2[led_data_index] = TMR1L;  /* 256のchar配列なのでTMR1Lだけ */
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
        copydata_led_data_ary3[led_data_index] = TMR1L;  /* 256のchar配列なのでTMR1Lだけ */
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
        copydata_led_data_ary4[led_data_index] = TMR1L;  /* 256のchar配列なのでTMR1Lだけ */
        if(led_data_index == 39)
        {
            led_data_ary_index = 0;
            led_data_index = 0;
            copydata_copy_comp = SET;    /* 計200byte読み取り完了 */
        }
        else
        {
            led_data_index++;
        }
    }
}