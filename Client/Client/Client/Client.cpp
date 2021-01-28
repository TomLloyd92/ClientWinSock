#include "Client.h"




Client::Client(std::string IP, int PORT)
{
	//Set up WinSock
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0) //Error if not 0
	{
		MessageBoxA(NULL, "Winsock startup failed!", "ERROR", MB_OK | MB_ICONERROR);
		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr(IP.c_str());	//Local broadcast
	addr.sin_port = htons(PORT);					//Port
	addr.sin_family = AF_INET;						//IPv4 Socket

	clientptr = this;
}

bool Client::Connect()
{
	Connection = socket(AF_INET, SOCK_STREAM, NULL);		// Set connection Socket
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0)  //if we cant connect
	{
		MessageBoxA(NULL, "Failed to connect", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//std::cout << "Connected" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL);	//Create the client thread
	return true;
}

bool Client::CloseConnection()
{
	if (closesocket(Connection) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAENOTSOCK)	//Check why it was wasnt closed correct
		{
			return true;	//If socket is closed just return true
		}

		std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, ErrorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

bool Client::ProcessPacket(Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage:
	{
		std::string Message;	//String to store out message recived
		if (!GetString(Message))
		{
			return false;
		}
		std::cout << Message << std::endl;	//Display message
		break;
	}
	default:
		std::cout << "Unrecognised Packet Client" << _packettype << std::endl;
		break;
	}
	return true;
}

void Client::ClientThread()
{
	Packet packettype;
	while (true)
	{
		if (!clientptr->GetPacketType(packettype))
		{
			break;
		}
		if (!clientptr->ProcessPacket(packettype))//If it is not proccess correctly
		{
			break;	//break the loop
		}
	}

	std::cout << "LOST CONNECTION TO SERVER" << std::endl;
	if (clientptr->CloseConnection())
	{
		std::cout << "Socket to the server was closed successfully" << std::endl;
	}
	else
	{
		std::cout << "Socket was not able to be closed." << std::endl;
	}
}

