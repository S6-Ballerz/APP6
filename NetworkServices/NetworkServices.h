#pragma once

//#define INCL_WINSOCK_API_PROTOTYPES
#include <WinSock2.h>
#include <stdexcept>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define DEFAULT_PORT 8888
#define MAX_FILE_SIZE 8192

struct FileStruct
{
	bool succes;
	char filename[201];
	unsigned int sizeFile;
};

class NetworkServices
{
public:
	// Constructeur / Destructeur
	NetworkServices();
	~NetworkServices();

	// Methods
	bool start(/*char * ipAddress, unsigned int port = DEFAULT_PORT*/);
	bool stop();
	bool sendFile(char* tampon, unsigned int size);
	FileStruct receiveFile(char * tampon, unsigned int port = DEFAULT_PORT);

private:
	SOCKET soc;
	WSADATA wsa;
	struct sockaddr_in server, si_other;
};

