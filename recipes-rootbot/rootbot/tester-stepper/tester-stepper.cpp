#include <iostream>
#include <fstream>
#include <thread>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>

#include "rootbot.h"

#define DEMO_STEPS 5000
#define STEP_DELAY_MS 1500

std::thread t_stepperL;
std::thread t_stepperR;

static DisplayData dd;

static int fd_stepperL;
static int fd_stepperR;

int testDeviceFiles();
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

    std::cout << "### Start stepperL first " << ret << std::endl;
    t_stepperL = std::thread(testStepperL);

    std::cout << "### Wait for " << DEMO_STEPS*500 << "ms... " << ret << std::endl;
    usleep(DEMO_STEPS*500);
    
    std::cout << "### Start stepperR... " << ret << std::endl;
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
        usleep(STEP_DELAY_MS);
    }
    ret = ioctl(fd_stepperL, IOCTL_STEPPER_L_STEP_NONE, NULL);
    if (ret != 0)
    {
        std::cout << "## test StepperL none failed with: " << ret << std::endl;
        return -2;
    }
    std::cout << "## testing stepperL reverse" << std::endl;
    for (i = 0; i < DEMO_STEPS; i++)
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
        usleep(STEP_DELAY_MS);
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
        usleep(STEP_DELAY_MS);
    }
    ret = ioctl(fd_stepperR, IOCTL_STEPPER_R_STEP_NONE, NULL);
    if (ret != 0)
    {
        std::cout << "## test StepperR none failed with: " << ret << std::endl;
        return -6;
    }
    std::cout << "## testing stepperR reverse" << std::endl;
    for (i = 0; i < DEMO_STEPS; i++)
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
        usleep(STEP_DELAY_MS);
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

int testDeviceFiles()
{
    std::cout << "## enter " << __FUNCTION__ << std::endl;
    std::string str_stepperL("Test string for Stepper motor LEFT!!!");
    std::string str_stepperR("Test string for Stepper motor RIGHT!!!");

    std::ofstream ofs_stepperL;
    std::ofstream ofs_stepperR;
    ofs_stepperL.open("/dev/stepperL", std::ios::out);            // only write
    ofs_stepperR.open("/dev/stepperR", std::ios::out);            // only write

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

    std::cout << "## Write to stepperL" << std::endl;
    ofs_stepperL << str_stepperL;

    std::cout << "## Write to stepperR" << std::endl;
    ofs_stepperR << str_stepperR;

    std::cout << "## Close all descriptors" << std::endl;

    ofs_stepperL.close();
    ofs_stepperR.close();
    std::cout << "## leave " << __FUNCTION__ << std::endl;
    return 0;
}
