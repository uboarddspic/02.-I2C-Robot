/*
 * Prototype definitions for user data
 */
#ifndef	__Userdata_h
#define	__Userdata_h

// User defined settings
#define BTNDOWN    0xF0     // switch status: 1 1 1 1 0
#define BTNRIGHT   0xE8     // switch status: 1 1 1 0 1
#define BTNMID     0xD8     // switch status: 1 1 0 1 1
#define BTNLEFT    0xB8     // switch status: 1 0 1 1 1
#define BTNUP      0x78     // switch status: 0 1 1 1 1

#define MOTOR_X     0X01
#define MOTOR_Y     0X02
#define MOTOR_Z     0X04
#define MOTOR_GRAB  0X04

#define LEFT      1
#define RIGHT    0
#define ALLOFF  0x00

#define PORTEXP_ROB    0x02
#define PORTEXP_UBRD    0x00

#define M1LEFT 0x01
#define M1RIGHT 0x02
#define M2LEFT 0x04
#define M2RIGHT 0x08
#define M3LEFT 0x10
#define M3RIGHT 0x20
#define M4LEFT 0x40
#define M4RIGHT 0x80

#define TMR_ON  IEC0bits.T1IE

void Init_mcprobot(void);
void motorcontrol(unsigned char currentmot, unsigned char direction);

#endif	//__USERDATA__
