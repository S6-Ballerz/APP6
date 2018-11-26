#include "NetworkServices.h"

using namespace std;

NetworkServices::NetworkServices()
{
}


NetworkServices::~NetworkServices()
{
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
	return FileStruct();
}
