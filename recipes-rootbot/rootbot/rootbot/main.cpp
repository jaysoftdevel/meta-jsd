#include "Rootbot.hpp"

using namespace std;
using namespace jsd;

static int fd_st7565;

int main(int argc, char const *argv[])
{
    // receive JSON datagram
    char buffer[1024] = {0};
    int dataRec = 0;
    int opt = 1;
    Rootbot rb;

    cout << "### rootbot main ###" << endl;
    try
    {

        const char *host = TCP_SOCKET_SERVER_IP;
        int port = TCP_SOCKET_PORT;
        int backlog = 5;

        // create socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            cerr << "Failed to create socket." << endl;
            return 1;
        }

        // Forcefully attaching socket to the address TCP_SOCKET_SERVER_IP
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            cerr << "Set socket options error" << endl;
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
            cerr << "Failed to bind socket to server address." << endl;
            close(sock);
            return 1;
        }

        // listen for incoming connections
        if (listen(sock, backlog) == -1)
        {
            cerr << "Failed to listen for incoming connections." << endl;
            close(sock);
            return 1;
        }

        cout << "## Waiting for incoming connections..." << endl;
        int client_sock;
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

        cout << "## Opening display device" << endl;
        fd_st7565 = open("/dev/st7565", O_RDWR | O_NONBLOCK | O_CLOEXEC);
        if (fd_st7565 < 0)
        {
            cerr << "Failed to open display. " << to_string(fd_st7565) << " #" << endl;
            close(sock);
            return 1;
        }
        cout << "## Clear display" << endl;
        if (ioctl(fd_st7565, IOCTL_LCD_CLEAR_ALL, NULL) != 0)
        {
            cout << "## Clearing display failed" << endl;
            return -4;
        }
        if (ioctl(fd_st7565, IOCTL_LCD_SETUP_WORKING_MODE, NULL) != 0)
        {
            cout << "## Set working mode failed" << endl;
            return -5;
        }
        // accept incoming connection
        if (client_sock == -1)
        {
            cerr << "Failed to accept incoming connection." << endl;
            close(sock);
            return 1;
        }

        cout << "## Incoming connection accepted." << endl;
        while (true)
        {
            int bytes_received = recv(client_sock, &buffer, sizeof(buffer), 0);
            if (bytes_received == -1)
            {
                cerr << "Failed to receive data." << endl;
                break;
            }
            else if (bytes_received == 0)
            {
                // connection inactive, waiting...
                client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

                cout << "## New incoming connection accepted." << endl;
                // accept incoming connection
                if (client_sock == -1)
                {
                    cerr << "Failed to accept incoming connection." << endl;
                    close(sock);
                    return 1;
                }
            }
            else if (bytes_received > 0)
            {
                cout << "## Data received:\n";
                buffer[bytes_received] = '\0';
                for (int i = 0; i <= bytes_received; i++)
                {
                    cout << to_string(i) << ": " << buffer[i] << " # ";
                }
                cout << endl;

                nlohmann::json recData = nlohmann::json::parse(buffer);
                try
                {
                    if (recData.is_array())
                    {
                        cout << "is array" << endl;
                        for (const auto &item : recData)
                        {
                            cout << "item: " << item << " with size " << item.size() << endl;
                            if (item.is_array())
                            {
                                cout << "is array again" << endl;
                                // DD
                                if (item.size() == 5) // distance sensors
                                {
                                    cout << "caught DD" << endl;
                                    for (size_t i=0; i < item.size(); ++i)
                                    {
                                        cout << "DD item: " << item[i] << endl;
                                        rb.distanceSensors.setDistanceSensor(i, (unsigned char)stoi(item[i].get<std::string>()));
                                    }
                                }
                                else if (item.size() == 2 && item[1].is_boolean()) // connection status
                                {
                                    cout << "caught CS" << endl;
                                    // for (size_t i=0; i < item.size(); ++i)
                                    // {
                                        rb.connectionStatus.setConnectionStatus((unsigned int)stoi(item[0].get<std::string>()), item[1].get<std::string>());
                                        cout << "CS item0: " << item[0] << " and CS item1: " << item[1]<< endl;
                                    // }
                                }
                                else if (item.size() == 2 && item[1].is_string()) // motor status
                                {
                                    cout << "caught MC" << endl;


                                        rb.motorStatus.setMotorStatus((unsigned short)stoi(item[0].get<std::string>()), (unsigned short)stoi(item[1].get<std::string>()));
                                        cout << "MC item1: " << item[0] << " and MC item2: " << item[1] << endl;

                                }
                            }
                            else if (item.is_string())
                            {
                                cout << "caught Load" << endl;
                                cout << "load: " << item << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "json type not detected" << endl;
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error parsing JSON: " << e.what() << endl;
                }

                dataRec += bytes_received;
                cout << "## Test IOCTL with DisplayData" << endl;

                // TODO: read dd from devices!
                auto data = rb.serialize_bytes();
                if (ioctl(fd_st7565, IOCTL_LCD_WORKING_MODE, &data[0]) != 0)
                {
                    cout << "## Switch to working mode failed" << endl;
                    return -6;
                }

                cout << "## sending data with size " << rb.serialize_bytes().size() << " back" << endl;
                int bytes_sent = send(client_sock, rb.serialize_bytes().data(), rb.serialize_bytes().size(), 0);

                if (bytes_sent == -1)
                {
                    cerr << "Failed to send back json data." << endl;
                    break;
                }
                cout << "## sent " << rb.serialize_bytes().size() << " bytes datagram" << endl;
                cout << "### Total received data: " << dataRec << " bytes #" << endl;
            }
        }

        // close client socket and server socket
        close(client_sock);
        close(sock);
        return 0;
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
