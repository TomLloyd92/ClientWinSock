#include "Client.h"


int main()
{
	Client myClient("127.0.0.1", 1111);	//Create client to Local host 


	//If Fail to connect
	if (!myClient.Connect())
	{
		std::cout << "Failed to connect to the server... SHIT!!!" << std::endl;
		system("pause");
		return 1;
	}


	//If Connect
	std::string userInput;	//String buffer
	while(true)
	{
		std::getline(std::cin, userInput);
		if (!myClient.SendString(userInput))
		{
			break;	//If we fail to send the string leave this loop since we have lost connection to the server
		}
		Sleep(10);
	}
	return 0;
}