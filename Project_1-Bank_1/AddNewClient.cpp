#include "main.h"

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app );

	if ((MyFile.is_open()))
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

void AddNewClient()
{
	sClient Client;

	Client = ReadNewClient();

	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddClients()
{
	char AddMore = 'Y';

	do
	{
		system("cls");
		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added SuccessFully, do you to add more clients? Y/N?";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}
