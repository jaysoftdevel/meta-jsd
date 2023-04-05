#include "rootbot.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <nlohmann/json.hpp>

DisplayData dd;

int main(int argc, char const *argv[])
{
    using namespace std;
    char text[] = R"(
     {
         "colors": {
	                "color": "black",
		        "category": "hue",
		        "type": "primary",
	                       "code": {
			        "rgba": [255,255,255,1],
			        "hex": "#000"
			      }
		     }		
     }
     )";

    // parsing and serializing JSON
    dd.distanceSensors.distFrontLeft = 12;
    dd.distanceSensors.distFrontCenter = 34;
    dd.distanceSensors.distFrontRight = 56;
    dd.distanceSensors.distRearLeft = 78;
    dd.distanceSensors.distRearRight = 90;
    dd.connectionStatus.connectionStatus = true;
    dd.connectionStatus.ping = 123u;
    dd.motorStatus.positionLeft = 19;
    dd.motorStatus.positionRight = 37;
    dd.currentLoad = 55;

    int opt = 1;
    const char *host = "192.168.7.2";
    int port = 12345;

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

    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
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

    //for (int i = 0; i < 4; i++)
    while (true)
    {    
        // send JSON datagram
        int bytes_sent = send(sock, to_string(datagram).c_str(), to_string(datagram).length(), 0);
        if (bytes_sent == -1)
        {
            std::cerr << "Failed to send data." << std::endl;
            break;
        }
        // std::cout << "Sent JSON datagram with length of " << bytes_sent << " : " << datagram << std::endl;
        sleep(.01);

        bytes_sent = send(sock, &dd, sizeof(dd), 0);
        if (bytes_sent == -1)
        {
            std::cerr << "Failed to send data." << std::endl;
            break;
        }

        std::cout << "Sent raw datagram with length of " << bytes_sent << " #" << std::endl;
        // sleep(.01);
    }
    close(sock);
    return 0;

    // good when sending ASCII datagrams (e.g. json)
    // not applicable when sending raw data!
    // try
    // {
    //     std::cout << "### connect to server" << std::endl;
    //     // Connection conn("127.0.0.1", TCP_SOCKET_PORT);
    //     Connection conn("192.168.7.2", TCP_SOCKET_PORT);
    //     for (int i = 0; i < 50; i++)
    //     {
    //         std::cout << "### sending..." << std::endl;
    //         //cout << "Sent to server" << endl;
    //         conn.tx(to_string(datagram));
    //         std::cout << "### receiving..." << std::endl;
    //         string s = conn.rx();
    //         cout << s << endl;
    //         usleep(25 * 1000);
    //     }
    //     conn.tx("quit");
    // }
    // catch (exception &e)
    // {
    //     cerr << e.what() << endl;
    //     return EXIT_FAILURE;
    // }
    return 0;
}