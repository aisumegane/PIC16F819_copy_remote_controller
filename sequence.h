/* 
 * File:   interrupt.h
 * Author: •XMEGANE
 *
 * Created on 2024/04/02, 17:43
 */

#ifndef SEQUENCE_H
#define	SEQUENCE_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define SEQUENCE_MAIN           0
    #define SEQUENCE_COPY           1
    #define SEQUENCE_SEND           2

    extern unsigned char sequence_num;
    extern void sequence_main(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SEQUENCE_H */

