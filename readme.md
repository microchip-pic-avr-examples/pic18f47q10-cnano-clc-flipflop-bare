<div id="readme" class="Box-body readme blob js-code-block-container">
  <article class="markdown-body entry-content p-3 p-md-6" itemprop="text"><p><a href="https://www.microchip.com" rel="nofollow"><img src="https://camo.githubusercontent.com/5fb5505f69a28ff407841612dfe2b7004f210594/68747470733a2f2f636c6475702e636f6d2f553071684c7742696a462e706e67" alt="MCHP" style="max-width:100%;"></a></p>

# PIC18F47Q10: Getting started with the CLC on PIC18 -> Using CLCs to Create a Data Signal Modulator -> Bare metal code

## Objective:
The PIC18F47Q10 features 8 Configurable Logic Cell (CLC) peripherals that can be used to implemenmt various logic functions.
This example shows an initialization of the CLC in the JK flip-flop with R mode and AND-OR mode, that enables the
implementation of a Data Signal Modulator (DSM) with timings controlled from the CCP peripheral.

## Resources:
- Technical Brief Link [(linkTBD)](http://www.microchip.com/)
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)
- [PIC18F47Q10 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40002043D.pdf) for more information or specifications.

## Hardware Configuration:

The PIC18F47Q10 Curiosity Nano Development Board [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029) is used as the test platform.

The following configurations must be made for this project:
- Timer 2 frequency = 1 MHz (1 us period)
- Timer 4 frequency = 500 kHz (2 us period)
- Timer 6 frequency = 62.5 kHz (16 us period)
- CCP1 has as source Timer6 and duty-cycle = 50%
- CLC1 is set up as JK flip-flop with R
- CLC2 is set up as JK flip-flop with R
- CLC3 is set up as AND-OR: used as 2 input OR


I/O configurations:
- RA2 pin - Configured output 
- RA3 pin - Configured output 
- RB3 pin - Configured output 
- RB0 pin - Configured output 


This setup will create an internal connection as depicted:



<img src="images/DSM.png" alt="Internal Depiction" width="640"/>


## Demo:
Run the code written in Bare metal, the following signals are to be seen on the oscilloscope:

In the figure below it is depicted the all the CLCs outputs and the CCP1 output side by side to show how this configuration
implements DSM function:
- Signal 1 (Yellow) is CCP1 output
- Signal 2 (Green) is CLC1 output
- Signal 3 (Blue) is CLC3 output
- Signal 4 (Red) is CLC2 output


<img src="images/scopeDSM.png" alt="Figure A"/>



