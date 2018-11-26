/*
Simple udp client
Silver Moon (m00n.silv3r@gmail.com)
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
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

NetworkServices TransportLayer;

int main(void)
{
	// Fonction pour aller lire dans fichier text + adresse destinataire 
	ifstream inFile;
	string FileName;
	string ipAdress;
	unsigned int File_Length;
	char FileContent[MAX_FILE_SIZE];


	//start communication
	while (1)
	{
		printf("\n Entrez le nom du fichier a televerser ");
		cin >> FileName;


		if (FileName == "validation.txt") {
			inFile.open("C:\\Users\\barm1815\\APP6\\validation.txt");
			if (!inFile) {
				cerr << "Unable to open file datafile.txt";
				exit(1);   // call system to stop
			}
			while (!inFile.eof()) {
				inFile >> FileContent;
				//cout << FileContent;
			}
			File_Length = inFile.tellg();
			cout << File_Length;
			inFile.close();
		}
		else {
			printf("\n Erreur mauvais nom de fichier");
		}

		printf("\n Entrer ladresse ip du destinataire (127.0.0.1) ");
		cin >> ipAdress;

		if (ipAdress == "127.0.0.1") {
		
			TransportLayer.start();
			TransportLayer.sendFile(FileContent, File_Length);
		
		
		}


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



	return 0;
}