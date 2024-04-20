/*
 * File:   interrupt.c
 * Author: 氷MEGANE
 *
 * Created on 2024/04/14, 23:38
 */

#include <xc.h>

#include "grobal_macro.h"
#include "interrupt.h"
#include "grobal_function.h"

#include "senddata.h"


unsigned char senddata_send_comp =CLEAR;   /* コピー処理完了フラグ */

void senddata_main(void);


void senddata_main(void)
{
    
}
