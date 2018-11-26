/*
	Programme de réception du serveur

	novembre 2018
	APP6 S6, Universite de Sherbrooke
*/

#include <thread>
#include <iostream>
#include <fstream>

#include "../NetworkServices/NetworkServices.h"

using namespace std;

NetworkServices transLayer;
FileStruct file;
ofstream fileStream;

char fileBuffer[MAX_FILE_SIZE];

void serverThreadFunction()
{
		file = transLayer.receiveFile(fileBuffer);
		
		if (file.succes)
		{
			cout << "Nouveau fichier reçu." << endl;
			cout << "Nom du fichier: " << file.filename << endl;
			cout << "Taille du fichier: " << file.sizeFile << " octets" << endl;

			// Write output file
			fileStream.open("C:\\Users\\dene2303\\APP6\\out\\validation.txt");
			fileStream.write(fileBuffer, file.sizeFile);

			fileStream.close();

			cout << "hhh" << endl;
		}
		else
		{
			cout << "Réception de fichier échouée." << endl;
			cout << "Nom du fichier: " << file.filename << endl;
			cout << "Taille du fichier: " << file.sizeFile << " octets" << endl;
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