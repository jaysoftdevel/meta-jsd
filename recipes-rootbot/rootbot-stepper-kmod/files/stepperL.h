// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef STEPPERMOTOR_CONTROL_L_H
#define STEPPERMOTOR_CONTROL_L_H

/* Right after startup kernel and system are still quite busy
* which could cause even with "lower" rates to stumble.
* After system is stable a best practice value is 1300ms.
* Safe value would be around 1500µs or 1400µs. */
#define STEPPER_L_INTERVAL 1300

// macro to convert bank and gpio into pin number
#define GPIO_TO_PIN(bank, gpio) (32 * (bank) + (gpio))

// Data and control lines
#define COIL_PIN_NORTH	GPIO_TO_PIN(2, 16)	// P8_36, blue
#define COIL_PIN_EAST	GPIO_TO_PIN(0, 8)	// P8_35  red
#define COIL_PIN_SOUTH	GPIO_TO_PIN(2, 17)	// P8_34, green
#define COIL_PIN_WEST	GPIO_TO_PIN(0, 9)	// P8_33, black

#define COIL_PIN_OFFSET COIL_PIN_WEST	// offset for base pin in iolib
#define NUM_OF_COILS 4	// for the 4 coil stepper motor
#define DELAY  1500 /* microseconds between steps */

/* Global variables of the driver */
#define CM_PER_BASE 0x44e00000
#define CM_WKUP_BASE 0x44e00400
#define GPIO0_CLK_CONFIG_OFFSET 0x8

//add your function definitions for the project Ultrtasonic_Distance_Simple here
typedef unsigned char uint8;
typedef struct tPos{
	uint8 coils[4];
	uint8 pos :2; // use 2bit field, to check for coil number, just use the overrun of the bitfield
}tPos;

//int initStepperRGpio(void);
//int deinitStepperRGpio(void);
int stepLNone(void);
int stepFwdL(void);
int stepRevL(void);

//Do not add code below this line
#endif /* STEPPERMOTOR_CONTROL_L_H */
