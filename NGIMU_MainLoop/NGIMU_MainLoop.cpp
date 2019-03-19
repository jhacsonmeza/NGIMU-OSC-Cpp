/*
	Example to process received OSC messages from NGIMU using oscpack.
	http://www.rossbencina.com/code/oscpack
*/

#include <iostream>
#include <signal.h>

// for oscpack library
#pragma comment(lib, "liboscpack_vc12x64D.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")


#include <string>
#include <vector>
#include <fstream>

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"


#define PORT 8001
float w, x, y, z;

class ExamplePacketListener : public osc::OscPacketListener {
protected:

	virtual void ProcessMessage(const osc::ReceivedMessage& m,
		const IpEndpointName& remoteEndpoint)
	{
		try {
			// example of parsing single messages. osc::OsckPacketListener
			// handles the bundle traversal.

			if (strcmp(m.AddressPattern(), "/quaternion") == 0) {
				// example #1 -- argument stream interface
				osc::ReceivedMessageArgumentStream args = m.ArgumentStream();

				args >> w >> x >> y >> z >> osc::EndMessage;

				raise(SIGINT);

			}
		}
		catch (osc::Exception& e) {
			// any parsing errors such as unexpected argument types, or 
			// missing arguments get thrown as exceptions.
			std::cout << "error while parsing message: "
				<< m.AddressPattern() << ": " << e.what() << "\n";
		}
	}
};

int main(int argc, char* argv[])
{
	ExamplePacketListener listener;
	UdpListeningReceiveSocket s(
		IpEndpointName(IpEndpointName::ANY_ADDRESS, PORT),
		&listener);



	std::vector<std::string> list;

	for (int i = 0; i < 100; i++)
	{
		s.RunUntilSigInt();
		std::cout << "quaternion: " << w << " " << x << " " << y << " " << z << "\n";

		list.push_back(std::to_string(w) + " " + std::to_string(x) + " " + std::to_string(y)
			+ " " + std::to_string(z));
	}



	std::ofstream outFile("NGIMUdata.txt");

	if (!list.empty())
	{
		for (const auto &line : list)
			outFile << line << "\n";
	}


	system("PAUSE");
	return 0;
}
