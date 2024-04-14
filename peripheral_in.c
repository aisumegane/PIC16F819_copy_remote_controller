/*
 * File:   register_setup.c
 * Author: �XMEGANE
 *
 * Created on 2024/04/11, 21:17
 */


#include <xc.h>

/*header*/
#include "grobal_macro.h"
#include "peripheral_in.h"

#define SW_ACTIVE      0
#define SW_INACTIVE    1

#define SW_CHATTER_PREV_CNT     10

const unsigned char sw_chatter_prev_cnt = 10;

/* SW1:�M���R�s�[�X�C�b�` */
static unsigned char copysw_port_data;
static unsigned char copysw_state_buffer;
unsigned char copysw_state;
static unsigned char copysw_chatter_prev_cnt;

/* SW2�F�M�����M�X�C�b�` */
static unsigned char sendsw_port_data;
static unsigned char sendsw_state_buffer;
unsigned char sendsw_state;
static unsigned char sendsw_chatter_prev_cnt;

/* SW3�F�d���X�C�b�` */
static unsigned char powersw_port_data;
static unsigned char powersw_state_buffer;
unsigned char powersw_state;
static unsigned char powersw_chatter_prev_cnt;

void peripheral_in_init(void);
void peripheral_in_main(void);

static void peripheral_in_get_port_state(void);
static void peripheral_in_judge_state(unsigned char *swx_port_data, unsigned char *swx_state_buffer, unsigned char *swx_chatter_prev_cnt, unsigned char *swx_state);

void peripheral_in_init(void)
{
    copysw_state = CLEAR;
    powersw_state = CLEAR;
    powersw_state = CLEAR;
    
    copysw_chatter_prev_cnt = 0x00;
    powersw_chatter_prev_cnt = 0x00;
    powersw_chatter_prev_cnt = 0x00;
    
    copysw_state_buffer = CLEAR;
    sendsw_state_buffer = CLEAR;
    powersw_state_buffer = CLEAR;
    
    
}

void peripheral_in_main(void)
{
    peripheral_in_get_port_state();
    peripheral_in_judge_state(&copysw_port_data, &copysw_state_buffer, &copysw_chatter_prev_cnt, &copysw_state);
    peripheral_in_judge_state(&sendsw_port_data, &sendsw_state_buffer, &sendsw_chatter_prev_cnt, &sendsw_state);
    peripheral_in_judge_state(&powersw_port_data, &powersw_state_buffer, &powersw_chatter_prev_cnt, &powersw_state);
}

static void peripheral_in_get_port_state(void)
{
    copysw_port_data = PORTAbits.RA4;
    sendsw_port_data = PORTBbits.RB1;
    powersw_port_data = PORTBbits.RB2;
}



static void peripheral_in_judge_state(unsigned char *swx_port_data, unsigned char *swx_state_buffer, unsigned char *swx_chatter_prev_cnt, unsigned char *swx_state)
{
    if( (*swx_port_data) == SW_ACTIVE)
    {
        if( (*swx_state_buffer) == CLEAR)
        {
            (*swx_chatter_prev_cnt) = 0x00;
            (*swx_state_buffer) = SET;
        }
        else /*(sw1_state_buffer == SET)*/
        {
            if( (*swx_chatter_prev_cnt) < sw_chatter_prev_cnt)
            {
                (*swx_chatter_prev_cnt)++;
                if( (*swx_chatter_prev_cnt) >= sw_chatter_prev_cnt)
                {
                    (*swx_state) = SET;
                }
            }
        }
    }
    else /* if(sw1_port_data = SW1_INACTIVE) */
    {
        if( (*swx_state_buffer) == SET)
        {
            (*swx_chatter_prev_cnt) = 0x00;
            (*swx_state_buffer) = CLEAR;
        }
        else /*(sw1_state_buffer == CLEAR)*/
        {
            if( (*swx_chatter_prev_cnt) < sw_chatter_prev_cnt)
            {
                (*swx_chatter_prev_cnt)++;
                if( (*swx_chatter_prev_cnt) >= sw_chatter_prev_cnt)
                {
                    (*swx_state) = CLEAR;
                }
            }
        }
    }
}