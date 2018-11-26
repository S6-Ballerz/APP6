#include "NetworkServices.h"

using namespace std;

NetworkServices::NetworkServices()
{
}


NetworkServices::~NetworkServices()
{
}

bool NetworkServices::start(char * ipAddress, char * port)
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;

	soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (soc == SOCKET_ERROR)
		return false;

	return true;
}

bool NetworkServices::stop()
{
	if (closesocket(soc) == SOCKET_ERROR)
		return false;
	if(WSACleanup() == SOCKET_ERROR)
		return false;

	return true;
}

bool NetworkServices::sendFile(char * tampon, unsigned int size)
{
	return false;
}

FileStruct NetworkServices::receiveFile(char * tampon, char * port)
{
	return FileStruct();
}
