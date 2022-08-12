#include <iostream>
#include <fstream>
#include <thread>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define TEST_IO_THING 3

#define IOCTL_LCD_WORKING_MODE _IOW(6, 1, unsigned long)
#define IOCTL_LCD_PIXEL_MODE _IOW(6, 2, unsigned long)
#define IOCTL_LCD_CLEAR_ALL _IOW(6, 3, unsigned long)
#define IOCTL_LCD_SETUP_WORKING_MODE _IOW(6, 4, unsigned long)
#define IOCTL_LCD_INTRO _IOW(6, 5, unsigned long)

#define IOCTL_HCSR04_FL_TRIGGER _IOW(7, 0, unsigned long)
#define IOCTL_HCSR04_FC_TRIGGER _IOW(7, 1, unsigned long)
#define IOCTL_HCSR04_FR_TRIGGER _IOW(7, 2, unsigned long)
#define IOCTL_HCSR04_RL_TRIGGER _IOW(7, 3, unsigned long)
#define IOCTL_HCSR04_RR_TRIGGER _IOW(7, 4, unsigned long)

#define IOCTL_STEPPER_L_STEP_FWD _IOW(8, 0, unsigned long)
#define IOCTL_STEPPER_L_STEP_REV _IOW(8, 1, unsigned long)
#define IOCTL_STEPPER_L_STEP_NONE _IOW(8, 2, unsigned long)

#define IOCTL_STEPPER_R_STEP_FWD _IOW(9, 0, unsigned long)
#define IOCTL_STEPPER_R_STEP_REV _IOW(9, 1, unsigned long)
#define IOCTL_STEPPER_R_STEP_NONE _IOW(9, 2, unsigned long)

typedef struct
{
    unsigned char distFrontLeft;
    unsigned char distFrontCenter;
    unsigned char distFrontRight;
    unsigned char distRearLeft;
    unsigned char distRearRight;
} DistanceSensors;

typedef struct
{
    unsigned int ping;
    bool connectionStatus;
} ConnectionStatus;

typedef struct
{
    unsigned char positionLeft;
    unsigned char positionRight;
} MotorStatus;

typedef struct
{
    DistanceSensors distanceSensors;
    ConnectionStatus connectionStatus;
    MotorStatus motorStatus;
    char currentLoad;
} DisplayData;

static DisplayData dd;

int testDeviceFiles();
int testDisplay();
int testHCSR04();
int testStepperL();
int testStepperR();

int main(void)
{
    int ret;
    std::cout << "### Test Device files" << std::endl;
    ret = testDeviceFiles();
    if (ret != 0)
    {
        std::cout << "### test device files failed with: " << ret << std::endl;
        return -1;
    }
    /* Sequencial test of all components */
    // sleep(2);
    // std::cout << "### Test display" << std::endl;
    // ret = testDisplay();
    // if (ret != 0)
    // {
    //     std::cout << "### test display failed with: " << ret << std::endl;
    //     return -2;
    // }
    // sleep(2);
    // std::cout << "### Test HCSR04 files" << std::endl;
    // ret = testHCSR04();
    // if (ret != 0)
    // {
    //     std::cout << "### test HCSR04 failed with: " << ret << std::endl;
    //     return -3;
    // }
    // sleep(2);
    // std::cout << "### Test Steppers files" << std::endl;
    // ret = testStepper();
    // if (ret != 0)
    // {
    //     std::cout << "### test Steppers failed with: " << ret << std::endl;
    //     return -4;
    // }
    std::cout << "### Testing with parallel threads... " << ret << std::endl;
    sleep(2);
    std::thread t_display (testDisplay);
    sleep(2);
    std::thread t_hcsr04 (testHCSR04);
    std::thread t_stepperL (testStepperL);
    std::thread t_stepperR (testStepperR);

    t_display.join();
    t_hcsr04.join();
    t_stepperL.join();
    t_stepperR.join();
    return 0;
}

