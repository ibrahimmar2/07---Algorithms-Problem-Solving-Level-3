#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
    bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim);

// Client
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#");
string ConvertRecordToLine(sClient Client, string Seperator = "#//#");
bool FIndClientByAccountNumber(string AccountNumber, sClient& Client)
sClient ChangeClientRecord(stringAccountNumber);
sClient ReadNewClient();
bool UpdateClientByAccountNumber(stringAccountNumber, vector<sClient> &vClients);
sClient ChangeClientRecord(stringAccountNumber);
string ReadClientAccountNumber();



vector <sClient> LoadCleintsDataFromFile(string FileName);

//factions print

void PrintClientCard(sClient Client);
void PrintClientRecord(sClient Client)
void PrintAllClientsData(vector <sClient> vClients);

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client);
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients);
vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> vClients);
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients);

//Add Client

void AddNewClient();
void AddClients();
AddDataLineToFile();




#endif
