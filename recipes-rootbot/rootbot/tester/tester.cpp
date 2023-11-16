#include "rootbot.h"

#include <iostream>
#include <thread>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

std::thread t_display;
std::thread t_hcsr04;
std::thread t_stepperL;
std::thread t_stepperR;

static DisplayData dd;

static int fd_hcsr04;
static int fd_stepperL;
static int fd_stepperR;
static int fd_st7565;

unsigned char getLoad();
int testDeviceFiles();
int testDisplay();
int testHCSR04();
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
    std::thread t_display(testDisplay);
    pthread_t displayThreadHandle = t_display.native_handle();
    auto threadError = pthread_setname_np(displayThreadHandle, "Display");
    if (threadError) {
        std::cerr << "Error setting thread name: " << threadError << std::endl;
    }
    sleep(5);

    std::thread t_hcsr04(testHCSR04);
    pthread_t hcsr04ThreadHandle = t_hcsr04.native_handle();
    threadError = pthread_setname_np(hcsr04ThreadHandle, "Sensors");
    if (threadError) {
        std::cerr << "Error setting thread name: " << threadError << std::endl;
    }

    auto fd_state = fcntl(fd_stepperL, F_GETFL);
    std::cout << "### BEFORE: " << std::to_string(fd_state) << " #" << std::endl;
    std::thread t_stepperL(testStepperL);
    pthread_t stepperLThreadHandle = t_display.native_handle();
    threadError = pthread_setname_np(stepperLThreadHandle, "StepperL");
    if (threadError) {
        std::cerr << "Error setting thread name: " << threadError << std::endl;
    }

    std::thread t_stepperR(testStepperR);
    pthread_t stepperRThreadHandle = t_display.native_handle();
    threadError = pthread_setname_np(stepperRThreadHandle, "StepperR");
    if (threadError) {
        std::cerr << "Error setting thread name: " << threadError << std::endl;
    }

    std::cout << "### Waiting for threads to join" << std::endl;
    t_display.join();
    std::cout << "### Display joined" << std::endl;
    t_hcsr04.join();
    std::cout << "### HCSR04 joined" << std::endl;
    t_stepperL.join();
    std::cout << "### StepperL joined" << std::endl;
    t_stepperR.join();
    std::cout << "### StepperR joined" << std::endl;
    return 0;
}

void sig_handler(int signo)
{
    // stop all threads and disarm motors
    m_stop = true;

    if (signo == SIGINT)
    {
        // std::cout << "### Received signal: " << signo << std::endl;
        // if (t_display.joinable())
        // {
        //     std::cout << "### display still running, detaching..." << std::endl;
        //     t_display.detach();
        // }
        // if (t_stepperL.joinable())
        // {
        //     std::cout << "### stepperL still running, detaching..." << std::endl;
        //     t_stepperL.detach();
        // }
        // if (t_stepperR.joinable())
        // {
        //     std::cout << "### stepperR still running, detaching..." << std::endl;
        //     t_stepperR.detach();
        // }
        // if (t_hcsr04.joinable())
        // {
        //     std::cout << "### HCSR04 still running, detaching..." << std::endl;
        //     t_hcsr04.detach();
        // }
        // // check for open file descriptors
        // int fd_state = fcntl(fd_hcsr04, F_GETFL);
        // if (fd_state == -1)
        // {
        //     std::cout << "### HCSR04 file stille open, closing" << std::endl;
        //     close(fd_hcsr04);
        // }
        // fd_state = fcntl(fd_stepperL, F_GETFL);
        // if (fd_state == -1)
        // {
        //     std::cout << "### stepperL file still open, closing" << std::endl;
        //     int ret = ioctl(fd_stepperL, IOCTL_STEPPER_R_STEP_NONE, NULL);
        //     if (ret != 0)
        //     {
        //         std::cout << "## test StepperR none failed with: " << ret << std::endl;
        //     }
        //     close(fd_stepperL);
        // }
        // fd_state = fcntl(fd_stepperR, F_GETFL);
        // std::cout << "#### FL: " << std::to_string(fd_state) << " # FD: " << std::to_string(fcntl(fd_stepperR, F_GETFD)) << " ##" << std::endl;
        
        // if (fd_state == -1)
        // {
        //     std::cout << "### stepperR file still open, closing" << std::endl;
        //                 int ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_NONE, NULL);
        //     if (ret != 0)
        //     {
        //         std::cout << "## test StepperR none failed with: " << ret << std::endl;
        //     }
        //     close(fd_stepperR);
        // }
        // fd_state = fcntl(fd_st7565, F_GETFL);
        // if (fd_state == -1)
        // {
        //     std::cout << "### display file stille open, closing" << std::endl;
        //     close(fd_st7565);
        // }

        // close(fd_hcsr04);
        // close(fd_st7565);
        // auto ret = ioctl(fd_stepperL, IOCTL_STEPPER_R_STEP_NONE, NULL);
        //     if (ret != 0)
        //     {
        //         std::cout << "## stop StepperL none failed with: " << ret << std::endl;
        //     }
        // close(fd_stepperL);
        // ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_NONE, NULL);
        // if (ret != 0)
        // {
        //     std::cout << "## test StepperR none failed with: " << ret << std::endl;
        // }
        // close(fd_stepperR);
        // t_display.detach();
        // t_hcsr04.detach();
        // t_stepperL.detach();
        // t_stepperR.detach();

        // std::cout << "###### Ultimately terminating everything..." << std::endl;        
        // std::exit(SIGINT);
        // raise(SIGKILL);
    }
    else{
        std::cout << "###### Received non SIGINT signal: " << std::to_string(signo) << std::endl;
    }
}

