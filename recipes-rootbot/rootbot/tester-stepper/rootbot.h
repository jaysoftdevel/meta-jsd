#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <sstream>
#include <nlohmann/json.hpp>
#include <sys/ioctl.h>
#include <fstream>
#include <fcntl.h>

//#include "Rootbot.hpp"

#define TCP_SOCKET_PORT 12345
#define TCP_SOCKET_SERVER_IP "192.168.5.10"
#define JSON_BUFFERSIZE_CLIENT 256

#define IOCTL_LCD_WORKING_MODE _IOW(6, 1, unsigned long)
#define IOCTL_LCD_PIXEL_MODE _IOW(6, 2, unsigned long)
#define IOCTL_LCD_CLEAR_ALL _IOW(6, 3, unsigned long)
#define IOCTL_LCD_SETUP_WORKING_MODE _IOW(6, 4, unsigned long)
#define IOCTL_LCD_INTRO _IOW(6, 5, unsigned long)

// #define DEBUG

#define TEST_IO_THING 3
#define LOAD_STAT_OFFSET 2

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

#pragma pack(push, 1)
typedef struct
{
        unsigned char distFrontLeft = 0;
        unsigned char distFrontCenter = 0;
        unsigned char distFrontRight = 0;
        unsigned char distRearLeft = 0;
        unsigned char distRearRight = 0;
} DistanceSensors;

typedef struct
{
        unsigned int ping = 0;
        bool connectionStatus = false;
} ConnectionStatus;

typedef struct
{
        unsigned char positionLeft = 0;
        unsigned char positionRight = 0;
} MotorStatus;

struct DisplayData
{
        DistanceSensors distanceSensors;
        ConnectionStatus connectionStatus;
        MotorStatus motorStatus;
        unsigned char currentLoad = 0;
};

#pragma pop
