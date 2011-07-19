///////////////////////////////////////////////////////////////////////////
//
//  File Name    : Userdata.c
//  Version      : 1.0
//  Description  : Code for controlling external motor board
//  Author       : Jim Clermonts
//  Target       : dsPIC33FJ64GP802 on uBRD
//  Compiler     : MPLAB C Compiler for PIC24 and dsPIC v3.25 in LITE mode
//  IDE          : MPLAB X IDE Beta4.0
//  Programmer   : uBRD bootloader
//  Last Updated : 09-03-2011
//
///////////////////////////////////////////////////////////////////////////
#include	"uBRD.h"
#include	"Delay.h"
#include	"Peripherals.h"

    unsigned char direction;
    unsigned char motor1l[60]=  "Motor 1                              "
                                "   Left    ";
    unsigned char motor1r[60]=  "Motor 1                              "
                                "   Right    ";
    unsigned char motor2l[60]=  "Motor 2                              "
                                "   Left    ";
    unsigned char motor2r[60]=  "Motor 2                              "
                                "   Right    ";

    unsigned char motor3l[60]=  "Motor 3                              "
                                "   Left    ";
    unsigned char motor3r[60]=  "Motor 3                              "
                                "   Right    ";
    unsigned char motor4l[60]=  "Motor 4                              "
                                "   Left    ";
    unsigned char motor4r[60]=  "Motor 4                              "
                                "   Right    ";

void Init_mcprobot(void)
{
  unsigned int config2, config1;
  config2 = 0x190;   // Baud rate is set for 100 Khz
  config1 = 0b1000001000100000;
  /*        (I2C_ON & I2C_IDLE_CON & I2C_CLK_HLD & I2C_IPMI_DIS & I2C_7BIT_ADD & I2C_SLW_DIS & I2C_SM_DIS &
             I2C_GCALL_DIS & I2C_STR_DIS & I2C_NACK & I2C_ACK_DIS & I2C_RCV_DIS & I2C_STOP_DIS & 
             I2C_RESTART_DIS & I2C_START_DIS);*/
  OpenI2C1(config1,config2);    // Configure I2C for 7 bit address mode 
  IdleI2C1();

  //Initialize MCP23017 i2c I/O expander 
  Write23X08_17(IOCONA,0b01111000,0x02);
  Write23X08_17(GPPUA,0xFF,0x02);    // Set Pull-up resistors
  Write23X08_17(GPPUB,0x00,0x02);    // Set Pull-up resistors
  Write23X08_17(IPOLA,0x00,0x02);    // I/O polarity normal
  Write23X08_17(IPOLB,0x00,0x02);    // I/O polarity normal
  Write23X08_17(GPIOA,0x00,0x02);    // Row is kept LOW while changing I/O
  Write23X08_17(GPIOB,0x00,0x02);    // Row is kept LOW while changing I/O
  Write23X08_17(IODIRA,0xFF,0x02);   // GPIOA 0/7 are the sensors
  Write23X08_17(IODIRB,0x00,0x02);   // GPIOB 0/7 are the motors
}
								
void motorcontrol(unsigned char currentmot, unsigned char direction)
{
    if ((currentmot==1) && (direction==LEFT))
    {
        Write23X08_17(GPIOB,M1LEFT,PORTEXP_ROB);
        write_lcd(motor1l);
    }

    if ((currentmot==1) && (direction==RIGHT))
    {
        Write23X08_17(GPIOB,M1RIGHT,PORTEXP_ROB);
        write_lcd(motor1r);
    }

    if ((currentmot==2) && (direction==LEFT))
    {
        Write23X08_17(GPIOB,M2LEFT,PORTEXP_ROB);
        write_lcd(motor2l);
    }

    if ((currentmot==2) && (direction==RIGHT))
    {
        Write23X08_17(GPIOB,M2RIGHT,PORTEXP_ROB);
        write_lcd(motor2r);
    }

    if ((currentmot==3) && (direction==LEFT))
    {
        Write23X08_17(GPIOB,M3LEFT,PORTEXP_ROB);
        write_lcd(motor3l);
    }

    if ((currentmot==3) && (direction==RIGHT))
    {
        Write23X08_17(GPIOB,M3RIGHT,PORTEXP_ROB);
        write_lcd(motor3r);
    }

    if ((currentmot==4) && (direction==LEFT))
    {
        Write23X08_17(GPIOB,M4LEFT,PORTEXP_ROB);
        write_lcd(motor4l);
    }

    if ((currentmot==4) && (direction==RIGHT))
    {
        Write23X08_17(GPIOB,M4RIGHT,PORTEXP_ROB);
        write_lcd(motor4r);
    }
}
