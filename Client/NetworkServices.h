#pragma once

//#define INCL_WINSOCK_API_PROTOTYPES
#include <WinSock2.h>

struct FileStruct
{
	bool succes;
	char filename[201];
	unsigned int sizeFile;
};

class NetworkServices
{
public:
	NetworkServices();
	~NetworkServices();

	// Methods
	bool start(char * ipAddress, char * port);
	bool stop();
	bool sendFile(char* tampon, unsigned int size);
	FileStruct receiveFile(char * tampon, char * port);

private:
	SOCKET soc;
	FileStruct fichierRecu;
	WSADATA wsa;
};

