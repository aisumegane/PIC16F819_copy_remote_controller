/*
 * File:   register_setup.c
 * Author: 氷MEGANE
 *
 * Created on 2024/03/27, 21:17
 */


#include <xc.h>
#include <pic16f819.h>

/*header*/
#include "grobal_macro.h"
#include "register_setup.h"

typedef union {
    struct {    /*定義順序注意(下位bitから詰める)*/
        unsigned char low_ccp1x          :1; /*bit 0     */
        unsigned char low_ccp1y          :1; /*bit 1     */
        unsigned char high_8bit          :8; /*bit 2?9  */
        unsigned char unusebit           :6; /*bit 10?15*/
    }bit_field;
    
    unsigned short u_short_pwm_duty;
} DUTY_REG_SET;

/*global func prototype*/
void pic819_register_setup_byte_set(void);
void pic819_register_setup(void);

void oscillator_setup(void);
void option_reg_setup(void);
void interrupt_setup(void);
void io_port_setup(void);
void ad_converter_setup();

void timer0_setup();
void timer1_setup();
void timer2_setup();
void set_pwm_duty(unsigned short duty);

void pic819_register_setup(void)
{         
    /*割込み禁止*/
    INTCONbits.GIE = CLEAR;         // グローバル割り込み禁止
    INTCONbits.PEIE = CLEAR;        // リフェラル割込み禁止
    
    
    oscillator_setup();         /*内蔵発振器設定*/
    option_reg_setup();         /*オプション設定*/
    interrupt_setup();          /*割込み設定*/
    io_port_setup();            /*IOポート設定*/
    ad_converter_setup();       /*ADコンバータ設定*/
    
    timer0_setup();             /*timer0設定*/
    timer1_setup();             /*timer1設定*/
    timer2_setup();             /*timer2設定*/
}

void oscillator_setup(void)
{   /* OSCCON */    /*datasheet P.40*/  /*内蔵発振器使用、8MHzに設定*/
    OSCCONbits.IRCF2 = SET;
    OSCCONbits.IRCF1 = SET;
    OSCCONbits.IRCF0 = SET;
}

void option_reg_setup(void)
{   /*OPTION_REG*//*datasheet P.19*//*WDTタイマ、ポート初期一部設定*/
    OPTION_REGbits.nRBPU   = SET;    /* PORT-B Pull-up Enable bit (1:Disable / 0:Enable) */
    OPTION_REGbits.INTEDG  = SET;      /* RB0/INT pin Interrupt Edge Select bit (1:rising edge / 0:falling edge) */ /* 初回は信号待ち(0→1待ち)なので立ち上がりエッジ */
    OPTION_REGbits.T0CS    = CLEAR;    /* TMR0 Clock Source Select bit (1:T0CKI pin / 0:Internal (CKLO)) */
    OPTION_REGbits.T0SE    = CLEAR;    /* TMR0 Source Edge Select bit(1:high-to-low transition on T0CKI / 0:low-to-high transition on T0CKI) */
    OPTION_REGbits.PSA     = CLEAR;    /* Prescaler Assignment bit (1:assigned to WDT / 0:assigned to Timer0) */
    OPTION_REGbits.PS2     = SET;      /* Prescaler Rate Select bit (PS2,1,0) */
    OPTION_REGbits.PS1     = CLEAR;
    OPTION_REGbits.PS0     = CLEAR;
    
    /*timer0設定*/
    TMR0 = 160;
}

void interrupt_setup(void)
{   /*INTCON*/    /*PIE1*/    /*datasheet P.20~21*/
    
    /*割込み許可をセット*/
    /*INTCON*/
    INTCONbits.GIE = CLEAR;   /*割込みベクタが1つしかないのでここ禁止しとくだけにする*/
    INTCONbits.PEIE = CLEAR;
    INTCONbits.TMR0IE = SET;
    INTCONbits.INTE = SET;
    
    INTCONbits.RBIE = CLEAR;
    INTCONbits.TMR0IF = CLEAR;
    INTCONbits.INTF = CLEAR;
    INTCONbits.RBIF = CLEAR;
    
    /*PIE1*/
    PIE1bits.ADIE = CLEAR;
    PIE1bits.SSPIE = CLEAR;
    PIE1bits.CCP1IE = SET;
    PIE1bits.TMR2IE = SET;      /*PWM mode*/
    PIE1bits.TMR1IE = CLEAR;
    
    /*PIE2*/
    PIE2bits.EEIE = CLEAR;
    


    
    /*PIR1*/
    PIR1bits.ADIF = CLEAR;
    PIR1bits.SSPIF = CLEAR;
    PIR1bits.CCP1IF = CLEAR;
    PIR1bits.TMR2IF = CLEAR;
    PIR1bits.TMR1IF = CLEAR;
    
    /*PIR2*/
    PIR2bits.EEIF = CLEAR;
}

