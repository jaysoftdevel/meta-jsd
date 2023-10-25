// Rootbot.hpp
#ifndef DATACONTAINER_HPP
#define DATACONTAINER_HPP

#include "DistanceSensors.hpp"
#include "ConnectionStatus.hpp"
#include "MotorStatus.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include <thread>
#include <sstream>
#include <sys/ioctl.h>
#include <fstream>
#include <fcntl.h>

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
namespace jsd
{
    class Rootbot
    {
    private:
        DistanceSensors distanceSensors;
        ConnectionStatus connectionStatus;
        MotorStatus motorStatus;
        unsigned char currentLoad=0xDDu;

    public:
        void initRootbot()
        {
            std::cout << "### initializing data container" << std::endl;
        }

        ~Rootbot() = default;

        const DistanceSensors &getDistanceSensors() const;
        DistanceSensors &getDistanceSensors();
        const ConnectionStatus &getConnectionStatus() const;
        ConnectionStatus &getConnectionStatus();
        const MotorStatus &getMotorStatus() const;
        MotorStatus &getMotorStatus();
        unsigned char getCurrentLoad() const;

        nlohmann::json serialize_json() const;
        std::vector<uint8_t> serialize_bytes() const;
        Rootbot deserialize_bytes(const std::vector<uint8_t> &bytes);
        Rootbot deserialize_json(const nlohmann::json &j);
    };
}; // namespace jsd
#endif // DATACONTAINER_HPP