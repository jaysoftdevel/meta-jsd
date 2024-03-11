/*
 * lcd.h
 *
 *  Created on: Dec 23, 2014
 *  Author: done
 */

#ifndef __ST7565_KERNEL_MODULE_H
#define __ST7565_KERNEL_MODULE_H
//#include <stdbool.h>

#define DEBUG

// macro to convert bank and gpio into pin number
#define GPIO_TO_PIN(bank, gpio) (32 * (bank) + (gpio))

// Data and control lines
#define ST7565_CS GPIO_TO_PIN(1, 13)  // P8_11
#define ST7565_RST GPIO_TO_PIN(2, 1)  // P8_18
#define ST7565_AP GPIO_TO_PIN(0, 23)  // P8_13
#define ST7565_A0 GPIO_TO_PIN(0, 26)  // P8_14
#define ST7565_CLK GPIO_TO_PIN(1, 15) // P8_15
#define ST7565_SI GPIO_TO_PIN(1, 14)  // P8_16
#define IOCTL_TEST _IOW(0, 6, unsigned long)

/* Dont support text mode in IOCTL!!
	-> length of data cannot be determined
	and therefore buffer length is unknown!
*/
//#define IOCTL_LCD_TEXT_MODE _IOW(6, 0, unsigned long)
#define IOCTL_LCD_WORKING_MODE _IOW(6, 1, unsigned long)
#define IOCTL_LCD_PIXEL_MODE _IOW(6, 2, unsigned long)
#define IOCTL_LCD_CLEAR_ALL _IOW(6, 3, unsigned long)
#define IOCTL_LCD_SETUP_WORKING_MODE _IOW(6,4, unsigned long)
#define IOCTL_LCD_INTRO _IOW(6,5, unsigned long)

#define LCD_COLS 128
#define LCD_PAGES 8
#define TOKENSIZE 6

// detect if image is built for QEMU
#define QEMUARM qemuarm
#define QEMUARM64 qemuarm64
#if defined(MACHINE) && (MACHINE == QEMUARM || MACHINE == QEMUARM64)
#define BUILD_FOR_QEMU
#endif

extern void write_banner(void);

typedef struct{
	unsigned char distFrontLeft;	
	unsigned char distFrontCenter;
	unsigned char distFrontRight;
	unsigned char distRearLeft;
	unsigned char distRearRight;
}DistanceSensors;

typedef struct{
	unsigned int ping;
	bool connectionStatus;
}ConnectionStatus;

typedef struct{
	unsigned short positionLeft;
	unsigned short positionRight;
}MotorStatus;

typedef struct{
	DistanceSensors distanceSensors;
	ConnectionStatus connectionStatus;
	MotorStatus motorStatus;
	unsigned char currentLoad;
}DisplayData;

#endif // __ST7565_KERNEL_MODULE_H
