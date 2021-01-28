/*
	Initialise Winsock
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library



enum Packet
{
	P_ChatMessage,
	P_Test

};

class Client
{
public:
	Client(std::string IP, int PORT);
	bool Connect();
	bool CloseConnection();
	bool SendString(std::string& _string);

private:
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();

	//Sending Functions
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);
	bool sendall(char* data, int totalbytes);


	//Getters
	bool GetInt(int& _int);
	bool GetPacketType(Packet& _packettype);
	bool GetString(std::string& _string);
	bool recvall(char* data, int totalbytes);

private:
	SOCKET Connection;	//Clients connection to the server
	SOCKADDR_IN addr;	//Address to be binded to our Connector Socket
	int sizeofaddr = sizeof(addr);	//Need sizeofaddr for the connect function

};

static Client* clientptr;