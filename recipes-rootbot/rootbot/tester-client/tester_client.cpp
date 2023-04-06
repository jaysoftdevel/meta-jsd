#include "rootbot.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <nlohmann/json.hpp>

DisplayData dd;

int main(int argc, char const *argv[])
{
    using namespace std;

    // parsing and serializing JSON
    dd.distanceSensors.distFrontLeft = 12;
    dd.distanceSensors.distFrontCenter = 34;
    dd.distanceSensors.distFrontRight = 56;
    dd.distanceSensors.distRearLeft = 78;
    dd.distanceSensors.distRearRight = 90;
    dd.connectionStatus.ping = 0x12345678u;
    dd.connectionStatus.connectionStatus = true;
    dd.motorStatus.positionLeft = 19;
    dd.motorStatus.positionRight = 37;
    dd.currentLoad = 55;

    char buffer[JSON_BUFFERSIZE_CLIENT] = {0};
    const char *host = TCP_SOCKET_SERVER_IP;
    int port = TCP_SOCKET_PORT;
    unsigned int total_sent_bytes, total_received_bytes = 0;

    // create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // create server address structure
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(host);
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0)
    {
        std::cerr << "Error: invalid address or address not supported\n";
        return 1;
    }

    // connect to server
    std::cout << "## try to connect to socket" << std::endl;
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Failed to connect to server." << std::endl;
        close(sock);
        return 1;
    }

    // create JSON datagram
    nlohmann::json datagram;
    datagram = dd.serialize_json();

    while (true)
    {
        int bytes_sent = send(sock, &dd, sizeof(dd), 0);
        if (bytes_sent == -1)
        {
            std::cerr << "Failed to send data." << std::endl;
            break;
        }
        total_sent_bytes += bytes_sent;
        std::cout << "Sent raw datagram with length of " << bytes_sent << " and " << total_sent_bytes << " in total #" << std::endl;

        int bytes_received = recv(sock, buffer, sizeof(buffer), 0);
        if (bytes_received == -1)
        {
            std::cerr << "Failed to receive data." << std::endl;
            break;
        }
        std::string json(buffer, sizeof(buffer));
        total_received_bytes += json.length();
        std::cout << "Received json data with size: " << json.length() << " and " << total_received_bytes << " in total: " << json << " #" << std::endl;
        sleep(0.1);
    }
    close(sock);
    return 0;
}