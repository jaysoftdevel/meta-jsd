#include "rootbot.h"

using namespace std;

static int fd_st7565;

int main(int argc, char const *argv[])
{
    // receive JSON datagram
    char buffer[sizeof(DisplayData)] = {0};
    int dataRec = 0;
    std::string str;
    int opt = 1;
    std::cout << "### rootbot main ###" << std::endl;
    try
    {

        const char *host = TCP_SOCKET_SERVER_IP;
        int port = TCP_SOCKET_PORT;
        int backlog = 5;

        // create socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            std::cerr << "Failed to create socket." << std::endl;
            return 1;
        }

        // Forcefully attaching socket to the address TCP_SOCKET_SERVER_IP
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

        std::cout << "Opening display device" << std::endl;
        fd_st7565 = open("/dev/st7565", O_RDWR | O_NONBLOCK | O_CLOEXEC);
        if (fd_st7565 < 0){
            std::cerr << "Failed to open display. " << std::to_string(fd_st7565) << " #" << std::endl;
            close(sock);
            return 1;
        }
        std::cout << "## Clear display" << std::endl;
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
            int bytes_received = recv(client_sock, &buffer, sizeof(buffer), 0);
            if (bytes_received == -1)
            {
                std::cerr << "Failed to receive data." << std::endl;
                break;
            }
            else if (bytes_received == 0)
            {
                // connection inactive, waiting...
                client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

                std::cout << "New incoming connection accepted." << std::endl;
                // accept incoming connection
                if (client_sock == -1)
                {
                    std::cerr << "Failed to accept incoming connection." << std::endl;
                    close(sock);
                    return 1;
                }
            }
            dataRec += bytes_received;
            std::string datagram(buffer, bytes_received);
            DisplayData dd = DisplayData::deserialize(datagram);
            std::cout << "## Test IOCTL with DisplayData" << std::endl;
            // TODO: read dd from devices!
            if (ioctl(fd_st7565, IOCTL_LCD_WORKING_MODE, &dd) != 0)
            {
                std::cout << "## Switch to working mode failed" << std::endl;
                return -6;
            }
            
            nlohmann::json json = dd.serialize_json();
            std::cout << "## done processing incoming datagram" << std::endl;
            // send JSON datagram
            int bytes_sent = send(client_sock, &json, json.size(), 0);
            if (bytes_sent == -1)
            {
                std::cerr << "Failed to send back json data." << std::endl;
                break;
            }
            std::cout << "## sent " << json.size() << " bytes json datagra" << std::endl;
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
    return 0;
}
