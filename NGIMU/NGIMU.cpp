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

class ExamplePacketListener : public osc::OscPacketListener
{
protected:
	virtual void ProcessMessage(const osc::ReceivedMessage& m,
		const IpEndpointName& remoteEndpoint)
	{
		try
		{
			if (strcmp(m.AddressPattern(), "/quaternion") == 0)
			{
				osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
				float a1, a2, a3, a4;
				args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;

				std::cout << "received '/quaternion' message with arguments: "
					<< a1 << " " << a2 << " " << a3 << " " << a4 << "\n";
			}
			else if (strcmp(m.AddressPattern(), "/sensors") == 0)
			{
				osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
				float gx, gy, gz, ax, ay, az, mx, my, mz, b;
				args >> gx >> gy >> gz >> ax >> ay >> az >> mx >> my >> mz >> b >> osc::EndMessage;

				//std::cout << "received '/sensors' message with arguments: "
					//<< gx << " " << gy << " " << gz << "\n";
			}
		}
		catch (osc::Exception& e)
		{
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

	std::cout << "press ctrl-c to end\n";

	s.RunUntilSigInt();

	system("PAUSE");
	return 0;
}
