#include "main.h"

void PrintClientRecord(sClient Client)
{

	cout << "\n\nThe following is the extracted client record:\n";
	cout << "\nAccout Number : " << Client.AccountNumber;
	cout << "\nPin Cod       : " << Client.PinCode;
	cout << "\nName          : " << Client.Name;
	cout << "\nPhone         : " << Client.Phone;
	cout << "\nAccout Balance: " << Client.AccountBalance;


}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter Account? ";
    cin >> AccountNumber;
    return AccountNumber;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

