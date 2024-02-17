#include "main.h"

/*
 *this is main faction
 */

int main()
{
	cout << "\nPlease Enter Client Data: \n\n";

	sClient Client;

	Client = ReadNewClient();

	cout << "\n\nClient Record for Saving is: \n";

	cout << ConvertRecordToLine(Client);

	return 0;

}
