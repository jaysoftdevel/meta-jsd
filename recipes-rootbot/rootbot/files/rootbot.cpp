#include <iostream>
#include <thread>
#include <stdexcept>

#include "rootbot.h"

int main(int argc, char const *argv[])
{
    std::string str;
    std::cout << "### rootbot main ###" << std::endl;
    try
    {
        Connection conn = PortListener(TCP_SOCKET_PORT).waitForConnection();
        while (str.compare("quit") != 0)
        {
            str = conn.rx();
            std::cout << str << std::endl;
            conn.tx("Hello from server");
            std::cout << "Hello message sent" << std::endl;
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
