#include "Client.h"

bool Client::recvall(char* data, int totalbytes)
{
	int bytesrecived = 0;
	while (bytesrecived < totalbytes)
	{
		int RetnCheck = recv(Connection, data + bytesrecived, totalbytes - bytesrecived, NULL);
		if (RetnCheck == SOCKET_ERROR)
		{
			return false; //failed to recvall
		}
	
		bytesrecived += RetnCheck;	//add yo total bytes
		
	}
	return true;	//success
}

bool Client::sendall(char* data, int totalbytes)
{
	int bytessent = 0;
	while (bytessent < totalbytes)
	{
		int RetnCheck = send(Connection, data + bytessent, totalbytes - bytessent, NULL);	//Send remaining
		if (RetnCheck == SOCKET_ERROR)
		{
			return false;
		}
		bytessent += RetnCheck;
	}
	return true;
}


bool Client::SendInt(int t_int)
{
	if (!sendall((char*)& t_int, sizeof(int)))
	{
		return false;
	}

	return true; //Int succesfully sent
}

bool Client::GetInt(int& t_int)
{

	if (!recvall((char*)&t_int, sizeof(int)))
	{
		return false;
	}

	return true;

}

bool Client::SendPacketType(Packet t_packettype)
{
	if (!sendall((char*)&t_packettype, sizeof(Packet)))
	{
		return false;
	}

	return true; //Int succesfully sent
}

bool Client::GetPacketType(Packet& t_packettype)
{
	//int RetnCheck = recv(Connection, (char*)&t_int, sizeof(int), NULL); //Recive Int

	if (!recvall((char*)&t_packettype, sizeof(Packet)))
	{
		return false;
	}

	return true;
}

bool Client::SendString(std::string& t_string)
{
	if (!SendPacketType(P_ChatMessage))
	{
		return false;	//String send failed
	}
	int bufferLength = t_string.size();
	if (!SendInt(bufferLength))
	{
		return false;
	}



	if (!sendall((char*)t_string.c_str(), bufferLength))
	{
		return false;
	}

	return true;	//String Successfully sent

}

bool Client::GetString(std::string& t_string)
{
	int bufferLength;
	if (!GetInt(bufferLength))
	{
		return false;
	}
	char* buffer = new char[bufferLength + 1];
	buffer[bufferLength] = '\0';
	
	if (!recvall(buffer, bufferLength))
	{
		delete[] buffer;	//prevent memory leak
		return false;
	}

	t_string = buffer;
	delete[] buffer;
	return true;	//Get string success
}