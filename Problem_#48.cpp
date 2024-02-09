#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;

    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stold(vClientData[4]);

    return Client;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			
			vClient.push_back(Client);
		}

		MyFile.close();
	}

	return vClient;
}

void PrintClientRecord(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}


void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << setw(15) << left << "Accout Number";
    cout << "| " << setw(10) << left << "Pin Code";
    cout << "| " << setw(40) << left << "Client Name";
    cout << "| " << setw(12) << left << "Phone";
    cout << "| " << setw(12) << left << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);

        cout << endl;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}


int main()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    PrintAllClientsData(vClients);

    system("pause>0");

    return 0;
}







