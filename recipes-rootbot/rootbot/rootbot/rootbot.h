// Adapted from C code example
// at https://www.geeksforgeeks.org/socket-programming-cc/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

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
        unsigned int ping;
        bool connectionStatus;
} ConnectionStatus;

typedef struct
{
        unsigned char positionLeft;
        unsigned char positionRight;
} MotorStatus;

struct DisplayData
{
        DistanceSensors distanceSensors;
        ConnectionStatus connectionStatus;
        MotorStatus motorStatus;
        unsigned char currentLoad;
        nlohmann::json serialize_json()
        {
                std::ostringstream oss;
                oss.flush();
                oss << "{\"distanceSensors\" : { \"distFrontLeft\": " << std::to_string(distanceSensors.distFrontLeft) << ", \"distFrontCenter\": " << std::to_string(distanceSensors.distFrontCenter) << ", \"distFrontRight\": " << std::to_string(distanceSensors.distFrontRight) << ", \"distRearLeft\": " << std::to_string(distanceSensors.distRearLeft) << ", \"distRearRight\": " << std::to_string(distanceSensors.distFrontRight) << "}, \"connectionStatus\": { \"ping\": " << std::to_string(connectionStatus.ping) << ", \"conectionStatus\":" << std::to_string(connectionStatus.connectionStatus) << "}, \"motorStatus\": { \"positionLeft\": " << std::to_string(motorStatus.positionLeft) << ", \"positionRight\": " << std::to_string(motorStatus.positionRight) << "}, \"currentLoad\": " << std::to_string(currentLoad) << "}";
                // std::cout << "## " << oss.str() << " ##" << std::endl;
                return nlohmann::json::parse(oss.str());
        }
        static DisplayData deserialize_json(std::string datagram)
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
                        std::cerr << "## No valid json datagram, parsing raw data..." << std::endl;
                        char buffer[sizeof(DisplayData)];
                        auto disp = reinterpret_cast<DisplayData*>(buffer);
                        dd = *disp;
                        // std::cerr << "## FL " << std::to_string(dd.distanceSensors.distFrontLeft) << " #"  << "## FC " << std::to_string(dd.distanceSensors.distFrontCenter) << " #"  << "## Fr " << std::to_string(dd.distanceSensors.distFrontRight) << " #" << "## RL " << std::to_string(dd.distanceSensors.distRearLeft) << " #"  << "## RR " << std::to_string(dd.distanceSensors.distRearRight) << " #"  << "## CS " << std::to_string(dd.connectionStatus.connectionStatus) << " #"  << "## Pi " << std::to_string(dd.connectionStatus.ping) << " #" << "## ML " << std::to_string(dd.motorStatus.positionLeft) << " #" << "## MR " << std::to_string(dd.motorStatus.positionRight) << " #" << "## Lo " << std::to_string(dd.currentLoad) << " #" << std::endl;
                        return dd;
                }
                
                if(json != nullptr){
                        std::cout << "### json NOT null #" << std::endl;
                        //std::cout << "### " << json["distanceSensors"] << " #" <<std::endl;
                }
                return dd;
        }
};

#define TCP_SOCKET_PORT 12345

class Socket
{
        int sock;

public:
        Socket(int socket) : sock(socket)
        {
                if (sock < 0)
                        throw std::runtime_error("Socket creation error");
        }
        Socket() : Socket(socket(AF_INET, SOCK_STREAM, 0)) {}
        std::string rx()
        {
                char buffer[1024] = {0};
                int n = read(sock, buffer, sizeof(buffer));
                return std::string(buffer, n);
        }
        void tx(std::string s)
        {
                send(sock, s.c_str(), s.length(), 0);
        }
        int getSocket()
        {
                return sock;
        }
};

class Connection : public Socket
{
public:
        Connection(int socket) : Socket(socket) {}
        Connection(std::string address, unsigned short port) : Socket()
        {
                struct sockaddr_in serv_addr;
                serv_addr.sin_family = AF_INET;
                serv_addr.sin_port = htons(port);
                // Convert IPv4 and IPv6 addresses from text to binary form
                if (inet_pton(
                        AF_INET,
                        address.c_str(),
                        &serv_addr.sin_addr) <= 0)
                        throw std::runtime_error("Invalid address: Address not supported");

                if (connect(
                        getSocket(),
                        (struct sockaddr *)&serv_addr,
                        sizeof(serv_addr)) < 0)
                        throw std::runtime_error("\nConnection Failed \n");
        }
};

class PortListener
{
        Socket server; // fd is created in default Socket constructor
        struct sockaddr_in address;
        int opt = 1;

public:
        PortListener(unsigned short port)
        {

                // Forcefully attaching socket to the port
                if (setsockopt(
                        server.getSocket(),
                        SOL_SOCKET,
                        SO_REUSEADDR | SO_REUSEPORT,
                        &opt,
                        sizeof(opt)))
                        throw std::runtime_error("setsockopt");

                address.sin_family = AF_INET;
                address.sin_addr.s_addr = INADDR_ANY;
                address.sin_port = htons(port);

                // Forcefully attaching socket to the port
                if (bind(
                        server.getSocket(),
                        (struct sockaddr *)&address,
                        sizeof(address)) < 0)
                        throw std::runtime_error("bind failed");

                if (listen(server.getSocket(), 3) < 0)
                {
                        throw std::runtime_error("listen");
                }
        }
        Connection waitForConnection()
        {
                int new_socket;
                int addrlen = sizeof(struct sockaddr_in);
                new_socket = accept(
                    server.getSocket(),
                    (struct sockaddr *)&address,
                    (socklen_t *)&addrlen);
                if (new_socket < 0)
                        throw std::runtime_error("accept");
                return Connection(new_socket);
        }
};