int testStepperL()
{
    int i, ret;
    fd_stepperL = open("/dev/stepperL", O_RDWR);
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    while (!m_stop)
    {

        if (dd.motorStatus.positionLeft++ > 359)
        {
            dd.motorStatus.positionLeft = 0;
            auto fd_state = fcntl(fd_stepperL, F_GETFL);
            std::cout << "### WITHIN: " << std::to_string(fd_state) << " #" << std::endl;
        }

        ret = ioctl(fd_stepperL, IOCTL_STEPPER_L_STEP_FWD, NULL);
        if (ret != 0)
        {
            std::cout << "## test StepperL fwd failed with: " << ret << std::endl;
            return -1;
        }
        usleep(1300);
    }
    std::cout << "## stopping StepperL" << std::endl;
    ret = ioctl(fd_stepperL, IOCTL_STEPPER_L_STEP_NONE, NULL);
    auto fd_state = fcntl(fd_stepperL, F_GETFL);
            std::cout << "### AFTER: " << std::to_string(fd_state) << " #" << std::endl;
    if (ret != 0)
    {
        std::cout << "## test StepperL none failed with: " << ret << std::endl;
        return -2;
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
    while (!m_stop)
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
    std::cout << "## stopping StepperR" << std::endl;
    ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_NONE, NULL);
    if (ret != 0)
    {
        std::cout << "## test StepperR none failed with: " << ret << std::endl;
        return -8;
    }
    std::cout << "## Close stepperR " << std::endl;
    close(fd_stepperR);
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    return 0;
}

int testHCSR04()
{
    std::cout << "## enter " << __FUNCTION__ << std::endl;

    fd_hcsr04 = open("/dev/hcsr04", O_RDWR);

    while (!m_stop)
    {
        dd.distanceSensors.distFrontLeft = ioctl(fd_hcsr04, IOCTL_HCSR04_FL_TRIGGER, NULL);
        usleep(100 * 1000);
        // std::cout << "## FL value is: " << FL << std::endl;
        dd.distanceSensors.distFrontCenter = ioctl(fd_hcsr04, IOCTL_HCSR04_FC_TRIGGER, NULL);
        usleep(100 * 1000);
        // std::cout << "## FC value is: " << FC << std::endl;
        dd.distanceSensors.distFrontRight = ioctl(fd_hcsr04, IOCTL_HCSR04_FR_TRIGGER, NULL);
        usleep(100 * 1000);
        // std::cout << "## FR value is: " << FR << std::endl;
        dd.distanceSensors.distRearLeft = ioctl(fd_hcsr04, IOCTL_HCSR04_RL_TRIGGER, NULL);
        usleep(100 * 1000);
        // std::cout << "## RL value is: " << RL << std::endl;
        dd.distanceSensors.distRearRight = ioctl(fd_hcsr04, IOCTL_HCSR04_RR_TRIGGER, NULL);
        // std::cout << "## RR value is: " << RR << std::endl;
        usleep(100 * 1000);
    }
    std::cout << "## Close HCSR04 ..." << std::endl;
    close(fd_hcsr04);
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    return 0;
}

int testDisplay()
{
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    fd_st7565 = open("/dev/st7565", O_RDWR | O_NONBLOCK | O_CLOEXEC);

    std::cout << "## Test IOCTL \"unknown\" control request" << std::endl;
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

    while (!m_stop)
    {
        dd.currentLoad = getLoad();
        if (ioctl(fd_st7565, IOCTL_LCD_WORKING_MODE, &dd) != 0)
        {
            std::cout << "## Switch to working mode failed" << std::endl;
            // 2Do: Send signal instead of termination
            std::terminate();
        }
        usleep(100 * 1000);
    }

    std::cout << "## Close display..." << std::endl;
    close(fd_st7565);
    std::cout << "## leaving " << __FUNCTION__ << std::endl;
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
