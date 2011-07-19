///////////////////////////////////////////////////////////////////////////
//  Product/Project : Robot control                                      //
///////////////////////////////////////////////////////////////////////////
//
//  File Name    : Main.c
//  Version      : 1.0
//  Description  : Press the down button to switch text on lcd
//  Author       : Jim Clermonts
//  Target       : dsPIC33FJ64GP802
//  Compiler     : MPLAB C Compiler for PIC24 and dsPIC v3.25 in LITE mode
//  IDE          : MPLAB X IDE Beta4.0
//  Programmer   : uBRD bootloader
//  Last Updated : 09-01-2011
//
//  Copyright (c) Staronic 2011.
//  All rights are reserved. Reproduction in whole or in part is
//  prohibited without the written consent of the copyright owner.
///////////////////////////////////////////////////////////////////////////
#include    "uBRD.h"
#include    "Delay.h"
#include    "Peripherals.h"
#include    "Userdata.h"

//Configuration-for-programmer--------------------------
_FBS(RBS_NO_RAM & BSS_NO_FLASH & BWRP_WRPROTECT_OFF); // No boot ram, flash, write protection
_FSS(RSS_NO_RAM & SWRP_WRPROTECT_OFF); // No protected sections
_FGS(GSS_OFF
        & GCP_OFF & GWRP_OFF); // No code protection
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF); // FRC Oscillator with PLL, no two-speed oscillator
_FOSC(FCKSM_CSDCMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_NONE); // Clock Switching and Fail Safe Clock Monitor is disabled
// Multiple I/O reconfigurations admitted                                                                  // OSC2 Pin is digital I/O														                      // Primaire Oscillator Mode: none
_FWDT(FWDTEN_OFF & WINDIS_OFF); // Watchdog Timer off
_FPOR(ALTI2C_ON & FPWRT_PWR64); // 64 ms power-up timer
_FICD(JTAGEN_OFF & ICS_PGD2); // JTAG program port off
//------------------------------------------------------

unsigned char gAddrPins; // I2C expander address
unsigned char buttonstatus; // on board switches
char currentmot = 1;
unsigned char sensortrigger;
// Lcd strings
unsigned char startup[60] = "uBoard                                  "
        "Robotarm v1";
unsigned char motorstop[14] = "Motor stop   ";
unsigned char sensortrigged[20] = "Sensor triggered";
unsigned char error[60] = "Error                                  "
        "Device lockdown";
int main(void) {
    Init();
    Init_port();
    Init_mcp();
    Init_mcprobot();
    Init_timer1();
    TMR_ON = 0;
    Init_LCD();
    TRISBbits.TRISB11 = 0; // Activate buzzer
    Write_LCD(startup);

    while (1) {
        sensortrigger = Read23X08_17(GPIOA, PORTEXP_ROB);
        sensortrigger = ~sensortrigger;
        Shiftleds(sensortrigger);
        // Enable line LCD has to be high
        Write23X08_17(GPIOB, 0x40, PORTEXP_UBRD);

        if (sensortrigger != 0) {
            // All motors immediately off!
            Write23X08_17(GPIOB, ALLOFF, PORTEXP_ROB);
            Write_LCD(sensortrigged);
        }

        buttonstatus = Read23X08_17(GPIOB, PORTEXP_UBRD);
        buttonstatus = buttonstatus << 3;

        switch (buttonstatus) {
            case BTNLEFT:
                TMR_ON = 1;
                currentmot--;
                if (currentmot <= 0)
                    currentmot = 4;
                TMR_ON = 0;
                Delayms(500);
                break;

            case BTNRIGHT:
                TMR_ON = 1;
                currentmot++;
                if (currentmot > 4)
                    currentmot = 1;
                TMR_ON = 0;
                Delayms(500);
                break;

            case BTNUP:
                TMR_ON = 1;
                motorcontrol(currentmot, LEFT);
                TMR_ON = 0;
                break;

            case BTNDOWN:
                TMR_ON = 1;
                motorcontrol(currentmot, RIGHT);
                TMR_ON = 0;
                break;

            case BTNMID:
                TMR_ON = 1;
                // All motors off!
                Write23X08_17(GPIOB, ALLOFF, PORTEXP_ROB);
                Write_LCD(motorstop);
                TMR_ON = 0;

                // Error, reset device
            default:
            Write_LCD(error);

                if (currentmot <= 0)
                    currentmot = 4;
                if (currentmot > 4)
                    currentmot = 1;
        }
    }
}