void io_port_setup(void)
{   /*TRISA,TRISB,PORTA,PORTB*/ /*datasheet P.4(ピン配置)*/ /*datasheet P.41*/  /*datasheet P.45*/  /*datasheet P.56(オプション)*/
    /*TRISA*/   /*1:入力 / 0:出力*/
#if 0
    TRISAbits.TRISA0 = SET;
    TRISAbits.TRISA1 = SET;
    TRISAbits.TRISA2 = SET;
    TRISAbits.TRISA3 = SET;
    
    TRISAbits.TRISA4 = SET;
    TRISAbits.TRISA5 = SET;
    TRISAbits.TRISA6 = SET;
    TRISAbits.TRISA7 = SET;
    
    /*TRISB*/   /*1:入力 / 0:出力*/
    TRISBbits.TRISB0 = SET;
    TRISBbits.TRISB1 = SET;
    TRISBbits.TRISB2 = SET;
    TRISBbits.TRISB3 = SET;
    
    TRISBbits.TRISB4 = SET;
    TRISBbits.TRISB5 = SET;
    TRISBbits.TRISB6 = SET;
    TRISBbits.TRISB7 = SET;
    
    /*PORTA*/   /*1:Hレベル出力 / 0:Lレベル出力*/ 
    PORTAbits.RA0 = CLEAR;
    PORTAbits.RA1 = CLEAR;
    PORTAbits.RA2 = CLEAR;
    PORTAbits.RA3 = CLEAR;
    
    PORTAbits.RA4 = CLEAR;
    PORTAbits.RA5 = CLEAR;
    PORTAbits.RA6 = CLEAR;
    PORTAbits.RA7 = CLEAR;
    
    /*PORTB*/   /*1:Hレベル出力 / 0:Lレベル出力*/
    PORTBbits.RB0 = CLEAR;
    PORTBbits.RB1 = CLEAR;
    PORTBbits.RB2 = CLEAR;
    PORTBbits.RB3 = CLEAR;
    
    PORTBbits.RB4 = CLEAR;
    PORTBbits.RB5 = CLEAR;
    PORTBbits.RB6 = CLEAR;
    PORTBbits.RB7 = CLEAR;
    
#else
    TRISAbits.TRISA0 = CLEAR;
    TRISAbits.TRISA1 = CLEAR;
    TRISAbits.TRISA2 = CLEAR;
    TRISAbits.TRISA3 = CLEAR;
    
    TRISAbits.TRISA4 = SET;
    TRISAbits.TRISA5 = SET;
    TRISAbits.TRISA6 = CLEAR;
    TRISAbits.TRISA7 = CLEAR;
    
    /*TRISB*/   /*1:入力 / 0:出力*/
    TRISBbits.TRISB0 = SET;
    TRISBbits.TRISB1 = SET;
    TRISBbits.TRISB2 = SET;
    TRISBbits.TRISB3 = CLEAR;
    
    TRISBbits.TRISB4 = CLEAR;
    TRISBbits.TRISB5 = CLEAR;
    TRISBbits.TRISB6 = SET;
    TRISBbits.TRISB7 = SET;
    
    /*PORTA*/   /*1:Hレベル出力 / 0:Lレベル出力*/ 
    PORTAbits.RA0 = CLEAR;
    PORTAbits.RA1 = CLEAR;
    PORTAbits.RA2 = CLEAR;
    PORTAbits.RA3 = CLEAR;
    
    PORTAbits.RA4 = CLEAR;
    PORTAbits.RA5 = CLEAR;
    PORTAbits.RA6 = CLEAR;
    PORTAbits.RA7 = CLEAR;
    
    /*PORTB*/   /*1:Hレベル出力 / 0:Lレベル出力*/
    PORTBbits.RB0 = CLEAR;
    PORTBbits.RB1 = CLEAR;
    PORTBbits.RB2 = CLEAR;
    PORTBbits.RB3 = CLEAR;
    
    PORTBbits.RB4 = CLEAR;
    PORTBbits.RB5 = CLEAR;
    PORTBbits.RB6 = CLEAR;
    PORTBbits.RB7 = CLEAR;
#endif
}

void ad_converter_setup(void)
{   /*ADCON0,ADCON1*/ /*datasheet P.83~84*/
    /*ADCON0*/
    ADCON0bits.ADCS1 = CLEAR;   /*ADCON1bits.ADCS2 check*/
    ADCON0bits.ADCS0 = CLEAR;   /*ADCON1bits.ADCS2 check*/
    
    ADCON0bits.CHS2 = CLEAR;    /*AD変換無効ならこの設定は無意味なので、使わないなら適当な値を入れておく*/
    ADCON0bits.CHS1 = CLEAR;
    ADCON0bits.CHS0 = CLEAR;
    
    ADCON0bits.GO_nDONE = CLEAR;    /* AD変換完了で自動クリア */
    ADCON0bits.ADON = CLEAR;
    
    /*ADCON1*/
    ADCON1bits.ADFM = SET;  /*右(16bitのうち10bit使用、下位ビット寄せて上位は使わない)*/
    ADCON1bits.ADCS2 = CLEAR;
    
    ADCON1bits.PCFG3 = CLEAR;
    ADCON1bits.PCFG2 = SET;
    ADCON1bits.PCFG1 = SET;
    ADCON1bits.PCFG0 = CLEAR;
}

