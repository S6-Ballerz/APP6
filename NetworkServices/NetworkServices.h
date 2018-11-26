#pragma once

//#define INCL_WINSOCK_API_PROTOTYPES
#include <WinSock2.h>
#include <stdexcept>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define DEFAULT_PORT 8888
#define MAX_FILE_SIZE 8192

#define PACKET_SIZE 200
#define HEADER_SIZE 11
#define DATA_LENGTH (PACKET_SIZE-HEADER_SIZE)

#define SERVER "127.0.0.1"  //ip address of udp server
#define PORT 8888   //The port on which to listen for incoming data

struct FileStruct
{
	bool succes;
	char filename[201];
	unsigned int sizeFile;
};

struct TlHeader
{
	unsigned premier;
	unsigned dernier;
	unsigned courant;
	char ctlChar;
	uint32_t CRC;
};

struct TlPacketInfo
{
	TlHeader header;
	char* data;
};

class NetworkServices
{
public:
	// Constructeur / Destructeur
	NetworkServices();
	~NetworkServices();

	// Methods
	bool start();
	bool stop();
	bool sendFile(char* tampon, unsigned int size);
	FileStruct receiveFile(char * tampon, unsigned int port = DEFAULT_PORT);

private:

	// Private data members
	SOCKET soc;
	WSADATA wsa;
	struct sockaddr_in server, si_other;
	int slen = sizeof(si_other);

	// Private Methods
	bool tlSend(TlHeader header, char* data);
	TlPacketInfo tlReceiver(char* data);
};

