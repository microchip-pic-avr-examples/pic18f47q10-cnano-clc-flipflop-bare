/**
* \file main.c
*
* \brief Main source file.
*
    (c) 2020 Microchip Technology Inc. and its subsidiaries.
	
    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.
    
	THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.
    
	IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

/* PIC18F47Q10 Configuration Bit Settings*/
#pragma config MCLRE = EXTMCLR    /* Master Clear Enable bit->MCLR pin (RE3) is MCLR */
#pragma config WDTE = OFF      /* WDT operating mode->WDT Disabled */
#pragma config LVP = ON       /* Low voltage programming enabled */

#include <xc.h>

/* Code Function Declarations */
static void CLK_init(void);
static void PORT_init(void);
static void TMR2_init(void);
static void TMR4_init(void);
static void TMR6_init(void);
static void CCP1_init(void);
static void CLC1_init(void);
static void CLC2_init(void);
static void CLC3_init(void);
static void PPS_init(void);

static void CLK_init(void)
{
    /* HFINTOSC Oscillator */
    OSCCON1bits.NOSC = 6 ;
    /* HFFRQ 64_MHz; */
    OSCFRQ = 0x08;
}

static void PORT_init(void)
{
    /*PORT RA2 and RA3 output driver enabled*/
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    /*PORT RB3 and RB0  output driver enabled*/ 
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB3 = 0;
}

static void TMR2_init(void)
{
    /* Set TMR2 to generate a pulse every 1us (Frequency = 1MHz)*/  
    /*  TIMER2 is also set to start at the same time as TIMER4 */
    /* Timer 2 clock source is FOSC/4 */
    T2CLKCONbits.CS = 1; 
    /* Timer2 Resets at rising TMR2_ers*/
    T2HLTbits.MODE = 4;
    /* Timer 2 reset source is TMR4_postscaled; */
    T2RSTbits.RSEL = 2;
    /* Load period values */
    T2PR = 0x0F; 
    /* Enable Timer2 */
    T2CON = 0x80;  
}

static void TMR4_init(void)
{
    /* Set TMR4 to generate a pulse every 2us (Frequency = 500kHz)*/
    /* Timer 4 clock source is FOSC/4 */
    T4CLKCONbits.CS = 1; 
    /* Load period values */
    T4PR = 0x1F;  
    /* Enable Timer4 */
    T4CON = 0x80; 
}

static void TMR6_init(void)
{
    /* Set TMR6 to generate a pulse every 16us (Frequency = 62.5kHz)*/
    /* Timer 6 clock source is FOSC/4 */
    T6CLKCONbits.CS = 1; 
    /* Load period values */
    T6PR = 0xFF; 
    /* Enable Timer6 */
    T6CON = 0x80;
}

static void CCP1_init(void)
 {   
    /* Set the CCP1 to run as a PWM with 50% duty-cycle and TIMER6 as source*/
    /* Enable CCP1 in PWM mode*/
	CCP1CON = 0x8C;
    /* Load duty-cycle values */
	CCPR1H = 0x01;    
	CCPR1L = 0xFF;    
    /* Select TIMER6 as pulse source*/
    CCPTMRS = 0x03; 
 }
 
static void CLC1_init(void)
{
    /* Set the CLC1 to implement JK flip-flop with R*/  
    /* Negated output for fourth OR Gate*/
    CLC1POL = 0x08;
    /* Configure TMR2_OUT as input for first OR Gate */
    CLC1SEL0 = 0x13;
    /* Configure CCP1_OUT as input for second OR Gate */
    CLC1SEL1 = 0x18;
    /* Configure TMR2_OUT as input for third OR Gate */
    CLC1SEL2 = 0x13;
    /* Configure TMR2_OUT as input for forth OR Gate */
    CLC1SEL3 = 0x13;
    /* All 4 inputs are not inverted*/
    CLC1GLS0 = 0x02; 
    CLC1GLS1 = 0x08; 
    CLC1GLS2 = 0x00; 
    CLC1GLS3 = 0x00; 
    /* CLC1 enabled */
    CLC1CONbits.EN = 1; 
    /* MODE JK flip-flop with R */
    CLC1CONbits.MODE = 6;
}
 
static void CLC2_init(void)
{
    /* Set the CLC2 to implement JK flip-flop with R*/
    /* Negated output for fourth OR Gate*/
    CLC2POL = 0x08;
    /* Configure TMR4_OUT as input for first OR Gate */
    CLC2SEL0 = 0x15; 
    /* Configure CCP1_OUT as input for second OR Gate */
    CLC2SEL1 = 0x18;
    /* Configure TMR4_OUT as input for third OR Gate */
    CLC2SEL2 = 0x15; 
    /* Configure TMR4_OUT as input for forth OR Gate */
    CLC2SEL3 = 0x15; 
    /* Input 1,3 and are not inverted; Input 2 inverted*/
    CLC2GLS0 = 0x02;
    CLC2GLS1 = 0x04;
    CLC2GLS2 = 0x00; 
    CLC2GLS3 = 0x00;
    /* CLC2 enabled */
    CLC2CONbits.EN = 1; 
    /* MODE JK flip-flop with R */
    CLC2CONbits.MODE = 6;
}
 
static void CLC3_init(void)
{
    /* Set the CLC3 to implement AND-OR Logic with the focus on 2-input OR*/
    /*  Clear the output polarity register */
    CLC3POL = 0x00;
    /* Configure CLC1_OUT as input for first OR Gate */
    CLC3SEL0 = 0x21; 
    /* Configure CLC1_OUT as input for second OR Gate */
    CLC3SEL1 = 0x21;
    /* Configure CLC2_OUT as input for third OR Gate */
    CLC3SEL2 = 0x22;
    /* Configure CLC2_OUT as input for forth OR Gate */
    CLC3SEL3 = 0x22; 
    /* All 4 inputs are not inverted*/
    CLC3GLS0 = 0x02; 
    CLC3GLS1 = 0x08; 
    CLC3GLS2 = 0x20;  
    CLC3GLS3 = 0x80; 
    /* CLC3 enabled */
    CLC3CONbits.EN = 1; 
    /* MODE AND-OR */
    CLC3CONbits.MODE = 0;
}

static void PPS_init(void)
{
    /*Configure RA2 for CLC1 output*/
    RA2PPS = 0x18; 
    /*Configure RA3 for CLC2 output*/
    RA3PPS = 0x19; 
    /*Configure RB0 for CLC3 output*/
    RB0PPS = 0x1A; 
    /*Configure RB3 for CCP1 output*/
    RB3PPS = 0x05;   
}
 
void main(void) {
    
    CLK_init();
    PORT_init();
    TMR2_init();
    TMR4_init();
    TMR6_init();
    CCP1_init();
    CLC1_init();
    CLC2_init();
    CLC3_init();
    PPS_init();
    
    while (1)
    {
       ;
    }
}
