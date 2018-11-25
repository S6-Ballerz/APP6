#pragma once

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

private:
	FileStruct fichierRecu;

};

