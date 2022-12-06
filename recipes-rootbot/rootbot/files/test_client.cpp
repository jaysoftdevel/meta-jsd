#include "rootbot.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <nlohmann/json.hpp>

static DisplayData dd;

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
    dd.distanceSensors.distFrontLeft=12;
    dd.distanceSensors.distFrontCenter=34;
    dd.distanceSensors.distFrontRight=56;
    dd.distanceSensors.distRearLeft=78;
    dd.distanceSensors.distRearRight=90;
    dd.connectionStatus.connectionStatus=true;
    dd.connectionStatus.ping=123;
    dd.motorStatus.positionLeft=19;
    dd.motorStatus.positionRight=37;
    dd.currentLoad=55;

    nlohmann::json datagram = nlohmann::json::parse(text);
    std::cout << std::setw(4) << datagram << endl;
    try
    {
        // Connection conn("127.0.0.1", TCP_SOCKET_PORT);
        Connection conn("192.168.5.10", TCP_SOCKET_PORT);
        for (int i = 0; i < 50; i++)
        {
            conn.tx(to_string(datagram));
            cout << "Sent to server" << endl;
            string s = conn.rx();
            cout << s << endl;
            usleep(25 * 1000);
        }
        conn.tx("quit");
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}