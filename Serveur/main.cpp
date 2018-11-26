/*
	Programme de r�ception du serveur

	novembre 2018
	APP6 S6, Universite de Sherbrooke
*/

#include <thread>
#include <iostream>

#include "../NetworkServices/NetworkServices.h"

using namespace std;

NetworkServices transLayer;
FileStruct file;

char fileBuffer[MAX_FILE_SIZE];

void serverThreadFunction()
{
	while (true)
	{
		file = transLayer.receiveFile(fileBuffer);

		if (file.succes)
		{
			cout << "Nouveau fichier re�u." << endl;
			cout << "Nom du fichier: " << file.filename << endl;
			cout << "Taille du fichier: " << file.sizeFile << " octets" << endl;

			// Write output file

		}
		else
		{
			cout << "R�ception de fichier �chou�e." << endl;
			cout << "Nom du fichier: " << file.filename << endl;
			cout << "Taille du fichier: " << file.sizeFile << " octets" << endl;
		}
	}
}

int main()
{
	// Starting server thread
	cout << "Lancement du serveur" << endl;
	thread serverThread(serverThreadFunction);

	// Watching for user input to stop program
	cout << "Appuyer sur ENTER pour terminer ce programme" << endl;
	cin.get();
	exit(0);
}