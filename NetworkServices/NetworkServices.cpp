#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "NetworkServices.h"
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <string>

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

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
}


NetworkServices::~NetworkServices()
{
	closesocket(soc);
	WSACleanup();
}

bool NetworkServices::start()
{
	int test;
	int test2;
	int connection_succes = -1;
	connection_succes = connect(soc, (struct sockaddr *) &si_other, sizeof(si_other));
	//printf("after conenct()\n");  //for debugging
	if (connection_succes != 0)
	{
		printf("Error %d La connection a echoue\n", WSAGetLastError());
		cin >> test2;
	}
	printf("La connectionne fonctionne!");

	cin >> test;

	return true;
}

bool NetworkServices::stop()
{

	return true;
}

bool NetworkServices::sendFile(char * tampon, unsigned int size)
{
	TlHeader entete;
	char donnee[DATA_LENGTH];

	int packetCount = 1 + ceil((float)size / (float)DATA_LENGTH);

	// Send first packet containing file name
	entete.premier = 0;
	entete.courant = 0;
	entete.dernier = packetCount - 1;
	entete.CRC = 0x30303030;
	entete.ctlChar = 'd';
	strcpy(donnee, "validation.txt");
	if (!tlSend(entete, donnee))
		return false;

	entete.ctlChar = 'x';
	while (entete.courant < entete.dernier) 
	{
		memset(donnee, '\0', DATA_LENGTH);
		strncpy(donnee, tampon, DATA_LENGTH);

		++entete.courant;

		if (entete.courant == entete.dernier)
			entete.ctlChar = 'e';

		if (!tlSend(entete, donnee))
			return false;
	}
	return true;
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
		char dataBuffer[DATA_LENGTH];
		TlPacketInfo packetInfo = tlReceiver(dataBuffer);

		// First packet
		if (packetInfo.header.ctlChar == 'd')
		{
			// Copy file name
			strncpy(fileIdentier.filename, dataBuffer, sizeof(dataBuffer));

			// Estimate length not counting the filename
			fileIdentier.sizeFile = (packetInfo.header.dernier - packetInfo.header.premier - 1) * DATA_LENGTH;

			continue;
		}

		// Copy data into file buffer
		int byteOffset = (packetInfo.header.courant - packetInfo.header.premier - 1) * DATA_LENGTH;
		memcpy(tampon + byteOffset, dataBuffer, DATA_LENGTH);

		//cout << "paquet code: " << packetInfo.header.ctlChar << endl;

		if (packetInfo.header.ctlChar == 'e')
		{
			fileIdentier.succes = true;
			break;
		}
	}

	return fileIdentier;
}

bool NetworkServices::tlSend(TlHeader header, char* data)
{
	char sendBuffer[PACKET_SIZE];

	memcpy(sendBuffer + 11, data, DATA_LENGTH);

	sendBuffer[0] = (header.premier % 100) / 10 + 0x30;
	sendBuffer[1] = header.premier % 10 + 0x30;
	sendBuffer[2] = (header.dernier % 100) / 10 + 0x30;
	sendBuffer[3] = header.dernier % 10 + 0x30;
	sendBuffer[4] = (header.courant % 100) / 10 + 0x30;
	sendBuffer[5] = header.courant % 10 + 0x30;

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
	char recvBuffer[PACKET_SIZE + 1];
	memset(recvBuffer, 0, PACKET_SIZE + 1);

	if ((byteCount = recvfrom(soc, recvBuffer, PACKET_SIZE, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
	{

	}

	cout << recvBuffer << endl;

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

