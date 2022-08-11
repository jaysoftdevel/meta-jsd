// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef STEPPERMOTOR_CONTROL_R_H
#define STEPPERMOTOR_CONTROL_R_H

/* Right after startup kernel and system are still quite busy
* which could cause even with "lower" rates to stumble.
* After system is stable a best practice value is 1300ms.
* Safe value would be around 1500µs or 1400µs. */
#define STEPPER_R_INTERVAL 1300

// macro to convert bank and gpio into pin number
#define GPIO_TO_PIN(bank, gpio) (32 * (bank) + (gpio))

// Data and control lines
#define COIL_PIN_NORTH	GPIO_TO_PIN(2, 22)	// P8_27, blue
#define COIL_PIN_EAST	GPIO_TO_PIN(2, 24)	// P8_28  red
#define COIL_PIN_SOUTH	GPIO_TO_PIN(2, 23)	// P8_29, green
#define COIL_PIN_WEST	GPIO_TO_PIN(2, 25)	// P8_30, black

#define COIL_PIN_OFFSET COIL_PIN_NORTH	// offset for base pin in iolib
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

long stepperR_control(struct file *f, unsigned int control, unsigned long value);
static ssize_t stepperR_write(struct file *f, const char __user *buf, size_t len, loff_t *off);
static int stepperR_open(struct inode *i, struct file *f);
static int stepperR_close(struct inode *i, struct file *f);

//int initStepperRGpio(void);
//int deinitStepperRGpio(void);
int stepRNone(void);
int stepFwdR(void);
int stepRevR(void);

//Do not add code below this line
#endif /* STEPPERMOTOR_CONTROL_R_H */
