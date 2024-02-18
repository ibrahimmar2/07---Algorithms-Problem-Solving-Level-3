#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

void MenueScreen();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
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

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}


sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);


    cout << "Enter Phone? ";
    getline(cin, Client.Phone);


    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
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

void PrintClientRecord(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowClient()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);


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

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number : " << Client.AccountNumber;
    cout << "\nPin Code      : " << Client.PinCode;
    cout << "\nName          : " << Client.Name;
    cout << "\nPhone         : " << Client.Phone;
    cout << "\nAccout Balance: " << Client.AccountBalance;

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

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

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            //Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void DeleteClients()
{
    cout << "----------------------------------------------------------" << endl;
    cout << "\t\t\t\t Delete Clients Screen \t\t\t\t" << endl;
    cout << "----------------------------------------------------------" << endl;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    string AccountNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void UpdataClients()
{
    cout << "----------------------------------------------------------" << endl;
    cout << "\t\t\t\t Updata Clients Screen \t\t\t\t" << endl;
    cout << "----------------------------------------------------------" << endl;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    string AccountNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClients);
}


void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddClients();
}


void FindClients()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

enum enOpClient { Show = 1, AddClient = 2, DeleteClient = 3, UpdataClient = 4, FindClient = 5, Exit = 6};


void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...\n";
    system("pause>0");
    MenueScreen();

}

short ReadMainMenueOption()
{
    cout <<"Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void StartBank( enOpClient OpClient)
{

    switch ( OpClient)
    {
        case enOpClient::Show:
            system("cls");
            ShowClient();
            GoBackToMainMenue();
            break;
        case enOpClient::AddClient:
            system("cls");
            ShowAddNewClientsScreen();
            GoBackToMainMenue();
            break;
        case enOpClient::DeleteClient:
            system("cls");
            DeleteClients();
            GoBackToMainMenue();
            break;
        case enOpClient::UpdataClient:
            system("cls");
            GoBackToMainMenue();
            break;
        case enOpClient::FindClient:
            system("cls");
            GoBackToMainMenue();
            break;
        case enOpClient::Exit:
            system("cls");
            ShowEndScreen();
            break;

    }
}

void MenueScreen()
{
    ResetScreen();
    cout << "=======================================================" << endl;
    cout << "\t\t\t\t Main Menue Screen \t\t\t\t" << endl;
    cout << "=======================================================" << endl;
    cout << "\t\t [1] Show Client List. \t\t" << endl;
    cout << "\t\t [2] Add New Client. \t\t" << endl;
    cout << "\t\t [3] Delete Client. \t\t" << endl;
    cout << "\t\t [4] Updata Client Info. \t\t" << endl;
    cout << "\t\t [5] Find Client. \t\t" << endl;
    cout << "\t\t [6] Exit. \t\t" << endl;
    cout << "=======================================================" << endl;
    StartBank((enOpClient)ReadMainMenueOption());
}

int main()
{

    MenueScreen();
    return 0;
}