void timer0_setup(void)
{   /*timer0についてはオプションで設定*/
    option_reg_setup();
}

void timer1_setup(void)
{
#if 0
    /*CCPモード設定*/
    /*T1CON*/ /*datasheet P.59*/
    /*T1CON*/
    T1CONbits.T1CKPS1 = SET;      /*(Fsoc/4)の8分周 */ /* 2MHz/8 = 250kHz(0.000,004 sec) */
    T1CONbits.T1CKPS0 = SET;
    T1CONbits.T1OSCEN = CLEAR;      /*for external clock*/        
    T1CONbits.nT1SYNC = SET;        /*for external clock*/
    T1CONbits.TMR1CS = CLEAR;       /*Internal clock*/
    T1CONbits.TMR1ON = CLEAR;

    /*CCP1CON*/ /*datasheet P.67*/
    /*CCP1CONbits_t.CCP1X = SET/CLEAR;*/
    /*CCP1CONbits_t.CCP1Y = SET/CLEAR;*/
    CCP1CONbits.CCP1M3 = SET;
    CCP1CONbits.CCP1M2 = CLEAR;
    CCP1CONbits.CCP1M1 = SET;
    CCP1CONbits.CCP1M0 = SET;
    
    /*CCPR1H,CCPR1L*/
    /* 動作周波数設定 = 50ms = 0.000,004 sec * 12500(0x30D4) */
    /* 0までロールオーバー(MAXの次に0を数えて1カウントする)ので、1引く */
    CCPR1H = 0x30;
    CCPR1L = 0xD3;  /* Timer0でも十分 */   
#endif
    /*PWMモード設定*/
    /*T1CON*/ /*datasheet P.59*/
    /*T1CON*/
    T1CONbits.T1CKPS1 = SET;      /*(Fsoc/4)の8分周 */ /* 2MHz/8 = 250kHz(0.000,004 sec) */
    T1CONbits.T1CKPS0 = SET;
    T1CONbits.T1OSCEN = CLEAR;      /*for external clock*/        
    T1CONbits.nT1SYNC = SET;        /*for external clock*/
    T1CONbits.TMR1CS = CLEAR;       /*Internal clock*/
    T1CONbits.TMR1ON = CLEAR;

    /*CCP1CON*/ /*datasheet P.67*/
    /*CCP1CONbits_t.CCP1X = SET/CLEAR;*/
    /*CCP1CONbits_t.CCP1Y = SET/CLEAR;*/
    CCP1CONbits.CCP1M3 = SET;
    CCP1CONbits.CCP1M2 = SET;
    CCP1CONbits.CCP1M1 = SET;   /*無効*/
    CCP1CONbits.CCP1M0 = SET;   /*無効*/
    
    /*CCPR1H,CCPR1L*/
    /* 動作周波数設定 = 50ms = 0.000,004 sec * 12500(0x30D4) */
    /* 0までロールオーバー(MAXの次に0を数えて1カウントする)ので、1引く */
    //CCPR1H = 0x30;  
    

#if 1
    CCPR1L = 0x11;
    CCP1CONbits.CCP1X = CLEAR;
    CCP1CONbits.CCP1Y = CLEAR;
#else
    set_pwm_duty(100);
#endif
}

void timer2_setup()
{
    T2CONbits.TOUTPS3   = CLEAR;
    T2CONbits.TOUTPS2   = CLEAR;
    T2CONbits.TOUTPS1   = CLEAR;
    T2CONbits.TOUTPS0   = CLEAR;
    T2CONbits.TMR2ON    = CLEAR;
    /*分周比:fosc/4を0分割：2,000,000Hz*/
    T2CONbits.T2CKPS1   = CLEAR;
    T2CONbits.T2CKPS0   = CLEAR;
    
    /*PWM周期(period)設定：52カウント:約38kHz*/
    PR2 = 0x34;
}

void set_pwm_duty(unsigned short duty)
{   /*0x0000 ? 0x03FF の範囲でduty指定*/
    DUTY_REG_SET pwm_duty;
    
    /*on-dutyを10bitで設定する:上位8bitがCCPR1L、下位2bitがCCP1XとCCP1L、なかなかキモイ*/
#if 0
    duty >>1;
    CCPR1L = (unsigned char)duty;
    CCP1CONbits.CCP1X = CLEAR;
    CCP1CONbits.CCP1Y = CLEAR;
#endif
    
#if 0
    if(duty > 0x3FF)
    {   /*オーバーフロー防止*/
        duty = 0x3FF;
    }
    
    //duty = duty << 2;
    
    /* 100%duty = 0x3FF (10bit MAX) */
    pwm_duty.u_short_pwm_duty = duty;
            
    CCPR1L = pwm_duty.bit_field.high_8bit;
    CCP1CONbits.CCP1X = pwm_duty.bit_field.low_ccp1x;
    CCP1CONbits.CCP1Y = pwm_duty.bit_field.low_ccp1y;
#endif
#if 0
    CCP1CONbits.CCP1X = duty & 0b0000000000000001;
    CCP1CONbits.CCP1Y = duty & 0b0000000000000010;
    
    CCPR1L = duty > 2;
#endif
}