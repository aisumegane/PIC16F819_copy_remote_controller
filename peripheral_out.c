/*
 * File:   register_setup.c
 * Author: •XMEGANE
 *
 * Created on 2024/04/11, 21:17
 */

#include <xc.h>
#include "grobal_macro.h"
#include "grobal_function.h"
#include "peripheral_in.h"
#include "peripheral_out.h"

void peripheral_out_init(void);
void peripheral_out_main(void);

static void peripheral_led_test(void);
static void peripheral_infrared_led_test(void);


void peripheral_out_init(void)
{
    
}


void peripheral_out_main(void)
{
    peripheral_led_test();
    peripheral_infrared_led_test();
}

static void peripheral_led_test(void)
{
    /**/
    if(copysw_state == SET)
    {
        PORTAbits.RA2 = SET;
    }
    else
    {
        PORTAbits.RA2 = CLEAR;
    }
    
    /**/
    if(sendsw_state == SET)
    {
        PORTAbits.RA3 = SET;
    }
    else
    {
        PORTAbits.RA3 = CLEAR;
    }
    
    /**/
    if(powersw_state == SET)
    {
        PORTBbits.RB5 = SET;
    }
    else
    {
        PORTBbits.RB5 = CLEAR;
    }
    
}

static void peripheral_infrared_led_test(void)
{   
    if(PORTBbits.RB0 == SET)
    {
        PORTBbits.RB3 = SET;
    }
    else
    {
        PORTBbits.RB3 = CLEAR;
    }
}