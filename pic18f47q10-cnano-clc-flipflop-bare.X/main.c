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
#pragma config WDTE = OFF       /* WDT operating mode->WDT Disabled */
#pragma config LVP = ON       /* Low voltage programming enabled */

#include <xc.h>
/*  Define reload values PR2 & PR4 & PR6 registers */
#define TIMER2PR 0x0F 
#define TIMER4PR 0x1F  
#define TIMER6PR 0xFF  
/*  Define NULL values for the CLC use */
#define CLCNULL 0x00 
/*  Define reload values CCPR1H & CCPR1L registers */
#define CCP1H 0x01 
#define CCP1L 0xFF 
/*  Define register values for PPS pin-mapping   */
#define PPS_CONFIG_RA2_CLC1_OUT 0x18 
#define PPS_CONFIG_RA3_CLC2_OUT 0x19
#define PPS_CONFIG_RB0_CLC3_OUT 0x1A
#define PPS_CONFIG_RB3_CCP1_OUT 0x05

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
    OSCCON1 = _OSCCON1_NOSC1_MASK
            | _OSCCON1_NOSC2_MASK;
    /* HFFRQ 64_MHz; */
    OSCFRQ = _OSCFRQ_FRQ3_MASK;
}

static void PORT_init(void)
{
    /*PORT RA2 and RA3 output driver enabled*/
    TRISA &= ~(_TRISA_TRISA2_MASK | _TRISA_TRISA3_MASK); 
    /*PORT RB3 and RB0  output driver enabled*/ 
    TRISB &= ~(_TRISB_TRISB3_MASK | _TRISB_TRISB0_MASK);      
}

static void TMR2_init(void)
{
    /* Set TMR2 to generate a pulse every 1us (Frequency = 1MHz)*/  
    /*  TIMER2 is also set to start at the same time as TIMER4 */
    /* Timer 2 clock source is FOSC/4 */
    T2CLKCON = _T2CLKCON_CS0_MASK; 
    /* Timer2 Resets at rising TMR2_ers*/
    T2HLT = _T2HLT_MODE2_MASK;
    /* Timer 2 reset source is TMR4_postscaled; */
    T2RST = _T2RST_RSEL1_MASK;
    /* Load period values */
    T2PR = TIMER2PR; 
    /* Enable Timer2 */
    T2CON = _T2CON_ON_MASK;  
}

static void TMR4_init(void)
{
    /* Set TMR4 to generate a pulse every 2us (Frequency = 500kHz)*/
    /* Timer 4 clock source is FOSC/4 */
    T4CLKCON = _T4CLKCON_CS0_MASK; 
    /* Load period values */
    T4PR = TIMER4PR;  
    /* Enable Timer4 */
    T4CON = _T4CON_ON_MASK; 
}

static void TMR6_init(void)
{
    /* Set TMR6 to generate a pulse every 16us (Frequency = 62.5kHz)*/
    /* Timer 6 clock source is FOSC/4 */
    T6CLKCON = _T6CLKCON_CS0_MASK; 
    /* Load period values */
    T6PR = TIMER6PR; 
    /* Enable Timer6 */
    T6CON = _T6CON_ON_MASK;
}

static void CCP1_init(void)
 {   
    /* Set the CCP1 to run as a PWM with 50% duty-cycle and TIMER6 as source*/
    /* Enable CCP1 in PWM mode*/
	CCP1CON = _CCP1CON_MODE2_MASK 
            | _CCP1CON_MODE3_MASK 
            | _CCP1CON_EN_MASK;
    /* Load duty-cycle values */
	CCPR1H = CCP1H;    
	CCPR1L = CCP1L;    
    /* Clear CCP1 pulse source */
    CCPTMRS &= ~(_CCPTMRS_C1TSEL0_MASK | _CCPTMRS_C1TSEL1_MASK);
    /* Select TIMER6 as pulse source*/
    CCPTMRS |= _CCPTMRS_C1TSEL_MASK; 
 }
 
