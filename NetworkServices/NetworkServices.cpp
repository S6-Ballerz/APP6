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

	// Structure to return 
	FileStruct fileIdentier;

	// Actual interpretation
	while (true)
	{
		
	}

	return fileIdentier;
}

bool NetworkServices::tlSend(TlHeader header, char* data)
{
	char sendBuffer[PACKET_SIZE];

	memcpy(sendBuffer + 11, data, DATA_LENGTH);

	snprintf(sendBuffer, 2, "%d", header.premier % 100);
	snprintf(sendBuffer + 2, 2, "%d", header.dernier % 100);
	snprintf(sendBuffer + 4, 2, "%d", header.courant % 100);

	sendBuffer[6] = header.ctlChar;
	memcpy(sendBuffer + 7, &header.CRC, sizeof(header.CRC));

	// Sending data to target
	if (sendto(soc, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		return false;

	return true;
}

TlPacketInfo NetworkServices::tlReceiver(char * data)
{
	unsigned byteCount;
	char recvBuffer[PACKET_SIZE];

	if ((byteCount = recvfrom(soc, recvBuffer, PACKET_SIZE, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
	{
		throw runtime_error("Reception error");
	}

	TlPacketInfo rcvData;

	rcvData.data = data;
	memcpy(data, recvBuffer + 11, DATA_LENGTH);

	rcvData.header.ctlChar = recvBuffer[6];
	memcpy(&rcvData.header.CRC, recvBuffer + 7, sizeof(rcvData.header.CRC));

	rcvData.header.premier = 10 * (recvBuffer[0] - 0x30) + recvBuffer[1] - 0x30;
	rcvData.header.dernier = 10 * (recvBuffer[2] - 0x30) + recvBuffer[3] - 0x30;
	rcvData.header.courant = 10 * (recvBuffer[4] - 0x30) + recvBuffer[5] - 0x30;

	return rcvData;
}

