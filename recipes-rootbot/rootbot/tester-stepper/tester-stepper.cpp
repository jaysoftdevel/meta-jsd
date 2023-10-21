#include <iostream>
#include <fstream>
#include <thread>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>

// #define DEBUG

#define TEST_IO_THING 3
#define LOAD_STAT_OFFSET 2

// #define IOCTL_LCD_WORKING_MODE _IOW(6, 1, unsigned long)
// #define IOCTL_LCD_PIXEL_MODE _IOW(6, 2, unsigned long)
// #define IOCTL_LCD_CLEAR_ALL _IOW(6, 3, unsigned long)
// #define IOCTL_LCD_SETUP_WORKING_MODE _IOW(6, 4, unsigned long)
// #define IOCTL_LCD_INTRO _IOW(6, 5, unsigned long)

// #define IOCTL_HCSR04_FL_TRIGGER _IOW(7, 0, unsigned long)
// #define IOCTL_HCSR04_FC_TRIGGER _IOW(7, 1, unsigned long)
// #define IOCTL_HCSR04_FR_TRIGGER _IOW(7, 2, unsigned long)
// #define IOCTL_HCSR04_RL_TRIGGER _IOW(7, 3, unsigned long)
// #define IOCTL_HCSR04_RR_TRIGGER _IOW(7, 4, unsigned long)

#define IOCTL_STEPPER_L_STEP_FWD _IOW(8, 0, unsigned long)
#define IOCTL_STEPPER_L_STEP_REV _IOW(8, 1, unsigned long)
#define IOCTL_STEPPER_L_STEP_NONE _IOW(8, 2, unsigned long)

#define IOCTL_STEPPER_R_STEP_FWD _IOW(9, 0, unsigned long)
#define IOCTL_STEPPER_R_STEP_REV _IOW(9, 1, unsigned long)
#define IOCTL_STEPPER_R_STEP_NONE _IOW(9, 2, unsigned long)

#define DEMO_STEPS 5000

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
    unsigned short positionLeft;
    unsigned short positionRight;
} MotorStatus;

typedef struct
{
    DistanceSensors distanceSensors;
    ConnectionStatus connectionStatus;
    MotorStatus motorStatus;
    unsigned char currentLoad;
} DisplayData;

// std::thread t_display;
// std::thread t_hcsr04;
std::thread t_stepperL;
std::thread t_stepperR;

static DisplayData dd;

// static int fd_hcsr04;
static int fd_stepperL;
static int fd_stepperR;
// static int fd_st7565;

// unsigned char getLoad();
int testDeviceFiles();
// int testDisplay();
// int testHCSR04();
int testStepperL();
int testStepperR();
void sig_handler(int signo);

static bool m_stop = false;

// detect if image is built for QEMU
#define QEMUARM qemuarm
#define QEMUARM64 qemuarm64
#if defined(MACHINE) && (MACHINE == QEMUARM || MACHINE == QEMUARM64)
#define BUILD_FOR_QEMU
#endif

int main(void)
{
    int ret;

    std::cout << "### Register signal handler" << std::endl;
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        std::cout << "### Failed to register signal handler" << std::endl;
    }
    std::cout << "### Initialize cpustat kernel file" << std::endl;
    std::cout << "### Test Device files" << std::endl;
    ret = testDeviceFiles();
    if (ret != 0)
    {
        std::cout << "### test device files failed with: " << ret << std::endl;
        return -1;
    }
    sleep(2);
    std::cout << "### Testing with parallel threads... " << ret << std::endl;
    t_stepperL = std::thread(testStepperL);
    t_stepperR = std::thread(testStepperR);

    std::cout << "### Waiting for threads to join" << std::endl;
    t_stepperL.join();
    std::cout << "### StepperL joined" << std::endl;
    t_stepperR.join();
    std::cout << "### StepperR joined" << std::endl;
    std::cout << "### All threads joined" << std::endl;
    return 0;
}

