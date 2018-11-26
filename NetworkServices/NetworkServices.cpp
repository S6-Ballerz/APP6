#include "NetworkServices.h"

using namespace std;

NetworkServices::NetworkServices()
{
	//Initialise winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		throw runtime_error("Failed to start winsock");

	// Creating socket
	if ((soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		throw runtime_error("Failed to create socket");
	}
}


NetworkServices::~NetworkServices()
{
	closesocket(soc);
	WSACleanup();
}

bool NetworkServices::start(char * ipAddress, unsigned int port)
{

	return true;
}

bool NetworkServices::stop()
{

	return true;
}

bool NetworkServices::sendFile(char * tampon, unsigned int size)
{
	return false;
}

FileStruct NetworkServices::receiveFile(char * tampon, unsigned int port)
{
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	// Binding the socket
	if (bind(soc, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		throw runtime_error("Bind failed");
	}

	//clear the buffer by filling null, it might have previously received data
	memset(tampon, '\0', MAX_FILE_SIZE);

	// Actual interpretation
	while (true);

	return FileStruct();
}
