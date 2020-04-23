<div id="readme" class="Box-body readme blob js-code-block-container">
 <article class="markdown-body entry-content p-3 p-md-6" itemprop="This needs to locked down and 'never' changed"><p><a href="https://www.microchip.com" rel="nofollow"><img src="images/Microchip.png" alt="MCHP" style="max-width:40%;"></a></p>
 
# PIC18F47Q10: Getting started with the CLC on PIC18 -> Using CLCs to Create a Data Signal Modulator -> Bare metal code

## Objective:
The PIC18F47Q10 features 8 Configurable Logic Cell (CLC) peripherals that can be used to implemenmt various logic functions.
This example shows an initialization of the CLC in the JK flip-flop with R mode and AND-OR mode, that enables the
implementation of a Data Signal Modulator (DSM) with timings controlled from the CCP peripheral.

## Related Documentation
Existing application notes or tech briefs that are related to the subject:
- [AN2133 - Extending PIC® MCU Capabilities Using CLC](http://ww1.microchip.com/downloads/en/AppNotes/00002133a.pdf)
- [TB3133 – Configurable Logic Cell on PIC® Microcontrollers](http://ww1.microchip.com/downloads/en/Appnotes/90003133A.pdf)
- [AN2805 - Robust Debouncing with Core Independent Peripherals](http://ww1.microchip.com/downloads/en/DeviceDoc/AN2805-Robust-Debounc-Core-Inddep-Periph-DS00002805A.pdf)
- [DS41631B - Configurable Logic Cell Tips ’n Tricks](http://ww1.microchip.com/downloads/en/devicedoc/41631b.pdf)
- [AN2912 - Using CLCs in Real-Time Applications](http://ww1.microchip.com/downloads/en/Appnotes/AN2912-Using-CLCs-in-Real-Time-Apps_00002912A.pdf)
- [AN1606 - Using the Configurable Logic Cell (CLC) to Interface a PIC16F1509 and WS2811 LED Driver](http://ww1.microchip.com/downloads/en/appnotes/00001606a.pdf)

- [20007 CIP1 - Applying Configurable Logic Cell CLC to Interconnect Peripheral Functions](https://www.youtube.com/watch?v=qT2Ma_XR3ZQ)

- [PIC18F-Q10 Family Product Page](https://www.microchip.com/design-centers/8-bit/pic-mcus/device-selection/pic18f-q10-product-family)


## Software Used
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or a newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) 3.95.0 or newer [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- MPLAB® Code Configurator (MCC) Device Libraries PIC10 / PIC12 / PIC16 / PIC18 MCUs [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- Microchip PIC18F-Q Series Device Support (1.4.109) or newer [(packs.download.microchip.com/)](https://packs.download.microchip.com/)


## Hardware Used
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)

## Setup
The following configurations must be made for this project:
- Timer 2 frequency = 1 MHz (1 us period)
- Timer 4 frequency = 500 kHz (2 us period)
- Timer 6 frequency = 62.5 kHz (16 us period)
- CCP1 has as source Timer6 and duty-cycle = 50%
- CLC1 is set up as JK flip-flop with R
- CLC2 is set up as JK flip-flop with R
- CLC3 is set up as AND-OR: used as 2 input OR

I/O configurations:
|Pin           | Configuration      |

| :----------: | :----------------: |

|RA2           | Digital Output     |

|RA3           | Digital Output     |

|RB3           | Digital Output     |

|RB0           | Digital Output     |


This setup will create an internal connection as depicted:



<img src="images/DSM.png" alt="Internal Depiction" width="860"/>


## Operation
Run the code written in Bare metal, the following signals are to be seen on the oscilloscope:

In the figure below it is depicted the all the CLCs outputs and the CCP1 output side by side to show how this configuration
implements DSM function:
- Signal 1 (Yellow) is CCP1 output
- Signal 2 (Green) is CLC1 output
- Signal 3 (Blue) is CLC3 output
- Signal 4 (Red) is CLC2 output


<img src="images/scopeDSM.png" alt="Figure A"/>


## Summary
This project showcases how the Core Independent Peripherals (CIPs) on the new PIC18-Q43 can be used to create an Data Signal Modulator (DSM). 
This example shows an initialization of the CLC in the JK flip-flop with R mode and AND-OR mode, that enables this implementation. 
The CLC is one of the most versatile peripherals in the PIC arsenal, and this example proves that the user can implement complex modules with its help.