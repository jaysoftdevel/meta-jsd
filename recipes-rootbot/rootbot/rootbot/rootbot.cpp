#include <iostream>
#include <thread>
#include <stdexcept>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <netinet/in.h>
#include <netinet/udp.h>

// #include <boost/asio.hpp>
// #include <boost/property_tree/ptree.hpp>
// #include <boost/property_tree/json_parser.hpp>

using namespace std;

// using boost::asio::ip::udp;
// using boost::property_tree::ptree;
// using boost::property_tree::read_json;

#include "rootbot.h"

const int BUFFER_SIZE = 1024;

int main(int argc, char const *argv[])
{
    // receive JSON datagram
    char buffer[1024] = {0};
    int dataRec = 0;
    std::string str;
    int opt = 1;
    std::cout << "### rootbot main ###" << std::endl;
    try
    {

        const char *host = "192.168.7.2";
        int port = 12345;
        int backlog = 5;

        // create socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            std::cerr << "Failed to create socket." << std::endl;
            return 1;
        }

        // Forcefully attaching socket to the address 192.168.7.2
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            std::cerr << "Set socket options error" << std::endl;
            return -1;
        }

        // create server address structure
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(host);
        server_addr.sin_port = htons(port);

        // bind socket to server address
        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        {
            std::cerr << "Failed to bind socket to server address." << std::endl;
            close(sock);
            return 1;
        }

        // listen for incoming connections
        if (listen(sock, backlog) == -1)
        {
            std::cerr << "Failed to listen for incoming connections." << std::endl;
            close(sock);
            return 1;
        }

        std::cout << "Waiting for incoming connections..." << std::endl;
        int client_sock;
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

        std::cout << "Incoming connection accepted." << std::endl;
        // accept incoming connection
        if (client_sock == -1)
        {
            std::cerr << "Failed to accept incoming connection." << std::endl;
            close(sock);
            return 1;
        }
        while (true)
        {
            int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
            if (bytes_received == -1)
            {
                std::cerr << "Failed to receive data." << std::endl;
                break;
            }
            else if (bytes_received == 0)
            {
                // connection inactive, waiting...
                client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

                std::cout << "Incoming connection accepted." << std::endl;
                // accept incoming connection
                if (client_sock == -1)
                {
                    std::cerr << "Failed to accept incoming connection." << std::endl;
                    close(sock);
                    return 1;
                }
            }
            dataRec += bytes_received;
            std::string json_datagram(buffer, bytes_received);
            DisplayData dd = DisplayData::deserialize_json(json_datagram);
            // std::cout << "Received datagram with length of " << bytes_received << " : " << json_datagram << " #" << std::endl;
            std::cout << "### Total received data: " << dataRec << " bytes #" << std::endl;
        }

        // close client socket and server socket
        close(client_sock);
        close(sock);
        return 0;
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    //  try
    // {
    //     boost::asio::io_service io_service;
    //     udp::socket socket(io_service, udp::endpoint(udp::v4(), 0));
    //     udp::resolver resolver(io_service);
    //     udp::resolver::query query(udp::v4(), "example.com", "9000");
    //     udp::endpoint server_endpoint = *resolver.resolve(query);

    //     std::array<char, 1024> buffer;
    //     udp::endpoint sender_endpoint;

    //     while (true)
    //     {
    //         size_t length = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);

    //         // Parse the received JSON data
    //         std::string json_data(buffer.data(), length);
    //         std::istringstream iss(json_data);
    //         ptree pt;
    //         read_json(iss, pt);

    //         // Do something with the JSON data
    //         std::cout << "Received JSON data:\n";
    //         std::cout << "  id: " << pt.get<std::string>("id") << std::endl;
    //         std::cout << "  message: " << pt.get<std::string>("message") << std::endl;
    //     }
    // }
    // catch (std::exception& e)
    // {
    //     std::cerr << "Exception: " << e.what() << std::endl;
    // }

    // return 0;

    try
    {
        Connection conn = PortListener(TCP_SOCKET_PORT).waitForConnection();
        while (str.compare("quit") != 0)
        {
            str = conn.rx();
            std::cout << str << std::endl;
            conn.tx("Data received: " + str.length());
            std::cout << "Data processed: " << str.length() << " # " << std::endl;
        }
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    std::thread t_socket(Socket);

    return 0;
}