int testStepperL()
{
    int i, ret;
    int fd_stepperL = open("/dev/stepperL", O_RDWR);
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    std::cout << "## testing stepperL forward" << std::endl;
    for (i = 0; i < 1500; i++)
    {
        ret = ioctl(fd_stepperL, IOCTL_STEPPER_L_STEP_FWD, NULL);
        if (ret != 0)
        {
            std::cout << "## test StepperL fwd failed with: " << ret << std::endl;
            return -1;
        }
        usleep(1300);
    }
    ret = ioctl(fd_stepperL, IOCTL_STEPPER_L_STEP_NONE, NULL);
    if (ret != 0)
    {
        std::cout << "## test StepperL none failed with: " << ret << std::endl;
        return -2;
    }
    std::cout << "## testing stepperL reverse" << std::endl;
    for (i = 0; i < 1500; i++)
    {
        ret = ioctl(fd_stepperL, IOCTL_STEPPER_L_STEP_REV, NULL);
        if (ret != 0)
        {
            std::cout << "## test StepperL rev failed with: " << ret << std::endl;
            return -3;
        }
        usleep(1300);
    }
    ret = ioctl(fd_stepperL, IOCTL_STEPPER_L_STEP_NONE, NULL);
    if (ret != 0)
    {
        std::cout << "## test StepperL none failed with: " << ret << std::endl;
        return -4;
    }
    std::cout << "## Close stepperL " << std::endl;
    close(fd_stepperL);
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    return 0;
}

int testStepperR()
{
    int i, ret;
    int fd_stepperR = open("/dev/stepperR", O_RDWR);
    std::cout << "## enter " << __FUNCTION__ << std::endl;

    std::cout << "## testing stepperR forward" << std::endl;
    for (i = 0; i < 1500; i++)
    {
        ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_FWD, NULL);
        if (ret != 0)
        {
            std::cout << "## test StepperR fwd failed with: " << ret << std::endl;
            return -5;
        }
        usleep(1300);
    }
    ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_NONE, NULL);
    if (ret != 0)
    {
        std::cout << "## test StepperR none failed with: " << ret << std::endl;
        return -6;
    }
    std::cout << "## testing stepperR reverse" << std::endl;
    for (i = 0; i < 1500; i++)
    {
        ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_REV, NULL);
        if (ret != 0)
        {
            std::cout << "## test StepperR rev failed with: " << ret << std::endl;
            return -7;
        }
        usleep(1300);
    }
    ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_NONE, NULL);
    if (ret != 0)
    {
        std::cout << "## test StepperR none failed with: " << ret << std::endl;
        return -8;
    }
    std::cout << "## Close steppers " << std::endl;
    close(fd_stepperR);
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    return 0;
}

int testHCSR04()
{
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    int fd_hcsr04 = open("/dev/hcsr04", O_RDWR);

    for (int i = 0; i < 50; i++)
    {
        dd.distanceSensors.distFrontLeft = ioctl(fd_hcsr04, IOCTL_HCSR04_FL_TRIGGER, NULL);
        //std::cout << "## FL value is: " << FL << std::endl;
        dd.distanceSensors.distFrontCenter = ioctl(fd_hcsr04, IOCTL_HCSR04_FC_TRIGGER, NULL);
        //std::cout << "## FC value is: " << FC << std::endl;
        dd.distanceSensors.distFrontRight = ioctl(fd_hcsr04, IOCTL_HCSR04_FR_TRIGGER, NULL);
        //std::cout << "## FR value is: " << FR << std::endl;
        dd.distanceSensors.distRearLeft = ioctl(fd_hcsr04, IOCTL_HCSR04_RL_TRIGGER, NULL);
        //std::cout << "## RL value is: " << RL << std::endl;
        dd.distanceSensors.distRearRight = ioctl(fd_hcsr04, IOCTL_HCSR04_RR_TRIGGER, NULL);
        //std::cout << "## RR value is: " << RR << std::endl;
        
    }
    std::cout << "## Close HCSR04 ..." << std::endl;
    close(fd_hcsr04);
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    return 0;
}