void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
        std::cout << "### Received signal: " << signo << std::endl;
        
        if (t_stepperL.joinable())
        {
            std::cout << "### stepperL still running, detaching..." << std::endl;
            t_stepperL.detach();
        }
        if (t_stepperR.joinable())
        {
            std::cout << "### stepperR still running, detaching..." << std::endl;
            t_stepperR.detach();
        }
        // check for open file descriptors
        int fd_state = fcntl(fd_stepperL, F_GETFL);
        if (fd_state == -1)
        {
            std::cout << "### stepperL file stille open, closing" << std::endl;
            close(fd_stepperL);
        }
        fd_state = fcntl(fd_stepperR, F_GETFL);
        if (fd_state == -1)
        {
            std::cout << "### stepperR file stille open, closing" << std::endl;
            close(fd_stepperR);
        }


        std::cout << "###### Ultimately terminating everything..." << std::endl;
        m_stop = true;
        std::terminate();
        //std::exit(SIGINT);
        // raise(SIGKILL);
    }
}

int testStepperL()
{
    int i, ret;
    fd_stepperL = open("/dev/stepperL", O_RDWR);
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    std::cout << "## testing stepperL forward" << std::endl;
    for (i = 0; i < DEMO_STEPS; i++)
    {

        if (dd.motorStatus.positionLeft++ > 359)
        {
            dd.motorStatus.positionLeft = 0;
        }

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
        if (dd.motorStatus.positionLeft-- <= 0)
        {
            dd.motorStatus.positionLeft = 359;
        }

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
    fd_stepperR = open("/dev/stepperR", O_RDWR);
    std::cout << "## enter " << __FUNCTION__ << std::endl;

    std::cout << "## testing stepperR forward" << std::endl;
    for (i = 0; i < DEMO_STEPS; i++)
    {
        ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_FWD, NULL);
        if (ret != 0)
        {
            std::cout << "## test StepperR fwd failed with: " << ret << std::endl;
            return -5;
        }
        if (++dd.motorStatus.positionRight >= 360)
        {
            dd.motorStatus.positionRight = 0;
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

        if (--dd.motorStatus.positionRight <= 0)
        {
            dd.motorStatus.positionRight = 359;
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

unsigned char getLoad()
{
    std::ifstream loadavg("/proc/loadavg", std::ifstream::in);
    std::string loadStr;
    if (!loadavg.is_open())
    {
        std::cout << "### error opening schedstat file..." << std::endl;
        return -1;
    }

    for (int i = 0; i < LOAD_STAT_OFFSET; i++)
    {
        loadavg.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
    // extract
    std::getline(loadavg, loadStr, ' ');
    float load = std::stof(loadStr);
    return static_cast<unsigned char>(load * 100);
}

int testDeviceFiles()
{
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    // std::string str_st7565("Test string for ST7565!!!");
    // std::string str_hcsr04("Test string for HCSR04 range sensor!!!");
    std::string str_stepperL("Test string for Stepper motor LEFT!!!");
    std::string str_stepperR("Test string for Stepper motor RIGHT!!!");

    // std::ofstream ofs_st7565;
    // std::ofstream ofs_hcsr04;
    std::ofstream ofs_stepperL;
    std::ofstream ofs_stepperR;
    // ofs_st7565.open("/dev/st7565", std::ios::out);                // only write
    // ofs_hcsr04.open("/dev/hcsr04", std::ios::out | std::ios::in); // read and write
    ofs_stepperL.open("/dev/stepperL", std::ios::out);            // only write
    ofs_stepperR.open("/dev/stepperR", std::ios::out);            // only write

    // if (!ofs_st7565)
    // {
    //     std::cout << "## opening of ST7565 failed..." << std::endl;
    //     return -1;
    // }
    // else
    // {
    //     std::cout << "## opening of ST7565 successful!" << std::endl;
    // }
    // if (!ofs_hcsr04)
    // {
    //     std::cout << "## opening of HCSR04 failed..." << std::endl;
    //     return -2;
    // }
    // else
    // {
    //     std::cout << "## opening of HCSR04 successful!" << std::endl;
    // }
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

    // // Try to write some data
    // std::cout << "## Write to st7565" << std::endl;
    // ofs_st7565 << str_st7565;

    // std::cout << "## Write to hcsr04" << std::endl;
    // ofs_hcsr04 << str_hcsr04;

    std::cout << "## Write to stepperL" << std::endl;
    ofs_stepperL << str_stepperL;

    std::cout << "## Write to stepperR" << std::endl;
    ofs_stepperR << str_stepperR;

    std::cout << "## Close all descriptors" << std::endl;

    // ofs_st7565.close();
    // ofs_hcsr04.close();
    ofs_stepperL.close();
    ofs_stepperR.close();
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    return 0;
}