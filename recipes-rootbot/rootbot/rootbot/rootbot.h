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

#define TCP_SOCKET_PORT 12345
#define TCP_SOCKET_SERVER_IP "192.168.10.39"
#define JSON_BUFFERSIZE_CLIENT 256

#pragma pack(push,1)
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
        nlohmann::json serialize_json()
        {
                std::ostringstream oss;
                oss.flush();
                oss.clear();
                oss << "{\"distanceSensors\" : { \"distFrontLeft\": " << std::to_string(distanceSensors.distFrontLeft) << ", \"distFrontCenter\": " << std::to_string(distanceSensors.distFrontCenter) << ", \"distFrontRight\": " << std::to_string(distanceSensors.distFrontRight) << ", \"distRearLeft\": " << std::to_string(distanceSensors.distRearLeft) << ", \"distRearRight\": " << std::to_string(distanceSensors.distFrontRight) << "}, \"connectionStatus\": { \"ping\": " << std::to_string(connectionStatus.ping) << ", \"connectionStatus\":" << std::to_string(connectionStatus.connectionStatus) << "}, \"motorStatus\": { \"positionLeft\": " << std::to_string(motorStatus.positionLeft) << ", \"positionRight\": " << std::to_string(motorStatus.positionRight) << "}, \"currentLoad\": " << std::to_string(currentLoad) << "}";
                // std::cout << "## " << oss.str() << " ##" << std::endl;
                return nlohmann::json::parse(oss.str());
        }
        static DisplayData deserialize(std::string datagram)
        {
                DisplayData dd = DisplayData();
                nlohmann::json json;
                try
                {
                        json.clear();
                        json = nlohmann::json::parse(datagram);
                }
                catch (std::exception e)
                {
                        // json parsing failed, assume raw data beens sent!
                        std::cerr << "## No valid json datagram, parsing raw data..." << std::endl;
                        dd.distanceSensors.distFrontLeft = datagram[0];
                        dd.distanceSensors.distFrontCenter = datagram[1];
                        dd.distanceSensors.distFrontRight = datagram[2];
                        dd.distanceSensors.distRearLeft = datagram[3];
                        dd.distanceSensors.distRearRight = datagram[4];
                        dd.motorStatus.positionLeft = datagram[10];
                        dd.motorStatus.positionRight = datagram[11];
                        dd.connectionStatus.ping = datagram[8]<<24|datagram[7]<<16|datagram[6]<<8|datagram[5];
                        dd.connectionStatus.connectionStatus = datagram[9];
                        dd.currentLoad = datagram[12];
                        return dd;
                }
                // json parsed was successfully, extract values to DisplayData type
                if(json != nullptr){
                        std::cout << "### json NOT null #" << std::endl;
                        dd.distanceSensors.distFrontLeft = static_cast<unsigned char>(json["distanceSensors"]["distFrontLeft"]);
                        dd.distanceSensors.distFrontCenter = static_cast<unsigned char>(json["distanceSensors"]["distFrontCenter"]);
                        dd.distanceSensors.distFrontRight = static_cast<unsigned char>(json["distanceSensors"]["distFrontRight"]);
                        dd.distanceSensors.distRearLeft = static_cast<unsigned char>(json["distanceSensors"]["distRearLeft"]);
                        dd.distanceSensors.distRearRight = static_cast<unsigned char>(json["distanceSensors"]["distRearRight"]);
                        dd.motorStatus.positionLeft = static_cast<unsigned char>(json["motorStatus"]["positionLeft"]);
                        dd.motorStatus.positionRight = static_cast<unsigned char>(json["motorStatus"]["positionRight"]);
                        dd.connectionStatus.ping = static_cast<unsigned int>(json["connectionStatus"]["ping"]);
                        dd.connectionStatus.connectionStatus = (json["connectionStatus"]["connectionStatus"] == 1) ? true : false;
                        dd.currentLoad = static_cast<unsigned char>(json["currentLoad"]);
                }
                return dd;
        }
};
#pragma pop