static void CLC1_init(void)
{
    /* Set the CLC1 to implement JK flip-flop with R*/  
    /*  Clear the output polarity register */
    CLC1POL = CLCNULL;
    /* Negated output for fourth OR Gate*/
    CLC1POL |= _CLC1POL_G4POL_MASK;
    /* Configure TMR2_OUT as input for first OR Gate */
    CLC1SEL0 = _CLC1SEL0_D1S0_MASK 
             | _CLC1SEL0_D1S1_MASK 
             | _CLC1SEL0_D1S4_MASK;
    /* Configure CCP1_OUT as input for second OR Gate */
    CLC1SEL1 = _CLC1SEL1_D2S3_MASK 
             | _CLC1SEL1_D2S4_MASK;
    /* Configure TMR2_OUT as input for third OR Gate */
    CLC1SEL2 = _CLC1SEL2_D3S0_MASK 
             | _CLC1SEL2_D3S1_MASK 
             | _CLC1SEL2_D3S4_MASK;
    /* Configure TMR2_OUT as input for forth OR Gate */
    CLC1SEL3 = _CLC1SEL3_D4S0_MASK 
             | _CLC1SEL3_D4S1_MASK 
             | _CLC1SEL3_D4S4_MASK;
    /* All 4 inputs are not inverted*/
    CLC1GLS0 = _CLC1GLS0_LC1G1D1T_MASK; 
    CLC1GLS1 = _CLC1GLS1_LC1G2D2T_MASK; 
    CLC1GLS2 = CLCNULL; 
    CLC1GLS3 = CLCNULL; 
    /* CLC1 enabled; MODE JK flip-flop with R*/
    CLC1CON = _CLC1CON_EN_MASK
            | _CLC1CON_MODE1_MASK 
            | _CLC1CON_MODE2_MASK;
}
 
static void CLC2_init(void)
{
    /* Set the CLC2 to implement JK flip-flop with R*/
    /*  Clear the output polarity register */
    CLC2POL = CLCNULL;
    /* Negated output for fourth OR Gate*/
    CLC2POL |= _CLC2POL_G4POL_MASK;
    /* Configure TMR4_OUT as input for first OR Gate */
    CLC2SEL0 = _CLC2SEL0_D1S0_MASK 
             | _CLC2SEL0_D1S2_MASK 
             | _CLC2SEL0_D1S4_MASK; 
    /* Configure CCP1_OUT as input for second OR Gate */
    CLC2SEL1 = _CLC2SEL1_D2S3_MASK 
             | _CLC2SEL1_D2S4_MASK;
    /* Configure TMR4_OUT as input for third OR Gate */
    CLC2SEL2 = _CLC2SEL2_D3S0_MASK 
             | _CLC2SEL2_D3S2_MASK 
             | _CLC2SEL2_D3S4_MASK; 
    /* Configure TMR4_OUT as input for forth OR Gate */
    CLC2SEL3 = _CLC2SEL3_D4S0_MASK 
             | _CLC2SEL3_D4S2_MASK 
             | _CLC2SEL3_D4S4_MASK; 
    /* Input 1,3 and are not inverted; Input 2 inverted*/
    CLC2GLS0 = _CLC2GLS0_LC2G1D1T_MASK;
    CLC2GLS1 = _CLC2GLS1_LC2G2D2N_MASK;
    CLC2GLS2 = CLCNULL; 
    CLC2GLS3 = CLCNULL;
    /* CLC2 enabled; MODE JK flip-flop with R*/
    CLC2CON = _CLC2CON_EN_MASK 
            | _CLC2CON_MODE1_MASK 
            | _CLC2CON_MODE2_MASK;
}
 
static void CLC3_init(void)
{
    /* Set the CLC3 to implement AND-OR Logic with the focus on 2-input OR*/
    /*  Clear the output polarity register */
    CLC3POL = CLCNULL;
    /* Configure CLC1_OUT as input for first OR Gate */
    CLC3SEL0 = _CLC3SEL0_D1S0_MASK 
             | _CLC3SEL0_D1S5_MASK; 
    /* Configure CLC1_OUT as input for second OR Gate */
    CLC3SEL1 = _CLC3SEL1_D2S0_MASK 
             | _CLC3SEL1_D2S5_MASK;
    /* Configure CLC2_OUT as input for third OR Gate */
    CLC3SEL2 = _CLC3SEL2_D3S1_MASK 
             | _CLC3SEL2_D3S5_MASK;
    /* Configure CLC2_OUT as input for forth OR Gate */
    CLC3SEL3 = _CLC3SEL3_D4S1_MASK 
             | _CLC3SEL3_D4S5_MASK; 
    /* All 4 inputs are not inverted*/
    CLC3GLS0 = _CLC3GLS0_LC3G1D1T_MASK; 
    CLC3GLS1 = _CLC3GLS1_LC3G2D2T_MASK; 
    CLC3GLS2 = _CLC3GLS2_LC3G3D3T_MASK;  
    CLC3GLS3 = _CLC3GLS3_LC3G4D4T_MASK; 
    /* CLC3 enabled; MODE AND-OR*/
    CLC3CON = _CLC3CON_EN_MASK;
}

static void PPS_init(void)
{
    /*Configure RA2 for CLC1 output*/
    RA2PPS = PPS_CONFIG_RA2_CLC1_OUT; 
    /*Configure RA3 for CLC2 output*/
    RA3PPS = PPS_CONFIG_RA3_CLC2_OUT; 
    /*Configure RB0 for CLC3 output*/
    RB0PPS = PPS_CONFIG_RB0_CLC3_OUT; 
    /*Configure RB3 for CCP1 output*/
    RB3PPS = PPS_CONFIG_RB3_CCP1_OUT;   
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
