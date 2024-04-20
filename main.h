/*
 * File:   main.h
 * Author: �XMEGANE
 * Mid-Range 8-bit MCUs PIC16F819
 * Created on 2024/04/14, 23:38
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define SEQUENCE_MAIN                0
    #define SEQUENCE_COPY_DATA           1
    #define SEQUENCE_SEND_DATA           2

    extern unsigned char sequence_num;

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

