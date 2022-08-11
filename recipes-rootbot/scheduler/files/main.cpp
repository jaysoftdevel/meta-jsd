#include <iostream>
#include <fstream>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define TEST_IO_THING 3

#define IOCTL_LCD_WORKING_MODE _IOW(6, 1, unsigned long)
#define IOCTL_LCD_PIXEL_MODE _IOW(6, 2, unsigned long)
#define IOCTL_LCD_CLEAR_ALL _IOW(6, 3, unsigned long)
#define IOCTL_LCD_SETUP_WORKING_MODE _IOW(6,4, unsigned long)
#define IOCTL_LCD_INTRO _IOW(6,5, unsigned long)

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
	unsigned char positionLeft;
	unsigned char positionRight;
}MotorStatus;

typedef struct{
	DistanceSensors distanceSensors;
	ConnectionStatus connectionStatus;
	MotorStatus motorStatus;
	char currentLoad;
}DisplayData;

int main(void)
{
    int fd_st7565 = open("/dev/st7565",O_RDWR);
    int fd_hcsr04 = open("/dev/hcsr04",O_RDWR);
    int fd_stepperL = open("/dev/stepperL",O_RDWR);
    int fd_stepperR = open("/dev/stepperR",O_RDWR);
    
    std::string str_st7565("Test string for ST7565!!!");
    std::string str_hcsr04("Test string for HCSR04 range sensor!!!");
    std::string str_stepperL("Test string for Stepper motor LEFT!!!");
    std::string str_stepperR("Test string for Stepper motor RIGHT!!!");

    std::ofstream ofs_st7565;
    std::ofstream ofs_hcsr04;
    std::ofstream ofs_stepperL;
    std::ofstream ofs_stepperR;
    ofs_st7565.open("/dev/st7565", std::ios::out); // only write
    ofs_hcsr04.open("/dev/hcsr04",std::ios::out|std::ios::in); // read and write
    ofs_stepperL.open("/dev/stepperL",std::ios::out); // only write
    ofs_stepperR.open("/dev/stepperR",std::ios::out); // only write

    if (!ofs_st7565)
    {
        std::cout << "## opening of ST7565 failed..." << std::endl;
    }
    else
    {
        std::cout << "## opening of ST7565 successful!" << std::endl;
    }
    if (!ofs_hcsr04)
    {
        std::cout << "## opening of HCSR04 failed..." << std::endl;
    }
    else
    {
        std::cout << "## opening of HCSR04 successful!" << std::endl;
    }
    if (!ofs_stepperL)
    {
        std::cout << "## opening of StepperL failed..." << std::endl;
    }
    else
    {
        std::cout << "## opening of StepperL successful!" << std::endl;
    }
    if (!ofs_stepperR)
    {
        std::cout << "## opening of StepperR failed..." << std::endl;
    }
    else
    {
        std::cout << "## opening of StepperR successful!" << std::endl;
    }

    // Try to write some data
    std::cout << "## Write to st7565" << std::endl;
    ofs_st7565 << str_st7565;

    std::cout << "## Write to hcsr04" << std::endl;
    ofs_hcsr04 << str_hcsr04;

    std::cout << "## Write to stepperL" << std::endl;
    ofs_stepperL << str_stepperL;

    std::cout << "## Write to stepperR" << std::endl;
    ofs_stepperR <<str_stepperR;
    
    std::cout << "## Close write descriptor for LCD" << std::endl;
    ofs_st7565.close();

    sleep(1);
    std::cout << "## Test IOCTL \"unknown\" control request" << std::endl;    
    ioctl(fd_st7565, TEST_IO_THING, 5);

    // setup test data with dummy values
    DisplayData dd;
    dd.distanceSensors.distFrontLeft = 12;
    dd.distanceSensors.distFrontCenter = 34;
    dd.distanceSensors.distFrontRight = 56;
    dd.distanceSensors.distRearLeft = 78;
    dd.distanceSensors.distRearRight = 90;
    dd.connectionStatus.connectionStatus = true;
    dd.connectionStatus.ping = 123;
    dd.motorStatus.positionLeft = 54;
    dd.motorStatus.positionRight = 32;
    dd.currentLoad = 89;;
    std::cout << "## Test IOCTL with DisplayData" << std::endl;

    ioctl(fd_st7565, IOCTL_LCD_CLEAR_ALL, NULL);
    ioctl(fd_st7565, IOCTL_LCD_SETUP_WORKING_MODE, NULL);
    ioctl(fd_st7565, IOCTL_LCD_WORKING_MODE, &dd);

    std::cout << "## closing all devices again..." << std::endl;
    close(fd_st7565);
    ofs_hcsr04.close();
    ofs_stepperL.close();
    ofs_stepperR.close();
    return 0;
}