#include "main.h"

bool FIndClientByAccountNumber(string AccountNumber, sClient& Client)
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

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