int testDisplay()
{
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    std::cout << "## Test IOCTL \"unknown\" control request" << std::endl;
    int fd_st7565 = open("/dev/st7565", O_RDWR);
    // planned error!
    if (ioctl(fd_st7565, TEST_IO_THING, 5) != -1)
    {
        std::cout << "## Unexpected control return..." << std::endl;
        return -1;
    }
    std::cout << "## Write banner sequence" << std::endl;
    if (ioctl(fd_st7565, IOCTL_LCD_CLEAR_ALL, NULL) != 0)
    {
        std::cout << "## Clearing display failed" << std::endl;
        return -2;
    }
    if (ioctl(fd_st7565, IOCTL_LCD_INTRO, NULL) != 0)
    {
        std::cout << "## Clearing display failed" << std::endl;
        return -3;
    }

    std::cout << "## Test IOCTL with DisplayData" << std::endl;

    if (ioctl(fd_st7565, IOCTL_LCD_CLEAR_ALL, NULL) != 0)
    {
        std::cout << "## Clearing display failed" << std::endl;
        return -4;
    }
    if (ioctl(fd_st7565, IOCTL_LCD_SETUP_WORKING_MODE, NULL) != 0)
    {
        std::cout << "## Set working mode failed" << std::endl;
        return -5;
    }
    if (ioctl(fd_st7565, IOCTL_LCD_WORKING_MODE, &dd) != 0)
    {
        std::cout << "## Switch to working mode failed" << std::endl;
        return -6;
    }

    for (int i = 0; i < 30; i++)
    {
        dd.distanceSensors.distFrontLeft++;
        dd.distanceSensors.distFrontCenter--;
        dd.distanceSensors.distFrontRight++;
        dd.distanceSensors.distRearLeft--;
        dd.distanceSensors.distRearRight++;
        dd.connectionStatus.connectionStatus=~(dd.connectionStatus.connectionStatus);
        dd.connectionStatus.ping--;
        dd.motorStatus.positionLeft++;
        dd.motorStatus.positionRight--;
        dd.currentLoad++;
        if (ioctl(fd_st7565, IOCTL_LCD_WORKING_MODE, &dd) != 0)
        {
            std::cout << "## Switch to working mode failed" << std::endl;
            std::terminate();
        }
        usleep(300 * 1000);
    }

    std::cout << "## Close display..." << std::endl;
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    close(fd_st7565);
    return 0;
}

int testDeviceFiles()
{
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    std::string str_st7565("Test string for ST7565!!!");
    std::string str_hcsr04("Test string for HCSR04 range sensor!!!");
    std::string str_stepperL("Test string for Stepper motor LEFT!!!");
    std::string str_stepperR("Test string for Stepper motor RIGHT!!!");

    std::ofstream ofs_st7565;
    std::ofstream ofs_hcsr04;
    std::ofstream ofs_stepperL;
    std::ofstream ofs_stepperR;
    ofs_st7565.open("/dev/st7565", std::ios::out);                // only write
    ofs_hcsr04.open("/dev/hcsr04", std::ios::out | std::ios::in); // read and write
    ofs_stepperL.open("/dev/stepperL", std::ios::out);            // only write
    ofs_stepperR.open("/dev/stepperR", std::ios::out);            // only write

    if (!ofs_st7565)
    {
        std::cout << "## opening of ST7565 failed..." << std::endl;
        return -1;
    }
    else
    {
        std::cout << "## opening of ST7565 successful!" << std::endl;
    }
    if (!ofs_hcsr04)
    {
        std::cout << "## opening of HCSR04 failed..." << std::endl;
        return -2;
    }
    else
    {
        std::cout << "## opening of HCSR04 successful!" << std::endl;
    }
    if (!ofs_stepperL)
    {
        std::cout << "## opening of StepperL failed..." << std::endl;
        return -3;
    }
    else
    {
        std::cout << "## opening of StepperL successful!" << std::endl;
    }
    if (!ofs_stepperR)
    {
        std::cout << "## opening of StepperR failed..." << std::endl;
        return -4;
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
    ofs_stepperR << str_stepperR;

    std::cout << "## Close all descriptors" << std::endl;

    ofs_st7565.close();
    ofs_hcsr04.close();
    ofs_stepperL.close();
    ofs_stepperR.close();
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    return 0;
}
