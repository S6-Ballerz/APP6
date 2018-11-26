/*
Simple udp client
Silver Moon (m00n.silv3r@gmail.com)
*/

#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <string>
#include "../NetworkServices/NetworkServices.h"

using namespace std;

/*
miguelito libre

*/
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#pragma warning (disable : 4996)


#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

int main(void)
{
	sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	// Fonction pour aller lire dans fichier text + adresse destinataire 
	ifstream inFile;
	string FileName;
	string ipAdress;
	const int File_Length = 8192;
	char FileContent[File_Length];

	


	//start communication
	while (1)
	{
		
		printf("\n Entrez le nom du fichier complet à téléverser : ");
		cin >> FileName;

		if (FileName == "validation.txt") {
			printf("\n Le fichier text est pret a etre envoyer ");
			inFile.open("C:\\Users\\barm1815\\APP6\\validation.txt");
			if (!inFile) {
				cerr << "Unable to open file datafile.txt";
				exit(1);   // call system to stop
			}
			while (!inFile.eof()) {
				inFile >> FileContent;
				cout << FileContent;
			}
			inFile.close();
		}
		else {
			printf("\n Erreur mauvais nom de fichier");
		}

		printf("\n Entrer ladresse ip du destinataire (127.0.0.1) ");
		cin >> ipAdress;

		sendFile(FileContent, File_Length);

		//printf("\n Entrez le message : ");
		//cin >> message;

		//send the message
		/*if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}*/

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		//memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		/*if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		cout << buf;*/
	}

	closesocket(s);
	WSACleanup();

	return 0;
}